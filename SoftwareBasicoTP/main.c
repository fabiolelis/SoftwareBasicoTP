/*
  main.c
  SoftwareBasicoTP

  Created by Fabio Lelis on 25/09/16.
  Copyright Â© 2016 Fabio Lelis. All rights reserved.
*/


#include "Decoder.h"

/*
typedef struct ast_struct AST;

struct AST{
    int line;
    int size;
    int value;
    char* label_name;
};
*/
const char* file_in = "teste.a";
const char* file_out = "output.mif";
/*const char* file_in = "/Users/fabiolelis/Git/SoftwareBasicoTP/SoftwareBasicoTP/teste.a";
const char* file_out = "/Users/fabiolelis/Git/SoftwareBasicoTP/SoftwareBasicoTP/output.mif";*/


int readFile(char** input);
void split_line();
int check_label();
int check_comment();
int check_data();
void writeFile(char** output, int input_size);

int current_fragment;


int main(int argc, const char * argv[]) {
    
    char** input = (char**)malloc(sizeof(char) * 256 * 30);
    char** output = (char**)malloc(sizeof(char) * 256 * 30);
    int input_size = 0;
    int line_number = 0;
    
    printf("started reading file \n");
    input_size = readFile(input);
    fflush(stdout);
    
    init_output(output);
    printf("%s", "\n create ast");
    AST* ast = (AST*)malloc(sizeof(AST)*20);
    printf("\n AST created");
    
    int label_idx = 0;
    int data_idx = 252;
    while(line_number < (input_size)){
        
        printf("%s", "\n start loop");
        fflush(stdout);

        char** line = (char**)malloc(sizeof(char) * 6 * 150);
        char* input_index = (char*) malloc(sizeof(char) * 32);
        strcpy(input_index, input[line_number]);
        split_line(line, input_index);
        int has_label = check_label(line[0]);
        
        int is_data = check_data(line[1+has_label]);
        if(has_label){
            printf("%s"," tem label");
            fflush(stdout);
            ast[label_idx].line = line_number;
            ast[label_idx].label_name = line[0];
            label_idx++;
        }
        if(is_data){
            printf("%s"," Ã© um .data");
            ast[label_idx].line = data_idx;
            ast[label_idx].label_name = line[1];
            ast[label_idx].size = atoi(line[2]);
            ast[label_idx].value = atoi(line[3]);
            label_idx++;
            data_idx--;data_idx--;
            
        }
        printf("%s", " closing loop");
        fflush(stdout);
        
        line_number++;
    }
    fflush(stdout);
    printf("%s", "\n end loop");
    
    line_number = 0;
    while(line_number < (input_size)){
        
        char** line = (char**)malloc(sizeof(char) * 6 * 150);
        char* input_index = (char*) malloc(sizeof(char) * 32);
        strcpy(input_index, input[line_number]);
        split_line(line, input_index);
        int has_label = check_label(line[0]);
        int is_data = check_data(line[1+has_label]);
        
        
        if(is_data){
            continue;
        }
        
        
        /*Cada pedaÃ§o da instrucao em line[pos] agora*/
        decode(line, output, line_number, has_label, ast);
        line_number++;

        
    }
    

    
    printf("\n end loop 2");
    
    writeFile(output, input_size);
    printf("\n wrote it");
    
    free(output);
    free(input);
    
    return 0;
}


int readFile(char* input[]){
    FILE* fp;
    char* line = NULL;
    int len = 0;
    int read;
    int i = 0;
    printf("\n reading");
    fp = fopen(file_in , "r");
    if (fp == NULL)
        printf("Endereco invalido");
    
    while (((read = getline(&line, &len, fp)) !=-1)) {
        printf("%d",i);
        input[i] = (char *) malloc(200*sizeof(char));
        strcpy(input[i], line);
        printf("%s", input[i]);
        i++;
    }
    fclose(fp);
    
    free(line);
    
    return i - 1;
    
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

int check_data(char* line){
    if(line == NULL)
        return 0;
    
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
    
    int i = 0;
    for(i = 0; i < 256; i++){
        
        fprintf(fp, "%X : %s;\n", i, output[i]);
    }
    
    fprintf(fp, "END;\n");
    
    fclose(fp);
}
