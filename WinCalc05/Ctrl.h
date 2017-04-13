#if !defined (CTRL_H)
#define CTRL_H
// Bartosz Milewski (c) 2000
#include "Control.h"
#include "View.h"
#include "Calc.h"
#include "Commander.h"

class TopController: public Win::Controller
{
public:
	bool OnCreate (Win::CreateData const * create, bool & success) throw ();
	bool OnDestroy () throw ()
	{
		::PostQuitMessage (0);
		return true;
	}
	bool OnCommand (int cmdId, bool isAccel) throw ();
	bool OnControl (Win::Dow control, int controlId, int notifyCode) throw ();
	bool OnFocus (Win::Dow winPrev) throw ();
	bool OnSize (int width, int height, int flags) throw ();
	bool OnInitPopup (HMENU menu, int pos) throw ();
	bool OnMenuSelect (int id, int flags, HMENU menu) throw ();
	bool OnUserMessage (UINT msg, 
						WPARAM wParam, 
						LPARAM lParam, 
						LRESULT & result) throw ();
private:
	std::auto_ptr<Commander>	_commander;
	std::auto_ptr<CmdVector>	_cmdVector;
	std::auto_ptr<View>			_view;
	// this is the Model
	Calculator	 _calc;
};

#endif
