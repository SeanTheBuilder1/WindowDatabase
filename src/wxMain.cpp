#include "wxMain.h"

wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
    EVT_BUTTON(10001, onButtonClick)
    EVT_BUTTON(10006, addItem)
    EVT_TEXT_ENTER(10003, loadArr)
wxEND_EVENT_TABLE()

wxMain::wxMain():wxFrame(nullptr, wxID_ANY, "Gavin Deposoy Simulator", wxDefaultPosition, wxSize(800, 600)){
    Centre();
    m_button = new wxButton(this, 10001, "Save Item", wxPoint(10, 10), wxSize(100, 50));
    m_text = new wxTextCtrl(this, 10002, "", wxPoint(10, 100), wxSize(300, 300), wxTE_MULTILINE);
    m_item = new wxTextCtrl(this, 10003, "", wxPoint(10, 70), wxSize(300, 30), wxTE_PROCESS_ENTER);
    m_display = new wxTextCtrl(this, 10004, "", wxPoint(310, 100), wxSize(300, 300), wxTE_MULTILINE | wxTE_READONLY);
    
    m_add = new wxTextCtrl(this, 10005, "", wxPoint(10, 440), wxSize(300, 30), wxTE_PROCESS_ENTER);
    m_add_button = new wxButton(this, 10006, "Add Item", wxPoint(310, 441), wxSize(90, 30));
    
    auditor.loadAll();
    displayIndices();
}

wxMain::~wxMain(){
    
}


    
void wxMain::displayIndices(){
    std::deque<Item>* temp;
    
    if(auditor.getAudit(temp)){
        m_display->SetEditable(true);
        m_display->ChangeValue("Loaded Items:");
        for(auto& i : *temp){
            m_display->AppendText('\n' + i.getIndex());
        }
        m_display->SetEditable(false);
    }
}

void wxMain::addItem(wxCommandEvent &evt){
    Item item(m_add->GetValue().ToStdString());
    auditor.addItem(item);
    displayIndices();
	evt.Skip(false);
}

void wxMain::loadArr(wxCommandEvent& evt){
    std::deque<std::string>* contents;
    if(auditor.exist(m_item->GetValue().ToStdString())){
        if(auditor.getItem(m_item->GetValue().ToStdString(), loadedItem)){
            std::cout << "hi\n";
            if(loadedItem->getContents(contents)){
                for(auto& i : *contents){
                    std::cout << i << '\n';
                }
                if(!contents->empty())
                    m_text->ChangeValue(contents->at(0));
                for(long i = 1; i < contents->size(); ++i){
                    m_text->AppendText('\n' + contents->at(i));
                }    
            }
        }
    }

    displayIndices();
    evt.Skip(false);
}

void wxMain::onButtonClick(wxCommandEvent& evt){
	if(loadedItem){
		std::deque<std::string> cont{slib::split_string_by_newline(m_text->GetValue().ToStdString())};
		
		std::deque<std::string>* contents;
		if(loadedItem->getContents(contents)){
			*contents = cont;
			auditor.saveItem(*loadedItem);
		}
		
		for(auto& i : cont){
			std::cout << i << '\n';
		}
	}
    evt.Skip();
}


