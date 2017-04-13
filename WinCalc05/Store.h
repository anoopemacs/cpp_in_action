#if !defined (STORE_H)
#define STORE_H
// (c) Bartosz Milewski 2000
#include "Serial.h"
#include <vector>
#include <cassert>

class SymbolTable;
class NotificationSink;

enum { stNotInit, stInit };

class Store: public Serializable
{
public:
	explicit Store (SymbolTable & symTab);
	void SetNotificationSink (NotificationSink * sink)
	{
		_sink = sink;
	}
	void Clear () 
	{
		_cell.clear ();
		_isInit.clear ();
		_firstVarId = 0;
	}
	bool HasVariables () const { return _cell.size () > _firstVarId; }
	void AddConstants (SymbolTable & symTab);
	void RefreshNotify () const;
	bool IsInit (unsigned id) const
	{
		return id < _isInit.size () && _isInit [id];
	}
	double Value (unsigned id) const
	{
		assert (IsInit (id));
		return _cell [id];
	}
	void SetValue (unsigned id, double val);
	void AddValue (unsigned id, double val);
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
private:
	unsigned			_firstVarId;
	std::vector<double>	_cell;
	std::vector<bool>	_isInit;
	NotificationSink  * _sink;
};

#endif
