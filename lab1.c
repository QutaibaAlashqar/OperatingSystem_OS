/// QUTAIBA ALASHQAR, 20290036;
/// OS lab_1;


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<unistd.h>


int function_1(int []);


void main(){

	pid_t pid;
	int result_1 = 0;
	int result_2 = 0;
	int numbers[4];

	for (int i = 0; i < 4; i++){
		scanf("%d", &numbers[i]);
	}
	
	pid = fork();
	
	
	if (pid < 0) {
		printf("something wrong, error!!!\n");
	  	exit(0);
	}
	
	else if (pid == 0) {
		printf("Server has received a shared memory of four integers...\n");
		printf("Server has attached the shared memory...\n");
		printf("Server has filled %d %d %d %d in shared memory...\n", numbers[0], 			numbers[1], 				numbers[2], numbers[3]);
		printf("Server is about to fork a child process...\n");
		result_1 = function_1(numbers);
		exit(0);
	}
	  
	wait(&result_1);
	
	for (int i = 0; i < 4; i++){
		result_2 += numbers[i];
	}
	
	
	
	printf("Server has detected the completion of its child...\n");
	
	wait(&result_2);
	
	printf("Parent sum of shared memory %d \n", result_2); 
	printf("Server has detached its shared memory...\n");
	printf("Server has removed its shared memory...\n");
	printf("Server exits...\n");
	
	exit(0);
	
}


int function_1(int num[]){

	int sonuc = 0;
	for (int i = 0; i < 4; i++){
		sonuc += num[i];			
	}
	
	printf("   Client process started\n");
	printf("   Client found %d %d %d %d in shared memory\n", num[0], 			num[1], num[2], num[3]);
	printf("   Client sum of shared integer values %d \n", sonuc);
	printf("   Client is about to exit\n");
	
	return (sonuc);
}
    
