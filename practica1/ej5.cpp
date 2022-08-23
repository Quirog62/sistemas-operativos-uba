#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>

int main(){
	pid p = fork();
	if(p==-1) 
		exit(EXIT_FAILURE);
	else if(p == 0){
		printf("Homer");
		pid p = fork();
		if(p==-1)
			exit(EXIT_FAILURE);
		else{
			if(p==0){
				printf("Bart");
			}
		}
		
		pid p = fork();
		if(p==-1)
			exit(EXIT_FAILURE);
		else{
			if(p==0)
				printf("Lisa");
		}

		pid p = fork();
		if(p==-1)
			exit(EXIT_FAILURE);
		else{
			if(p==0)
				printf("Maggie");
		}

	}
	else{
		printf("Abraham");
	}
	return 0;
}
