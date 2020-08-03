#include <wx/wx.h>
#include <wx/frame.h>

class Main : public wxFrame {
  public:
    Main();
    ~Main();
    // components:
    wxButton *m_btn1 = nullptr;
    wxTextCtrl *m_txt1 = nullptr;
    wxListBox *m_list1 = nullptr;
    // int nFieldWidth{10};
    // int nFieldHeight{10};
    // wxButton **btn;  // array of pointers to buttons

    void OnBtnClicked(wxCommandEvent &event);

    // handling events:
    wxDECLARE_EVENT_TABLE();

  private:
};