#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>


int main(){
	pid_t p = fork();
	if(p==-1) 
		exit(EXIT_FAILURE);
	else if(p == 0){
		pid_t p = fork();
		if(p==-1) exit(EXIT_FAILURE);
        else if(p==0){
            printf("Bart\n");
        }
        else{
            pid_t p = fork();
            if(p==-1) exit(EXIT_FAILURE);
			else if(p==0){
				printf("Lisa\n");
			}
			else{
				pid_t p = fork();
				if(p==-1) exit(EXIT_FAILURE);
				else if(p==0){
					printf("Maggie\n");
				}
				else{
					waitpid(p,NULL,0);
					printf("Homer\n");
				}
			}
        }
	}
	else{
        waitpid(p,NULL,0);
		printf("Abraham\n");
	}
	return 0;
}
