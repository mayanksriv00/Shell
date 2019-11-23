/*
 * @Mayank Srivastava
 * Tis section of the code is called from the main funciton and the major contribution of this code is to handle the teminal
 */

#include "mysh.h"
#define MY_DELIM " \t\r\n\a"
char *my_command[]=
{
	"cd",
	"exit",
	"pwd",
	"set"
};


int (*my_commands_fun[])(char **) = {
	&my_cd,
	&my_exit,
	&my_pwd,
	&my_set
};

void start()
{
	int stat,te=0,ie=0,pe=0,ge=0,bcg=0;
	char ch_e='|',ch_gg='>',ch_l='<',ch_bg='&';
	char *line;
	char **args;
	do
	{
		te=0,ie=0,pe=0,ge=0,bcg=0;
		printf("$ ");
		line = my_readline();
		args=my_div_line(line);
		//printf("%s \n",args[0]);
		//-------
		if(args[1]==NULL)
		{
			for(ie=0;ie<strlen(args[0]);ie++)
			{
				if((ch_e==args[0][ie])||(ch_gg==args[0][ie])||(ch_l==args[0][ie]))
				{
					//printf("inside error checking condition 1\n");
					if(ch_e==args[0][ie])
					{
						pe++;
					}
					if((ch_gg==args[0][ie])||(ch_l==args[0][ie]))
					{
						ge++;
					}
					te++;
				}
			}
			if(te>0)
			{
				if(pe>0)
				{
					//printf("Inside my_pipe fun\n");
					stat=my_pipe(args);
				}
				if(ge>0)
				{	
					//printf("Inside my_io fun\n");
					stat=my_io(args);
				}
			}
			else	
				stat=my_execute(args);
		}
		else{
			//printf("%ld %s\n",strlen(args[1]),args[1]);
			for(ie=0;ie<strlen(args[1]);ie++)
			{
				if((ch_e==args[1][ie])||(ch_gg==args[1][ie])||(ch_l==args[1][ie])||(ch_bg==args[1][ie]))
				{
					//printf("Inside error checking condition\n");
					if(ch_e==args[1][ie])
					{
						pe++;
					}
					if((ch_gg==args[1][ie])||(ch_l==args[1][ie]))
					{
						ge++;
					}
					if(ch_bg==args[1][ie])
					{
						bcg++;
					}
					te++;
				}
			}
			if(te>0)
			{	
				if(pe>0)
				{
					//printf("Inside my pipe fun\n");
					stat=my_pipe(args);
				}
				if(ge>0)
				{
					//printf("inside my io fun\n");
					stat=my_io(args);
				}
				if(bcg>0)
				{
					//printf("going for backgtoung fun\n");
					stat=backgr(args);
				}
			}
			else
				stat=my_execute(args);
		}
		free(line);
		free(args);
	}while(stat);
}
#if 0
char *my_readline()
{
	char *buffer;
	size_t buffersize = 80;
	size_t carc;
	ssize_t read;
	buffer=(char *)malloc(sizeof(char)*buffersize);
	if(buffer == NULL)
	{
		perror("Unable to allocate buffer");
		exit(1);
	}
	carc=getline(&buffer,&buffersize,stdin);
	if((read != -1)&&(read<=BUFFER_SIZE))
		return buffer;
}
#endif
char *my_readline()
{
	int buffersize = 1024;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffersize);
	int c;

	if(!buffer){
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		c=getchar();
		if(c==EOF){
			exit(EXIT_SUCCESS);
		}
		else if(c=='\n'){
			buffer[position]='\0';
			return buffer;
		} else {
			buffer[position]=c;
		}
		position++;
		if(position>=buffersize){
			buffersize = buffersize+80;
			buffer=realloc(buffer,buffersize);
			if(!buffer){
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
char **my_div_line(char *line)
{
	int buffersize = BUFFER_SIZE;
	int position = 0;
	char *token, **token_backup;
	char **tokens = malloc(buffersize * sizeof(char*));
	if(!tokens)
	{
		fprintf(stderr, "allocation error \n");
		exit(EXIT_FAILURE);
	}
	token=strtok(line,MY_DELIM);
	while(token != NULL)
	{
		tokens[position] = token;
		position++;

		if(position >= buffersize)
		{
			buffersize = buffersize + BUFFER_SIZE;
			token_backup = tokens;
			tokens = realloc(tokens, buffersize*sizeof(char*));
			if(!tokens)
			{
				free(token_backup);
				fprintf(stderr,"allocation error \n");
				exit(EXIT_FAILURE);	
			}
		}
		token = strtok(NULL, MY_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}
int my_buf()
{
	return sizeof(my_command) / sizeof(char *);
}
int ext_com(char **args)
{
	pid_t pid;
	int status;

	/*forking to run the build in unix command */
	pid = fork();
	if(pid==0)
	{
		/*child process*/
		if(execvp(args[0],args) == -1)
		{
			perror("terminal error");
		}
		exit(0);
	}
	else if(pid<0)
	{	
		/* forking error*/
		perror("terminal error");
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}
int my_execute(char **args)
{
	int t=0;
	if(args[0] == NULL) /* NULL command has been entered then*/
		return 1;

	for(t=0;t<my_buf();t++)
	{
		if(strcmp(args[0],my_command[t])==0)
			return(*my_commands_fun[t])(args);
	}
	/*start(args);*/
	return ext_com(args);
}













































































































