/*@Mayank Srivastava
 * This section of the code works for the pipe Unix implementation: it support atmost 2 pipes
 */




#include "mysh.h"
int my_pipe(char **args)
{
	char stri[50];
	int i=0,t=0;
	char *p_s; int len=0; 
        char ch='|'; char ccmd1[20],ccmd2[20],ccmd3[20],ccmd11[10],ccmd21[10],ccmd31[10],ccmd12[10],ccmd22[10],ccmd32[10];
        int con1=0,con2=0,con3=0,l12=0,l22=0,l32=0,stat=0,l1=0,l2=0,l3=0;
        int child[3];
        int fds[2],fds1[2];
        char *argvr[3];
        ccmd12[0]='\0';ccmd22[0]='\0';ccmd32[0]='\0';
	//printf("Inside file\n");
	strcpy(stri,args[0]);

	if(args[1]!=NULL){
	stri[strlen(stri)]=' ';
	strcat(stri,args[1]);}
	stri[strlen(stri)]='\0';
	//printf("%s \n",stri);
	for(i=0;i<strlen(stri);i++)
	{
		if('|'==stri[i])
			t++;
	}
	/*
	if(t==0)
		printf("Not found\n");
	if(t>0)
		printf("found %d\n",t);
	
	*/
	if(t>0)
	{
		//strcpy(stri,argv[1]); i=0;
		len=strlen(stri);
		if(t==1)
		{
			//int stat=0,l1=0,l2=0,x1=0,y1=0;
			for(i=0;i<len;i++)
			{
				if(stri[i]=='|'){
					stat++;
					continue;}
				if(stat==0)
				{
					ccmd1[l1]=stri[i]; l1++;
				}
				if(stat==1)
				{
					ccmd2[l2]=stri[i]; l2++;
				}
				ccmd1[l1]='\0';ccmd2[l2]='\0';
			}
			l1=0;l2=0;
			for(i=0;i<strlen(ccmd1);i++)
			{
				if((ccmd1[i]==' ')&&(con1==0))
				{
					con1++;
					continue;
				}
				if(con1==0)
				{
					ccmd11[l1]=ccmd1[i];
					l1++;
				}
				if(con1>0)
				{
					ccmd12[l12]=ccmd1[i];
					l12++;
				}
			}
			for(i=0;i<strlen(ccmd2);i++)
			{
				if((ccmd2[i]==' ')&&(con2==0))
				{
					con2++;
					continue;
				}
				if(con2==0)
				{
					ccmd21[l2]=ccmd2[i];
					l2++;
				}
				if(con2>0)
				{
					ccmd22[l22]=ccmd2[i];
					l22++;
				}
			}
			ccmd11[l1]='\0';ccmd21[l2]='\0';
			ccmd12[l12]='\0'; ccmd22[l22]='\0';
		}
		if(t==2)
		{
			//int stat=0,l1=0,l2=0,l3=0;
			for(i=0;i<len;i++)
			{
				if(stri[i]=='|'){
					stat++;
					continue;}
				if(stat==0)
				{
					ccmd1[l1]=stri[i]; l1++;
				}
				if(stat==1)
				{
					ccmd2[l2]=stri[i]; l2++;
				}
				if(stat==2)
				{
					ccmd3[l3]=stri[i]; l3++;
				}
			}

			ccmd1[l1]='\0';ccmd2[l2]='\0';ccmd3[l3]='\0';
			l1=0;l2=0;l3=0;
			for(i=0;i<strlen(ccmd1);i++)
			{
				if((ccmd1[i]==' ')&&(con1==0))
				{	
					con1++;
					continue;
				}
				if(con1==0)
				{
					ccmd11[l1]=ccmd1[i];
					l1++;
				}
				if(con1>0)
				{
					ccmd12[l12]=ccmd1[i];
					l12++;
				}
			}
			for(i=0;i<strlen(ccmd2);i++)
			{
				if((ccmd2[i]==' ')&&(con2==0))
				{	
					con2++;
					continue;
				}
				if(con2==0)
				{
					ccmd21[l2]=ccmd2[i];
					l2++;
				}
				if(con2>0)
				{
					ccmd22[l22]=ccmd2[i];
					l22++;
				}
			}
			for(i=0;i<strlen(ccmd3);i++)
			{
				if((ccmd3[i]==' ')&&(con3==0))
				{
					con3++;
					continue;
				}
				if(con3==0)
				{
					ccmd31[l3]=ccmd3[i];
					l3++;
				}
				if(con3>0)
				{
					ccmd32[l32]=ccmd3[i];
					l32++;
				}
			}
			ccmd11[l1]='\0';ccmd21[l2]='\0';ccmd31[l3]='\0';
			ccmd12[l12]='\0';ccmd22[l22]='\0';ccmd32[l32]='\0';
		}
	}
//	printf("%s %s %s\n",ccmd1,ccmd2,ccmd3);
//	printf("%s %s %s\n",ccmd11,ccmd21,ccmd31);
//	printf("%s %s %s\n",ccmd12,ccmd22,ccmd32);




	//int child[3];
	//int fds[2],fds1[2];
	//char *argvr[3];
	pipe(fds);
	pipe(fds1);
	if (fork()== 0) {
		close(1); dup(fds[1]);  /* redirect standard output to fds[0] */
		close(fds[1]);close(fds[0]);
		argvr[0] = ccmd11;
		if(ccmd12[0]=='\0')
			argvr[1]=NULL;
		else
			argvr[1] =ccmd12 ;
	       	argvr[2] = NULL;
		//execvp(argvr[0],argvr);
		execlp(argvr[0],ccmd1,NULL);
		exit(0);
	}
	if(t==1){
		if (fork() == 0) {
			close(0); dup(fds[0]);  
			close(fds[0]);close(fds[1]);
			// close(1); dup(fds1[1]);
			// close(fds1[0]); close(fds1[1]);
			argvr[0] = ccmd21;
			if(ccmd22[0]='\0')
				argvr[1]=NULL;
			else
			       	argvr[1] = ccmd22;
	     		argvr[2] = NULL;		
			//execvp(argvr[0], argvr);
			execlp(argvr[0],ccmd2,NULL);
			exit(0);
		}
	} 
	if(t==2){
		if (fork() == 0) {
			close(0); dup(fds[0]); 
			close(fds[0]);close(fds[1]);
			close(1); dup(fds1[1]);
			close(fds1[0]); close(fds1[1]);
			argvr[0] = ccmd21;
			if(ccmd22[0]=='\0')
				argvr[1]=NULL;
			else
				argvr[1] = ccmd22;
	     		argvr[2] = NULL;		
			//execvp(argvr[0], argvr);
			execlp(argvr[0],ccmd2,NULL);
			exit(0);
		}
		if(fork() == 0){
			sleep(1);
			close(0); dup(fds1[0]);
			close(fds1[0]); close(fds1[1]);
			close(fds[0]); close(fds[1]);
			argvr[0] = ccmd31;
			if(ccmd32[0]=='\0')
				argvr[1]=NULL;
			else
				argvr[1] = ccmd32;
			argvr[2] = NULL;
			//execvp(argvr[0],argvr);
			execlp(argvr[0],ccmd2,NULL);
			exit(0);
		}
	}
	close(fds[0]); close(fds[1]); close(fds1[0]); close(fds1[1]);
	wait(&child[0]);
	wait(&child[1]);
	wait(&child[2]);

	return 1;  
}

