#include <stdlib.h>
#define KE_RUNNING =0
#define KE_READY =1
#define KE_BLOCKED =2
#define KE_NEW =3


struct pcb{
	int STAT;
	int P_ID;
	int PC;
	int R0;
    int R1;
    int R2;
    int R3;
    int R4;
    int R5;
    int R6;
    int R7;
    int R8;
    int R9;
    int R10;
    int R11;
    int R12;
    int R13;
    int R14;
	int R15;
    int CPU_TIME;
};

int ke_current_user_time(){
	/*...*/
	return 0;
}

void ke_reset_current_user_time(){
	/*...*/
}

void ret(){
	/*...*/	
}

void set_current_process(int pid){
	/*...*/
}

void ke_context_switch(pcb* pcb_0, pcb* pcb_1){
	
	
	//Guardo el contexto del proceso anterior
	pcb_0->R0 = R0;
	pcb_0->R1 = R1;
	pcb_0->R2 = R2;
	/*...*/
	pcb_0->R15 = R15;
	
	//Guardo el tiempo de ejecucion viejo y lo actualizo
	pcb_0->CPU_TIME = ke_current_user_time();
	ke_reset_current_user_time();
	
    //Cambio el estado del proceso
	pcb_0->STAT = KE_BLOCKED;
    
	//Cargo a los registros el contexto del proceso nuevo
	R0 = pcb_1->R0;
	R1 = pcb_1->R1;
	R2 = pcb_1->R2;
	/*...*/
	R15 = pcb_1->R15;
	
	//Actualizo el estado del nuevo proceso
	pcb_1->STAT = KE_RUNNING;

	set_current_process(pcb_1->P_ID);
	ret();
}
