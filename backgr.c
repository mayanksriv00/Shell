#include "mysh.h"
int backgr(char **args)
{
	int i=0;
	char str[100];
	pid_t pid;
	int status;
	
	for(i=0;i<(strlen(args[1]));i++)
	{
		if(args[1][i]=='&')
		{
			args[1][i]='\0';
			break;
		}
	}
	printf("args val %s\n%s\n",args[0],args[1]);
	pid=fork();
	if(pid==0)
	{
		//inside child process
		if(execvp(args[0],args)==-1)
		{
			perror("terminal error");
		}
	}
	
	return 1;
}
