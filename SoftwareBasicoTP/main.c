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
#include "Decoder.h"


const char* file_in = "/Users/fabiolelis/Git/SoftwareBasicoTP/teste.a";
const char* file_out = "/Users/fabiolelis/Git/SoftwareBasicoTP/output.mif";

void readFile();
void split_line();
int check_label();
int check_comment();
int check_data();
void writeFile(char** output, int input_size);

int current_fragment;


int main(int argc, const char * argv[]) {
    
    char** input = (char**)malloc(sizeof(char) * 256 * 30);
    int input_size = 0;
    readFile(input, &input_size);
    char** output = (char**)malloc(sizeof(char) * 256 * 30);
    init_output(output);
    int line_number = 0;
    
    for(line_number = 0; line_number < input_size; line_number++){

        char** line = (char**)malloc(sizeof(char) * 6 * 15);
        split_line(line, input[line_number]);
        int has_label = check_label(line[0]);
        int is_comment = check_comment(line[0]);
        int is_data = check_data(line[1+has_label]);

        if(has_label){
            //tem label
            //TODO: tratar a ocorrencia de labels
        }
        if(is_data){
            //é um .data
            //TODO: tratar a ocorrencia do .data
        }
        if(is_comment){
            continue;
        }
        
        //Cada pedaço da instrucao em line[pos] agora
        decode(line, output, line_number, has_label);
        
        
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
    
    fp = fopen(file_in , "r");
    if (fp == NULL)
        printf("Endereco invalido");
    
    while ((read = getline(&line, &len, fp)) != -1) {
        
        input[i] = (char *) malloc(60*sizeof(char));
        strcpy(input[i], line);
        printf("%s", line);
        i++;
    }
    
    fclose(fp);
    if (line)
        free(line);
    
    *input_size = i - 1;
    
}

void split_line(char** line, char* input){
    line[0] = (char *) malloc(32*sizeof(char));
    line[0] = strtok(input," ");
    
    int pos = 0;
    while (line[pos] != NULL)
    {
        pos ++;
        line[pos] = (char *) malloc(32*sizeof(char));
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

int check_comment(char* line){
    switch (line[0]) {
        case ';':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

int check_data(char* line){
    if(strcmp(line, ".data") == 0){
        return 1;
    }
    else{
        return 0;
    }
}


void writeFile(char** output, int input_size){
    FILE* fp;
    
    fp = fopen(file_out , "w");
    if (fp == NULL)
        printf("Endereco invalido");
    
    fprintf(fp, "DEPTH = %d;\n", 256);
    fprintf(fp, "WIDTH = 8;\n");
    fprintf(fp, "ADDRESS_RADIX = HEX;\n");
    fprintf(fp, "DATA_RADIX = BIN;\n");
    fprintf(fp, "CONTENT\n");
    fprintf(fp, "BEGIN\n");

    
    for(int i = 0; i < 256; i++){
        
        fprintf(fp, "%X : %s;\n", i, output[i]);
    }
    
    fprintf(fp, "END;\n");
    
    
    fclose(fp);
    
}
