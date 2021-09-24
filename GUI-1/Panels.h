#pragma once

#include <wx/wx.h>
#include <wx/panel.h>

class toolsPanel : public wxPanel
{
public:
	toolsPanel(wxPanel* parent);
	void OnSave(wxCommandEvent& event);
	void OnPlay(wxCommandEvent& event);
	void OnClrlast(wxCommandEvent& event);
	void OnClrall(wxCommandEvent& event);
	void OnOk(wxCommandEvent& event);
	wxStaticText* m_title;
	wxStaticText* m_port;
	wxButton* play;
	wxButton* save;
	wxButton* clrlast;
	wxButton* clrall;
	wxButton* ok;
	wxPanel* m_parent;
	wxTextCtrl* m_txt1;
	int flag;
};

class firstPanel : public wxPanel
{
public:
	firstPanel(wxPanel* parent);
	wxStaticText* m_title;
	wxSlider* slider;
	wxString* data;
	int pos;
	wxStaticText* m_value;
	void OnScroll(wxScrollEvent& event);
};

class secondPanel : public wxPanel
{
public:
	secondPanel(wxPanel* parent);
	wxStaticText* m_title;
	wxSlider* slider;
	wxString* data;
	int pos;
	wxStaticText* m_value;
	void OnScroll(wxScrollEvent& event);

};

class thirdPanel : public wxPanel
{
public:
	thirdPanel(wxPanel* parent);
	wxStaticText* m_title;
	wxSlider* slider;
	wxString* data;
	int pos;
	wxStaticText* m_value;
	void OnScroll(wxScrollEvent& event);
};

class fourthPanel : public wxPanel
{
public:
	fourthPanel(wxPanel* parent);
	wxStaticText* m_title;
	wxSlider* slider;
	wxString* data;
	int pos;
	wxStaticText* m_value;
	void OnScroll(wxScrollEvent& event);
};

class fifthPanel : public wxPanel
{
public:
	fifthPanel(wxPanel* parent);
	wxStaticText* m_title;
	wxSlider* slider;
	wxString* data;
	int pos;
	wxStaticText* m_value;
	void OnScroll(wxScrollEvent& event);
};

const int ID_SLIDER = 100;