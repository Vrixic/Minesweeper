#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App()
{

}

App::~App()
{

}

bool App::OnInit()
{
	mMainWindowPtr = new MainWindow();
	mMainWindowPtr->Show();

	return true;
}