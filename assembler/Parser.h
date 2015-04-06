/*
	Class: Parser
	Namespace: parth::nand2tetris::assembler

	@author Parth Thakkar
*/

#ifndef PARSER
#define PARSER 1

#include <fstream>
#include <string>
#include <exception>
#include "./Errors.h"
#include "./C_Commands.h"

using namespace std;

namespace parth {
namespace nand2tetris {
namespace assembler {

enum CommandType {
	A_COMMAND, C_COMMAND, L_COMMAND
};

class Parser {
	private:
		string _currLine;
		ifstream& _in;
		CommandType _cmdType;
		string _symbol;
		string _dest;
		string _comp;
		string _jump;
		
		DestinationMapper& dest_mnemonics;
		CompMapper& comp_mnemonics;
		JumpMapper& jump_mnemonics;

		int _pos;
		int _lineNum;			// the line number in 
								// the .asm file

		void skipWhitespace();
							// advance _pos till a non-ws char
		string extractSymbol();
		void handleComment();
		void handleACommand();
		void handleCCommand();
		void handleLCommand();

	public:
		Parser(ifstream& f, DestinationMapper& dm, 
			CompMapper& cm, JumpMapper& jm) 
			:_in(f), dest_mnemonics(dm), comp_mnemonics(cm),
			 jump_mnemonics(jm), _pos(0), _lineNum(0) {}
		~Parser();
		bool hasMoreCommands();
		void advance();
		CommandType commandType();
		string symbol();
		string dest();
		string comp();
		string jump();
		// for debugging.
		string getCurrentLine() { return _currLine; }
};

}
}
}

#endif