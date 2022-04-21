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
    
    string filename; // holds name of input file

    bool running = true;
    while(running){
        
    // collect input file
    cout<<"Enter the input file name\n";
    cin>>filename;
    fileRead(filename);
        
        //process code

        //generate output line

        if(running){ //check if user wants to run program again

        }
        //user doesn't wanna run program
        running = false;
    }
    
}




//Fetch

//Decode

//Execute

//Memory

//Write Back

