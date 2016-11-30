#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"

void executeReDIRECT(char ** input, char redirector);
void executeMAIN(char ** input);
void executeCD(char * dir);
void executeEXIT();
