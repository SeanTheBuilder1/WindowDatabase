#include "wxMain.h"

wxBEGIN_EVENT_TABLE(wxMain, wxFrame)
    EVT_BUTTON(10001, onButtonClick)
    EVT_BUTTON(10007, addItem)
    EVT_BUTTON(10008, loadButtonClick)
    EVT_TEXT_ENTER(10003, loadArr)
    EVT_BUTTON(10004, delItem)
    EVT_BUTTON(10013, sortButton)
    EVT_MENU(10014, onOpen)
    EVT_MENU(10015, onSave)
    EVT_MENU(10016, onClose)
wxEND_EVENT_TABLE()

wxMain::wxMain():wxFrame(nullptr, wxID_ANY, "Window Database BETA", wxDefaultPosition, wxSize(800, 450), wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN){
    Centre();
    m_button_panel = new wxPanel(this, 10010, wxPoint(660, 10), wxSize(90, 120));

    m_text_panel = new wxPanel(this, 10011, wxPoint(10, 10), wxSize(600, 330));
    m_add_panel = new wxPanel(this, 10012, wxPoint(10, 360), wxSize(390, 31));

    m_button = new wxButton(m_button_panel, 10001, "Save Item", wxPoint(0, 60), wxSize(90, 30));
    m_load_button = new wxButton(m_button_panel, 10008, "Load Item", wxPoint(0, 0), wxSize(90, 30));
    m_del_button = new wxButton(m_button_panel, 10004, "Delete Item", wxPoint(0, 30), wxSize(90, 30));
    m_sort_button = new wxButton(m_button_panel, 10013, "Sort Items", wxPoint(0, 90), wxSize(90,30));

    // m_text = new wxTextCtrl(m_text_panel, 10002, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    // m_item = new wxTextCtrl(m_text_panel, 10003, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    // m_display = new wxListBox(m_text_panel, 10005, wxDefaultPosition, wxDefaultSize);
    // m_item_label = new wxStaticText(m_text_panel, 10009, " Loaded Items:", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

    m_text = new wxTextCtrl(m_text_panel, 10002, "", wxPoint(0, 30), wxSize(300, 300), wxTE_MULTILINE);
    m_item = new wxTextCtrl(m_text_panel, 10003, "", wxPoint(0, 0), wxSize(300, 30), wxTE_PROCESS_ENTER);
    m_display = new wxListBox(m_text_panel, 10005, wxPoint(300, 30), wxSize(300, 300));
    m_item_label = new wxStaticText(m_text_panel, 10009, " Loaded Items:", wxPoint(300, 0), wxSize(300, 30), wxTE_READONLY);

    m_item_label->SetWindowStyle(wxTE_READONLY);

    m_text_panel->SetBackgroundColour(wxColour(0,255,255));
    
    this->SetBackgroundColour(wxColour(0,255,255)); 

    m_add = new wxTextCtrl(m_add_panel, 10006, "", wxPoint(0, 0), wxSize(300, 30), wxTE_PROCESS_ENTER);
    m_add_button = new wxButton(m_add_panel, 10007, "Add Item", wxPoint(300, 1), wxSize(90, 30));

    m_menu_bar = new wxMenuBar();
    this->SetMenuBar(m_menu_bar);
    
    wxMenu* menu = new wxMenu();
    menu->Append(10014, "Open");
    menu->Append(10015, "Save");
    menu->Append(10016, "Close");

    m_menu_bar->Append(menu, "File");



    /*
    wxBoxSizer* textSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* verSizer2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* verSizer = new wxBoxSizer(wxVERTICAL);

    verSizer->Add(m_item_label, 1);
    verSizer->Add(m_display, 10);

    verSizer2->Add(m_item, 1);
    verSizer2->Add(m_text, 10);
    
    textSizer->Add(verSizer2, 1);
    textSizer->Add(verSizer, 1);
    */

    /*
    wxFlexGridSizer* flexSizer = new wxFlexGridSizer(2, 2, 0, 0);
    
    flexSizer->Add(m_item, 1);
    flexSizer->Add(m_item_label, 1);
    flexSizer->Add(m_text, 10);
    flexSizer->Add(m_display, 5);

    */
    
    auditor.loadAll();
    displayIndices();
    
    /*
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer3 = new wxBoxSizer(wxVERTICAL);

    sizer3->Add(m_text_panel, 8);
    sizer3->Add(m_add_panel, 1);
    sizer->Add(sizer3, 8);
    sizer->Add(m_button_panel, 1);
    m_text_panel->SetSizerAndFit(textSizer);
    this->SetSizerAndFit(sizer);
    */

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

void wxMain::sortButton(wxCommandEvent& evt){
    auditor.sort();
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

void wxMain::onOpen(wxCommandEvent& evt){
    wxFileDialog* fileDlg = new wxFileDialog(this, _("Choose the Database file"), wxEmptyString, wxEmptyString, _("TXT file|*.txt|All files|*.*"));
    if (fileDlg->ShowModal() == wxID_OK){
        wxString path = fileDlg->GetPath();
        auditor.openDatabase(path.ToStdString());
        auditor.loadAll();
    }
    delete fileDlg;
    displayIndices();
    evt.Skip();
}

void wxMain::onSave(wxCommandEvent& evt){
    
    evt.Skip();
}

void wxMain::onClose(wxCommandEvent& evt){
    Destroy();
    evt.Skip();
}
