#include "SymTab.h"
// (c) Bartosz Milewski 2000
#include "Serial.h"
#include "Notify.h"
#include "Exception.h"
#include <cassert>
#include <algorithm>

unsigned SymbolTable::ForceAdd (std::string const & str)
{
	_dictionary [str] = _id;
	// Notify of new item
	if (_sink)
		_sink->AddItem (_id);
	return _id++;
}

unsigned SymbolTable::Find (std::string const & str) const
{
	std::map<std::string, unsigned>::const_iterator it;
	it = _dictionary.find (str);
	if (it != _dictionary.end ())
		return it->second;
	return idNotFound;
}

class IsEqualId
{
public:
	IsEqualId (unsigned id) : _id (id) {}
	bool operator () (std::pair<std::string const, unsigned> const & it) const
	{
		return it.second == _id;
	}
private:
	unsigned _id;
};

std::string SymbolTable::GetSymbolName (unsigned id) const
{
	iterator it = std::find_if (_dictionary.begin (), 
								_dictionary.end (), 
								IsEqualId (id));
	if (it == _dictionary.end ())
		throw Win::Exception ("Internal error: missing entry in symbol table");
	return it->first;
}

void SymbolTable::Serialize (Serializer & out) const
{
	out.PutULong (_dictionary.size ());
	std::map<std::string, unsigned>::const_iterator it;
	for (it = _dictionary.begin (); it != _dictionary.end (); ++it)
	{
		out.PutString (it->first);
		out.PutULong (it->second);
	}
	out.PutULong (_id);
}

void SymbolTable::DeSerialize (DeSerializer & in)
{
	_dictionary.clear ();
	unsigned len = in.GetULong ();
	for (unsigned i = 0; i < len; ++i)
	{
		std::string str = in.GetString ();
		unsigned id = in.GetULong ();
		_dictionary [str] = id;
	}
	_id = in.GetULong ();
}
