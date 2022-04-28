#include <iostream>
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
		cout << "Please enter the name of the output file: " << endl;
		//outputFile = "output.txt"; 
		//cin >> outputFile;

		MIPS processor;

		//This function reads the input file
		fileRead(inputFile, &processor);

		//MIPS
		ofstream ols;
		ols.open(outputFile);
		codeNode* curCode;
		curCode = processor.getCodeHead();
		int linesExecuted = 1;
		int instructionSubCount = 1;

		while (curCode != NULL) {
			//FETCH
			processor.Fetch(curCode);
			cout << "C#" << instructionSubCount++ << " I" << linesExecuted << "-IF" << endl;
			//DECODE
			processor.Decode();
			cout << "C#" << instructionSubCount++ << " I" << linesExecuted << "-ID" << endl;
			//EXECUTE
			processor.Execute(curCode);
			cout << "C#" << instructionSubCount++ << " I" << linesExecuted << "-EX" << endl;

			//MEMORY ACCESS
			if (processor.getDoMEM()) {
				processor.memAccess();
				cout << "C#" << instructionSubCount++ << " I" << linesExecuted << "-MEM" << endl;
			}

			//WRITE BACK
			if (processor.getDoWB()) {
				processor.writeBack();
				cout << "C#" << instructionSubCount++ << " I" << linesExecuted << "-WB" << endl;
			}

			curCode = processor.getCodeHead();
			linesExecuted++;
			curCode = curCode->next;
		}

		processor.printRegisterList();
		processor.printMemoryList();

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

