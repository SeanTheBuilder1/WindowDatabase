#include "wxMain.h"

wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
    EVT_BUTTON(10001, onButtonClick)
    EVT_TEXT_ENTER(10003, loadArr)
wxEND_EVENT_TABLE()

wxMain::wxMain():wxFrame(nullptr, wxID_ANY, "Gavin Deposoy Simulator", wxDefaultPosition, wxSize(800, 600)){
    Centre();
    m_button = new wxButton(this, 10001, "Lamao", wxPoint(10, 10), wxSize(100, 50));
    m_text = new wxTextCtrl(this, 10002, "", wxPoint(10, 100), wxSize(300, 300), wxTE_MULTILINE);
    m_item = new wxTextCtrl(this, 10003, "", wxPoint(10, 70), wxSize(300, 30), wxTE_PROCESS_ENTER);
    m_display = new wxTextCtrl(this, 10004, "", wxPoint(310, 100), wxSize(300, 300), wxTE_MULTILINE | wxTE_READONLY);
    auditor.loadAll();
    std::vector<std::string> txt;
    txt.emplace_back("ayy");
    txt.emplace_back("lmoa");
    txt.emplace_back("lamafao");
    
}

wxMain::~wxMain(){
    
}


    

void wxMain::loadArr(wxCommandEvent& evt){
    std::cout << "hello\n";
    std::deque<std::string>* contents;
    if(auditor.getItem(m_item->GetValue().ToStdString(), loadedItem)){
        std::cout << "hi\n";
        if(loadedItem->getContents(contents)){
            for(auto& i : *contents){
                std::cout << i << '\n';
            }
            m_text->ChangeValue(contents->at(0));
            for(long i = 1; i < contents->size(); ++i){
                m_text->AppendText('\n' + contents->at(i));
            }    
        }
    }
    

    std::deque<Item>* temp;
    if(auditor.getAudit(temp)){
        std::cout << "lamao\n";
        for(auto& i : *temp){
            std::cout << i.getIndex() << '\n';
        }
    }
    evt.Skip(false);
}

void wxMain::onButtonClick(wxCommandEvent& evt){
    std::deque<std::string> lmao{slib::split_string_by_newline(m_text->GetValue().ToStdString())};
    
    std::deque<std::string>* contents;
    if(loadedItem->getContents(contents)){
        *contents = lmao;
        auditor.saveItem(*loadedItem);
    }
    
    for(auto& i : lmao){
        std::cout << i << '\n';
    }
    evt.Skip();
}


