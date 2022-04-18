#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <stdint.h>

//32-bit registers
//32 bits is 4 bytes
//1 byte is 8 bits

//references: lect 4 & 5 ppts

#define NUMREGISTERS 32

struct register{
    string name;
    string usage;
    //int32_t number; //Register number is the index of the register in the register_block
    int32_t data;
};
typedef struct register registerType;

registerType register_block[NUMREGISTERS];
//#0 Constant 0
//#1 Reserved for assembler
//#2-#3 expression evaluation and results
//#4-#7 arguments
//#8-#15 temporary registers
//#16-#23 saved temporary
//#24-#25 temporary registers
//#26-#27 reserved for os kernel
//#28 Pointer to global area
//#29 Stack Pointer
//#30 Frame pointer
//#31 Return address (used by function call)




void Init_Registers(void) {
    register_block[0].name = "zero";
    register_block[0].usage = "Constant 0";
    register_block[0].data = 0;

    register_block[1].name = "at";
    register_block[1].usage = "Reserved for assembler";
    register_block[1].data = 0;

    register_block[2].name = "v0";
    register_block[2].usage = "Expression evaluation";
    register_block[2].data = 0;

    register_block[3].name = "v1";
    register_block[3].usage = "results of a function";
    register_block[3].data = 0;

    register_block[4].name = "Argument 1";
    register_block[4].usage = "a0";
    register_block[4].data = 0;

    register_block[5].name = "Argument 2";
    register_block[5].usage = "a1";
    register_block[5].data = 0;

    register_block[6].name = "Argument 3";
    register_block[6].usage = "a2";
    register_block[6].data = 0;

    register_block[7].name = "Argument 4";
    register_block[7].usage = "a3";
    register_block[7].data = 0;

    register_block[8].name = "t0";
    register_block[8].usage = "Temporary (not preserved across call)";
    register_block[8].data = 0;

    register_block[9].name = "t1";
    register_block[9].usage = "Temporary (not preserved across call)";
    register_block[9].data = 0;

    register_block[10].name = "t2";
    register_block[10].usage = "Temporary (not preserved across call)";
    register_block[10].data = 0;

    register_block[11].name = "t3";
    register_block[11].usage = "Temporary (not preserved across call)";
    register_block[11].data = 0;

    register_block[12].name = "t4";
    register_block[12].usage = "Temporary (not preserved across call)";
    register_block[12].data = 0;

    register_block[13].name = "t5";
    register_block[13].usage = "Temporary (not preserved across call)";
    register_block[13].data = 0;

    register_block[14].name = "t6";
    register_block[14].usage = "Temporary (not preserved across call)";
    register_block[14].data = 0;

    register_block[15].name = "t7";
    register_block[15].usage = "Temporary (not preserved across call)";
    register_block[15].data = 0;

    register_block[16].name = "s0";
    register_block[16].usage = "Saved temporary (preserved across call)";
    register_block[16].data = 0;

    register_block[17].name = "s1";
    register_block[17].usage = "Saved temporary (preserved across call)";
    register_block[17].data = 0;

    register_block[18].name = "s2";
    register_block[18].usage = "Saved temporary (preserved across call)";
    register_block[18].data = 0;

    register_block[19].name = "s3";
    register_block[19].usage = "Saved temporary (preserved across call)";
    register_block[19].data = 0;

    register_block[20].name = "s4";
    register_block[20].usage = "Saved temporary (preserved across call)";
    register_block[20].data = 0;

    register_block[21].name = "s5";
    register_block[21].usage = "Saved temporary (preserved across call)";
    register_block[21].data = 0;

    register_block[22].name = "s6";
    register_block[22].usage = "Saved temporary (preserved across call)";
    register_block[22].data = 0;

    register_block[23].name = "s7";
    register_block[23].usage = "Saved temporary (preserved across call)";
    register_block[23].data = 0;

    register_block[24].name = "t8";
    register_block[24].usage = "Temporary (not preserved across call)";
    register_block[24].data = 0;

    register_block[25].name = "t9";
    register_block[25].usage = "Temporary (not preserved across call)";
    register_block[25].data = 0;

    register_block[26].name = "k0";
    register_block[26].usage = "Reserved for OS kernel";
    register_block[26].data = 0;

    register_block[27].name = "k1";
    register_block[27].usage = "Reserved for OS kernel";
    register_block[27].data = 0;

    register_block[28].name = "gp";
    register_block[28].usage = "Pointer to global area";
    register_block[28].data = 0;

    register_block[29].name = "sp";
    register_block[29].usage = "Stack pointer";
    register_block[29].data = 0;

    register_block[30].name = "fp";
    register_block[30].usage = "Frame pointer";
    register_block[30].data = 0;

    register_block[31].name = "ra";
    register_block[31].usage = "Return address (used by function call)";
    register_block[31].data = 0;

}


// problem originates with the source register. The target register modifies the source register. The result of the modification is stored in the destination register


///// For use in external arithmetic functions

//read register
// takes register number and returns register data

int32_t readRegister(int32_t regNum) {
    return register_block[regNum].data;
}

//write register
// takes data writes it into the intended register

void writeRegister(int32_t destRegNum, int32_t data) {
    register_block[destRegNum].data = data;
}

//////



///// For use in data transfers functions

//register to register data transfer
//vars: destinationregister sourceregister targetregister

void lwFromRegister(destRegNum, srcRegNum){
    register_block[destRegNum].data = register_block[srcRegNum].data;
}


/////////////WIP

//register to memory data transfer
//vars: memorylocation sourceregister targetregister

void lwFromMemory(destRegNum, srcRegNum) {
    //register_block[destRegNum].data = register_block[srcRegNum].data;
}