#include <algorithm>
#include "Cell.h"

Cell::~Cell()
{
    observers.clear();
    cells.clear();
}

void Cell::setValue(const std::string& v)
{
    value = v;
    notify();
}

void Cell::setOperationId(OperationId id)
{
    operation = id;   
    notify();
}

void Cell::subscribe(Observer *o)
{
    auto s = dynamic_cast<Subject*>(o);
    if (s) {
        // Controlla che il puntatore 'o' non sia già presente in 'observers' e che non sia 'this'
        if (s != this && std::find(observers.begin(), observers.end(), o) == observers.end() && std::find(cells.begin(), cells.end(), s) == cells.end()) {
            observers.push_back(o);
            //else{/*gestisci*/}
        }else {
            // Gestisci il caso in cui 'o' sia già presente o se stai cercando di auto-collegarti
            // Ad esempio, puoi lanciare un'eccezione o loggare un messaggio di errore
            value = "bob";
        }
    } else {
        // Gestisci l'errore se il cast fallisce
        // Ad esempio, puoi lanciare un'eccezione o loggare un messaggio di errore
    }
}

void Cell::unsubscribe(Observer *o)
{
    observers.remove(o);
}

void Cell::notify()
{
    for(auto obs:observers)
        obs->update();
}

void Cell::update()
{
    calcValue();
}

void Cell::attach(Subject* s) {
    try {
        auto o = dynamic_cast<Observer*>(s);
        if (o) {
            if (o != this && std::find(observers.begin(), observers.end(), o) == observers.end() && std::find(cells.begin(), cells.end(), s) == cells.end()) {
                Cell* c = dynamic_cast<Cell*>(s);
                if (c) {
                    c->subscribe(this);
                    cells.push_back(c);
                } else {
                    throw std::invalid_argument("Il puntatore passato non è una Cell valida.");
                }
            } else {
                throw std::logic_error("Auto-collegamento o puntatore duplicato non consentiti.");
            }
        } else {
            throw std::invalid_argument("Il puntatore passato non è un Observer valido.");
        }
    } catch (const std::invalid_argument& e) {
        wxMessageBox(wxString::FromUTF8(e.what()),
                     "Errore di Validazione",
                     wxOK | wxICON_ERROR);
    } catch (const std::logic_error& e) {
        wxMessageBox(wxString::FromUTF8(e.what()),
                     "Errore Logico",
                     wxOK | wxICON_ERROR);
    } catch (const std::exception& e) {
        wxMessageBox(wxString::FromUTF8(e.what()),
                     "Errore Generico",
                     wxOK | wxICON_ERROR);
    } catch (...) {
        wxMessageBox("Errore sconosciuto durante l'esecuzione di attach.",
                     "Errore Sconosciuto",
                     wxOK | wxICON_ERROR);
    }
}



void Cell::detach(Subject* s)
{
    s->unsubscribe(this);
}

void Cell::clearWatchedCells()
{
    for(auto c:cells){
        detach(c);
    }
    cells.clear();
}

void Cell::calcValue()
{
    double v;
    switch (operation)
    {
    case OperationId::Max:
        v = calcMax();
        break;
    case OperationId::Min:
        v = calcMin();
        break;
    case OperationId::Mean:
        v = calcMean();
        break;
    case OperationId::Sum:
        v = calcSum();
        break;
    default:
        return;
    }

    try {
        // Gestione di NaN o infinito
        if (std::isnan(v) || std::isinf(v)) {
            throw std::runtime_error("Il risultato è NaN o infinito");
        }
        value = std::to_string(v);
    }catch (const std::invalid_argument& e) {
        // Errore di conversione durante std::stod (se applicato internamente)
        value = "Errore: Valore non valido";
        std::cerr << "Errore di argomento non valido: " << e.what() << std::endl;

    } catch (const std::out_of_range& e) {
        // Valore fuori intervallo durante la conversione
        value = "Errore: Valore troppo grande";
        std::cerr << "Errore di valore fuori intervallo: " << e.what() << std::endl;

    } catch (const std::runtime_error& e) {
        // Gestione specifica per NaN o infinito
        value = "Errore: Risultato non valido";
        std::cerr << "Errore di calcolo: " << e.what() << std::endl;

    } catch (...) {
        // Gestione di eventuali altri errori
        value = "Errore sconosciuto";
        std::cerr << "Errore sconosciuto durante il calcolo" << std::endl;
    }

    notify();
}

double Cell::calcMax() const
{
    double v, max = -std::numeric_limits<double>::infinity();
    for (auto c:cells) {
        try {
            if (!c->value.empty()) {
                if (std::stod(c->value) > max)
                    max = std::stod(c->value);
            }
        } catch (const std::invalid_argument&) {
            continue;
        } catch (const std::out_of_range&) {
            continue;
        }
    }
    return max;
}

double Cell::calcMin() const
{
    double v, min = std::numeric_limits<double>::infinity();
    for (auto c:cells) {
        try {
            if (!c->value.empty()) {
                if (std::stod(c->value) < min)
                    min = std::stod(c->value);
            }
        } catch (const std::invalid_argument&) {
            continue;
        } catch (const std::out_of_range&) {
            continue;
        }
    }
    return min;
}

double Cell::calcMean() const
{
    if (cells.empty()) {
        return 0.0;
    }
    return calcSum() / cellsSize();
}

double Cell::calcSum() const
{
    double s = 0;
    for (auto c : cells) {
        try {
            if (!c->value.empty()) { // Salta le celle vuote
                s += std::stod(c->value);
            }
        } catch (const std::invalid_argument&) {
            // Ignora i valori non validi
        } catch (const std::out_of_range&) {
            // Ignora valori fuori dall'intervallo
        }
    }
    return s;
}

int Cell::cellsSize() const {
    int size = 0;
    for (auto c : cells) {
        try {
            if (!c->value.empty()) {
                std::stod(c->value);
                size++;                             //sfrutto stack unwinding per contare le celle con valori validi
            }
        } catch (const std::invalid_argument&) {
        } catch (const std::out_of_range&) {
        }
    }
    return size;
}

bool Cell::checkValidity(const std::string& str) const {
    bool valid = true;
    try {
        if (!str.empty()) {
            std::stod(str);
        }
    } catch (const std::invalid_argument&) {
        //continue;
    } catch (const std::out_of_range&) {
        //continue;
    }
    return valid;
}
