#include "wxWin.h"

wxIMPLEMENT_APP(wxWin);

void myAss(){
    std::cout << "ayy lmao\n";
    std::cin.get();
}

wxWin::wxWin(){

}

wxWin::~wxWin(){

}

bool wxWin::OnInit(){
    m_frame1 = new wxMain();
    m_frame1->Show();
    return true;
}