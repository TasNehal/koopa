ksh: parse.c execute.c ksh.c
	gcc parse.c execute.c ksh.c -o ksh

clean:
	rm ksh

run:
	./ksh
