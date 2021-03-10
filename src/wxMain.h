#ifndef MAIN_FILE
#define MAIN_FILE

#include <string>
#include <sstream>
#include "wx/wx.h"
#include "database/auditor.h"
//#include "databaseslib.h"

std::vector<std::string> split_string_by_newline(const std::string& str);

class wxMain : public wxFrame{
private:
    Item* loadedItem = nullptr;
    Data& database = dataGet();
    Auditor& auditor = getAuditor();
public:
    
    wxMain();
    ~wxMain();

    wxButton* m_button = nullptr;
    wxTextCtrl* m_item = nullptr;
    wxTextCtrl* m_text = nullptr;

    wxListBox* m_display = nullptr;
    wxButton* m_del_button = nullptr;
    wxButton* m_load_button = nullptr;
    wxButton* m_sort_button = nullptr;

    wxPanel* m_button_panel = nullptr;
    wxPanel* m_text_panel = nullptr;
    wxPanel* m_add_panel = nullptr;

    wxTextCtrl* m_add = nullptr;
    wxButton* m_add_button = nullptr;

    wxStaticText* m_item_label = nullptr;

    void addItem(wxCommandEvent& evt);
    void displayIndices();
    void loadArr(wxCommandEvent& evt);
    void onButtonClick(wxCommandEvent& evt);
    void onEnter(wxCommandEvent& evt);
    void delItem(wxCommandEvent& evt);
    void loadButtonClick(wxCommandEvent& evt);
    void sortButton(wxCommandEvent& evt);
    void loadItem(const std::string& index);


    wxDECLARE_EVENT_TABLE();
};


#endif // WXMAIN