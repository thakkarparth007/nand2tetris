This is the code for an assembler made for the HACK platform,
in the nand2tetris course. 

Main file is "Assembler.cpp".
The modules used are:
Parser,
SymbolTable,
C_Commands (the book calls it "Code Module")

Assembler controls all these classes and gets the work done in sync.

Usage: assembler (filename.asm)
Output: generates filename.hack if the code is without any syntax errors

Compilation:
g++ -o assembler Assembler.cpp Parser.cpp C_Commands.cpp Errors.cpp SymbolTable.cpp

Author: Parth Thakkar