# ksh - Koopa Shell
<i>NOT to be confused with kornshell, which is probably useful and probably doesn't segfault ~50% of the time.</i>

<img src="http://image.flaticon.com/icons/svg/60/60758.svg" height="150" />
<img src="http://vignette2.wikia.nocookie.net/nintendo/images/8/83/KoopaNSMB.png/revision/latest?cb=20110724132501&path-prefix=en" height="150" />

## Features
```
TBD
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
        	  char delim 
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
  
ksh.h
  TBD
  
ksh.c
  TBD
```
