#include "main.h"
#include <iostream>

// wxWindowID id = 10001;

// event handling:
wxBEGIN_EVENT_TABLE(Main, wxFrame)
  EVT_BUTTON(10001, Main::OnBtnClicked)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "Scraper Project – Sergei Kononov", wxPoint(50, 50), wxSize(640, 480)) {
  m_btn1 = new wxButton(this, 10001, "Button 1", wxPoint(10, 10), wxSize(150, 50));  // insert "this", becuase the window is the parent of the button 
  m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
  m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
  // // creating array of buttons
  // btn = new wxButton*[nFieldWidth * nFieldHeight];
  // wxGridSizer *grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);
  // for (int i = 0; i < nFieldWidth; i++) {
  //   for (int j = 0; j < nFieldHeight; j++) {
  //     btn[j * nFieldWidth + i] = new wxButton(this, 10000 + (j * nFieldWidth + i));
  //     grid->Add(btn[j * nFieldWidth + i], 1, wxEXPAND | wxALL);
  //     // dynamically allocate event handlers
  //     btn[j * nFieldWidth + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnBtnClicked, this);
  //   }
  // }
  // this->SetSizer(grid);
  // grid->Layout();
}

Main::~Main() {
  
}

void Main::OnBtnClicked(wxCommandEvent &event) {
  std::cout << "btn clicked" << std::endl;
  m_list1->AppendString(m_txt1->GetValue());
  // tell the system that the event has finished:
  event.Skip();  // Skip checking all of the parents in the event tree
}