#include <wx/wx.h>
#include "main.h"

class App : public wxApp {
  public:
    App();
    ~App();
    virtual bool OnInit();

  private:
    Main *m_frame1 = nullptr;
};

