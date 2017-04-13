#include "Ctrl.h"
#include "Class.h"
#include "Maker.h"
#include "Window.h"
#include "MsgLoop.h"
#include <Resource.h>

enum
{
	WIN_WIDTH = 400,
	WIN_HEIGHT = 400
};

int WINAPI WinMain
	(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
	try
	{
		char className [] = "SymCalcClass";
		Win::ClassMaker winClass (className, hInst);
		winClass.SetIcons (IDI_MAIN);
		winClass.Register ();
		Win::Maker maker (className, hInst);
	    maker.SetSize (WIN_WIDTH, WIN_HEIGHT);
		TopController ctrl;
		Win::Dow win = maker.Create (ctrl, "Symbolic Calculator");
		win.Display (cmdShow);
	
	    Win::MsgPrepro loop;
	    return loop.Pump ();
	}
	catch (char const * msg)
	{
		::MessageBox (0, msg, "Internal error", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		::MessageBox (0, "Unknown", "Internal error", MB_OK | MB_ICONERROR);
	}
	return 1;
}
