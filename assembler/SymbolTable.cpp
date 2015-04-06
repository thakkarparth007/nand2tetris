#include "./SymbolTable.h"
#include "./Errors.h"
#include <string>

using namespace std;

namespace parth {
namespace nand2tetris {
namespace assembler {

void SymbolTable::addEntry(string s, int addr) {
	_tab[s] = addr;
}
bool SymbolTable::contains(string s) {
	_tab.find(s) != _tab.end();
}
string SymbolTable::formatAsBin(int addr) {
	string bin(15,'0');
	int n = 14;
	while(addr) {
		bin[n--] = addr & 1 ? '1' : '0';
		addr >>= 1;
	}
	return bin;
}
string SymbolTable::getAddress(string s) {
	if(!contains(s)) {
		throw UndefinedSymbolException(
			string("Undefined symbol: '") + s + "'");
	}
	return formatAsBin(_tab[s]);
}

}
}
}