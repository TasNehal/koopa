//will execute things, and will handle redirects and custom commands
#include "execute.h"

//returns array of [string, redirector, string]
//second string can also have redirectors, executemain should do them in order
char ** findRedirector(char * input) {
    char ** retAry = (char * *)malloc(sizeof(char *) * strlen(input));
    for (int a = 0 ; a < 3 ; a++) {
        for (int b = 0 ; b < (int)strlen(retAry[a]) ; b++) {
            retAry[a][b] = '\0';
        }
    }
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
                printf("%s\n\n", retAry[0]);
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
    umask(0);
    int fd;
    int fd2 = dup(0);

    printf("(%s)\n(%s)\n(%s)\n", input[0], input[1], input[2]);
    
    if ((!strcmp(input[1], ">"))) {
        fd = open( input[2], O_CREAT | O_WRONLY | O_TRUNC, 666);
        fd2 = dup(fd);
        dup2(fd, 1);
    }
    else if ((!strcmp(input[1], "2>"))) {
        fd = open( input[2], O_CREAT | O_WRONLY | O_TRUNC, 666);
        fd2 = dup(fd);
        dup2(fd, 2);
    }
    else if ((!strcmp(input[1], ">>"))) {
        fd = open( input[2], O_CREAT | O_WRONLY | O_APPEND, 666);
        fd2 = dup(fd);
        dup2(fd, 1);
    }
    else if ((!strcmp(input[1], "2>>"))) {
        fd = open( input[2], O_CREAT | O_WRONLY | O_APPEND, 666);
        fd2 = dup(fd);
        dup2(fd, 2);
    }
    else if ((!strcmp(input[1], "<"))) {
        fd = open( input[2], O_CREAT | O_RDONLY, 444);
        fd2 = dup(fd);
        dup2(fd, 0);
    }
    //pipe?
    else {
        int fds[2];
        fd2 = dup(1);
        
        int status;          
        int f = fork();
        
        if (f == 0) {
            dup2(fds[1], 1);
            //will have to change this later
            execvp(input[0], &input[0]);
        }
        else {         
            wait(&status);
            dup2(1, fd2);
            close(fds[1]);
        }
    }
    close(fd2);
}

void executeMain(char * data) {
  int x = hasRedirector(data);
  if (x) {
    char ** redirect = findRedirector(data);
    for (int i = 0 ; i < 3 ; i++) {
        redirect[i] = trim(redirect[i]);
    }
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
