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

int main(int argc, char** argv) {
    
    string inputFile, outputFile; // holds name of input and output files

    bool running = true;
    while(running){
        
    // collect input and output file
    cout<< "Enter the input file name" << endl;
    cin>> inputFile;
      //cout << "Enter the output file name" << endl;
      //cin >> outputFile;
    fileRead(filename);
        
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
		    cout << "Invalid Input, please try agian. (Y/N): ";
			cin >> runAgain;
        }
    }
    
}
