// This function made by Kyle Ramsey

int fileRead(string filename){
    
    string line;    // holds read in line
    ifstream inFile; // file object
    inFile.open(filename);  // opens file
    
    inFile>>line;   // reads in a single line of file as a string, delimits with spaces or line return, will be used a lot
    
    if(line.compare("REGISTERS")==0){   // this creates a string with registers names and values
        inFile>>line;
        while(line.compare("MEMORY")!=0){   // this will end when it comes across the memory section
            regData = regData.append(line); //adds each line to register string
            regData = regData.append(" ");
            inFile>>line;
        }
        //cout<<regData<<endl;
    }
    
    if(line.compare("MEMORY")==0){  // creates string to hold memory values
        inFile>>line;
        while(line.compare("CODE")!=0){ // ends at code section
            memData = memData.append(line);
            memData = memData.append(" ");
            inFile>>line;
        }
        //cout<<memData<<endl;
    }
    if(line.compare("CODE")==0){    // creates a string of 32 bit code instructions
        inFile>>line;
        while(!inFile.eof()){       // ends at end of file or eof
            codeData = codeData.append(line);
            codeData = codeData.append(" ");
            inFile>>line;
        }
        //cout<<codeData<<endl;
    }

        inFile.close(); // closes file
    
    
    return 1;
}
