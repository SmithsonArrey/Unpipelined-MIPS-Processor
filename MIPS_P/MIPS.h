//#pragma once
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

struct registerNode{
	int registerNum, registerData;
	registerNode* next;
};

struct memoryNode{
	int memoryLocation, memoryData;
	memoryNode* next;
};

struct codeNode{
	string binaryCode;
	codeNode* next;
};

class MIPS{

private:
	registerNode* registerHead = NULL;
	memoryNode* memoryHead = NULL;
	codeNode* codeHead = NULL;
	string codeLine;
	int opcodeNum, sourceRegisterNum, targetRegisterNum, destinationRegisterNum, shiftAmountNum, functionNum, offsetNum;
	int destinationContent, destinationExists, sourceContent, targetContent, memLocation, memoryExists;
	bool doMEM, doWB;

public:
	// Unpipelined MIPs Stages
	void Fetch(codeNode* curNode);
	void Decode();
	void Execute(codeNode* curNode);
	void memAccess();
	void writeBack();

	// MIPS Instructions
	void add(int sourceRegister, int targetRegister, int destinationRegister);
	void sub(int sourceRegister, int targetRegister, int destinationRegister);
	void slt(int sourceRegister, int targetRegister, int destinationRegister);
	void addI(int sourceRegister, int destinationRegister, int immediate);
	void loadWord(int sourceRegister, int destinationRegister, int offset);
	void storeWord(int sourceRegister, int destinationRegister, int offset);
	void branchEqual(codeNode** curNode);
	void branchNotEqual(codeNode** curNode);

	// Helper Functions
	void printRegisterList();
	void printMemoryList();
	void printCodeList();
	void appendRegisterNode(int regNum, int regData);
	void appendMemoryNode(int memLocation, int memData);
	void appendCodeNode(string codeLine);
	void sortRegisters(registerNode* start);
	void sortMemory(memoryNode* start);
	codeNode* getCodeHead() { return codeHead;}
	bool getDoMEM() { return doMEM; }
	bool getDoWB() { return doWB; }
};

int strToInt(string number);
int binaryStrToInt(string number);
void swapRegister(registerNode* a, registerNode* b);
void swapMemory(memoryNode* a, memoryNode* b);

