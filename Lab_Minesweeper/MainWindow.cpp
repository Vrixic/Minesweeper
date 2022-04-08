#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Vrij", 
	wxPoint(420, 180),	wxSize(1080, 720))
{
	mButtons = new wxButton*[mFieldWidth * mFieldHeight];
	wxGridSizer* grid = new wxGridSizer(mFieldWidth, mFieldHeight, 0 ,0);
	this->SetBackgroundColour(wxColor(128, 255, 0));

	mButtonBackgroundColor = wxColor(0, 255, 128);

	mField = new int[mFieldWidth * mFieldHeight];

	wxFont font(24, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (unsigned int x = 0; x < mFieldWidth; x++)
	{
		for (unsigned int y = 0; y < mFieldHeight; y++)
		{
			mButtons[y * mFieldWidth + x] = new wxButton(this, 10000 + (y * mFieldWidth + x));
			mButtons[y * mFieldWidth + x]->SetFont(font);
			mButtons[y * mFieldWidth + x]->SetBackgroundColour(mButtonBackgroundColor);
			grid->Add(mButtons[y * mFieldWidth + x], 1, wxEXPAND | wxALL);

			mButtons[y * mFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);

			mField[y * mFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

MainWindow::~MainWindow()
{
	delete[] mButtons;
}

void MainWindow::OnButtonClicked(wxCommandEvent& event)
{
	// Get Coordinate of button in the field array
	int x = (event.GetId() - 10000) % mFieldWidth;
	int y = (event.GetId() - 10000) / mFieldWidth;

	mButtons[y * mFieldWidth + x]->SetBackgroundColour(wxColor(0, 204, 102));

	if (bFirstClick)
	{
		int mines = 30;

		for (unsigned int x = 0; x < mFieldWidth; x++)
		{
			for (unsigned int y = 0; y < mFieldHeight; y++)
			{
				mButtons[y * mFieldWidth + x]->SetBackgroundColour(mButtonBackgroundColor);
			}
		}

		while (mines)
		{
			int rx = rand() % mFieldWidth;
			int ry = rand() % mFieldHeight;

			if (mField[ry * mFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				mField[ry * mFieldWidth + rx] = -1;
				mines--;
			}
		}

		bFirstClick = false;
	}

	// Disable button, preventing it being pressed again
	mButtons[y * mFieldWidth + x]->Enable(false);

	// Check if player hit mine
	if (mField[y * mFieldWidth + x] == -1)
	{
		wxMessageBox("GET BETTER!!! -- Game Over :(");

		// Reset game
		bFirstClick = true;
		for (unsigned int x = 0; x < mFieldWidth; x++)
		{
			for (unsigned int y = 0; y < mFieldHeight; y++)
			{
				if(mField[y * mFieldWidth + x] == -1)
					mButtons[y * mFieldWidth + x]->SetBackgroundColour(wxColor(255, 0, 0));

				mField[y * mFieldWidth + x] = 0;
				mButtons[y * mFieldWidth + x]->SetLabel("");
				mButtons[y * mFieldWidth + x]->Enable(true);
				
			}
		}
	}
	else
	{
		// Counting Neighboouring mines
		int minesCount = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < mFieldWidth && y + j >= 0 && y + j < mFieldHeight)
				{
					if (mField[(y + j) * mFieldWidth + (x + i)] == -1)
						minesCount++;
				}
			}
		}

		// Update buttons label to show mine count if > 0
		if (minesCount > 0)
		{
			mButtons[y * mFieldWidth + x]->SetLabel(std::to_string(minesCount));
		}
	}

	

	event.Skip();	
}