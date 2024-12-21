#ifndef LAB2_H
#define LAB2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** readLinesFromFile(const char* filename, int* numLines);
void replaceInLines(char** lines, int numLines, const char* oldText, const char* newText);
int extractTextFromRegex(const char* input, char** oldText, char** newText);
void addTextToBegin(char** lines, int numLines, const char* textToAdd);
void addTextToEnd(char** lines, int numLines, const char* textToAdd);
void removeTextFromLines(char** lines, int numLines, const char* textToRemove);
void writeLinesToFile(char** lines, int numLines, const char* filename);
void freeLines(char** lines, int numLines);

#endif

