#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"

void executeRedirector(char ** input);
char ** findRedirector(char * input);
int hasRedirector(char * input);
void executeMain(char * data);
void executeCD(char * dir);
void executeEXIT();
