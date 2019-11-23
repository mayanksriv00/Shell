/*
 * @Mayank Srivastava
 * This section of the code is independent and it works as a replica of ls -la funtion 
 */



#include<stdio.h> 
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<pwd.h>
#include<grp.h>
int main(int argc, char *argv[])
{
	if(argv[1]==NULL)
	{
		argv[1]="./";
	}
	const char *path=argv[1];
	struct dirent *de;
	struct stat buf;
	DIR *dr=opendir(path);
	struct passwd *nam;
	char buff[512];
	char tim[512],ftim[15];
	int i=0,x=0;
	struct group *gr;
	if(dr==NULL)
	{
		perror("Could not open current directory");
		return 0;
	}
	while((de=readdir(dr))!=NULL)
	{
		/*printf("%s\n",de->d_name);*/
		sprintf(buff,"%s/%s",argv[1],de->d_name);
		stat(buff,&buf);
		printf((S_ISDIR(buf.st_mode))?"d":"-");
		printf((buf.st_mode & S_IRUSR)?"r":"-");
		printf((buf.st_mode & S_IWUSR)?"w":"-");
		printf((buf.st_mode & S_IXUSR)?"x":"-"); 
		printf((buf.st_mode & S_IRGRP)?"r":"-");
		printf((buf.st_mode & S_IWGRP)?"w":"-"); 
		printf((buf.st_mode & S_IXGRP)?"x":"-"); 
		printf((buf.st_mode & S_IROTH)?"r":"-"); 
		printf((buf.st_mode & S_IWOTH)?"w":"-"); 
		printf((buf.st_mode & S_IXOTH)?"x":"- ");
		nam=getpwuid(buf.st_uid);
		printf(" %d ",buf.st_nlink);
		if(nam!=NULL)
			printf("%s ",nam->pw_name);
		else
			perror("Error in retriving user id");
		gr=getgrgid(buf.st_gid);
		printf(" %s ",gr->gr_name);
		//printf("%d ",buf.st_nlink);
		//printf("%U %G ",buf.st_uid,buf.st_gid);	
		printf(" %zu ",buf.st_size);
		//printf("%s ",asctime(&buf.st_mtime));
		strcpy(tim,ctime(&buf.st_mtime));
		//tim=asctime(&buf.st_mtime);
		//printf("%s ",tim);
		for(i=0;i<strlen(tim)-1;i++)
			printf("%c",tim[i]);
		printf(" ");
		/*for(i=0;i<11;i++)
		  {
		  ftim[x]=tim[i];
		  x++;
		  }*/
		//ftim[11]='\0';
		//printf("%s ",ftim);
		//tim=ctime(&buf.st_mtime);
		//printf("%s %d %d ",tm_mon,tm_mday,tm_year);
		printf(" %s\n",de->d_name);
	}
	/*using stat */
	/*	while((de==stat(argv[1],&buf))!=NULL)
		{
		printf("Inside stat\n");
		printf("%s \n",ctime(&buf.st_ctime));
		}

*/	closedir(dr);
	return 0;
}
