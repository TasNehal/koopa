#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

int count_tokens(char *line, char delim) {
    int ctr = 1;
    while (*line) {
        if (*line == delim) {
            ctr++;
        }
        line++;
    }
    return ctr;
}

char ** parse_line(char *line, char delim) {
    line = trim(line);
    char ** retArr = (char * *)malloc(sizeof(char *) * strlen(line));
    int ctr = 0;

    while (line) {
        retArr[ctr] = strsep(&line, delim);
        printf("%s\n", retArr[ctr]);
        ctr++;
    }
    retArr[ctr] = 0;
    return retArr;
}

char * trim(char *line) {
    char * retP = line;

    while (line[0] == ' ') {
        for (int i = 0 ; i < (int)strlen(line) - 1 ; i++) {
            line[i] = line[i + 1];
        }
    }
    //getting rid of whitespace at end
    for (int j = 0 ; j < (int)strlen(line) - 1 ; j++) {
        //in bash double spaces in between words fail
        if (line[j] == ' ' && line[j + 1] == ' ') {
            for (int k = j ; k < (int)strlen(line) ; k++) {
                line[k] = '\0';
            }
        }
    }

    
    return retP;
}

int main() {
    return 0;
}
