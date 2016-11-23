ksh: ksh
	gcc parse.c main.c execute.c -o ksh

run:
	./ksh
