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
    
    char* line[5];
    int has_label = 0;
    
    printf("%s %d \n", input[0], input_size);
    
    for(int line_number = 0; line_number < input_size; line_number++){

        split_line(line, input, line_number);
        if(check_label(line)){
            //tem label
        }
        
        //Cada pedaço da instrucao em line[pos] agora
        
    }
    
    
    return 0;
}




void readFile(char* input[1000], int* input_size){
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    
    fp = fopen("/Users/fabiolelis/Git/SoftwareBasicoTP/teste.a" , "r");
    if (fp == NULL)
        printf("Endereco invalido");
    
    while ((read = getline(&line, &len, fp)) != -1) {
        strcpy(input[i],line);
        i++;
    }
    
    fclose(fp);
    if (line)
        free(line);
    
    *input_size = i;
    
}

void split_line(char* line[], char* input[], line_number){
    line[0] = strtok(input[line_number]," ");
    
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
