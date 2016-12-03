# ksh - Koopa Shell
by Ayman Ahmed and Jason Chua

<img src="http://image.flaticon.com/icons/svg/60/60758.svg" height="150" />
<img src="http://vignette2.wikia.nocookie.net/nintendo/images/8/83/KoopaNSMB.png/revision/latest?cb=20110724132501&path-prefix=en" height="150" />

## Features
```
- Forks and executes commands
- Executes multiple commands by parsing on semicolons
```
## Attempted
```
TBD
```
## Bugs
```
TBD
```
## Files and Function Headers
```
parse.h
  int count_tokens(char *line, char delim);
  char ** parse_line(char *line);
  char * trim(char *line);
  
parse.c
	Handles all line parsing fucntions
	/*======== int count_tokens() ==========
	Inputs:  char *line
        	  char *delims
	Returns: Number of tokens in line separated by delim

	Counts the number of times the character delim appears in the
	 string line
	The number of tokens is 1 more than the number of appearences 
	of delim
	If delim does not appear, 1 is returned
	====================*/

	/*======== char ** parse_line() ==========
	Inputs:  char *line 
	Returns: Array of strings where each entry is a token 
	separated by delim

	If line contains multiple tokens separated by delim, this 
	function will put each token into an array of strings
	====================*/

	/*======== char * trim() ==========
	Inputs:  char *line 
	Returns: Pointer to the beginning of line

	Removes leading and trailing whitespace on the string line.
	Terminating '\0' is placed at a new location if necessary.
	====================*/

execute.h
  char ** findRedirector(char * input);
  int hasRedirector(char * input);
  void execute(char * data);
  void executeRedirector(char * input);
  void executeMain(char * data);
  void executeCD(char * dir);

execute.c 
	/*======== char ** findRedirector() ==========
	Inputs:  char * input
	Returns: Array separating commands and redirector

	Finds the redirector in the given string and returns
	an array with the commands/redirectors separated.
	====================*/
	
	/*======== int hasRedirector() ==========
	Inputs:  char * input
	Returns: 0 or 1

	Returns 0 or 1 depending on whether or not there is
	a redirector in the input.
	====================*/
	
	/*======== void execute() ==========
	Inputs:  char * data
	Returns: 

	Executes a single command.
	====================*/
	
	/*======== void executeRedirector() ==========
	Inputs:  char * input
	Returns: 

	Executes commands that have redirectors.
	====================*/
	
	/*======== void executeMain() ==========
	Inputs:  char * data
	Returns: 

	Main execute function that takes the whole line as an input.
	Runs execute() or executeRedirector().
	====================*/
	
	/*======== void executeCD() ==========
	Inputs:  char * dir
	Returns: 

	Changes directories.
	====================*/
	
ksh.h
  void ksh_run(char * input);
  
ksh.c
	/*======== void ksh_run ==========
	Inputs:  char * input
	Returns: 

	Separates input line by semicolons and runs executeMain()
	on each segment.
	====================*/
```
