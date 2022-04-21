#include <iostream>
using namespace std;
#include <string>
#include<math.h>

int main() {
//after reading the file, we can assign each register value in a R array 
  int R[32];

  // R type Rs Rn adn Rd in the code
  int Rs[5];
  int Rn[5];
  int Rd[5];
  //Rt and imm for I type
  int Rt[5];
  int imm[16];
  
  //show decimal value after convert binary to decimal 
  int Rs_decimal; 
  int Rn_decimal;
  int Rd_decimal;
  int Rt_decimal;
  int imm_decimal;

  //varible that outputs R type regsitor value after insturction
  int Rd_finalValue;
  //varible that outputs I type regsitor value after insturction
  int Rt_finalValue;

  

  
  //code instruction 32 bits;
  char code[32];

  //read code;
  for (int i=0;i<32;i++){
    cin >>code[i];
  }
  

  // determin if it is R-type */

  if(code[0]=='0' && code[1]=='0' && code[2]=='0' && code[3]=='0' && code[4]=='0' && code[5]=='0'){
    
    //determin Rs Rn and Rd
    for(int i=0;i<5;i++){
        Rs[i]=code[i+6]-48;
    }
    Rs_decimal= 16*Rs[0]+8*Rs[1]+4*Rs[2]+2*Rs[3]+1*Rs[4];

    
    for(int i=0;i<5;i++){
        Rn[i]=code[i+11]-48;
    }
    Rn_decimal= 16*Rn[0]+8*Rn[1]+4*Rn[2]+2*Rn[3]+1*Rn[4];


    for(int i=0;i<5;i++){
        Rd[i]=code[i+16]-48;
    }
    Rd_decimal= 16*Rd[0]+8*Rd[1]+4*Rd[2]+2*Rd[3]+1*Rd[4];

    
    // determin if it is ******Addtion*****   (add)
    
    if (code[26]=='1'&& code[27]=='0'&& code[28]=='0'&& code[29]=='0'&& code[30]=='0'&& code[31]=='0'){
      Rd_finalValue= R[Rs_decimal]+R[Rn_decimal];
    }

    // if it is ***** subtraction *****    (sub)

    if (code[26]=='1'&& code[27]=='0'&& code[28]=='0'&& code[29]=='0'&& code[30]=='1'&& code[31]=='0'){
      Rd_finalValue= R[Rs_decimal]-R[Rn_decimal];
    }
  
  }


//************************************************************


  


  // determin if it is ******I-type ADDI or SUBI**********  (addi)
  
if(code[0]=='0' && code[1]=='0' && code[2]=='1' && code[3]=='0' && code[4]=='0' && code[5]=='0'){
  
  //determin Rs  Rt and imm
  for(int i=0;i<5;i++){
        Rs[i]=code[i+6]-48;
    }
    Rs_decimal= 16*Rs[0]+8*Rs[1]+4*Rs[2]+2*Rs[3]+1*Rs[4];

  
   for(int i=0;i<5;i++){
        Rt[i]=code[i+11]-48;
    }
    Rt_decimal= 1*Rt[0]+2*Rt[1]+4*Rt[2]+8*Rt[3]+16*Rt[4];

  
  for(int i=0;i<16;i++){
        imm[i]=code[i+16]-48;
    }
  
  if(imm[0]==0){ //that means it adds a possitave num
    imm_decimal= pow(2,15)*imm[0]+pow(2,14)*imm[1]+pow(2,13)*imm[2]+pow(2,12)*imm[3]+pow(2,11)*imm[4]+pow(2,10)*imm[5]+pow(2,9)*imm[6]+pow(2,8)*imm[7]+pow(2,7)*imm[8]+pow(2,6)*imm[9]+pow(2,5)*imm[10]+pow(2,4)*imm[11]+pow(2,3)*imm[12]+pow(2,2)*imm[13]+pow(2,1)*imm[14]+1*imm[15];
      }
  
  if(imm[0]==1){ //that means it adds a negative num
    imm_decimal= pow(2,14)*imm[1]+pow(2,13)*imm[2]+pow(2,12)*imm[3]+pow(2,11)*imm[4]+pow(2,10)*imm[5]+pow(2,9)*imm[6]+pow(2,8)*imm[7]+pow(2,7)*imm[8]+pow(2,6)*imm[9]+pow(2,5)*imm[10]+pow(2,4)*imm[11]+pow(2,3)*imm[12]+pow(2,2)*imm[13]+pow(2,1)*imm[14]+1*imm[15]-pow(2,15);
      }

  Rt_finalValue=R[Rs_decimal]+imm_decimal;

  

  }
  return 0;  
}