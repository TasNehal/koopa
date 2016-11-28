//will execute things, and will handle stuff like pipes and redirects
#include "execute.h"

void executeRedirect(char *line, char redirector) {

}

void executeMultiple(char *line) {

}

void executeMain(char *line) {
  char * command = line;
  execvp(&command[0], &command);
}
