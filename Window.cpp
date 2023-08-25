#include "Window.h"
#include <wx/wx.h>

#include <string>
#include <vector>
#include "qrcodegen.hpp"
using namespace qrcodegen;

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;


wxStaticText* header = NULL;
Window::Window(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* panel = new wxPanel(this, wxID_ANY,wxDefaultPosition,wxDefaultSize);
	panel->SetBackgroundColour(*wxBLUE);

	Window::header = new wxStaticText(panel, wxID_ANY, " QR-GEN ",wxPoint(100,50),wxSize(400,100),
		wxALIGN_CENTER);
	header->SetForegroundColour(*wxWHITE);
	header->SetFont(wxFont(30,wxFONTFAMILY_SCRIPT,wxFONTSTYLE_ITALIC,wxFONTWEIGHT_EXTRABOLD));

	wxStaticText* Data = new wxStaticText(panel,wxID_ANY,"ENTER DATA: ",wxPoint(25,175),wxSize(100,50),wxALIGN_LEFT);
	Data->SetForegroundColour(*wxWHITE);
	Data->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	Window::data = new wxTextCtrl(panel,wxID_ANY,"",wxPoint(175,175),wxSize(350,100),wxTE_MULTILINE);

	wxButton* gen = new wxButton(panel,wxID_ANY,"Generate",wxPoint(250,300),wxSize(100,-1));
	gen->SetBackgroundColour(*wxGREEN);
	gen->SetForegroundColour(*wxBLACK);
	gen->Bind(wxEVT_BUTTON,&Window::OnButtonClicked,this); 

	
}
void Window::OnButtonClicked(wxCommandEvent& evt)
{
	wxString text = Window::data->GetValue();
	const QrCode::Ecc errCorLv1 = QrCode::Ecc::LOW;
	const QrCode qr = QrCode::encodeText(text.c_str(), errCorLv1);
	const int scale = 10;
	const int size = qr.getSize() * scale;
	const int byteWidth = (size + 7) / 8;
	char* bitsChar = (char*)calloc(size * byteWidth,sizeof(char));
	for (int y=0;y<size;y++)
	{
		for (int xByte = 0;xByte < byteWidth;xByte++)
		{
			char bitChar = 0x00;
			if(text!="")
				for (int xBit = 0;xBit < 8;xBit++)
				{
					int x = xByte * 8 + xBit;
					int xModule = x / scale;
					int yModule = y / scale;
					bool black = qr.getModule(xModule,yModule);
					bitChar += black << (xBit % 8);
				}
			bitsChar[y * byteWidth + xByte] = bitChar;
		}
	}
	wxBitmap* bitmap = new wxBitmap(bitsChar,size,size,1);
	wxImage img = bitmap->ConvertToImage();
	wxBitmap mm = wxBitmap(img.Scale(200,200,wxIMAGE_QUALITY_NORMAL));
	wxStaticBitmap* qr_img = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxPoint(200, 350), wxSize(200, 200));
	qr_img->SetBitmap(mm);
	header->SetFont(wxFont(30, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
	Refresh();
}
//https://bit-bangalore.edu.in/
//www.youtube.com
	/*wxStaticText* header = new wxStaticText(this, wxID_ANY, "###  QR-GEN ###", wxPoint(100, 50), wxSize(400, 100),
		wxALIGN_CENTER);
	header->SetBackgroundColour(*wxBLUE);
	header->SetForegroundColour(*wxWHITE);
	header->SetFont(wxFont(30, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRABOLD));
	*/
	/*enum IDs
	{
		gen_ID=2,
		header_ID=3,
		data_ID=4,
		qrImg_ID=5
	};

	wxBEGIN_EVENT_TABLE(Window, wxFrame)
		EVT_BUTTON(gen_ID,Window::OnButtonClicked)
		EVT_BUTTON(header_ID, Window::OnButtonClicked)
		EVT_BUTTON(data_ID, Window::OnButtonClicked)
		EVT_BUTTON(qrImg_ID, Window::OnButtonClicked)
	wxEND_EVENT_TABLE()
	*/
