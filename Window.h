#pragma once
#include<wx/wx.h>
class Window : public wxFrame
{
public:
	Window(const wxString& title);
	wxTextCtrl* data;
	wxStaticText* header;
private:
	void OnButtonClicked(wxCommandEvent& evt);	
};
//wxDECLARE_EVENT_TABLE();