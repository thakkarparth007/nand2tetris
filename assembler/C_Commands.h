/*
	Classes: DestinationMapper, CompMapper, JumpMapper
	Namespace: parth::nand2tetris::assembler

	@author Parth Thakkar
*/

#ifndef C_Commands
#define C_Commands 1

#include <map>
#include <string>

/*
	Todo:
		How to make singleton classes in C++?
		Hiding the unnecessary details.
*/
using namespace std;

namespace parth {
namespace nand2tetris {
namespace assembler {

// destinations
// comp codes
// jump codes

class DestinationMapper {
	private:
		map<string, string> codes;
	public:
		DestinationMapper();
		bool isMnemonicValid(string m) {
			return codes.find(m) != codes.end();
		}
		string getBinaryCode(string m) {
			return codes[m];
		}
};

class CompMapper {
	private:
		map<string, string> codes;
	public:
		CompMapper();
		bool isMnemonicValid(string m) {
			return codes.find(m) != codes.end();
		}
		string getBinaryCode(string m) {
			return codes[m];
		}
};

class JumpMapper {
	private:
		map<string, string> codes;
	public:
		JumpMapper();
		bool isMnemonicValid(string m) {
			return codes.find(m) != codes.end();
		}
		string getBinaryCode(string m) {
			return codes[m];
		}
};

}
}
}

#endif