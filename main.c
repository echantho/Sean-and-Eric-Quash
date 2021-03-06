#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

static char* currentDir;

#define colorNormal  	"\x1B[0m"
#define colorRed  	"\x1B[31m"

//Display the current user? and directory
void showPrompt()
{
	currentDir = (char*) calloc(1024, sizeof(char));
	printf("\n[Quash 2015] %s: ", getcwd(currentDir, 1024));
}

int main(int argc, char *argv[], char *envp[])
{
	pid_t pid1;
	
	char tmp[10] = "";
	char input = '\0';
	
	showPrompt();
	while(input != EOF)
	{
		input = getchar();
		switch(input) 
		{
			case '\n':
				if (!strcmp(tmp,"ls"))
				{
					pid1 = fork();
					
					if (pid1 == 0)
						execve("/bin/ls", argv, envp);
					else
						wait(NULL);
				}
				else if (!strcmp(tmp,"quit") || !strcmp(tmp,"exit"))
				{
					printf("Exiting\n");
					exit(EXIT_SUCCESS);
				}
				else
				{
					printf(colorRed "IDK what to do with: %s\n" colorNormal, tmp);
				}
				
				bzero(tmp, sizeof(tmp));
				showPrompt();
				break;
				
			default: strncat(tmp, &input, 1);
				break;
		}
	}
	
	printf("\n");
	return 0;
}

