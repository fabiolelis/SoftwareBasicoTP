//
//  Decoder.h
//  SoftwareBasicoTP
//
//  Created by Fabio Lelis on 02/10/16.
//  Copyright Â© 2016 Fabio Lelis. All rights reserved.
//
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
typedef struct ast_struct AST;

struct ast_struct{
    int line;
    int size;
    int value;
    char* label_name;
};

void init_output(char* output[]);
void decode(char** line, char** output, int line_number, int has_label, AST* ast);
void getDecoded(char* instruction, char* op1, char* op2, char* op3,  char* decoded1, char* decoded2, AST* ast);
char* getRegisterToBinary(char* reg);
char* getDecimalToBinary(char* chardec);
char* getSignedDecimalToBinary(char* chardec);
void splitInTwo(char* sixteen_bit, char* decoded1, char* decoded2);
char *replace(const char *src, const char *from, const char *to);

void init_output(char* output[]){
    
    
    
    for(int i = 0; i < 256; i++){
        output[i] = (char *) malloc(20*sizeof(char));
        strcpy(output[i], "00000000");
    }
}


void decode(char** line, char** output, int line_number, int has_label, AST* ast){
    char *decoded1 = (char *) malloc(8*sizeof(char));
    char *decoded2 = (char *) malloc(8*sizeof(char));
    
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
    
    getDecoded(instruction, op1, op2, op3, decoded1, decoded2, ast);
    
    printf("inst %s \n", instruction);
    
    output[2*line_number + 1] = (char *) malloc(20*sizeof(char));
    output[2*line_number] = (char *) malloc(20*sizeof(char));
    strcpy(output[2*line_number], decoded1);
    strcpy(output[2*line_number + 1], decoded2);
    
}

void getDecoded(char* instruction, char* op1, char* op2, char* op3,  char* decoded1, char* decoded2, AST* ast ){
    
    char* sixteen_bit_inst = (char *) malloc(20*sizeof(char));
    
    strcpy(sixteen_bit_inst, "0000000000000000"); //em caso de instruÃ§Ã£o nÃ£o reconhecida, encerra
    
    if(strcmp(instruction, "exit") == 0){
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
    
    if(strcmp(instruction, "add") == 0){ //00011 RRR RRR 00000
        strcpy(sixteen_bit_inst, "00011"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, "00000"); //5bits
    }
    
    if(strcmp(instruction, "subtract") == 0){ //00100 RRR RRR 00000
        strcpy(sixteen_bit_inst, "00100"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, "00000"); //5bits
    }
    
    if(strcmp(instruction, "multiply") == 0){ //00101 RRR RRR 00000
        strcpy(sixteen_bit_inst, "00101"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, "00000"); //5bits
    }
    
    if(strcmp(instruction, "divide") == 0){ //00110 RRR RRR 00000
        strcpy(sixteen_bit_inst, "00110"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, "00000"); //5bits
    }
    
    if(strcmp(instruction, "jump") == 0){ //00111 000 AAAAAAAA
        strcpy(sixteen_bit_inst, "00111"); //5bits
        strcat(sixteen_bit_inst, "000"); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op1)); //8bits
        
        /*
         TODO: tratar jump label
         */
        
    }
    
    if(strcmp(instruction, "jmpz") == 0){ //01000 RRR AAAAAAAA
        strcpy(sixteen_bit_inst, "01000"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
        
        /*
         TODO: tratar jmpz label
         */
    }
    
    if(strcmp(instruction, "jmpn") == 0){ //01001 000 AAAAAAAA
        strcpy(sixteen_bit_inst, "01001"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
        
        /*
         TODO: tratar jmpn label
         */
    }
    
    if(strcmp(instruction, "move") == 0){ //01010 RRR RRR 00000
        strcpy(sixteen_bit_inst, "01010"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, "00000"); //5bits
    }
    
    if(strcmp(instruction, "load") == 0){ //01011 RRR RRR 00000
        strcpy(sixteen_bit_inst, "01011"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, "00000"); //5bits
    }
    
    if(strcmp(instruction, "store") == 0){ //01100 RRR RRR 00000
        strcpy(sixteen_bit_inst, "01100"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, "00000"); //5bits
    }
    
    if(strcmp(instruction, "loadc") == 0){ //01101 RRR CCCCCCCC
        strcpy(sixteen_bit_inst, "01101"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getSignedDecimalToBinary(op2)); //3bits
    }
    
    if(strcmp(instruction, "moveSp") == 0){ //01110 RRR 00000000
        strcpy(sixteen_bit_inst, "01111"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getSignedDecimalToBinary("00000000")); //8bits
    }
    
    if(strcmp(instruction, "slt") == 0){ //01110 RRR RRR RRR 00
        strcpy(sixteen_bit_inst, "10000"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op3)); //3bits
        strcat(sixteen_bit_inst, "00"); //2bits
    }
    
    if(strcmp(instruction, "call") == 0){ //10001 000 PPPPPPPP
        strcpy(sixteen_bit_inst, "10001"); //5bits
        strcat(sixteen_bit_inst, "000"); //3bits
        
        /*
         TODO: buscar o endereÃ§o do label "op1" na tabela
         */
        strcat(sixteen_bit_inst, getDecimalToBinary(op1)); //8bits
    }
    
    if(strcmp(instruction, "loadSp") == 0){ //10010 RRR AAAAAAAA
        strcpy(sixteen_bit_inst, "10010"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
    }
    
    if(strcmp(instruction, "storeSp") == 0){ //10011 RRR AAAAAAAA
        strcpy(sixteen_bit_inst, "10011"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
    }
    
    if(strcmp(instruction, "ret") == 0){ //10100 00000000000
        strcpy(sixteen_bit_inst, "1010000000000000");
    }
    
    if(strcmp(instruction, "loadRa") == 0){ //10101 000 AAAAAAAA
        strcpy(sixteen_bit_inst, "10101"); //5bits
        strcat(sixteen_bit_inst, "000"); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op1)); //8bits
    }
    
    if(strcmp(instruction, "storeRa")== 0){ //10110 00000000000
        strcpy(sixteen_bit_inst, "10110"); //5bits
        strcat(sixteen_bit_inst, "000"); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op1)); //8bits
    }
    
    if(strcmp(instruction, "addi") == 0){ //10111 000 CCCCCCCC
        strcpy(sixteen_bit_inst, "10111"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getSignedDecimalToBinary(op2)); //8bits
    }
    
    if(strcmp(instruction, "sgt") == 0){ //11000 RRR RRR RRR 00
        strcpy(sixteen_bit_inst, "11000"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op3)); //3bits
        strcat(sixteen_bit_inst, "00"); //2bits
    }
    
    if(strcmp(instruction, "set") == 0){ //11001 RRR RRR RRR 00
        strcpy(sixteen_bit_inst, "11001"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op2)); //3bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op3)); //3bits
        strcat(sixteen_bit_inst, "00"); //2bits
    }
    
    if(strcmp(instruction, "jmpp") == 0){ //11010 000 AAAAAAAA
        strcpy(sixteen_bit_inst, "11010"); //5bits
        strcat(sixteen_bit_inst, getRegisterToBinary(op1)); //3bits
        strcat(sixteen_bit_inst, getDecimalToBinary(op2)); //8bits
        
        /*
         TODO: tratar jmpp label
         */
    }
    
    printf("%s, \n", sixteen_bit_inst);
    splitInTwo(sixteen_bit_inst, decoded1, decoded2);
    
    
}


char* getRegisterToBinary(char* reg){
    
    strcpy(reg, replace(reg, "\n", ""));
    if(strcmp(reg, "R0") == 0){
        return "000";
    }
    if(strcmp(reg, "R1") == 0){
        return "001";
    }
    if(strcmp(reg, "R2") == 0){
        return "010";
    }
    if(strcmp(reg, "R3") == 0){
        return "011";
    }
    if(strcmp(reg, "R4") == 0){
        return "100";
    }
    if(strcmp(reg, "R5") == 0){
        return "101";
    }
    if(strcmp(reg, "R6") == 0){
        return "110";
    }
    if(strcmp(reg, "R7") == 0){
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
    
    return binary;
}

char* getSignedDecimalToBinary(char* chardec){
    //Complemento de dois
    
    char* binary = (char*) malloc(sizeof(char) * 8);
    int dec = atoi(chardec);
    strcpy(binary, "0");
    
    int decNeg = dec;
    
    if(dec < 0){
        dec *= -1;
        dec --;
    }
    
    int div = 64;
    while(div >= 1){
        if(dec >= div){
            strcat(binary, "1");
            dec = dec - div;
        }
        else{
            strcat(binary, "0");
        }
        
        div = div/2;
        
    }
    
    if(decNeg < 0){
        for(int i = 0; i < 8; i++){
            if(binary[i] == '0'){
                binary[i] = '1';
            }
            else{
                binary[i] = '0';
            }
        }
    }
    
    
    return binary;
}

void splitInTwo(char* sixteen_bit, char* decoded1, char* decoded2){
    for(int i = 0; i < 8; i++){
        decoded1[i] = sixteen_bit[i];
        decoded2[i] = sixteen_bit[i+8];
    }
}


char *replace(const char *src, const char *from, const char *to)
{
    size_t size    = strlen(src) + 1;
    size_t fromlen = strlen(from);
    size_t tolen   = strlen(to);
    char *value = malloc(size);
    char *dst = value;
    if ( value != NULL )
    {
        for ( ;; )
        {
            const char *match = strstr(src, from);
            if ( match != NULL )
            {
                size_t count = match - src;
                char *temp;
                size += tolen - fromlen;
                temp = realloc(value, size);
                if ( temp == NULL )
                {
                    free(value);
                    return NULL;
                }
                dst = temp + (dst - value);
                value = temp;
                memmove(dst, src, count);
                src += count;
                dst += count;
                memmove(dst, to, tolen);
                src += fromlen;
                dst += tolen;
            }
            else
            {
                strcpy(dst, src);
                break;
            }
        }
    }
    return value;
}
