#if !defined (FUNTAB_H)
#define FUNTAB_H
// (c) Bartosz Milewski 2000

class SymbolTable;

typedef double (*PtrFun) (double);

namespace Function
{
	class Table
	{
	public:
		Table (SymbolTable & symTab);
		void Init (SymbolTable & symTab);
		~Table ();
		unsigned Size () const { return _size; }
		PtrFun GetFun (unsigned id) const { return _pFun [id]; }
	private:
		PtrFun		  * _pFun;
		unsigned		_size;
	};
}
#endif
