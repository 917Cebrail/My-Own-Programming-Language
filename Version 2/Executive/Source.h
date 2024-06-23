#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int Var;
int ram[128];
char str_ram[128];

void Compiler(char *code)
{
    if (strncmp(code, "VAR", 3) == 0) 
    {
        int add, _Var;
        char ch;
        sscanf(code, "VAR %c = %d , ADDRESS : %d", &ch, &_Var, &add);
        Var = _Var;
        ram[add] = Var;
    }
    else if (strncmp(code, "PNT", 3) == 0)
    {
        char m[256];
        sscanf(code, "PNT %s", m);
        printf("%s\n", m);
    }
    else if (strncmp(code, "PRINT", 5) == 0)
    {
        int add;
        sscanf(code, "PRINT %d", &add);
        printf("%d\n", ram[add]);
    }
    else if (strncmp(code, "SPRINT", 6) == 0)
    {
        int add;
        sscanf(code, "SPRINT %d", &add);
        printf("%d\n", str_ram[add]);
    }    
    else if (strncmp(code, "INPUT", 5) == 0)
    {
        int add;
        char codes[10], message[256];
        sscanf(code, "INPUT ( %s ) %s = ADDRESS : %d", message, codes, &add);
        printf("%s", message);
        if (strcmp(codes, "STRING") == 0)
        {
            char inputted[50];
            scanf("%s", inputted);
            str_ram[add] = strdup(inputted);
        }
        else if (strcmp(codes, "INT") == 0)
        {
            int inputted_val;
            scanf("%d", &inputted_val);
            ram[add] = inputted_val;
        }
        else
        {
            printf("Invalid Code\n");
        }
    }
    else if (strncmp(code, "ARG", 3) == 0)
    {
        int add1, add2;
        char operator[4];
        sscanf(code, "ARG ADDRESS : %d , ADDRESS : %d , %s", &add1, &add2, operator);
        int s1 = ram[add1], s2 = ram[add2];
        if (strcmp(operator, "ADD") == 0)
        {
            printf("%d\n", (s1 + s2));
        }
        else if (strcmp(operator, "SUB") == 0)
        {
            printf("%d\n", (s1 - s2));
        }
        else if (strcmp(operator, "MUL") == 0)
        {
            printf("%d\n", (s1 * s2));
        }
        else if (strcmp(operator, "DIV") == 0)
        {
            printf("%d\n", (s1 / s2));
        }
        else if (strcmp(operator, "POW") == 0)
        {
            printf("%d\n", (int)pow(s1, s2));
        }
        else
        {
            printf("OPERATOR ERROR");
        }
    }
    else if (strncmp(code, "FILE", 4) == 0)
    {
        char files[51];
        sscanf(code, "FILE : %s", files);
        FILE *file;
        char line[100];
        file = fopen(files, "r");
        while (fgets(line, sizeof(line), file) != NULL) 
        { Compiler(line); }
        fclose(file);
    }
    else if (strncmp(code, "FOR", 3) == 0)
    {
        int i, address;
        char opera[3];
        sscanf(code, "FOR %d , ADDRESS %d : %s", &i, &address, &opera);
        int jjj = ram[address];
        if (strcmp(opera, "++"))
        {
            for (int k = 0; k < i; k++)
            {
                ram[address] = jjj + (k);
            }
        }
        else if (strcmp(opera, "--"))
        {
            for (int k = 0; k < i; k++)
            {
                ram[address] = jjj - (k);
            }
            
        }
        else
        {
            printf("OPERATOR ERROR");
        }
    }
    else if (strncmp(code, "IF", 2) == 0)
    {
        int a1, a2;
        char s1[256], s2[256];
        sscanf(code, "IF ADDRESS %d == ADDRESS %d -> %s --> %s", &a1, &a2, s1, s2);
        if (ram[a1] == ram[a2])
        {          
            printf("%s", s1); 
        }
        else
        {
            printf("%s", s2);
        }
        printf("\n");
    }
    else 
    {
        printf("Invalid command\n");
    }
}

#endif