#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include "MIPS.h"
#include "fileRead.h"

int main(){
	int repeat = 1;
	while (repeat == 1){
		//This part of the code takes input and output file names
		string inputFile, outputFile;
		cout << "Please enter the name of the input file: ";
		//inputFile = "input.txt"; 
		cin >> inputFile;
		//cout << "Please enter the name of the output file: " << endl; 
		//cin >> outputFile;

		MIPS processor;

		//This function reads the input file
		fileRead(inputFile, &processor);

		//MIPS
		codeNode* curCode;
		curCode = processor.getCodeHead();
		int linesExecuted = 1;
		int instructionSubCount = 1;

		ofstream output;
		output.open("output.txt");

		while (curCode != NULL) {
			//FETCH
			processor.Fetch(curCode);
			output << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
			cout << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
			instructionSubCount++;
			//DECODE
			processor.Decode();
			output << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
			cout << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
			instructionSubCount++;
			//EXECUTE
			processor.Execute(curCode);
			output << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
			cout << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
			instructionSubCount++;
			//MEMORY ACCESS
			if (processor.getDoMEM()) {
				processor.memAccess();
				output << "C#" << instructionSubCount << " I" << linesExecuted << "-MEM" << endl;
				cout << "C#" << instructionSubCount << " I" << linesExecuted << "-MEM" << endl;
				instructionSubCount++;
			}

			//WRITE BACK
			if (processor.getDoWB()) {
				processor.writeBack();
				output << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
				cout << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
				instructionSubCount++;
			}

			curCode = processor.getCodeHead();
			linesExecuted++;
			curCode = curCode->next;
		}

		processor.printRegisterList(output);
		processor.printMemoryList(output);
		output.close();

		//This part of the code checks if the user would like to run the program again
		char runAgain;
		int notValid = 1;
		cout << "Would you like to run the MIPS Unpiplined Processor Simulator again? (Y/N): ";
		cin >> runAgain;
		cout << endl;
		while (notValid == 1){
			if (runAgain == 'Y'){
				repeat = 1;
				notValid = 0;
			}
			else if (runAgain == 'N'){
				repeat = 0;
				notValid = 0;
			}
			else{
				cout << "Invalid Input, please try agian. (Y/N): ";
				cin >> runAgain;
			}
		}
	}
}