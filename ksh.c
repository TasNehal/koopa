//main file, will get input and will split the semicolons
#include "ksh.h"

void ksh_run(char * input) {
    * input = * trim(input);
    int tokens = count_tokens(input, ';');
    if (!tokens) {
        //split by spaces and redirectors, send to execmain
        char ** data = parse_line(input, ">2&<|");
        executeMain(data);
    }
    else {
        //recursively run each semicolon seperated part
        char ** lineItems = parse_line(input, ";");
        while (lineItems) {
            ksh_run(*lineItems);
            lineItems++;
        }
    }
    
}

int main() {
    
    char input[262144];
    printf("➜ ");
    fgets(input, 262144, stdin);
    return 0;
    
}
