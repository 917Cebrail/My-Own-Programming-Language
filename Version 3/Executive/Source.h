#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define RAM_SIZE 1024
#define STRING_RAM_SIZE 256
#define LABEL_COUNT 100

typedef enum { INT, FLOAT, CHAR, STRING } VarType;

typedef struct {
    char name[50];
    int address;
    VarType type;
} Variable;

typedef struct {
    char label[50];
    int line_number;
} Label;

int ram[RAM_SIZE];
float float_ram[RAM_SIZE];
char char_ram[RAM_SIZE];
char str_ram[STRING_RAM_SIZE][50];
Variable variables[RAM_SIZE];
Label labels[LABEL_COUNT];
int label_count = 0;

int DEBUG_MODE = 0;

void clear_memory() {
    memset(ram, 0, sizeof(ram));
    memset(float_ram, 0, sizeof(float_ram));
    memset(char_ram, 0, sizeof(char_ram));
    memset(str_ram, 0, sizeof(str_ram));
    if (DEBUG_MODE)
        printf("Memory cleared.\n");
}

void define_label(const char *label, int line_number) {
    if (label_count < LABEL_COUNT) {
        strcpy(labels[label_count].label, label);
        labels[label_count].line_number = line_number;
        label_count++;
    } else {
        printf("Maximum label count reached.\n");
    }
}

int find_label(const char *label) {
    for (int i = 0; i < label_count; i++) {
        if (strcmp(labels[i].label, label) == 0) {
            return labels[i].line_number;
        }
    }
    return -1;
}

void Compiler(char *code) {
    if (DEBUG_MODE)
        printf("Executing: %s\n", code);

    if (strncmp(code, "VAR", 3) == 0) {
        char name[50], type[10];
        int address;
        sscanf(code, "VAR %s %s ADDRESS : %d", name, type, &address);

        if (strcmp(type, "INT") == 0) {
            variables[address] = (Variable){ .address = address, .type = INT };
        } else if (strcmp(type, "FLOAT") == 0) {
            variables[address] = (Variable){ .address = address, .type = FLOAT };
        } else if (strcmp(type, "CHAR") == 0) {
            variables[address] = (Variable){ .address = address, .type = CHAR };
        } else {
            printf("Invalid type: %s\n", type);
        }

        strcpy(variables[address].name, name);
        printf("Variable %s of type %s defined at address %d\n", name, type, address);
    }
    else if (strncmp(code, "LABEL", 5) == 0) {
        char label[50];
        sscanf(code, "LABEL %s", label);
        define_label(label, __LINE__);
    }
    else if (strncmp(code, "GOTO", 4) == 0) {
        char label[50];
        sscanf(code, "GOTO %s", label);
        int target_line = find_label(label);
        if (target_line != -1) {
            printf("Jumping to label: %s at line %d\n", label, target_line);
        } else {
            printf("Label not found: %s\n", label);
        }
    }
    else if (strncmp(code, "PNT", 3) == 0) {
        char message[256];
        sscanf(code, "PNT %[^\n]", message);
        printf("%s\n", message);
    }
    else if (strncmp(code, "PRINT", 5) == 0) {
        int address;
        sscanf(code, "PRINT %d", &address);

        if (variables[address].type == INT) {
            printf("%d\n", ram[address]);
        } else if (variables[address].type == FLOAT) {
            printf("%.2f\n", float_ram[address]);
        } else if (variables[address].type == CHAR) {
            printf("%c\n", char_ram[address]);
        } else {
            printf("Unknown variable type\n");
        }
    }
    else if (strncmp(code, "FOR", 3) == 0) {
        int start, end, step, address;
        sscanf(code, "FOR %d TO %d STEP %d : ADDRESS %d", &start, &end, &step, &address);

        for (int i = start; i <= end; i += step) {
            ram[address] = i;
            printf("Loop value: %d at address %d\n", i, address);
        }
    }
    else if (strncmp(code, "IF", 2) == 0) {
        int a1, a2;
        char cond[3], true_branch[256], false_branch[256];
        sscanf(code, "IF ADDRESS %d %s ADDRESS %d -> %s : %s", &a1, cond, &a2, true_branch, false_branch);

        int condition = 0;
        if (strcmp(cond, "==") == 0) condition = (ram[a1] == ram[a2]);
        else if (strcmp(cond, "!=") == 0) condition = (ram[a1] != ram[a2]);
        else if (strcmp(cond, ">") == 0) condition = (ram[a1] > ram[a2]);
        else if (strcmp(cond, "<") == 0) condition = (ram[a1] < ram[a2]);
        else if (strcmp(cond, ">=") == 0) condition = (ram[a1] >= ram[a2]);
        else if (strcmp(cond, "<=") == 0) condition = (ram[a1] <= ram[a2]);

        if (condition) {
            Compiler(true_branch);
        } else {
            Compiler(false_branch);
        }
    }
    else if (strncmp(code, "CLEAR", 5) == 0) {
        clear_memory();
    }
    else {
        printf("Invalid command: %s\n", code);
    }
}

#endif

