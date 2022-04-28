#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void fileRead(string inputFile, MIPS* processor) {
	ifstream ils(inputFile);
	int indicator = 0, regCount, memoryCount, codeCount;
	string line;

	while (getline(ils, line)){
		// check for the text line "REGISTERS" 
		if (line == "REGISTERS"){
			indicator = 1;
			regCount = 0;
		}
		// check for the text line "MEMORY"
		else if (line == "MEMORY"){
			indicator = 2;
			memoryCount = 0;
		}
		// check for the text line "CODE"
		else if (line == "CODE"){
			indicator = 3;
			codeCount = 0;
		}

		// Parses the string lines followed by the word "REGISTERS" and stores the register by number and content into the registerNode;
		if( indicator == 1){
		    string regNum, regCont;
			int changeStringFlag = 0;
			for (int i = 0; i < line.size(); i++){
				if (regCount != 0){
					if (line[i] == ' '){
						changeStringFlag = 1;
					}
					if (changeStringFlag == 0){
						if (line[i] != 'R'){
							regNum += line[i];
						}
					}
					else{
						if (line[i] != ' '){
							regCont += line[i];
						}
					}
				}
			}
			if (regCount != 0){
				int regNumber = strToInt(regNum);
				int regContent = strToInt(regCont);
				processor->appendRegisterNode(regNumber, regContent);
			}
			regCount++;
		}

		// Parses the string lines followed by the word "MEMORY" and stores the value and adress into the memoryNode (memory)
		else if (indicator == 2){
			string memNum, memCont;
			int lineSize = line.size();
			int changeStringFlag = 0;
			for (int i = 0; i < line.size(); i++){
				if (line[i] == ' '){
					changeStringFlag = 1;
				}
				if (changeStringFlag == 0){
					memNum += line[i];
				}
				else{
					if (line[i] != ' '){
						memCont += line[i];
					}
				}
			}
			if (memoryCount != 0){
				int memNumber = strToInt(memNum);
				int memContent = strToInt(memCont);
				processor->appendMemoryNode(memNumber, memContent);
			}
			memoryCount++;
		}

		// Parses the code string lines followed by the word "CODE" and stores the strings into the codeNode;
		else if (indicator == 3){
			if (codeCount != 0){
				processor->appendCodeNode(line);
			}
			codeCount++;
		}
	}
}
