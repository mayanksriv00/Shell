/*
 * @Mayank Srivastava
 * This program works for the all ioredirections options specific to assignment 1

*/
#include "mysh.h"
#include <fcntl.h>


int my_io(char **args)
{	
	char str[100],str1[50],str2[50],str3[50],str11[50],str12[50];
        char str_a2[50],str_a3[50];
        int sym_count_g=0,sym_count_l=0,i=0,l1=0,l2=0,l3=0,tt=0,l11=0,l12=0,tt1=0,big=0;
        int a2=0,a3=0;
        int f1,f2;

	//printf("Inside my io function\n");
	strcpy(str,args[0]);

	if(args[1]!=NULL){
	str[strlen(str)]=' ';
	strcat(str,args[1]);}
	str[strlen(str)]='\0';
	//printf("%s \n",str);
	for(i=0;i<strlen(str);i++)
	{
		if(str[i]=='>')
			sym_count_g++;
		if(str[i]=='<')
			sym_count_l++;

	}
	if((sym_count_g + sym_count_l)==1)
	{
		/*divide string*/
		for(i=0;i<(strlen(str));i++)
		{

			if((str[i]=='>')||(str[i]=='<'))
			{
				tt++;
				continue;
			}
			if(tt==0)
			{
				str1[l1]=str[i];
				l1++;
				if(str[i]==' ')
				{
					tt1++;
					continue;
				}
				if(tt1==0)
				{
					str11[l11]=str[i];
					l11++;
				}
				if(tt1==1)
				{
					str12[l12]=str[i];
					l12++;
				}
			}
			if(tt==1)
			{
				str2[l2]=str[i];
				l2++;
			}
		}
		str1[l1]='\0'; str2[l2]='\0'; str12[l12]='\0';str11[l11]='\0';
		//printf("%s %s %s\n",str,str1,str2);
		//printf("%d %d\n",sym_count_g,sym_count_l);
		if(sym_count_l)
		{
			if(fork()==0)
			{	
				close(0);
				f1=open(str2,O_RDONLY, 0777);
				if(f1==-1)
					perror("Error in opening file");
				execlp(str11,str1,NULL);
				exit(0);

			}
		}
		if(sym_count_g)
		{
			if(fork()==0){
				close(1);
				f2=open(str2,O_CREAT|O_WRONLY, 0777);
				if(f2==-1)
					perror("Error in openeing file");
				execlp(str11,str1,NULL);
				exit(0);
			}
		}
	}
	if((sym_count_g + sym_count_l) > 1)
	{
		for(i=0;i<(strlen(str));i++)
		{
			if((str[i]=='>')||(str[i]=='<'))
			{
				tt++;
				continue;
			}
			if(tt==0)
			{
				str1[l1]=str[i];
				l1++;
				if(str[i]==' ')
				{
					tt1++;
					continue;
				}
				if(tt1==0)
				{
					str_a2[a2]=str[i];
					a2++;	
						
				}
				if(tt1==1)
				{
					str_a3[a3]=str[i];
					a3++;
				}
			}
			if(tt==1)
			{
				str2[l2]=str[i];
				l2++;
			}
			if(tt==2)
			{
				str3[l3]=str[i];
				l3++;
			}	
		}
		str1[l1]='\0'; str2[l2]='\0'; str3[l3]='\0'; str_a2[a2]='\0';str_a3[a3]='\0';
		//printf("str=%s \n str1=%s \n str2=%s \n str3= %s\n",str,str1,str2,str3);
		//printf("%d %d\n",sym_count_g,sym_count_l);
		//printf("Hi\n");
		if(fork() == 0)
		{
			close(0);
			f1=open(str2,O_RDONLY, 0777);
			if(f1==-1)
				perror("Error in opening file1");
			close(1);
			f2=open(str3,O_WRONLY|O_CREAT,0777);
			if(f2==-1)
				perror("Error in opening file2");
			execlp(str_a2,str1,NULL);
			exit(0);
		}		
	
	}
	wait(NULL);
	return 1; //should be return 1;
}

