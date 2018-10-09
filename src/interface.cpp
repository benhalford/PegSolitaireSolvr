#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <thread>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/gdicmn.h>

#include "backend.h"
#include "interface.h"


bool MyApp::OnInit() {
	MyFrame *frame = new MyFrame("PegSolver", wxPoint(50, 50), wxSize(150,350) );
	frame->SetMinSize(wxSize(150,350));
	frame->SetMaxSize(wxSize(150,350));
	frame->Show( true );
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size) {
	wxFont* tmpFont = new wxFont(11,wxTELETYPE,wxNORMAL,wxNORMAL);
	panel->SetFont(*tmpFont);

	m_button = new wxButton(panel, ID_Button, "Go", wxPoint(-1,-1), wxSize(148,50), 0);

	m_tut = new wxStaticText(panel, -1, "@/O\n Peg/NoPeg", wxPoint(27.5,60),wxSize(110,75), wxALIGN_CENTRE);
	m_textfield0 = new wxTextCtrl(panel, -1, "", wxPoint(53.5,110),wxSize(43,25));
	m_textfield1 = new wxTextCtrl(panel, -1, "", wxPoint(53.5,135),wxSize(43,25));
	m_textfield2 = new wxTextCtrl(panel, -1, "", wxPoint(35,160),wxSize(80,25));
	m_textfield3 = new wxTextCtrl(panel, -1, "", wxPoint(35,185),wxSize(80,25));
	m_textfield4 = new wxTextCtrl(panel, -1, "", wxPoint(35,210),wxSize(80,25));
	m_textfield5 = new wxTextCtrl(panel, -1, "", wxPoint(53.5,239),wxSize(43,25));
	m_textfield6 = new wxTextCtrl(panel, -1, "", wxPoint(53.5,264),wxSize(43,25));
	m_textfield0 -> SetMaxLength(3);
	m_textfield1 -> SetMaxLength(3);
	m_textfield2 -> SetMaxLength(7);
	m_textfield3 -> SetMaxLength(7);
	m_textfield4 -> SetMaxLength(7);
	m_textfield5 -> SetMaxLength(3);
	m_textfield6 -> SetMaxLength(3);

}

void MyFrame::RunIt(wxCommandEvent& event){
	if(m_textfield0->GetLineText(0).length() == 3 &&
	   m_textfield1->GetLineText(0).length() == 3 &&
	   m_textfield2->GetLineText(0).length() == 7 &&
     m_textfield3->GetLineText(0).length() == 7 &&
     m_textfield4->GetLineText(0).length() == 7 &&
	   m_textfield5->GetLineText(0).length() == 3 &&
     m_textfield6->GetLineText(0).length() == 3){

	  std::string toBack = ( m_textfield0->GetLineText(0).ToStdString()+m_textfield1->GetLineText(0).ToStdString()+m_textfield2->GetLineText(0).ToStdString()+m_textfield3->GetLineText(0).ToStdString()+m_textfield4->GetLineText(0).ToStdString()+m_textfield5->GetLineText(0).ToStdString()+m_textfield6->GetLineText(0).ToStdString() );
		bool valid = true;

		for (int i = 0; i < 33; i++)
			if(toBack[i] == '@' || toBack[i] == 'O'){
			}else{
				valid = false;
			}

		if(valid == true){

			wxString result;
			if (toBack != "OOOOOOOOOOOOOOOO@OOOOOOOOOOOOOOOO") {
				backend(toBack);
				result = printOut();
			} else {
				result = "\n\n\n\n\n      Mate,\n  It's already\n   completed!\n\n";
			}

			if (result == "") {
				result = "Couldn't find a solution mate! ";
			}

			m_resButton = new wxButton(panel, ID_ResButton, "Reset", wxPoint(-1,-1), wxSize(148,50), 0);
			m_resultsfield = new wxTextCtrl(panel, -1, result, wxPoint(-1,225),wxSize(162,350), wxTE_MULTILINE);
			m_resultsfield->SetEditable(false);
			m_resultsfield->IsMultiLine();

			m_tut->Destroy();
			m_button->Destroy();
			m_textfield0->Destroy();
			m_textfield1->Destroy();
			m_textfield2->Destroy();
			m_textfield3->Destroy();
			m_textfield4->Destroy();
			m_textfield5->Destroy();
			m_textfield6->Destroy();
			m_resultsfield->SetSize(wxSize(160,270));
			m_resultsfield->SetPosition(wxPoint(-1,50));
		}
	}
}

void MyFrame::ResetIt(wxCommandEvent& event) {
	execl("./app", NULL);
	exit(0);
}
