#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_tokens(char *line, char delim);
char ** parse_line(char *line, char * delims);
char * trim(char *line);
