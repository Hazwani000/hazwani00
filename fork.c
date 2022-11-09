#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int fd_1[2];
	int fd_2[2];

	char fixed_str[] = "gmail.com";
	char input_str[100];
	pid_t a;

	if (pipe(fd_1) == -1){
	    fprintf(stderr, "Pipe is FAILED!");
	    return 1;
	}
	
	if (pipe(fd_2) == -1){
	   fprintf(stderr, "Pipe is FAILED!");
	   return 1;
	}

	scanf("%s", input_str);
	a = fork();

	if (a < 0){
	   fprintf(stderr, "fork is FAILED!");
	   return 1;
	}

	else if (a > 0){
		char concatenate_str[100];

		close(fd_1[0]);

		write(fd_1[1], input_str, strlen(input_str) + 1);
		close(fd_1[1]);

		wait(NULL);

		close(fd_2[1]);

		read(fd_2[0],concatenate_str, 100);
		printf("Concatenated string is %s \n ", concatenate_str);
		close(fd_2[0]);
	}

	else{
	     close(fd_1[1]);
	     
	     char concatenate_str[100];
	     read(fd_1[0], concatenate_str, 100);

	     int j = strlen(concatenate_str);
	     int i;
	     for (i=0; i< strlen(fixed_str); i++)
		     concatenate_str[j++] = fixed_str[i];

	     concatenate_str[j] = '\0';

	     close(fd_1[0]);
	     close(fd_2[0]);

	     write(fd_2[1], concatenate_str, strlen(concatenate_str) + 1);
	     close(fd_2[1]);

	     exit(0);

	}

}

