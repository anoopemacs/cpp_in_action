#include "Ctrl.h"
// Bartosz Milewski (c) 2000
#include "Scanner.h"
#include "Parser.h"
#include "SyntaxErr.h"
#include "Output.h"
#include "Canvas.h"
#include "Resource.h"
#include <sstream>

bool TopController::OnCreate (Win::CreateData const * create, bool & success) throw ()
{
	try
	{
		TheOutput.Init (_h);
		_commander.reset (new Commander (_h, _calc));
		_cmdVector.reset (new CmdVector (Cmd::Table, _commander.get ()));
		_view.reset(new View (_h, _cmdVector.get (), _calc));
		_calc.SetNotificationSink (_view.get ());
		// view must be fully constructed before calling this
		_view->Init (_h);
		_view->SetStatus ("Ready");
		success = true;
	}
	catch (Win::Exception & e)
	{
		TheOutput.Error (e.GetMessage ());
		success = false;
	}
	catch (...)
	{
		TheOutput.Error ("Internal Error:\nFailure to initialize.");
		success = false;
	}
	return true;
}

bool TopController::OnCommand (int cmdId, bool isAccel) throw ()
{
	try
	{
		_cmdVector->Execute (cmdId);
	}
	catch (Win::ExitException)
	{
		_h.Destroy ();
	}
	catch (Win::Exception const & e)
	{
		TheOutput.Error (e.GetMessage ());
	}
	catch (char const * str)
	{
		TheOutput.Error (str);
	}
	catch (...)
	{
		TheOutput.Error ("Internal error");
	}
	return true;
}

bool TopController::OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
{
	if (controlId == IDOK)
	{
		try
		{
			std::string expr = _view->GetInput ();
			std::istringstream in (expr);
			Scanner scanner (in);
			Parser  parser (scanner, _calc);
			parser.Parse ();
			double result = parser.Calculate ();
			_view->UpdateHistory (expr, result);
			std::ostringstream out;
			out << result;
			std::string strOut = out.str ();
			_view->SetResult (strOut.c_str ());
		}
		catch (Syntax const & err)
		{
			TheOutput.Error (err.GetString ());
			_view->SetResult ("");
		}
		catch (...)
		{
			TheOutput.Error ("Internal error");
			_view->SetResult ("");
		}
		return true;
	}
	return false;
}

bool TopController::OnFocus (Win::Dow winPrev) throw ()
{
	if (_view.get () != 0)
	    _view->SetFocus ();
	return true;
}

bool TopController::OnSize (int width, int height, int flags) throw ()
{
	if (flags != SIZE_MINIMIZED)
	{
		_view->Size (width, height);
	}
	return true;
}

bool TopController::OnInitPopup (HMENU menu, int pos) throw ()
{
	try
	{
		_view->RefreshPopup (menu, pos);
	}
	catch (...) 
	{}
	return true;
}

bool TopController::OnMenuSelect (int id, int flags, HMENU menu) throw ()
{
	if (flags == 0xffff)
	{
		// menu dismissed
		_view->SetStatus ("Ready");
		return true;
	}
	if ((flags & MF_SEPARATOR) || (flags & MF_SYSMENU))
	{
		return false;
	}
	if (!(flags & MF_POPUP))
	{
		// menu item selected
		_view->SetStatus (_cmdVector->GetHelp (id));
		return true;
	}
	return false;
}

bool TopController::OnUserMessage ( UINT msg, 
									WPARAM wParam, 
									LPARAM lParam, 
									LRESULT & result) throw ()
{
	if (msg == UM_MEMCLEAR)
	{
		_view->ClearMemory ();
		_calc.RefreshMemory ();
		return true;
	}
	return false;
}
