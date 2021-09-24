#include "main.h"
#include "SC.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	SC* sc = new SC(wxT("Servo Controller"));
	sc->Show();

	return true;
}