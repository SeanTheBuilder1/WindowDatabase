#include "wxMain.h"

wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
    EVT_BUTTON(10001, onButtonClick)
    EVT_BUTTON(10007, addItem)
    EVT_BUTTON(10008, loadButtonClick)
    EVT_TEXT_ENTER(10003, loadArr)
    EVT_BUTTON(10004, delItem)
wxEND_EVENT_TABLE()

wxMain::wxMain():wxFrame(nullptr, wxID_ANY, "Gavin Deposoy Simulator", wxDefaultPosition, wxSize(800, 600)){
    Centre();
    m_button = new wxButton(this, 10001, "Save Item", wxPoint(10, 10), wxSize(100, 50));
    m_text = new wxTextCtrl(this, 10002, "", wxPoint(10, 100), wxSize(300, 300), wxTE_MULTILINE);
    m_item = new wxTextCtrl(this, 10003, "", wxPoint(10, 70), wxSize(300, 30), wxTE_PROCESS_ENTER);

    m_load_button = new wxButton(this, 10008, "Load Item", wxPoint(610, 40), wxSize(90, 30));
    m_del_button = new wxButton(this, 10004, "Delete Item", wxPoint(610, 10), wxSize(90, 30));
    m_display = new wxListBox(this, 10005, wxPoint(310, 100), wxSize(300, 300));
    
    m_add = new wxTextCtrl(this, 10006, "", wxPoint(10, 440), wxSize(300, 30), wxTE_PROCESS_ENTER);
    m_add_button = new wxButton(this, 10007, "Add Item", wxPoint(310, 441), wxSize(90, 30));
    
    auditor.loadAll();
    displayIndices();
}

wxMain::~wxMain(){
    
}


    
void wxMain::displayIndices(){
    std::deque<Item>* temp;
    
    if(auditor.getAudit(temp)){
        wxArrayString items;
        items.Alloc(temp->size() + 1);
        for(auto& i : *temp){
            items.Add(i.getIndex());
        }
        m_display->Set(items);
    }
    else{
        m_display->Clear();
    }
}

void wxMain::addItem(wxCommandEvent &evt){
    Item item(m_add->GetValue().ToStdString());
    auditor.addItem(item);
    displayIndices();
	evt.Skip(false);
}

void wxMain::delItem(wxCommandEvent &evt){
    int index = m_display->GetSelection();
    if(index != wxNOT_FOUND){
        auditor.delItem(m_display->GetString(index).ToStdString());
        displayIndices();
    }
}

void wxMain::loadButtonClick(wxCommandEvent& evt){
    int index = m_display->GetSelection();
    if(index != wxNOT_FOUND){
        loadItem(m_display->GetString(index).ToStdString());
        m_item->SetValue(m_display->GetString(index).ToStdString());
        displayIndices();
    }
    evt.Skip();
}

void wxMain::loadItem(const std::string& index){
    std::deque<std::string>* contents;
    if(auditor.exist(index)){
        if(auditor.getItem(index, loadedItem)){
            if(loadedItem->getContents(contents)){
                for(auto& i : *contents){
                    std::cout << i << '\n';
                }
                if(!contents->empty()){
                    m_text->ChangeValue(contents->at(0));
                    for(long i = 1; i < contents->size(); ++i){
                        m_text->AppendText('\n' + contents->at(i));
                    }
                }    
                else{
                    m_text->Clear();
                }
                
            }
        }
    }
}

void wxMain::loadArr(wxCommandEvent& evt){
    loadItem(m_item->GetValue().ToStdString());

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


