#ifndef WX_WIN
#define WX_WIN

#include "wx/wx.h"
#include "wxMain.h"

#include <iostream>

class wxWin : public wxApp{
public:
    wxWin();
    ~wxWin();

    virtual bool OnInit();

private:
    wxMain* m_frame1 = nullptr;
};

#endif // WXWIN