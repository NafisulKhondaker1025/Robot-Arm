#pragma once

#include "wx/wx.h"

class widget : public wxPanel
{
public:
	widget(wxPanel* parent, int id);
	wxPanel* m_parent;

	void OnSize(wxSizeEvent& event);
	void OnPaint(wxPaintEvent& event);

};

