#ifndef MYSH_H
#define MSH_H

/*headers*/
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define BUFFER_SIZE 80
/*function decleration*/

int my_cd(char **args);      /* This funtion execute the cd command */
int my_pwd(char **args);     /*This function execute the pwd command */
int my_exit(char **args);    /*THis funtion execute the exit command */
int my_set(char **args);     /*THis function execute the environment set command */
void start();                /*THis is the shell begining/initial command */

char *my_readline();
char **my_div_line(char *line);
int my_execute(char **args);
int my_pipe(char **args);
int my_io(char **args);
int backgr(char **args);
#endif
