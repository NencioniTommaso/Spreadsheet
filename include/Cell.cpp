#include <algorithm>
#include "Cell.h"

#include "OperationFactory.h"

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

void Cell::setOperation(OperationId id)
{
    operationId = id;
    operation = OperationFactory::createOperation(id);
    notify();
}

void Cell::subscribe(Observer* o) {
    try {
        auto s = dynamic_cast<Subject*>(o);
        if (s) {
            if (s != this && std::find(observers.begin(), observers.end(), o) == observers.end() && std::find(cells.begin(), cells.end(), s) == cells.end()) {
                observers.push_back(o);
            } else {
                throw std::logic_error("Auto-collegamento o duplicato non consentito.");
            }
        } else {
            throw std::invalid_argument("Il puntatore passato non è un Subject valido.");
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
        wxMessageBox("Errore sconosciuto durante l'esecuzione di subscribe.",
                     "Errore Sconosciuto",
                     wxOK | wxICON_ERROR);
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
    if(!operation)
        return;

    double v;
    v = operation->compute(cells);

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
