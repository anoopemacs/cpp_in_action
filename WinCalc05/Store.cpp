#include "Store.h"
// (c) Bartosz Milewski 2000
#include "SymTab.h"
#include "Serial.h"
#include "Notify.h"
#include <cmath>

Store::Store (SymbolTable & symTab)
	:_sink (0)
{
	AddConstants (symTab);
}

void Store::AddConstants (SymbolTable & symTab)
{
	// add predefined constants
	// Note: if more needed, do a more general job
	unsigned id = symTab.ForceAdd ("e");
	AddValue (id, std::exp (1.0));
	id = symTab.ForceAdd ("pi");
	AddValue (id, 2.0 * std::acos (0.0));
	_firstVarId = id + 1;
}

void Store::SetValue (unsigned id, double val)
{
	if (id < _cell.size ())
	{
		_cell [id] = val;
		_isInit [id] = true;
	}
	else
	{
		AddValue (id, val);
	}
	// Notify of change
	if (_sink)
		_sink->UpdateItem (id);
}

void Store::RefreshNotify () const
{
	if (_sink == 0)
		return;
	for (unsigned i = 0; i < _cell.size (); ++i)
	{
		if (_isInit [i] == true)
			_sink->AddItem (i);
	}
}

void Store::AddValue (unsigned id, double val)
{
	_cell.resize (id + 1);
	_isInit.resize (id + 1);
	_cell [id] = val;
	_isInit [id] = true;
}

void Store::Serialize (Serializer & out) const
{
	unsigned len = _cell.size ();
	out.PutULong (len);
	for (unsigned i = 0; i < len; ++i)
	{
		out.PutDouble (_cell [i]);
		out.PutBool (_isInit [i]);
	}
}

void Store::DeSerialize (DeSerializer & in)
{
	_cell.clear ();
	_isInit.clear ();
	unsigned long len = in.GetULong ();
	_cell.resize (len);
	_isInit.resize (len);
	for (unsigned i = 0; i < len; ++i)
	{
		_cell [i] = in.GetDouble ();
		_isInit [i] = in.GetBool ();
	}
}
