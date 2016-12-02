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
                return retAry;
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
                return retAry;
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
                    return retAry;
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
                    return retAry;
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
            return retAry;
        }
        else if (input[i] == '<') {
            for (int j = 0 ; j < i ; j++) {
                retAry[0][j] = input[j];
            }
            retAry[1] = "<";
            for (int k = i + 1 ; k < (int)strlen(input) ; k++) {
                retAry[2][k - i - strlen(retAry[1])] = input[k];
            }
            return retAry;
        }
        else if (input[i] == '|') {
            for (int j = 0 ; j < i ; j++) {
                retAry[0][j] = input[j];
            }
            retAry[1] = "|";
            for (int k = i + 1 ; k < (int)strlen(input) ; k++) {
                retAry[2][k - i - strlen(retAry[1])] = input[k];
            }
            return retAry;            
        }
        else {
            retAry[0] = input;
            return retAry;
        }
    }
    //will never reach here
    return retAry;
}

//redirect based on the stuf; first 
void executeRedirector(char ** input) {
    //if there aren't any redirectors
    if (!input[1]) {
        executeMain(input[0]);
    }
    else {
        //if the second part has no redirectors in it
        if (!hasRedirector(input[2])) {
            if (!strcmp(input[1], ">>")) {
                
            }
            else if (!strcmp(input[1], ">")) {
                //continue like this
            }
        }
        else {
            
        }
    }
    
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

void executeMain(char * data) {
  char ** command = parse_line(data, " ");
  if (!strcmp(command[0], "cd"))
    chdir(command[1]);
  else if (!strcmp(command[0], "exit"))
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

