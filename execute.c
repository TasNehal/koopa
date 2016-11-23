#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void executeRedirect(char *line, char redirector) {

}

void executeMultiple(char *line) {

}

void execute(char *line) {
  char * command[] = line;
  execvp(command[0], command);
}

int main() {
  char input[262144]
  printf("Do something: ");
  fgets(input, 262144, stdin);
  *strchr(input, "\n") = 0;
  char * line = parse_line(input);
  execute(input);
  return 0;
}
