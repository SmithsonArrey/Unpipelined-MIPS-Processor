#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "MIPS.h"
using namespace std;

////////////////////////////////////////////
///      UNPIPELINED MIPS/RISC STAGES    ///
////////////////////////////////////////////

/* This method performs the Fetch(IF) stage of the MIPS processor.It fetches the instruction bits stored in the "lineNum" to the Decode(ID) stage / method.
lineIndex acts as the program counter(PC) of the processor. */
void MIPS::Fetch(int lineIndex) {
    codeLine = Code[lineIndex];
};

/* This method performs the Decode(ID) stage of the MIPS processor.It reads the IF/ID pipeline to get the instruction bits, decodes the  instruction, identifies if 
the instruction is of I or R type based on its "opcodeNum" and splits the remaining bits into the control signals rs, rt, rd, shamt, and funct for R type instructions
or rs, rd and offset/immediate for I type instructions. */
void MIPS::Decode() {
    string opcode_b, sourceRegister_b, targetRegister_b, destinationRegister_b, shiftAmount_b, function_b, offset_b;
    for (int i = 0; i < 6; i++) {
        opcode_b += codeLine[i];
    }
    opcodeNum = binaryStrToInt(opcode_b);  // opcode_b (string) -> opcodeNum (int)

    if (opcodeNum == 0) {
        //I know the instruction is of R type because opcode is 000000
        for (int i = 6; i < 11; i++) {
            sourceRegister_b += codeLine[i];
        }
        sourceRegisterNum = binaryStrToInt(sourceRegister_b);

        for (int i = 11; i < 16; i++) {
            targetRegister_b += codeLine[i];
        }
        targetRegisterNum = binaryStrToInt(targetRegister_b);

        for (int i = 16; i < 21; i++) {
            destinationRegister_b += codeLine[i];
        }
        destinationRegisterNum = binaryStrToInt(destinationRegister_b);

        for (int i = 21; i < 26; i++) {
            shiftAmount_b += codeLine[i];
        }
        shiftAmountNum = binaryStrToInt(shiftAmount_b);

        for (int i = 26; i < 32; i++) {
            function_b += codeLine[i];
        }
        functionNum = binaryStrToInt(function_b);
    }

    else {
        //I know the instruction is of I type because opcode is not 000000
        for (int i = 6; i < 11; i++) {
            sourceRegister_b += codeLine[i];
        }
        sourceRegisterNum = binaryStrToInt(sourceRegister_b);

        for (int i = 11; i < 16; i++) {
            destinationRegister_b += codeLine[i];
        }
        destinationRegisterNum = binaryStrToInt(destinationRegister_b);

        for (int i = 16; i < 32; i++) {
            offset_b += codeLine[i];
        }
        offsetNum = binaryStrToInt(offset_b);
    }
};

/* This method/stage reads the ID/EX pipeline register to get the values and control signals to execute/call the appropiate MIPS instruction/ALU operation based on its 
"opcodeNum" and/or "fuctionNum". This method is also responsible for determining if a branch should be taken and whether the MEM and/or WB stages should accessed.In case 
of a branch, the targets (PC+4+offset) should be computed. The available ALU operations for calling in this method are: add, sub, slt, lw, sw, addI, bne, and beq. */
void MIPS::Execute() {
    // R-TYPE
    if (opcodeNum == 0) {
        if (functionNum == 32) {
            //function to be carried out is addition (add)
            add(sourceRegisterNum, targetRegisterNum, destinationRegisterNum);
            doMEM = false;  // Do not perfrom MEM stage
            doWB = true;    // Perform WB stage
        }
        else if (functionNum == 34) {
            //function to be carried out is subtraction (sub)
            sub(sourceRegisterNum, targetRegisterNum, destinationRegisterNum);
            doMEM = false;
            doWB = true;
        }
        else if (functionNum == 42) {
            //function to be carried out is set less than (stl)
            slt(sourceRegisterNum, targetRegisterNum, destinationRegisterNum);
            doMEM = false;
            doWB = true;
        }
    }

    // I-TYPE
    else if (opcodeNum == 35) {
        //call loadWord function (lw)
        loadWord(sourceRegisterNum, destinationRegisterNum, offsetNum);
        doMEM = true;
        doWB = true;
    }
    else if (opcodeNum == 43) {
        //call storeWord function (sw)
        storeWord(sourceRegisterNum, destinationRegisterNum, offsetNum);
        doMEM = true;
        doWB = false;
    }
    else if (opcodeNum == 8) {
        //offsetNum is 16-bit signed 
        if (offsetNum > 32767) {
            offsetNum = offsetNum - 2 * (32768);
        }
        //call addI function
        addI(sourceRegisterNum, destinationRegisterNum, offsetNum);
        doMEM = false;
        doWB = true;
    }
    else if (opcodeNum == 4) {
        //call beq function
        branchEqual();
        doMEM = false;
        doWB = false;
    }
    else if (opcodeNum == 5) {
        //call bne function
        branchNotEqual();
        doMEM = false;
        doWB = false;
    }
    //codeHead = curNode;
};

/* This method/stage reads the EX/MEM pipeline register to get the values and control bits to perform memory load/store into the Mem array if needed. */
void MIPS::memAccess() {
    if (doMEM == true) {
            if (Mem[memLocation/4].memContent != NULL) {
                memoryExists = true;
                if (doWB == false) {
                    Mem[memLocation/4].memContent = destinationContent;    // Stores the content of rd into the memory cell Mem[location/4] data member memContent.
                }
                else {
                    destinationContent = Mem[memLocation/4].memContent;    // Loads the memory content into rd of LW.
                }
            }
        if (memoryExists == false) {
            setMemory(memLocation, destinationContent);   // If no value exists in the acessed memory cell, the memory entry is set. 
        }
    }
    else {
        // Instruction does not access memory
    }
};

/* This method reads the MEM/WB pipeline register to get the values and control bits, and selects the value to write into the apporitare register file (Reg) */
void MIPS::writeBack() {
    if (doWB == true) {
        if (destinationExists == true) {
            Reg[destinationRegisterNum] = destinationContent;   // Writes the content of rd into the specified register.
        }
        else {
            //destination does not exist, create and place accordingly
            setRegister(destinationRegisterNum, destinationContent);
        }
    }
};

//////////////////////////////////////////////////
///      MIPS Instructions / ALU Operations    ///
//////////////////////////////////////////////////

/* This method computes the sourceContent (rs) and memLocation (Mem[location/4]) for use in the MEM and WB stages  */
void MIPS::loadWord(int sourceRegister, int destinationRegister, int offset) {
    //need to access memory list here
    destinationExists = false;
 
    sourceContent = Reg[sourceRegister];

    if (Reg[destinationRegister] != NULL) {
        destinationExists = true;
    }

    memLocation = sourceContent + offset;
};

/* This method computes the sourceContent (rs) and memLocation (Mem[location/4]) for use in the MEM stage */
void MIPS::storeWord(int sourceRegister, int destinationRegister, int offset) {
    memoryExists = false;

        sourceContent = Reg[sourceRegister];

        if (Reg[destinationRegister] != NULL){
            destinationContent = Reg[destinationRegister];
        }

    memLocation = sourceContent + offset;
};

/* This method computes the sourceContent (rs) and desitinationRegister (rd) which are compared. If rs and rd are not equal, the lineIndex (PC) is incremented by the offset value.  */
void MIPS::branchNotEqual() {
        sourceContent = Reg[sourceRegisterNum];

        destinationContent = destinationRegisterNum;

    if (sourceContent != destinationContent) {
        for (int i = 0; i < offsetNum; i++) {
            lineIndex++;                          // Increments the lineIndex (PC) by the offset. lineIndex = lineIndex + 4 + offset. The 4(1) is incremented outside this function.
        }
    }
};

/* This method computes the sourceContent (rs) and desitinationRegister (rd) which are compared. If rs and rd are equal, the lineIndex (PC) is incremented by the offset value.  */
void MIPS::branchEqual() {
    sourceContent = Reg[sourceRegisterNum];

    destinationContent = destinationRegisterNum;

    if (sourceContent == destinationContent) {
        for (int i = 0; i < offsetNum; i++) {
            lineIndex++;
        }
    }
};

/* This method computes the sourceContent (rs) and targetRegister (rt) and stores the result of the adittion arithmetic operation of both values into the destinationRegister (rd). */
void MIPS::add(int sourceRegister, int targetRegister, int destinationRegister) {
    destinationExists = false;

    sourceContent = Reg[sourceRegister];
    targetContent = Reg[targetRegister];

    if (destinationRegister < 32) {
        destinationExists = true;
    }

    destinationContent = sourceContent + targetContent;
};


/* This method computes the sourceContent (rs) and targetRegister (rt) and stores the result of substraction arithmetic operation (rs-rt) into the destinationRegister (rd). */
void MIPS::sub(int sourceRegister, int targetRegister, int destinationRegister) {
    destinationExists = false;

    sourceContent = Reg[sourceRegister];
    targetContent = Reg[targetRegister];

    if (destinationRegister < 32) {
        destinationExists = true;
    }

    destinationContent = sourceContent - targetContent;
};

/* This method computes the sourceContent (rs) and targetRegister (rt). If rs < rt, the content of red is set to 0. Else, the content of rd is set to 1. */
void MIPS::slt(int sourceRegister, int targetRegister, int destinationRegister) {
    destinationExists = false;

    sourceContent = Reg[sourceRegister];
    targetContent = Reg[targetRegister];

    if (Reg[destinationRegister] != NULL) {
        destinationExists = true;
    }

    if (sourceContent < targetContent) {
        destinationContent = 0;
    }
    else {
        destinationContent = 1;
    }
};

/* This method computes the sourceContent (rs) and sets the content of the destinationRegister (rd) to rs + offset */
void MIPS::addI(int sourceRegister, int destinationRegister, int immediate) {
    destinationExists = false;

    sourceContent = Reg[sourceRegister];

    if (Reg[destinationRegister] != NULL) {
        destinationExists = true;
    
    }
    destinationContent = sourceContent + immediate;
};

//////////////////////////////////////////////////
///                Helper Methods              ///
//////////////////////////////////////////////////

/* This method initializes all the data members of the struct array "Mem". The "memContent" data member is initialized to 0, and "memLocation" is initialized to increments of 4 starting from 0. */
void MIPS::initMemory() {
    int loc = -4;
    for (int i = 0; i < 250; i++) { // 0, 1, ..., 249.
        loc += 4;
        Mem[i].memLocation = loc;   // 0, 4, ..., 996.
        Mem[i].memContent = 0;      // 0, 0, ..., 0.
    }
};

/* This method initializes all the contents of the int array "Reg" to 0. */
void MIPS::initRegisters() {
    for (int i = 0; i < 32; i++) { // 0, 1, ..., 249.
        Reg[i] = 0;                // 0, 0, ..., 0.
    }
};

/* This method is used to set the int value "regData" into the private data member int array "Reg" at index "regNum". */
void MIPS::setRegister(int regNum, int regData) {
    Reg[regNum] = regData;
};

/* This method is used to set the integers "memNum" and "memData" into the private data member struct array "Mem" at index "memNum/4". */
void MIPS::setMemory(int memNum, int memData) {  // memNum: memory location, memData: memory content
    Mem[memNum/4].memLocation = memNum;   
    Mem[memNum/4].memContent = memData;
};

/* This method is used to set the string "lineCode" into the private data member string array "Code" at index "lineIndex". */
void MIPS::setCodeLine(int lineIndex, string lineCode) {
    Code[lineIndex] = lineCode;
};

void MIPS::setLineIndex(int index) {
    lineIndex = index;
};

/* This method is used get/retrieve the string of the private data member string array "Code" at index "lineIndex". */
string MIPS::getCodeLine(int lineIndex) {
    return Code[lineIndex];
}

/* This method is used get/retrieve the private data member lineIndex (used as PC). */
int MIPS::getLineIndex() {
    return lineIndex;
}; 

/* This method is used get/retrieve the private data member doMEM which is used to assert if the MEM stage/method should be executed for the assigned instruction. */
bool MIPS::getDoMEM() {
    return doMEM;
};

/* This method is used get/retrieve the private data member doWB which is used to assert if the WB stage/method should be executed for the assigned instruction. */
bool MIPS::getDoWB() {
    return doWB;
};

/* This method is used to print all the registers numbers and contents into console and the output file "outFile" */
void MIPS::printRegisterList(ofstream& outFile) {
    cout << "REGISTERS" << endl;
    outFile << "REGISTERS" << endl;
    for (int i = 0; i < 32; i++) {
        if (Reg[i] != NULL) {
            cout << "R" << i << " " << Reg[i] << endl;
            outFile << "R" << i << " " << Reg[i] << endl;
        }
    }
};

/* This method is used to print all the memory locations and contents into console and the output file "outFile" */
void MIPS::printMemoryList(ofstream& outFile) {
    cout << "MEMORY" << endl;
    outFile << "MEMORY" << endl;
    for (int i = 0; i < 250; i++) {
        if (Mem[i].memContent != NULL) {
            cout << Mem[i].memLocation << " " << Mem[i].memContent << endl;
            outFile << Mem[i].memLocation << " " << Mem[i].memContent << endl;
        }
    }
};

//////////////////////////////////////////////////
///                Helper Functions            ///
//////////////////////////////////////////////////

/* This function is used to convert a string numbers (ASCII) into their respective integer value. */
int strToInt(string number) {
    int stringSize = number.size();
    int returnVal = 0;
    for (int i = 0; i < stringSize; i++) {
        returnVal += (number[i] - 48) * pow(10, (stringSize - i - 1));
    }
    return returnVal;
}

/* This function is used to convert a string in binary format (0s and 1s) into an integer. */
int binaryStrToInt(string number){
    int stringSize = number.size();
    int returnVal = 0;
    for (int i = 0; i < stringSize; i++) {
        returnVal += (number[i] - 48) * pow(2, (stringSize - i - 1));
    }
    return returnVal;
}