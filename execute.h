#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"

void executeRedirect(char *line, char redirector);
void executeMultiple(char *line);
void executeMain(char *line);
