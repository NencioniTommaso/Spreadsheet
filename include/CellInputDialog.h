//
// Created by nenci on 30/11/2024.
//

#ifndef CELLINPUTDIALOG_H
#define CELLINPUTDIALOG_H

#include <wx/wx.h>

class CellInputDialog : public wxDialog {
public:
    CellInputDialog(wxWindow* parent)
        : wxDialog(parent, wxID_ANY, "Select Result Cell", wxDefaultPosition, wxSize(300, 200)) {

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Input per riga
        wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);
        rowSizer->Add(new wxStaticText(this, wxID_ANY, "Row:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        m_rowInput = new wxTextCtrl(this, wxID_ANY, "");
        rowSizer->Add(m_rowInput, 1, wxALL | wxEXPAND, 5);
        mainSizer->Add(rowSizer, 0, wxALL | wxEXPAND, 5);

        // Input per colonna (lettera)
        wxBoxSizer* colSizer = new wxBoxSizer(wxHORIZONTAL);
        colSizer->Add(new wxStaticText(this, wxID_ANY, "Column (A, B, ...):"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        m_colInput = new wxTextCtrl(this, wxID_ANY, "");
        colSizer->Add(m_colInput, 1, wxALL | wxEXPAND, 5);
        mainSizer->Add(colSizer, 0, wxALL | wxEXPAND, 5);

        // Pulsanti OK e Cancel
        mainSizer->Add(CreateSeparatedButtonSizer(wxOK | wxCANCEL), 0, wxALL | wxEXPAND, 10);

        SetSizer(mainSizer);
        mainSizer->Fit(this);
    }

    // Funzione per ottenere la riga
    int GetRow() const {
        return wxAtoi(m_rowInput->GetValue());
    }

    int GetCol() const {
        wxString colStr = m_colInput->GetValue().Upper(); // Converti in maiuscolo
        if (!colStr.IsEmpty() && wxIsalpha(colStr[0])) {
            return colStr[0] - 'A' + 1; // Converte 'A' in 1, 'B' in 2, ecc.
        }
        return -1; // Valore non valido
    }

private:
    wxTextCtrl* m_rowInput;
    wxTextCtrl* m_colInput;
};


#endif //CELLINPUTDIALOG_H
