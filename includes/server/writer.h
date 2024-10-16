#ifndef FILE_WRITER
#define FILE_WRITER

#include <stdio.h>

int appendToFile(char* line, FILE *filePointer, int is_log);
void initWrite(char *fileName);

#endif