#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <signal.h>
#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



int main(int argc, char* argv[]) {
	int status;
	long int orig_rax;
	long int rsi;
	pid_t child;

	if (argc <= 1) {
		fprintf(stderr, "Uso: %s comando [argumentos ...]\n", argv[0]);
		exit(1);
	}

	/* Fork en dos procesos */
	child = fork();
	if (child == -1) { perror("ERROR fork"); return 1; }
	if (child == 0) {

		ptrace(PTRACE_TRACEME, 0, NULL,NULL);

		/* S'olo se ejecuta en el Hijo */
		execvp(argv[1], argv+1);
		/* Si vuelve de exec() hubo un error */
		perror("ERROR child exec(...)"); exit(1);
	} else {
		/* S'olo se ejecuta en el Padre */

		while(1) {
			if (wait(&status) < 0) { perror("waitpid"); break; }
			if (WIFEXITED(status)) break; /* Proceso terminado */

			orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX,NULL);	
			rsi = ptrace(PTRACE_PEEKUSER,child,8 * RSI,NULL);
            //El rsi, rdi y orig_rax tienen que ver por los parametros de la función kill
			if(orig_rax == SYS_kill & rsi == SIGKILL){
				printf("El proceso %d ha intentado enviar SIGKILL y por eso ha sido detenido.\n",child);
				ptrace(PTRACE_KILL,child);
				break;
			}
			else{
				ptrace(PTRACE_SYSCALL,child,0,0);
			}
		}
		ptrace(PTRACE_DETACH, child, 0, 0);
	}
	return 0;
}
