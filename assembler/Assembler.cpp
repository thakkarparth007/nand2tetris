#include "./Parser.h"
#include "./C_Commands.h"
#include "./Errors.h"
#include "./SymbolTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace parth::nand2tetris::assembler;
using namespace std;

int main(int argc, char** argv) {
	string input_name;

	if(argc != 2) {
		cout << "Error. Expected exactly one argument: "
			 << "The name of the file.\n";
		cout << "Do you wish to enter the file name here? "
			 << "[Y/N] ";
		char c;
		cin >> c;
		if(c != 'Y' && c != 'y') 
			return 1;

		cout << "Enter the file name: ";
		cin >> input_name;
	}
	else {
		input_name = argv[1];
	}
	ifstream in(input_name.c_str());
	if(!in) {
		cout << "Error. The given file can't be opened. "
			 << "It is either being used, or does not exist."
			 << "\n";
		cout << argv[1] << "\n";
		return 1;
	}

	int ext = input_name.find(".asm");
	if(ext == string::npos) {
		cout << "Error. A '.asm' file expected.\n";
		return 1;
	}

	// first pass
	DestinationMapper dest_mnemonics;
	CompMapper comp_mnemonics;
	JumpMapper jump_mnemonics;

	Parser parser(in, dest_mnemonics, comp_mnemonics,
			jump_mnemonics);
	SymbolTable sym_tab;
	int instruction_count = 0;
	/*
		Maintains the instruction count - only counts the
		A and C commands. Not the L commands.
	*/
	try {
		while(parser.hasMoreCommands()) {
			parser.advance();
			switch(parser.commandType()) {
				/*
					in the first pass, we only intend to find 
					out the labels, so bother only about the
					L-commands.
				*/
				case L_COMMAND:
					sym_tab.addEntry(parser.symbol(), 
									instruction_count);
					break;
				default:
					// don't count L commands
					instruction_count++;
			}
		}
	}
	catch(IllegalCallException& e) {
		cout << e.what() << "\n";
		return 1;
	}
	catch(SyntaxErrorException& e) {
		cout << e.what() << "\n";
		return 1;
	}
	catch(...) {
		cout << "An unknown error occured. Exiting.\n";
		return 1;
	}

	// second pass

	// reset the file used by parser.
	// bad style?
	in.close();
	in.open(input_name.c_str());
	Parser parser2(in, dest_mnemonics, comp_mnemonics,
			jump_mnemonics);

	input_name = input_name.substr(0, ext);
	ofstream out((input_name + ".hack").c_str());
	string sym;
	int reg;			// comp uses 'A' (0) or 'M' (1)?
	int RAM_running_addr = 16;

	/*
		Insert the predefined symbols in the table
	*/
	sym_tab.addEntry("SP", 0);
	sym_tab.addEntry("LCL", 1);
	sym_tab.addEntry("ARG", 2);
	sym_tab.addEntry("THIS", 3);
	sym_tab.addEntry("THIS", 4);
	sym_tab.addEntry("R0", 0);
	sym_tab.addEntry("R1", 1);
	sym_tab.addEntry("R2", 2);
	sym_tab.addEntry("R3", 3);
	sym_tab.addEntry("R4", 4);
	sym_tab.addEntry("R5", 5);
	sym_tab.addEntry("R6", 6);
	sym_tab.addEntry("R7", 7);
	sym_tab.addEntry("R8", 8);
	sym_tab.addEntry("R9", 9);
	sym_tab.addEntry("R10",10);
	sym_tab.addEntry("R11",11);
	sym_tab.addEntry("R12",12);
	sym_tab.addEntry("R13",13);
	sym_tab.addEntry("R14",14);
	sym_tab.addEntry("R15",15);
	sym_tab.addEntry("SCREEN", 16384);
	sym_tab.addEntry("KBD", 24576);


	// don't bother about syntax errors now.
	// but do bother about IllegalCallExceptions.
	try {
		while(parser2.hasMoreCommands()) {
			parser2.advance();
			switch(parser2.commandType()) {
				case A_COMMAND:
					sym = parser2.symbol();
					if(!isdigit(sym[0])) {
						if(sym_tab.contains(sym)) {
							// it's a label
							out << "0" 
								 << sym_tab.getAddress(sym) 
								 << "\n";
						}
						else {
							// it's a variable
							sym_tab.addEntry(sym, RAM_running_addr);
							out << "0" 
								<< sym_tab.formatAsBin(
										RAM_running_addr++
									)
								<< "\n";
						}
					}
					else {
						int constant = 0;
						for(int i = 0; i < sym.size(); i++) {
							constant *= 10;
							constant += sym[i] - '0';
						}
						out << "0"
							 << sym_tab.formatAsBin(constant)
							 << "\n";
					}
					break;
				case C_COMMAND:
					reg = parser2.comp().find("M") 
							!= string::npos 
							? 1 : 0;
					out << "111"
						 << reg
						 << comp_mnemonics
						 		.getBinaryCode(parser2.comp())
						 << dest_mnemonics
						 		.getBinaryCode(parser2.dest())
						 << jump_mnemonics
						 		.getBinaryCode(parser2.jump())
						 << "\n";
					break;
				case L_COMMAND:
					// ignore.
					break;
			}
		}
	}
	catch(IllegalCallException& e) {
		cout << "Illegal Call Exception\n";
		return 0;
	}

	in.close();
	out.close();
	cout << "Done successfully.\n";
	return 0;
}
