//will parse the input text from the user
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

char ** parse_line(char *line, char * delims) {
    line = trim(line);
    char ** retArr = (char * *)malloc(sizeof(char *) * strlen(line));
    int ctr = 0;

    while (line) {
        retArr[ctr] = strsep(&line, delims);
        ctr++;
    }
    retArr[ctr] = 0;
    return retArr;
}

char * trim(char *line) {
    char * retP = line;
    //beginning
    while (line[0] == ' ') {
        int i;
        for (i = 0 ; i < (int)strlen(line) ; i++) {
            line[i] = line[i + 1];
        }
        //line[i] = '\0';
    }
    //end?
    for (int l = strlen(line) ; l > 0 ; l--) {
        if (line[l] == '\n' || line[l] == ' ') {
            line[l] = '\0';
        }
        else if (line[l] != '\n' && line[l] != '\0' && line[l] != ' '){
            break;
        }
    }
    return retP;
}

