#include <stdio.h>
#include "Source.h"
#define TASK_RUN

int main()
{
    FILE *file;
    char line[256];
    TASK_RUN
        file = fopen("TASK_VARIABLE.ce", "r");
        while (fgets(line, sizeof(line), file) != NULL) 
        { Compiler(line); }
        fclose(file);
    return 0;
}
