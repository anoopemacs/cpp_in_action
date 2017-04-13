#if !defined (SYMTAB_H)
#define SYMTAB_H
// (c) Bartosz Milewski 2000
#include "Serial.h"
#include <map>
#include <string>
class NotificationSink;

// String table maps strings to ints
// and ints to strings

class SymbolTable: public Serializable
{
	typedef std::map<std::string, unsigned>::const_iterator iterator;
public:
	enum { idNotFound = 0xffffffff };
	SymbolTable () : _id (0), _sink (0) {}
	void SetNotificationSink (NotificationSink * sink)
	{
		_sink = sink;
	}
	void Clear () 
	{ 
		_dictionary.clear ();
		_id = 0;
	}
	unsigned ForceAdd (std::string const & str);
	unsigned Find (std::string const & str) const;
	std::string GetSymbolName (unsigned id) const;
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
private:
	std::map<std::string, unsigned> _dictionary;
	unsigned _id;
	NotificationSink * _sink;
};

#endif
