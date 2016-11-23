#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

/*======== int count_tokens() ==========
	Inputs:  char *line
        	  char delim 
	Returns: Number of tokens in line separated by delim

	Counts the number of times the character delim appears in the
	 string line
	The number of tokens is 1 more than the number of appearences 
	of delim
	If delim does not appear, 1 is returned
	====================*/

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

	/*======== char ** parse_line() ==========
	Inputs:  char *line 
	Returns: Array of strings where each entry is a token 
	separated by delim

	If line contains multiple tokens separated by delim, this 
	function will put each token into an array of strings
	====================*/

char ** parse_line(char *line) {
    char ** retArr = (char * *)malloc(sizeof(char *) * strlen(line));
    int ctr = 0;

    while (line) {
        retArr[ctr] = strsep(&line, ";");
        printf("%s\n", retArr[ctr]);
        ctr++;
    }
    retArr[ctr] = 0;
    return retArr;
}

/*======== char * trim() ==========
	Inputs:  char *line 
	Returns: Pointer to the beginning of line

	Removes leading and trailing whitespace on the string line.
	Terminating '\0' is placed at a new location if necessary.
	====================*/

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
