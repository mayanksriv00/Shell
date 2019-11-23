# THis is a Makefile to run multiple files all together
#

all: output myls

output: main.o my_execute.o myshell_command.o my_pipe.o my_io.o backgr.o
	gcc main.o my_execute.o myshell_command.o my_pipe.o my_io.o backgr.o -o output

main.o: main.c
	gcc -c main.c

my_execute.o: my_execute.c 
	gcc -c my_execute.c

myshell_command.o: myshell_command.c
	gcc -c myshell_command.c

my_pipe.o: my_pipe.c
	gcc -c my_pipe.c

my_io.o: my_io.c
	gcc -c my_io.c

backgr.o: backgr.c
	gcc -c backgr.c

myls: myls.c
	gcc myls.c -o myls

clean:
	rm -f *.o output myls
