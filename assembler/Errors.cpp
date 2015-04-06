#include <sstream>
#include "./Errors.h"

using namespace parth::nand2tetris::assembler;
using namespace std;

string IllegalCallException::what() {
	return _errMessage;
}

string SyntaxErrorException::what() {
	stringstream err;
	string caret(_code.size(), ' ');
	caret[_pos] = '^';

	err << "Syntax error at: \n"
		<< "Line number: " << _lineNum << "\n"
		<< "Code: '" << _code << "'\n"
		<< "       " << caret << "'\n"
		<< _expected << "\n";

	return err.str();
}
string UndefinedSymbolException::what() {
	return _errMessage;
}
