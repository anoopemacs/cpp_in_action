#include "Calc.h"
// Bartosz Milewski (c) 2000

void Calculator::RefreshMemory () const
{
	_store.RefreshNotify ();
}

void Calculator::ClearMemory ()
{
	_symTab.Clear ();
	_store.Clear ();
	_funTab.Init (_symTab);
	_store.AddConstants (_symTab);
}

std::string Calculator::GetVariableName (unsigned id) const
{
	return _symTab.GetSymbolName (id);
}

bool Calculator::GetVariableValue (unsigned id, double & val) const
{
	if (_store.IsInit (id))
	{
		val = _store.Value (id);
		return true;
	}
	else
	{
		return false;
	}
}

void Calculator::Serialize (Serializer & out) const
{
	_symTab.Serialize (out);
	_store.Serialize (out);
}

void Calculator::DeSerialize (DeSerializer & in)
{
	_symTab.DeSerialize (in);
	_store.DeSerialize (in);
}
