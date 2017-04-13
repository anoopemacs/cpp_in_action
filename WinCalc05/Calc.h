#if !defined (CALC_H)
#define CALC_H
// Bartosz Milewski (c) 2000
#include "SymTab.h"
#include "FunTab.h"
#include "Store.h"
#include "Serial.h"
class NotificationSink;

class Calculator: public Serializable
{
	friend class Parser;
public:
	Calculator ()
		: _funTab (_symTab), _store (_symTab)
	{}
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
	void SetNotificationSink (NotificationSink * sink)
	{
		_symTab.SetNotificationSink (sink);
		_store.SetNotificationSink (sink);
	}
	std::string GetVariableName (unsigned id) const;
	bool GetVariableValue (unsigned id, double & val) const;
	void RefreshMemory () const;
	void ClearMemory ();
	bool HasVariables () const { return _store.HasVariables (); }
private:
	Store & GetStore () { return _store; }
	PtrFun GetFun (unsigned id) const
	{
		return _funTab.GetFun (id);
	}
	bool IsFunction (unsigned id) const 
	{
		return id < _funTab.Size (); 
	}
	unsigned AddSymbol (std::string const & str)
	{
		return _symTab.ForceAdd (str);
	}
	unsigned FindSymbol (std::string const & str) const
	{
		return _symTab.Find (str);
	}

	SymbolTable     _symTab;
	Function::Table _funTab;
	Store           _store;
};

#endif
