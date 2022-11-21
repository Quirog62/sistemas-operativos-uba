#include <signal.h> /* constantes como SIGINT*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int count = 0;
pid_t hijo = 0;

void signal_handler(int sig){
	write(1,"Ya va!\n",8);
	count++;
}

void signal_handler2(int sig){
	wait(NULL);
	exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
  	
	if(argc <= 1){
		printf("Uso: ./hai commando [argumentos ...]\n");
		exit(1);
	}

	hijo = fork();

	if (hijo == 0)
	{
		signal(SIGURG,signal_handler);
		while(count < 5){}
		kill(getppid(),SIGINT);
		execvp(argv[1], (char*const*)(argv+1));
		exit(EXIT_SUCCESS);
	}
	else{
		signal(SIGINT,signal_handler2);
		while(1){
			sleep(1);
			write(1,"Sup!\n",6);
			kill(hijo,SIGURG);
		}
	}
	return 0;
}
