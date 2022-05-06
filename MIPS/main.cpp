#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include "MIPS.h"
#include "fileRead.h"

int main() {
	int repeat = 1; 
	// The simulation repeats as long as "repeat" is 1.
	while (repeat == 1) {
		//This part of the code takes input and output file names form the user
		string inputFile, outputFile;
		cout << "Please enter the name of the input file: ";
		cin >> inputFile;
		cout << "Please enter the name of the output file: "; 
		cin >> outputFile;

		MIPS processor; // Declaration MIPS object class.
		processor.initRegisters(); // Initializes the registers contents (int array Reg); see function description in MIPS.cpp
		processor.initMemory();    // Initializes the memory locations and contents (struct array Mem); see function description in MIPS.cpp

		// This function reads the input file and sets the initial contents of the registers, memory, and the instruction lines listed in the file into the Reg, Mem, and Code MIPS data members.
		// See function full description in fileRead.h 
		fileRead(inputFile, &processor);

		//MIPS
		int codeIndex = 0;      // Initial codeIndex corresponding to the Program Counter (PC) of the processor
		int linesExecuted = 1;
		int instructionSubCount = 1;

		// Creates an ofstream object and opens the output file "outputFile" for writing.
		ofstream output;
		output.open(outputFile);

		while (!(processor.getCodeLine(codeIndex).empty())) {   // Processor executes as long as there are instructions remaining as indicated by the program counter (PC)
			processor.setLineIndex(codeIndex);              
			//FETCH
			processor.Fetch(codeIndex); // See full description in MIPS.cpp
			output << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
			cout << "C#" << instructionSubCount << " I" << linesExecuted << "-IF" << endl;
			instructionSubCount++;
			//DECODE
			processor.Decode(); // See full description in MIPS.cpp
			output << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
			cout << "C#" << instructionSubCount << " I" << linesExecuted << "-ID" << endl;
			instructionSubCount++;
			//EXECUTE
			processor.Execute(); // See full description in MIPS.cpp
			output << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
			cout << "C#" << instructionSubCount << " I" << linesExecuted << "-EX" << endl;
			instructionSubCount++;
			//MEMORY ACCESS
			if (processor.getDoMEM()) {   // If control line MemRead (doMEM) asserrts true, the Memory Access stage is executed.
				processor.memAccess();    // See full description in MIPS.cpp
				output << "C#" << instructionSubCount << " I" << linesExecuted << "-MEM" << endl;
				cout << "C#" << instructionSubCount << " I" << linesExecuted << "-MEM" << endl;
				instructionSubCount++;
			}

			//WRITE BACK
			if (processor.getDoWB()) {  // If (doMEM) asserrts true, the Write Back stage is executed.
				processor.writeBack();   // See full description in MIPS.cpp
				output << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
				cout << "C#" << instructionSubCount << " I" << linesExecuted << "-WB" << endl;
				instructionSubCount++;
			}

			codeIndex = processor.getLineIndex();  // Updates the PC for any changes.
			codeIndex++;                           // Increments the PC.
			linesExecuted++;
		}

		processor.printRegisterList(output);       
		processor.printMemoryList(output); 
		output.close(); 

		//This part of the code checks if the user would like to run the program again
		string runAgain;
		int notValid = 1;
		cout << "Would you like to run the MIPS Unpiplined Processor Simulator again? (Yes/No): ";
		cin >> runAgain;
		cout << endl;
		while (notValid == 1) {
			if (runAgain == "Yes") {
				repeat = 1;
				notValid = 0;
			}
			else if (runAgain == "No") {
				repeat = 0;
				notValid = 0;
			}
			else {
				cout << "Invalid Input, please try agian. (Yes/No): ";
				cin >> runAgain;
			}
		}
	}
}
