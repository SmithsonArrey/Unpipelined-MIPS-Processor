//#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

// Struct for grouping the locations and contents of memory cells.
struct MEMORY {
	int memContent;
	int memLocation;
};

class MIPS {

private:
	int Reg[32];            // 32 register initialization
	MEMORY Mem[250];        // 0-249    249*4 = 996
	string Code[250];       // For storing instructions lines and incrementing the program counter (PC)
	string codeLine;
	// MIPS control signals
	int opcodeNum, sourceRegisterNum, targetRegisterNum, destinationRegisterNum, shiftAmountNum, functionNum, offsetNum;
	int destinationContent, destinationExists, sourceContent, targetContent, memLocation, memoryExists, lineIndex;
	bool doMEM, doWB;

public:
	// Unpipelined MIPS' Stages
	void Fetch(int lineNum);
	void Decode();
	void Execute();
	void memAccess();
	void writeBack();

	// MIPS Instructions
	void loadWord(int sourceRegister, int destinationRegister, int offset);
	void storeWord(int sourceRegister, int destinationRegister, int offset);
	void branchEqual();
	void branchNotEqual();
	void add(int sourceRegister, int targetRegister, int destinationRegister);
	void sub(int sourceRegister, int targetRegister, int destinationRegister);
	void slt(int sourceRegister, int targetRegister, int destinationRegister);
	void addI(int sourceRegister, int destinationRegister, int immediate);

	// Helper methods
	void initMemory();
	void initRegisters();
	void setRegister(int regNum, int regData);
	void setMemory(int memNum, int memData);
	int getRegister(int regNum);
	int getMemory(int memNum);
	void setCodeLine(int lineIndex, string lineCode);
	void setLineIndex(int lineIndex);
	string getCodeLine(int lineIndex);
	int getLineIndex();
	bool getDoMEM();
	bool getDoWB();

	void printRegisterList(ofstream& outFile);
	void printMemoryList(ofstream& outFile);
};

// Helper functions
int strToInt(string number);
int binaryStrToInt(string number);
