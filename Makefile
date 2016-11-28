ksh: ksh
	gcc parse.c execute.c ksh.c -o ksh

run:
	./ksh
