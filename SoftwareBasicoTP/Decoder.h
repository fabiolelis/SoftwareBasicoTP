//
//  Decoder.h
//  SoftwareBasicoTP
//
//  Created by Fabio Lelis on 02/10/16.
//  Copyright © 2016 Fabio Lelis. All rights reserved.
//

#include <Math.h>

void init_output(char* output[]);
void decode(char** line, char** output, int line_number, int has_label);
void getDecoded(char* instruction, char* op1, char* op2, char* op3,  char* decoded1, char* decoded2);
char* getRegisterToBinary(char* reg);
char* getDecimalToBinary(char* chardec);

void init_output(char* output[]){
    
    for(int i = 0; i < 256; i++){
        output[i] = (char *) malloc(20*sizeof(char));
        strcpy(output[i], "00000000");
    }
}


void decode(char** line, char** output, int line_number, int has_label){
    char* decoded1 = "01010101";
    char* decoded2 = "10101010";

    //printf("line %s %s\n", line[0], line[1]);
    char *instruction, *op1, *op2, *op3;
    instruction = (char *) malloc(20 * sizeof(char));
    op1 = (char *) malloc(20 * sizeof(char));
    op2 = (char *) malloc(20 * sizeof(char));
    op3 = (char *) malloc(20 * sizeof(char));
    strcpy(instruction, line[0+has_label]);
    if(line[1+has_label] != NULL)
        strcpy(op1, line[1+has_label]);
    if(line[2+has_label] != NULL)
        strcpy(op2, line[2+has_label]);
    if(line[3+has_label] != NULL)
        strcpy(op3, line[3+has_label]);
    
    getDecoded(instruction, op1, op2, op3, decoded1, decoded2);
    
    printf("inst %s \n", instruction);
    
    output[2*line_number + 1] = (char *) malloc(20*sizeof(char));
    output[2*line_number] = (char *) malloc(20*sizeof(char));
    strcpy(output[2*line_number], decoded1);
    strcpy(output[2*line_number + 1], decoded2);
    
}

void getDecoded(char* instruction, char* op1, char* op2, char* op3,  char* decoded1, char* decoded2){
    
    char* sixteen_bit_inst = (char *) malloc(20*sizeof(char));
    if(strcmp(instruction, "exit")){
        strcpy(sixteen_bit_inst, "0000000000000000");
    }
    
    if(strcmp(instruction, "loadi") == 0){ //00001 RRR AAAAAAAA
        strcpy(sixteen_bit_inst, "00001"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
    }
    
    if(strcmp(instruction, "storei") == 0){ //00010 RRR AAAAAAAA
        strcpy(sixteen_bit_inst, "00010"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
    }
    
    if(strcmp(instruction, "add") == 0){ //00011 RRR RRR XXXXX
        strcpy(sixteen_bit_inst, "00011"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary("00000")); //5bits
    }
    
    if(strcmp(instruction, "subtract") == 0){ //00100 RRR RRR XXXXX
        strcpy(sixteen_bit_inst, "00100"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary("00000")); //5bits
    }
    
    if(strcmp(instruction, "multiply") == 0){ //00101 RRR RRR XXXXX
        strcpy(sixteen_bit_inst, "00101"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary("00000")); //5bits
    }
    
    if(strcmp(instruction, "divide") == 0){ //00110 RRR RRR XXXXX
        strcpy(sixteen_bit_inst, "00110"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary("00000")); //5bits
    }
    
    if(strcmp(instruction, "jump") == 0){ //00111 000 AAAAAAAA
        strcpy(sixteen_bit_inst, "00111"); //5bits
        strcat(sixteen_bit_inst, "000"); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op1)); //8bits
        
        /*
         TODO: tratar jump label
        */
        
    }
    
    if(strcmp(instruction, "jmpz") == 0){ //00111 000 AAAAAAAA
        strcpy(sixteen_bit_inst, "01000"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
        
        /*
         TODO: tratar jmpz label
         */
    }
    
    if(strcmp(instruction, "jmpn") == 0){ //00111 000 AAAAAAAA
        strcpy(sixteen_bit_inst, "01001"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
        
        /*
         TODO: tratar jmpn label
         */
    }
    
    if(strcmp(instruction, "move") == 0){ //00101 RRR RRR XXXXX
        strcpy(sixteen_bit_inst, "01010"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary("00000")); //5bits
    }
    
    if(strcmp(instruction, "load") == 0){ //00101 RRR RRR XXXXX
        strcpy(sixteen_bit_inst, "01011"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary("00000")); //5bits
    }
    
    if(strcmp(instruction, "store") == 0){ //00101 RRR RRR XXXXX
        strcpy(sixteen_bit_inst, "01100"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary("00000")); //5bits
    }
    
}


char* getRegisterToBinary(char* reg){
    
    if(strcmp(reg, "R0")){
        return "000";
    }
    if(strcmp(reg, "R1")){
        return "001";
    }
    if(strcmp(reg, "R2")){
        return "010";
    }
    if(strcmp(reg, "R3")){
        return "011";
    }
    if(strcmp(reg, "R4")){
        return "100";
    }
    if(strcmp(reg, "R5")){
        return "101";
    }
    if(strcmp(reg, "R6")){
        return "110";
    }
    if(strcmp(reg, "R7")){
        return "111";
    }
    
    return NULL;
}

char* getDecimalToBinary(char* chardec){
    
    char* binary = (char*) malloc(sizeof(char) * 9);
    int dec = atoi(chardec);
    
    int div = 128;
    while(div >= 1){
        if(dec >= div){
            strcat(binary, "1");
            dec = dec - div;
        }
        else
            strcat(binary, "0");
        
        div = div/2;

    }
    
    printf("bin %s\n", binary);
    
    return binary;
}
