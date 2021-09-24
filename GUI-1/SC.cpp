#include "SC.h"
SC::SC(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 1000))
{
    wxImage::AddHandler(new wxPNGHandler);
    SetIcon(wxIcon(wxT("icon.png"), wxBITMAP_TYPE_PNG));
    m_parent = new wxPanel(this, wxID_ANY);

    quit = new wxButton(m_parent, wxID_EXIT, wxT("Quit"));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SC::OnQuit));

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);


    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
    toolbar = new toolsPanel(m_parent);
    m_1p = new firstPanel(m_parent);
    m_2p = new secondPanel(m_parent);
    m_3p = new thirdPanel(m_parent);
    m_4p = new fourthPanel(m_parent);
    m_5p = new fifthPanel(m_parent);
    
    vbox->Add(toolbar, 5, wxALIGN_TOP, 5);
    hbox->Add(m_1p, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_2p, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_3p, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_4p, 1, wxEXPAND | wxALL, 5);
    hbox->Add(m_5p, 1, wxEXPAND | wxALL, 5);
    vbox->Add(hbox, 25, wxEXPAND | wxALL, 5);
    vbox->Add(quit, 1, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5);

    m_parent->SetSizer(vbox);

    std::vector<positions> init(5);
    init.at(0).data.assign("a\n90\n");
    init.at(1).data.assign("b\n90\n");
    init.at(2).data.assign("c\n90\n");
    init.at(3).data.assign("d\n90\n");
    init.at(4).data.assign("e\n90\n");
    init.at(0).pos = 90;
    init.at(1).pos = 90;
    init.at(2).pos = 90;
    init.at(3).pos = 90;
    init.at(4).pos = 90;

    tempPositions = init;

    savedPositions.push_back(init);

    Centre();
}

SC::~SC(void)
{
    delete(toolbar);
    delete(m_1p);
    delete(m_2p);
    delete(m_3p);
    delete(m_4p);
    delete(m_5p);
    delete(quit);
    delete(m_parent);
    for (int i = 0; i < savedPositions.size(); ++i)
    {
        if (i < 4) {
            tempPositions.pop_back();
            savedPositions.pop_back();
        }
        else {
            savedPositions.pop_back();
        }
    }

}

void SC::Clrall(void)
{
    savedPositions.clear();
    std::vector<positions> init(5);
    init.at(0).data.assign("a\n90\n");
    init.at(1).data.assign("b\n90\n");
    init.at(2).data.assign("c\n90\n");
    init.at(3).data.assign("d\n90\n");
    init.at(4).data.assign("e\n90\n");
    init.at(0).pos = 90;
    init.at(1).pos = 90;
    init.at(2).pos = 90;
    init.at(3).pos = 90;
    init.at(4).pos = 90;
    savedPositions.push_back(init);
}

bool SC::OpenSerialPort()
{
    if (PortSpecifier == "")
    {
        return false;
    }

    hPort = CreateFile(PortSpecifier, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (!GetCommState(hPort, &dcb))
    {
        return false;
    }
    
    dcb.BaudRate = CBR_9600; //9600 Baud
    dcb.ByteSize = 8; //8 data bits
    dcb.Parity = NOPARITY; //no parity
    dcb.StopBits = ONESTOPBIT; //1 stop

    if (!SetCommState(hPort, &dcb))
    {
        return false;
    }
    return true;
}

void SC::SendData5(wxString data)
{
   WriteFile(hPort, data, 5, &byteswritten, NULL);
}
void SC::SendData6(wxString data)
{
    WriteFile(hPort, data, 6, &byteswritten, NULL);
}

void SC::CloseSerialPort()
{
    CloseHandle(hPort);
}

//bool SC::WriteComPort(wxString PortSpecifier, wxString data)
//{
//    if (PortSpecifier == "")
//    {
//        return false;
//    }
//    DCB dcb;
//    DWORD byteswritten;
//
//    HANDLE hPort = CreateFile(PortSpecifier, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
//
//    if (!GetCommState(hPort, &dcb))
//    {
//        return false;
//    }
//
//    dcb.BaudRate = CBR_9600; //9600 Baud
//    dcb.ByteSize = 8; //8 data bits
//    dcb.Parity = NOPARITY; //no parity
//    dcb.StopBits = ONESTOPBIT; //1 stop
//
//    if (!SetCommState(hPort, &dcb))
//    {
//        return false;
//    }
//
//    bool retVal = WriteFile(hPort, data, 1, &byteswritten, NULL);
//    CloseHandle(hPort); //close the handle
//    return true;
//}

void SC::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}