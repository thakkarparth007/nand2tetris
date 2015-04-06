/*
	Classes: IllegalCallException, SyntaxErrorException,
			 UndefinedSymbolException
	Namespace: parth::nand2tetris::assembler

	@author Parth Thakkar
*/

#ifndef ERRORS
#define ERRORS 1

#include <string>

/*
	TODO:
		Exception classes use their own "what" method.
		Find out more about exception classes, and how to
		inherit one.
		Modification must be made in the .cpp file too.
*/

using namespace std;

namespace parth {
namespace nand2tetris {
namespace assembler {

class IllegalCallException /*: public exception*/ {	
/*
	The class used to throw an exception in case something like 
	this happens:
	if one calls comp() even if commandType() != C_COMMAND
	in such cases, an exception will be thrown. Etc.
*/
	private:
		string _errMessage;
	public:
		IllegalCallException(string s)
			: _errMessage(s) {}
		string what();
};

class SyntaxErrorException /*: public exception */{
	private:
		int _lineNum;
		int _pos;
		string _code;
		string _expected;
	public:
		SyntaxErrorException(int lineNum, int pos, 
							string code, string expected)
			: _lineNum(lineNum), _pos(pos), 
			  _code(code), _expected(expected) {}
		string what();
};


class UndefinedSymbolException /*: public exception*/ {	
/*
	The class used to throw an exception in case a symbol
	isn't defined and is used. Unlikely to happen because of
	wrong code. Could happen only in case of a programming
	mistake.
*/
	private:
		string _errMessage;
	public:
		UndefinedSymbolException(string s)
			: _errMessage(s) {}
		string what();
};


}
}
}

#endif