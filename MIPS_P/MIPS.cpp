#include <iostream>
#include <stdio.h>
#include <string>
#include "MIPS.h"
using namespace std;

void MIPS::appendRegisterNode(int regNum, int regData) {
    registerNode* curNode, * newNode;
    newNode = new registerNode;
    newNode->registerNum = regNum;
    newNode->registerData = regData;
    newNode->next = NULL;
    if (registerHead == NULL) {
        registerHead = newNode;
    }
    else {
        curNode = registerHead;
        while (curNode->next != NULL) {
            curNode = curNode->next;
        }
        curNode->next = newNode;
    }
};

void MIPS::appendMemoryNode(int memLoc, int memData) {
    memoryNode* curNode, * newNode;
    newNode = new memoryNode;
    newNode->memoryLocation = memLoc;
    newNode->memoryData = memData;
    newNode->next = NULL;
    if (memoryHead == NULL) {
        memoryHead = newNode;
    }
    else {
        curNode = memoryHead;
        while (curNode->next != NULL) {
            curNode = curNode->next;
        }
        curNode->next = newNode;
    }
};

void MIPS::appendCodeNode(string codeLine){
    codeNode* curNode, * newNode;
    newNode = new codeNode;
    newNode->binaryCode = codeLine;
    newNode->next = NULL;
    if (codeHead == NULL){
        codeHead = newNode;
    }
    else{
        curNode = codeHead;
        while (curNode->next != NULL){
            curNode = curNode->next;
        }
        curNode->next = newNode;
    }
};

void MIPS::Fetch(codeNode *curNode) {
    codeLine = curNode->binaryCode;
};

void MIPS::Decode() {
    string opcode_b, sourceRegister_b, targetRegister_b, destinationRegister_b, shiftAmount_b, function_b, offset_b;
    for (int i = 0; i < 6; i++) {
        opcode_b += codeLine[i];
    }
    opcodeNum = binaryStrToInt(opcode_b);

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
}

void MIPS::Execute(codeNode* curNode) {
    // R-TYPE
    if (opcodeNum == 0) {
        if (functionNum == 32) {
            //function to be carried out is addition (add)
            add(sourceRegisterNum, targetRegisterNum, destinationRegisterNum);
            doMEM = false;
            doWB = true;
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
            offsetNum = offsetNum - 2*(32768);
        }
        //call addI function
        addI(sourceRegisterNum, destinationRegisterNum, offsetNum);
        doMEM = false;
        doWB = true;
    }
    else if (opcodeNum == 4) {
        //call beq function
        branchEqual(&curNode);
        doMEM = false;
        doWB = false;
    }
    else if (opcodeNum == 5) {
        //call bne function
        branchNotEqual(&curNode);
        doMEM = false;
        doWB = false;
    }
    codeHead = curNode;
};

void MIPS::memAccess() {
    memoryNode* curMemory = memoryHead;

    if (doMEM == true) {
        while (curMemory != NULL) {
            if (curMemory->memoryLocation == memLocation) {
                memoryExists = true;
                if (doWB == false) {
                    curMemory->memoryData = destinationContent;
                    break;
                }
                else {
                    destinationContent = curMemory->memoryData;
                    break;
                }
            }
            curMemory = curMemory->next;
        }
        if (memoryExists == false) {
            appendMemoryNode(memLocation, destinationContent);
        }
    }
    else {
        // Instruction does not access memory
    }
};

void MIPS::writeBack() {
    registerNode* curRegister;
    if (doWB == true) {
        if (destinationExists == true) {
            curRegister = registerHead;
            while (curRegister != NULL) {
                if (curRegister->registerNum == destinationRegisterNum) {
                    curRegister->registerData = destinationContent;
                    break;
                }
                curRegister = curRegister->next;
            }
        }
        else {
            //destination does not exist, create and place accordingly
            appendRegisterNode(destinationRegisterNum, destinationContent);
        }
    }
};

void MIPS::printRegisterList() {
    registerNode* curNode;
    curNode = registerHead;
    sortRegisters(curNode);
    cout << "REGISTERS" << endl;
    while (curNode != NULL) {
        cout << "R" << curNode->registerNum << " " << curNode->registerData << endl;
        curNode = curNode->next;
    }
};

void MIPS::printMemoryList() {
    memoryNode* curNode;
    curNode = memoryHead;
    sortMemory(curNode);
    cout << "MEMORY" << endl;
    while (curNode != NULL) {
        cout << curNode->memoryLocation << " " << curNode->memoryData << endl;
        curNode = curNode->next;
    }
};

void MIPS::printCodeList() {
    codeNode* curNode;
    curNode = codeHead;
    while (curNode != NULL) {
        cout << curNode->binaryCode << endl;
        curNode = curNode->next;
    }
};

void MIPS::add(int sourceRegister, int targetRegister, int destinationRegister) {
    destinationExists = false;
    registerNode* curRegister = registerHead;
    
    while (curRegister != NULL){
        if (curRegister->registerNum == sourceRegister){
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == targetRegister){
            targetContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegister){
            destinationExists = true;
        }
        curRegister = curRegister->next;
    }
    destinationContent = sourceContent + targetContent;
};

void MIPS::sub(int sourceRegister, int targetRegister, int destinationRegister) {
    destinationExists = false;
    registerNode* curRegister = registerHead;

    while (curRegister != NULL){
        if (curRegister->registerNum == sourceRegister){
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == targetRegister){
            targetContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegister){
            destinationExists = true;
        }
        curRegister = curRegister->next;
    }
    destinationContent = sourceContent - targetContent;
};

void MIPS::slt(int sourceRegister, int targetRegister, int destinationRegister) {
    destinationExists = false;
    registerNode* curRegister = registerHead;

    while (curRegister != NULL) {
        if (curRegister->registerNum == sourceRegister) {
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == targetRegister) {
            targetContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegister) {
            destinationExists = true;
        }
        curRegister = curRegister -> next;
    }
    if (sourceContent < targetContent){
        destinationContent = 0;
    }
    else{
        destinationContent = 1;
    }
};

void MIPS::loadWord(int sourceRegister, int destinationRegister, int offset) {
    //need to access memory list here
    destinationExists = false;
    registerNode* curRegister = registerHead;
    //memoryNode* curMemory = memoryHead;
    while (curRegister != NULL){
        if (curRegister->registerNum == sourceRegister){
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegister){
            destinationExists = true;
        }
        curRegister = curRegister->next;
    }
    memLocation = sourceContent + offset;
};

void MIPS::storeWord(int sourceRegister, int destinationRegister, int offset) {
    bool memoryExists = false;
    registerNode* curRegister = registerHead;
    //memoryNode* cuMemory = memoryHead;
    while (curRegister != NULL)
    {
        if (curRegister->registerNum == sourceRegister)
        {
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegister)
        {
            destinationContent = curRegister->registerData;
        }
        curRegister = curRegister->next;
    }
    memLocation = offset + sourceContent;
};

void MIPS::branchEqual(codeNode** codeL) {
    registerNode* curRegister = registerHead;
    while (curRegister != NULL) {
        if (curRegister->registerNum == sourceRegisterNum) {
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegisterNum) {
            destinationContent = curRegister->registerData;
        }
        curRegister = curRegister->next;
    }
    if (sourceContent == destinationContent) {
        for (int i = 0; i < offsetNum; i++) {
            *codeL = (*codeL)->next;
        }
    }
};

void MIPS::branchNotEqual(codeNode** codeL) {
    registerNode* curRegister = registerHead;
    while (curRegister != NULL){
        if (curRegister->registerNum == sourceRegisterNum){
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegisterNum){
            destinationContent = curRegister->registerData;
        }
        curRegister = curRegister->next;
    }
    if (sourceContent != destinationContent){
        for (int i = 0; i < offsetNum; i++){
            *codeL = (*codeL)->next;
        }
    }
};

void MIPS::addI(int sourceRegister, int destinationRegister, int immediate) {
    destinationExists = false;
    registerNode* curRegister = registerHead;
    while (curRegister != NULL){
        if (curRegister->registerNum == sourceRegister){
            sourceContent = curRegister->registerData;
        }
        if (curRegister->registerNum == destinationRegister){
            destinationExists = true;
        }
        curRegister = curRegister->next;
    }
    destinationContent = sourceContent + immediate;
};

void MIPS::sortRegisters(registerNode* start) {
    int swapped, i;
    struct registerNode* ptr1;
    struct registerNode* lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;
    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->registerNum > ptr1->next->registerNum) {
                swapRegister(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
};

void MIPS::sortMemory(memoryNode* start) {
    int swapped, i;
    struct memoryNode* ptr1;
    struct memoryNode* lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;
    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->memoryLocation > ptr1->next->memoryLocation) {
                swapMemory(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
};

int strToInt(string number) {
    int stringSize = number.size();
    int returnVal = 0;
    for (int i = 0; i < stringSize; i++){
        returnVal += (number[i] - 48) * pow(10, (stringSize - i - 1));
    }
    return returnVal;
}

int binaryStrToInt(string number)
{
    int stringSize = number.size();
    int returnVal = 0;
    for (int i = 0; i < stringSize; i++){
        returnVal += (number[i] - 48) * pow(2, (stringSize - i - 1));
    }
    return returnVal;
}

void swapRegister(registerNode* a, registerNode* b) {
    int temp = a->registerNum;
    int temp2 = a->registerData;
    a->registerNum = b->registerNum;
    a->registerData = b->registerData;
    b->registerNum = temp;
    b->registerData = temp2;
};

void swapMemory(memoryNode* a, memoryNode* b){
    int temp = a->memoryLocation;
    int temp2 = a->memoryData;
    a->memoryLocation = b->memoryLocation;
    a->memoryData = b->memoryData;
    b->memoryLocation = temp;
    b->memoryData = temp2;
};