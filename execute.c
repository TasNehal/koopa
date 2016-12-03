//will execute things, and will handle redirects and custom commands
#include "execute.h"

//returns array of [string, redirector, string]
//second string can also have redirectors, executemain should do them in order
char ** findRedirector(char * input) {
    char ** retAry = (char * *)malloc(sizeof(char *) * strlen(input));
    //making the first part, the pipe, and the rest of the line
    for (int i = 0 ; i < (int)strlen(input) - 1 ; i++) {
        if (input[i] == '>') {
            // >> operator
            if (input[i + 1] == '>') {
                for (int j = 0 ; j < i ; j++) {
                    retAry[0][j] = input[j];
                }
                retAry[1] = ">>";
                for (int k = i + 2 ; k < (int)strlen(input) ; k++) {
                    retAry[2][k - i - strlen(retAry[1])] = input[k];
                }
            }
            // > operator
            else {
                for (int j = 0 ; j < i ; j++) {
                    retAry[0][j] = input[j];
                }
                retAry[1] = ">";
                for (int k = i + 1 ; k < (int)strlen(input) ; k++) {
                    retAry[2][k - i - strlen(retAry[1])] = input[k];
                }
            }
        }
        else if (input[i] == '2') {
            if (input[i + 1] == '>') {
                // 2>> operator
                if (input[i + 2] == '>') {
                    for (int j = 0 ; j < i ; j++) {
                        retAry[0][j] = input[j];
                    }
                    retAry[1] = "2>>";
                    for (int k = i + 3 ; k < (int)strlen(input) ; k++) {
                        retAry[2][k - i - strlen(retAry[1])] = input[k];
                    }
                }
                // 2> operator
                else {
                    for (int j = 0 ; j < i ; j++) {
                        retAry[0][j] = input[j];
                    }
                    retAry[1] = "2>";
                    for (int k = i + 2 ; k < (int)strlen(input) ; k++) {
                        retAry[2][k - i - strlen(retAry[1])] = input[k];
                    }
                }
            }
        }
        else if (input[i] == '&' && input[i + 1] == '>') {
            for (int j = 0 ; j < i ; j++) {
                retAry[0][j] = input[j];
            }
            retAry[1] = "&>";
            for (int k = i + 2 ; k < (int)strlen(input) ; k++) {
                retAry[2][k - i - strlen(retAry[1])] = input[k];
            }
        }
        else if (input[i] == '<') {
            for (int j = 0 ; j < i ; j++) {
                retAry[0][j] = input[j];
            }
            retAry[1] = "<";
            for (int k = i + 1 ; k < (int)strlen(input) ; k++) {
                retAry[2][k - i - strlen(retAry[1])] = input[k];
            }
        }
        else if (input[i] == '|') {
            for (int j = 0 ; j < i ; j++) {
                retAry[0][j] = input[j];
            }
            retAry[1] = "|";
            for (int k = i + 1 ; k < (int)strlen(input) ; k++) {
                retAry[2][k - i - strlen(retAry[1])] = input[k];
            }
        }
        else {
            retAry[0] = input;
        }
    }
    //trimmin
    retAry[0] = trim(retAry[0]);
    retAry[2] = trim(retAry[2]);
    return retAry;
}

int hasRedirector(char * input) {
    char * first;
    if (strchr(input, '>') || strchr(input, '<') || strchr(input, '|')) {
        return 1;
    }
    else if ((first = strchr(input, '&')) != '\0') {
        first++;
        if (*first == '>') {
            return 1;
        }
        else {
            return 0;
        }
    }
    else if ((first = strchr(input, '2')) != '\0') {
        first++;
        if (*first == '>') {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

void execute(char * data) {
  char ** command = parse_line(data, " ");
  if ((!command[2]) && (!strcmp(command[0], "cd")))
    executeCD(command[1]);
  else if ((!command[1]) && (!strcmp(command[0], "exit")))
    exit(0);
  else {
    int f;
    int status;
    f = fork();
    if (!f)
      execvp(command[0], command);
    else
      wait(&status);
  }
}

void executeRedirector(char ** input) {
  int fd;
  int stdDup = dup(STDOUT_FILENO);
  if (!strcmp(input[1], "<")) {
    fd = open(input[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execute(input[2]);
  }
  else if (!strcmp(input[1], ">")) {
    fd = open(input[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execute(input[0]);
  }
  dup2(stdDup, STDOUT_FILENO);
}

void executeMain(char * data) {
  int x = hasRedirector(data);
  if (x) {
    char ** redirect = findRedirector(data);
    executeRedirector(redirect);
  }
  else
    execute(data);
}

void executeCD(char * dir) {
    //tilde expansion
    if (dir[0] == '~') {
        chdir(getenv("HOME"));
        int i;
        for (i = 0 ; i < (int)strlen(dir) - 2 ; i++) {
            dir[i] = dir[i + 2];
        }
        dir[i] = '\0';
    }
    chdir(dir);
}
