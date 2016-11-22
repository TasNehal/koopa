#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char ** retArr = malloc(sizeof(retArr) + 1);
    int ctr = 0;

    while (line) {
        retArr[ctr] = strsep(&line, ";");
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

int main() {
    char x[6] = "a;b;c";
    char ** y = parse_line(x);
    printf("done");
    while (y) {
        printf("%s", *y);
        y++;
    }
}
