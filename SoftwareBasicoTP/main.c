//
//  main.c
//  SoftwareBasicoTP
//
//  Created by Fabio Lelis on 25/09/16.
//  Copyright © 2016 Fabio Lelis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile();
void split_line();
int check_label();
void decode(char* line[], char* output[], int line_number);
void writeFile(char* output[], int input_size);

enum Instruction_Fragment{
    label,
    instruction,
    first_operator,
    second_operator
};

int current_fragment;


int main(int argc, const char * argv[]) {
    
    enum Instruction_Fragment inst_fragment;
    inst_fragment = label;
    
    char* input[1000];
    
    int input_size = 0;
    readFile(input, &input_size);
    char* output[input_size];

    
    
    printf("%s %d \n", input[0], input_size);
    
    for(int line_number = 0; line_number < input_size; line_number++){

        char* line[5];

        split_line(line, input[line_number]);
        if(check_label(line[0])){
            //tem label
            //bota numa tabela?
            
        }
        
        //Cada pedaço da instrucao em line[pos] agora
        decode(line, output, line_number);
        
        
    }
    
    writeFile(output, input_size);
    
    
    return 0;
}




void readFile(char* input[], int* input_size){
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    
    fp = fopen("/Users/fabiolelis/Git/SoftwareBasicoTP/teste.a" , "r");
    if (fp == NULL)
        printf("Endereco invalido");
    
    while ((read = getline(&line, &len, fp)) != -1) {
        
        input[i] = (char *) malloc(16*sizeof(char));
        strcpy(input[i], line);
        printf("%s", line);
        i++;
    }
    
    fclose(fp);
    if (line)
        free(line);
    
    *input_size = i;
    
}

void split_line(char* line[], char* input){
    line[0] = strtok(input," ");
    
    int pos = 0;
    while (line[pos] != NULL)
    {
        pos ++;
        line[pos] = strtok(NULL," ");
    }
}

int check_label(char* line){
    switch (line[0]) {
        case '_':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

void decode(char* line[], char* output[], int line_number){
    char* decoded = "0101010101010101";
    
    //decode line
    
    output[line_number] = NULL;
    output[line_number] = (char *) malloc(20*sizeof(char));
    
    strcpy(output[line_number], decoded);
    
}


void writeFile(char* output[], int input_size){
    FILE* fp;
    
    fp = fopen("/Users/fabiolelis/Git/SoftwareBasicoTP/output.mif" , "w");
    if (fp == NULL)
        printf("Endereco invalido");
    
    fprintf(fp, "DEPTH = %d;\n", input_size);
    fprintf(fp, "WIDTH = 16;\n");
    fprintf(fp, "ADDRESS_RADIX = HEX;\n");
    fprintf(fp, "DATA_RADIX = BIN;\n");
    fprintf(fp, "CONTENT\n");
    fprintf(fp, "BEGIN\n");

    
    for(int i = 0; i < input_size; i++){
        
        fprintf(fp, "%X : %s\n", i, output[i]);
    }
    
    fprintf(fp, "END\n");
    
    
    fclose(fp);
    
}
