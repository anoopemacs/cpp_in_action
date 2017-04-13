#if !defined (VIEW_H)
#define VIEW_H
// Bartosz Milewski (c) 2000
#include "MenuTable.h"
#include "Notify.h"
#include "StatusBar.h"
#include "ListBox.h"
#include "Edit.h"
class Calculator;

class EditController: public Win::SubController
{
public:
	bool OnKeyDown (int vKey, int flags) throw ();
};

class View: public NotificationSink
{
public:
	View (Win::Dow winTop, Cmd::Vector * cmdVector, Calculator const & calc);
	void Init (Win::Dow win);
	void Size (int width, int height);
	void SetFocus ()
	{
		_edit.SetFocus ();
	}
	std::string GetInput ()
	{
		return _edit.GetText ();
	}
	void SetResult (char const * str);
	void SetStatus (char const * str);
	void UpdateHistory (std::string const & str, double result);
	void ClearMemory () { _memoryView.Clear (); }
	void RefreshPopup (HMENU menu, int pos)
	{
		_menu.RefreshPopup (menu, pos);
	}
	// NotificationSink
	void AddItem (int id);
	void UpdateItem (int id);
private:
	std::string FormatMemoryString (int id);
private:
	int _charWidth, _charHeight;
	int _wValue;		// width in pixels of value field
	int _varNameChars;  // width in chars of name field
	
	Calculator const & _calc;
	
	EditController	_editCtrl;

	Menu::DropDown	_menu;
	Win::StatusBar	_status;
	Win::ListBox	_historyView;
	Win::ListBox	_memoryView;
	Win::Edit		_edit;
	Win::Edit		_result;
};

#endif
