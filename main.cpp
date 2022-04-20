#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <fstream>

using namespace std;

int fileRead(string filename); //file read in function
string regData="";  // strings that hold read in of registers, memory, and code
string memData="";
string codeData="";

//DATA DECODING - HELPER FUNCTIONS
int strToInt(string number) {
	int stringSize = number.size();
	int returnVal = 0;
	for (int i = 0; i < stringSize; i++)
	{
		returnVal += (number[i] - 48) * pow(10, (stringSize - i - 1));
	}
	return returnVal;
}

int binaryStrToInt(string number)
{
	int stringSize = number.size();
	int returnVal = 0;
	for (int i = 0; i < stringSize; i++)
	{
		returnVal += (number[i] - 48) * pow(2, (stringSize - i - 1));
	}
	return returnVal;
}

// MAIN FUNCTION
int main(int argc, char** argv) {
    
    string inputFile, outputFile; // holds name of input and output files

    bool running = true;
    while(running){
        
    // collect input file
    cout<< "Enter the input file name" << endl;
    cin>> inputFile;

    fileRead(filename); // reads input file 
	    
    //process code
    //generate output line
        
    //This part of the code checks if the user would like to run the program again
    char runAgain;
    bool notValid = true;
    cout << "Do you want to run the simulation again? (Y/N): ";
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
	    cout << "Invalid Input, please try again. (Y/N): ";
	    cin >> runAgain;
	}
    }
}
