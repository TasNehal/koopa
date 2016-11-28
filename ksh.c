//main file, will get input and will have special commands like cd and exit
#include "ksh.h"

int main() {
    char input[262144];
    printf("➜ ");
    fgets(input, 262144, stdin);
    *strchr(input, "\n") = 0;
    char * line = parse_line(input);
    executeMain(input);
    return 0;
}
