#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab2.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Использование: %s <имя_файла> <команда> <аргументы>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    const char* command = argv[2];
    const char* args = argv[3];

    int numLines = 0;
    
    char** lines = readLinesFromFile(filename, &numLines);
    if (lines == NULL) return 1;

    char* oldText = NULL;
    char* newText = NULL;

    if (strcmp(command, "replace") == 0) {
        if (!extractTextFromRegex(args, &oldText, &newText)) {
            fprintf(stderr, "Неверный формат аргументов для команды 'replace'\n");
            freeLines(lines, numLines);
            return 1;
        }
        replaceInLines(lines, numLines, oldText, newText);
        free(oldText);
        free(newText);
    } else if (strcmp(command, "addBegin") == 0) {
        addTextToBegin(lines, numLines, args);
    } else if (strcmp(command, "addEnd") == 0) {
        addTextToEnd(lines, numLines, args);
    } else if (strcmp(command, "remove") == 0) {
        removeTextFromLines(lines, numLines, args);
    } else {
        fprintf(stderr, "Неизвестная команда: %s\n", command);
        freeLines(lines, numLines);
        return 1;
    }

    writeLinesToFile(lines, numLines, filename);
    freeLines(lines, numLines);
    return 0;
}

