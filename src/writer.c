#include "../includes/writer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int appendToFile (char* line, char* fileName) {
    char path[100];
    char* directory = "output/";

    strcpy(path, directory);
    strcat(path, fileName);

    FILE *filePointer;
    filePointer = fopen(path, "a");
    
    if (filePointer == NULL) {
        printf("Failed to open the file: %s\n", path);
        return 0;
    }

    if (fprintf(filePointer, "%s\n", line) < 0) {
        printf("Failed to write to the file: %s\n", path);
        fclose(filePointer);
        return 0;
    }

    fclose(filePointer);
    return 1;
}