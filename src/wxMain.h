#ifndef MAIN_FILE
#define MAIN_FILE

#include <string>
#include <sstream>
#include "wx/wx.h"
#include "auditor.h"
#include "slib.h"

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
    wxTextCtrl* m_display = nullptr;
    wxTextCtrl* m_add = nullptr;
    wxButton* m_add_button = nullptr;

    void addItem(wxCommandEvent &evt);
    void displayIndices();
    void loadArr(wxCommandEvent& evt);
    void onButtonClick(wxCommandEvent& evt);
    void onEnter(wxCommandEvent& evt);

    wxDECLARE_EVENT_TABLE();
};


#endif // WXMAIN