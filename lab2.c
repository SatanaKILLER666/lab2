#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "lab2.h"


char** readLinesFromFile(const char* filename, int* numLines) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return NULL;
    }

    char** lines = NULL;
    *numLines = 0;
    char line[2048]; 

    while (fgets(line, sizeof(line), file) != NULL) {
        (*numLines)++;
        lines = realloc(lines, (*numLines) * sizeof(char*));
        if (lines == NULL) {
            perror("Ошибка выделения памяти");
            fclose(file);
            return NULL;
        }
        lines[*numLines - 1] = strdup(line); 
        if (lines[*numLines - 1] == NULL) {
            perror("Ошибка выделения памяти");
            fclose(file);
            for (int i = 0; i < *numLines - 1; ++i) {
                free(lines[i]);
            }
            free(lines);
            return NULL;
        }

    }

    fclose(file);
    return lines;
}



void replaceInLines(char** lines, int numLines, const char* oldText, const char* newText) {
    for (int i = 0; i < numLines; ++i) {
        char* pos = lines[i];
        while ((pos = strstr(pos, oldText)) != NULL) {
            size_t newLineLength = strlen(lines[i]) - strlen(oldText) + strlen(newText) + 1;
            lines[i] = realloc(lines[i], newLineLength);
            if (lines[i] == NULL) {
                perror("Ошибка выделения памяти");
                exit(1); 
            }
            memmove(pos + strlen(newText), pos + strlen(oldText), strlen(pos + strlen(oldText)) + 1);
            memcpy(pos, newText, strlen(newText));
            pos += strlen(newText);
        }
    }
}



int extractTextFromRegex(const char* input, char** oldText, char** newText) {
    
    if (input[0] != '/' || input[strlen(input) - 1] != '/') {
        return 0; 
    }
    char* oldNew = strdup(input + 1);
    char* delimiter = strchr(oldNew, '/');
    if(delimiter == NULL) return 0; 
    *delimiter = '\0';
    *oldText = strdup(oldNew);
    *newText = strdup(delimiter + 1);
    free(oldNew);
    return 1; 
}


void addTextToBegin(char** lines, int numLines, const char* textToAdd) {
    for (int i = 0; i < numLines; i++) {
        size_t newLineLength = strlen(lines[i]) + strlen(textToAdd) + 1;
        lines[i] = realloc(lines[i], newLineLength);
        if (lines[i] == NULL) {
            perror("Ошибка выделения памяти");
            exit(1);
        }
        memmove(lines[i] + strlen(textToAdd), lines[i], strlen(lines[i]) + 1);
        memcpy(lines[i], textToAdd, strlen(textToAdd));
    }
}


void addTextToEnd(char** lines, int numLines, const char* textToAdd) {
    for (int i = 0; i < numLines; i++) {
        size_t newLineLength = strlen(lines[i]) + strlen(textToAdd) + 1;
        lines[i] = realloc(lines[i], newLineLength);
        if (lines[i] == NULL) {
            perror("Ошибка выделения памяти");
            exit(1);
        }
        strcat(lines[i], textToAdd);
    }
}


void removeTextFromLines(char** lines, int numLines, const char* textToRemove) {
    for (int i = 0; i < numLines; ++i) {
        char* pos = lines[i];
        while ((pos = strstr(pos, textToRemove)) != NULL) {
            size_t newLineLength = strlen(lines[i]) - strlen(textToRemove) + 1;
            lines[i] = realloc(lines[i], newLineLength);
            if (lines[i] == NULL) {
                perror("Ошибка выделения памяти");
                exit(1);
            }
            memmove(pos, pos + strlen(textToRemove), strlen(pos + strlen(textToRemove)) + 1);
        }
    }
}



void writeLinesToFile(char** lines, int numLines, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка открытия файла на запись");
        return;
    }
    for (int i = 0; i < numLines; ++i) {
        fputs(lines[i], file);
    }
    fclose(file);
}



void freeLines(char** lines, int numLines) {
    for (int i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);
}

