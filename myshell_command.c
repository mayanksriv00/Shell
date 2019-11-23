/*
 * @Mayank Srivastava
 * THis shell contais both codes of all the commands set,exit,pwd and cd
*/
#include "mysh.h"

/*change directory command*/

int my_cd(char **args)
{
	if(args[1] == NULL)
	{
		fprintf(stderr," argument not present in cd \n");
	}
	else
	{
		if(chdir(args[1]) != 0)
		{
			perror("shell error");
		}
	}
return 1;
}

/*exit from the shell */

int my_exit(char **args)
{
	return 0;
}
/*Getting path*/
int my_pwd(char **args)
{
	char path[256];
	if(getcwd(path,sizeof(path))==NULL)
	perror(" Path pwd error");
	else
	printf("%s \n",path);
	return 1;
}
/*set environment variable*/
int my_set(char **args)
{
	char str[80],str1[10];
	int l=0,i=0,x=0;
	l=strlen(args[1]);
	while(i<8)
	{
		str1[i]=args[1][i];
		i++;
	}
	str1[7]='\0'; i=0;
	if(str1[6]=='=')
	{
		str1[6]='\0';
		for(i=7;i<(strlen(args[1]));i++)
		{
			str[x]=args[1][i];
			x++;
		}
		str[x]='\0';
	}
	/*printf("%s\n %s\n",str1,str);*/

	/*Now setting the environment */
	/*compare whether it is MYPATH */
	if(strcmp("MYPATH",str1)==0)
	{
		/*inside env check*/
		int x=0;
		x=setenv(str1,str,1);
		if(x==0)  /*environment variable set */
		{
			printf("Environment valiable successfully set: Displaying the env variable for this terminal \n");
			printf(" MYPATH = %s \n",getenv("MYPATH"));
		}
		else
		{
			perror("error in creating environment variable");
		}
	}
	else
	{
		perror("The environemnt variable does not match with MYPATH");
	}	
	return 1;
}

