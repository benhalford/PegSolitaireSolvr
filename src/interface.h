#ifndef __BASE_H
#define __BASE_H
#endif

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	wxPanel *panel = new wxPanel(this, wxID_ANY);

	wxButton *m_button;
	wxButton *m_resButton;

	wxStaticText *m_tut;

	wxTextCtrl *m_textfield0;
	wxTextCtrl *m_textfield1;
	wxTextCtrl *m_textfield2;
	wxTextCtrl *m_textfield3;
	wxTextCtrl *m_textfield4;
	wxTextCtrl *m_textfield5;
	wxTextCtrl *m_textfield6;

	wxTextCtrl *m_resultsfield;
private:
	void RunIt(wxCommandEvent& event);
	void ResetIt(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};


enum
{
	ID_Button = 1,
	ID_ResButton = 2
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_BUTTON(ID_ResButton, MyFrame::ResetIt)
    EVT_BUTTON(ID_Button, MyFrame::RunIt)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);
