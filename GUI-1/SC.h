#pragma once
//#include <iostream>
#include "Panels.h"
#include <wx/wxprec.h>
#include <wx/string.h>
#include <vector>

struct positions
{
	wxString data;
	int pos;
};

class SC : public wxFrame
{
public:
	SC(const wxString& title);
	~SC();
	toolsPanel* toolbar;
	firstPanel* m_1p;
	secondPanel* m_2p;
	thirdPanel* m_3p;
	fourthPanel* m_4p;
	fifthPanel* m_5p;
	wxPanel* m_parent;
	wxButton* quit;
	wxString PortSpecifier;
	DCB dcb;
	DWORD byteswritten;
	HANDLE hPort;
	std::vector<std::vector<positions>> savedPositions;
	std::vector<positions> tempPositions;

	void OnQuit(wxCommandEvent& event);
	//bool WriteComPort(wxString PortSpecifier, wxString data);
	bool OpenSerialPort();
	void SendData5(wxString data);
	void SendData6(wxString data);
	void CloseSerialPort();
	void Clrall(void);
};

