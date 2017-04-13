#include "Serial.h"
// Bartosz Milewski (c) 2000
using std::ios_base;

const unsigned long TruePattern = 0xfab1fab2;
const unsigned long FalsePattern = 0xbad1bad2;

Serializer::Serializer (std::string const & nameFile)
	: _stream (nameFile.c_str (), ios_base::out | ios_base::binary)
{
	if (!_stream.is_open ())
		throw "couldn't open file";
}

void Serializer::PutULong (unsigned long x)
{
	_stream.write (reinterpret_cast<char *> (&x), sizeof (unsigned long));
	if (_stream.bad())
		throw "file write failed";
}

void Serializer::PutDouble (double x)
{
	_stream.write (reinterpret_cast<char *> (&x), sizeof (double));
	if (_stream.bad())
		throw "file write failed";
}

void Serializer::PutString (std::string const & str)
{
	unsigned len = str.length ();
	PutULong (len);
	_stream.write (str.data (), len);
	if (_stream.bad())
		throw "file write failed";
}

void Serializer::PutBool (bool x)
{
	unsigned long ul = x? TruePattern: FalsePattern;
	PutULong (ul);
	if (_stream.bad ())
		throw "file write failed";
}

DeSerializer::DeSerializer (std::string const & nameFile)
	: _stream (nameFile.c_str (), ios_base::in | ios_base::binary)
{
	if (!_stream.is_open ())
		throw "couldn't open file";
}

unsigned long DeSerializer::GetULong ()
{
	if (_stream.eof())
		throw "unexpected end of file";
	unsigned long ul;
	_stream.read (reinterpret_cast<char *> (&ul), sizeof (unsigned long));
	if (_stream.bad())
		throw "file read failed";
	return ul;
}

double DeSerializer::GetDouble ()
{
	double d;
	if (_stream.eof())
		throw "unexpected end of file";
	_stream.read (reinterpret_cast<char *> (&d), sizeof (double));
	if (_stream.bad())
		throw "file read failed";
	return d;
}

std::string DeSerializer::GetString ()
{
	unsigned long len = GetULong ();
	if (len > 0x100000) // If it's that long, we are probably reading the wrong file
		throw "bad file format";
	std::string str;
	str.resize (len);
	_stream.read (&str [0], len);
	if (_stream.bad())
		throw "file read failed";
	return str;
}

bool DeSerializer::GetBool ()
{
	unsigned long b = GetULong ();
	if (_stream.bad())
		throw "file read failed";
	if (b == TruePattern)
		return true;
	else if (b == FalsePattern)
		return false;
	else
		throw "data corruption";
	return false;
}
