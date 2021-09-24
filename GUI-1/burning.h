#pragma once

#include <wx/wx.h>
#include "widget.h"


class Burning : public wxFrame
{
public:
	Burning(const wxString& title);

	void OnScroll(wxScrollEvent& event);
	int GetCurWidth();

	wxSlider* m_slider;
	widget* m_wid;

	int cur_width;
};

