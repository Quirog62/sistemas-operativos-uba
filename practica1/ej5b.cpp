#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

int main(){
	pid p = fork();
	if(p==-1) 
		exit(EXIT_FAILURE);
	else if(p == 0){
		pid p = fork();
		if(p==-1) exit(EXIT_FAILURE);
        else if(p==0){
            printf("Bart");
        }
        else{
            pid p = fork();
            if(p==-1) exit(EXIT_FAILURE);
			else if(p==0){
				printf("Lisa");
			}
			else{
				pid p = fork();
				if(p==-1) exit(EXIT_FAILURE);
				else if(p==0){
					printf("Maggie");
				}
				else{
					wait_for_child(p);
					printf("Homer");
				}
			}
        }
	}
	else{
        wait_for_child(p);
		printf("Abraham");
	}
	return 0;
}
