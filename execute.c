//will execute things, and will handle redirects and custom commands
#include "execute.h"

void executeMAIN(char ** input) {
    //if only one item and its exit, run exit
    if ((sizeof(input) / sizeof(char *)) == 1 && (!strcmp(input[0], "exit"))) {
        executeEXIT();
    }
    //if two items with cd as first, run cd on second
    else if ((sizeof(input) / sizeof(char *)) == 2 && (!strcmp(input[0], "cd"))) {
        executeCD(input[2]);
    }
    else {
        // fork and run?
        int fid = fork();
        int status;
        //check for redirectors
    }
}

void executeEXIT() {
    //is that it?
    exit(0);
}

void executeCD(char * dir) {
    chdir(dir);
}
