#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

/* 
The fileRead function is responsible for opening and reading the contents of the input text file 
(inputFile), parsing the text line by line, and storing the contents into the appropiate data members 
(registers, memory, code) of the MIPS class referenced as the second parameter of the function. 
*/

void fileRead(string inputFile, MIPS* processor) {
	ifstream ils(inputFile);                                 // Constructs an ifstream object with the file inputFile
	int indicator = 0, regCount, memoryCount, codeCount;     // Flag variables used to identify what section of the input file is being read.
	                                                         // REGISTERS: 1, MEMORY: 2, CODE: 3;
	string line;                                            

	while (getline(ils, line)) {                    //Extracts characters from the ifstream object "ils" and stores them into string "line" until new line is found.
		// check for the text line "REGISTERS" 
		if (line == "REGISTERS") {
			indicator = 1;
			regCount = 0;
		}
		// check for the text line "MEMORY"
		else if (line == "MEMORY") {
			indicator = 2;
			memoryCount = 0;
		}
		// check for the text line "CODE"
		else if (line == "CODE") {
			indicator = 3;
			codeCount = -1;
		}

		// Parses and splits the string lines (character R and blank spaces) followed by the word "REGISTERS" and stores the register's number and content into regNum and regCont.
		if (indicator == 1) {
			string regNum, regCont;
			int changeStringFlag = 0;
			for (int i = 0; i < line.size(); i++) {
				if (regCount != 0) {
					if (line[i] == ' ') {
						changeStringFlag = 1;
					}
					if (changeStringFlag == 0) {
						if (line[i] != 'R') {
							regNum += line[i];
						}
					}
					else {
						if (line[i] != ' ') {
							regCont += line[i];
						}
					}
				}
			}
	    //Converts the register number and content into integers and stores them into register array (Reg), where the index is the number and the content is the data at that index.
			if (regCount != 0) {
				int regNumber = strToInt(regNum);
				int regContent = strToInt(regCont);
				processor->setRegister(regNumber, regContent);
			}
			regCount++;
		}

		// Parses and splits the string lines (blank spaces) followed by the word "REGISTERS" and stores the memory's location and content into memNum and memCont.
		else if (indicator == 2) {
			string memNum, memCont;
			int lineSize = line.size();
			int changeStringFlag = 0;
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == ' ') {
					changeStringFlag = 1;
				}
				if (changeStringFlag == 0) {
					memNum += line[i];
				}
				else {
					if (line[i] != ' ') {
						memCont += line[i];
					}
				}
			}
		//Converts the memory's number and content into integers and stores them into the memory struct array (Mem), where the index is the location divided by 4 and the content is the data at that index.
			if (memoryCount != 0) {
				int memNumber = strToInt(memNum);
				int memContent = strToInt(memCont);
				processor->setMemory(memNumber, memContent);
			}
			memoryCount++;
		}

		// Stores the string lines (instructions in binary) followed by the word "CODE" into the Code array (Code) which acts as a program counter (PC);
		else if (indicator == 3) {
			if (codeCount != -1) {
				processor->setCodeLine(codeCount, line);
			}
			codeCount++;
		}
	}
}
