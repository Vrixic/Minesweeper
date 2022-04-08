#pragma once

#include "wx/wx.h"

class MainWindow : public wxFrame
{
private:
	unsigned int mFieldWidth = 10;
	unsigned int mFieldHeight = 10;

	wxButton** mButtons = nullptr;

	int* mField = nullptr;
	bool bFirstClick = true;

	wxColor mButtonBackgroundColor;

private:
	void OnButtonClicked(wxCommandEvent& event);

public:
	MainWindow();
	~MainWindow();

	wxDECLARE_EVENT_TABLE();
};

