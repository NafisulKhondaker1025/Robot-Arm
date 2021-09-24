#include <wx/stattext.h>
#include "SC.h"

toolsPanel::toolsPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_RAISED)
{
	m_parent = parent;
	m_title = new wxStaticText(this, -1, wxT("Program the Servos With Desired Positions"));

	wxBoxSizer* vbox1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);

	play = new wxButton(this, 1000, wxT("Play Positions"));
	Connect(1000, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(toolsPanel::OnPlay));
	save = new wxButton(this, 1001, wxT("Save"));
	Connect(1001, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(toolsPanel::OnSave));
	clrlast = new wxButton(this, 1002, wxT("Clear Last Position"));
	Connect(1002, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(toolsPanel::OnClrlast));
	clrall = new wxButton(this, 1003, wxT("Clear All Positions"));
	Connect(1003, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(toolsPanel::OnClrall));
	m_port = new wxStaticText(this, -1, wxT("Port Name:"));
	m_txt1 = new wxTextCtrl(this, 1005, "");
	ok = new wxButton(this, 1006, wxT("OK"));
	Connect(1006, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(toolsPanel::OnOk));

	vbox1->Add(m_title, 1, wxALIGN_CENTER_HORIZONTAL, 5);
	hbox3->Add(m_port, 1, wxEXPAND | wxALL, 5);
	hbox3->Add(m_txt1, 5, wxEXPAND | wxALL, 5);
	hbox3->Add(ok, 1, wxEXPAND | wxALL, 5);
	vbox1->Add(hbox3, 0, wxEXPAND | wxALL, 5);
	hbox1->Add(play, wxEXPAND | wxALL, 5);
	hbox1->Add(save, wxEXPAND | wxALL, 5);
	vbox1->Add(hbox1, 0, wxEXPAND | wxALL, 5);
	hbox2->Add(clrlast, wxEXPAND | wxALL, 5);
	hbox2->Add(clrall, wxEXPAND | wxALL, 5);
	vbox1->Add(hbox2, 0, wxEXPAND | wxALL, 5);
	this->SetSizer(vbox1);
}


void toolsPanel::OnPlay(wxCommandEvent& WXUNUSED(event))
{
	SC* sc1 = (SC*)m_parent->GetParent();
	for (int i = 0; i < sc1->savedPositions.size(); ++i)
	{
		sc1->OpenSerialPort();
		for (int j = 0; j < 5; j++)
		{
			if (sc1->savedPositions.at(i).at(j).pos < 100) {
				sc1->SendData5(sc1->savedPositions.at(i).at(j).data);
			}
			else {
				sc1->SendData6(sc1->savedPositions.at(i).at(j).data);
			}
		}
		sc1->CloseSerialPort();
		Sleep(1000);
	}
}
void toolsPanel::OnSave(wxCommandEvent& WXUNUSED(event))
{
	SC* sc1 = (SC*)m_parent->GetParent();

	sc1->savedPositions.push_back(sc1->tempPositions);
}
void toolsPanel::OnClrlast(wxCommandEvent& WXUNUSED(event))
{
	SC* sc1 = (SC*)m_parent->GetParent();
	sc1->savedPositions.pop_back();
}
void toolsPanel::OnClrall(wxCommandEvent& WXUNUSED(event))
{
	SC* sc1 = (SC*)m_parent->GetParent();
	sc1->Clrall();
}
void toolsPanel::OnOk(wxCommandEvent& WXUNUSED(event))
{
	flag = 1;
	SC* sc1 = (SC*)m_parent->GetParent();
	sc1->PortSpecifier.assign(m_txt1->GetValue());
}


firstPanel::firstPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_RAISED)
{
	data = new wxString;
	m_parent = parent;
	m_title = new wxStaticText(this, -1, wxT("Servo 1"), wxPoint(30, 10));
	slider = new wxSlider(this, ID_SLIDER, 90, 0, 180, wxPoint(35, 50), wxSize(20, 650), wxSL_VERTICAL);
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(firstPanel::OnScroll));
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d"), pos));
	m_value = new wxStaticText(this, -1, *data, wxPoint(70, 367));
}

void firstPanel::OnScroll(wxScrollEvent& event)
{
	SC* sc1 = (SC*)m_parent->GetParent();
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d\n"), pos));
	m_value->SetLabel(*data);
	sc1->tempPositions.at(0).pos = pos;
	sc1->tempPositions.at(0).data.assign("a\n");
	sc1->tempPositions.at(0).data.Append(*data);
	if (sc1->toolbar->flag == 1) {
		sc1->OpenSerialPort();
		if (pos < 100) {
			sc1->SendData5(sc1->tempPositions.at(0).data);
		}
		else {
			sc1->SendData6(sc1->tempPositions.at(0).data);
		}
		sc1->CloseSerialPort();

	}
}

secondPanel::secondPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_RAISED)
{
	data = new wxString;
	m_parent = parent;
	m_title = new wxStaticText(this, -1, wxT("Servo 2"), wxPoint(30, 10));
	slider = new wxSlider(this, ID_SLIDER, 90, 0, 180, wxPoint(35, 50), wxSize(20, 650), wxSL_VERTICAL);
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(secondPanel::OnScroll));
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d"), pos));
	m_value = new wxStaticText(this, -1, *data, wxPoint(70, 367));
}

void secondPanel::OnScroll(wxScrollEvent& event)
{
	SC* sc1 = (SC*)m_parent->GetParent();
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d\n"), pos));
	m_value->SetLabel(*data);
	sc1->tempPositions.at(1).pos = pos;
	sc1->tempPositions.at(1).data.assign("b\n");
	sc1->tempPositions.at(1).data.Append(*data);
	if (sc1->toolbar->flag == 1) {
		sc1->OpenSerialPort();
		if (pos < 100) {
			sc1->SendData5(sc1->tempPositions.at(1).data);
		}
		else {
			sc1->SendData6(sc1->tempPositions.at(1).data);
		}
		sc1->CloseSerialPort();
	}
}

thirdPanel::thirdPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_RAISED)
{
	data = new wxString;
	m_parent = parent;
	m_title = new wxStaticText(this, -1, wxT("Servo 3"), wxPoint(30, 10));
	slider = new wxSlider(this, ID_SLIDER, 90, 0, 180, wxPoint(35, 50), wxSize(20, 650), wxSL_VERTICAL);
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(thirdPanel::OnScroll));
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d"), pos));
	m_value = new wxStaticText(this, -1, *data, wxPoint(70, 367));
}

void thirdPanel::OnScroll(wxScrollEvent& event)
{
	SC* sc1 = (SC*)m_parent->GetParent();
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d\n"), pos));
	m_value->SetLabel(*data);
	sc1->tempPositions.at(2).pos = pos;
	sc1->tempPositions.at(2).data.assign("c\n");
	sc1->tempPositions.at(2).data.Append(*data);
	if (sc1->toolbar->flag == 1) {
		sc1->OpenSerialPort();
		if (pos < 100) {
			sc1->SendData5(sc1->tempPositions.at(2).data);
		}
		else {
			sc1->SendData6(sc1->tempPositions.at(2).data);
		}
		sc1->CloseSerialPort();
	}
}

fourthPanel::fourthPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_RAISED)
{
	data = new wxString;
	m_parent = parent;
	m_title = new wxStaticText(this, -1, wxT("Servo 4"), wxPoint(30, 10));
	slider = new wxSlider(this, ID_SLIDER, 90, 0, 180, wxPoint(35, 50), wxSize(20, 650), wxSL_VERTICAL);
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(fourthPanel::OnScroll));
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d"), pos));
	m_value = new wxStaticText(this, -1, *data, wxPoint(70, 367));
}

void fourthPanel::OnScroll(wxScrollEvent& event)
{
	SC* sc1 = (SC*)m_parent->GetParent();
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d\n"), pos));
	m_value->SetLabel(*data);
	sc1->tempPositions.at(3).pos = pos;
	sc1->tempPositions.at(3).data.assign("d\n");
	sc1->tempPositions.at(3).data.Append(*data);
	if (sc1->toolbar->flag == 1) {
		sc1->OpenSerialPort();
		if (pos < 100) {
			sc1->SendData5(sc1->tempPositions.at(3).data);
		}
		else {
			sc1->SendData6(sc1->tempPositions.at(3).data);
		}
		sc1->CloseSerialPort();
	}
}

fifthPanel::fifthPanel(wxPanel* parent) : wxPanel(parent, -1, wxPoint(-1, -1), wxSize(-1, -1), wxBORDER_RAISED)
{
	data = new wxString;
	m_parent = parent;
	m_title = new wxStaticText(this, -1, wxT("Servo 5"), wxPoint(30, 10));
	slider = new wxSlider(this, ID_SLIDER, 90, 0, 180, wxPoint(35, 50), wxSize(20, 650), wxSL_VERTICAL);
	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(fifthPanel::OnScroll));
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d"), pos));
	m_value = new wxStaticText(this, -1, *data, wxPoint(70, 367));
}

void fifthPanel::OnScroll(wxScrollEvent& event)
{
	SC* sc1 = (SC*)m_parent->GetParent();
	pos = slider->GetValue();
	data->assign(wxString::Format(wxT("%d\n"), pos));
	m_value->SetLabel(*data);
	sc1->tempPositions.at(4).pos = pos;
	sc1->tempPositions.at(4).data.assign("e\n");
	sc1->tempPositions.at(4).data.Append(*data);
	if (sc1->toolbar->flag == 1) {
		sc1->OpenSerialPort();
		if (pos < 100) {
			sc1->SendData5(sc1->tempPositions.at(4).data);
		}
		else {
			sc1->SendData6(sc1->tempPositions.at(4).data);
		}
		sc1->CloseSerialPort();
	}
}