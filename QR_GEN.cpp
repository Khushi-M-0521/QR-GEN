#include "QR_GEN.h"
#include "Window.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(QR_GEN);

bool QR_GEN::OnInit()
{
	Window* window = new Window("QR CODE GENERATOR");
	window->SetClientSize(600,600);
	window->Center();
	window->Show();
	return true;
}