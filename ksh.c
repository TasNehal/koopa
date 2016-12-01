//main file, will get input and will split the semicolons
#include "ksh.h"

void ksh_run(char * input) {
    int tokens = count_tokens(input, ';');
    if (tokens == 1) {
        //split by spaces and redirectors, send to execmain
        executeMain(input);
    }
    else {
        //recursively run each semicolon seperated part
        char ** lineItems = parse_line(input, ";");
        for (int i = 0 ; i < count_tokens(input, ';') ; i++) {
            printf("%d", i);
            ksh_run(lineItems[i]);
        }
    }
    
}

int main() {
    
    char input[262144];
    char cwd[262144];
    while (1) {
        getcwd(cwd, sizeof(cwd));
        printf("(%s) %s ❯ ", getenv("USER"), cwd);
        fgets(input, 262144, stdin);
        * input = * trim(input);
        ksh_run(input);
    }
    return 0;
    
}
