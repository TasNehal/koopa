//main file, will get input and will have special commands like cd and exit
#include "ksh.h"

//find if command is exit ONLY (1 item), then run ksh_exit() find if first command is cd, then give second object as dirname to ksh_cd(dirname)
//delete these comments once implemented
int main() {
    char input[262144];
    printf("➜ ");
    fgets(input, 262144, stdin);
    * input = * trim(input);
    char ** line = parse_line(input, ';');
    executeMain(input);
    return 0;
}
