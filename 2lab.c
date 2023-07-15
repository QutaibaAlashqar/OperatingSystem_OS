/// Qutaiba ALASHQAR, 20290036;
/// OS, lab_2;
 

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>


double new_list[500];
int line_counter = 0;
int number_of_threads = 5;
int reminder = 0;
int threadPERline;
int line_counter_file = 0;

int counter_entering_thread = 0;
int number_threads_to_do = 5;
int count_print_off = 1;
int counter_thread_in = 0;
float sum = 0.0;
int flag = 0;




sem_t semaphore_1;


int function_1();


int function_1(){

	float x = line_counter / (float)number_of_threads;
	int xx = line_counter / number_of_threads;
	
	if (x != xx){
		threadPERline = x + 1;
		reminder = ((number_of_threads * threadPERline) - line_counter); 
	}
	else{
		threadPERline = x;
	}

	///	
	if (reminder >= threadPERline){
		
		int y = reminder / threadPERline;
		number_threads_to_do -= y;
		flag = 1;
	}
	
	if ((number_threads_to_do * threadPERline) == line_counter){
			flag = 0;
	}
	
	///		
}


void *function_thread_calling(void *vargp){

	counter_entering_thread++;	

	if (counter_entering_thread == number_threads_to_do && flag == 1){

		for (int i = 0; i <= (line_counter - (count_print_off - 1)); i++){
			printf("Thread %d reads %d. line. The value is %0.2f \n", counter_entering_thread, count_print_off, new_list[count_print_off - 1]);
			sum += new_list[count_print_off - 1];
			count_print_off++;
		}
	}
	
	
	
	else if (counter_entering_thread == number_threads_to_do && ((number_threads_to_do * threadPERline) == line_counter && flag == 0)){

		for (int i = 0; i < (threadPERline); i++){
			printf("Thread %d reads %d. line. The value is %0.2f \n", counter_entering_thread, count_print_off, new_list[count_print_off - 1]);
			sum += new_list[count_print_off - 1];
			count_print_off++;
		}
	}
	
	
	
	else if (counter_entering_thread == number_threads_to_do){
		for (int i = 0; i < (threadPERline - reminder); i++){

			printf("Thread %d reads %d. line. The value is %0.2f \n", counter_entering_thread, count_print_off, new_list[count_print_off - 1]);
			sum += new_list[count_print_off - 1];
			count_print_off++;
		}
	}
	
	    
	else{
		for (int i = 0; i < threadPERline; i++){
			printf("Thread %d reads %d. line. The value is %0.2f \n", counter_entering_thread, 					count_print_off, new_list[count_print_off - 1]);
			sum += new_list[count_print_off - 1];
			count_print_off++;
		}
	}

	printf("Shared Resource: %0.2f\n", sum);

	//sem_wait(&semaphore_1);
	//sem_post(&semaphore_1);

	return (0);
}


int main(){
	
	
	///
	/*
	FILE *the_file;
	the_file = fopen("input.txt", "r");
	if (the_file == NULL){
		printf("Could not open file input.txt");
		return (0);
	}
	for (char line_reder = getc(the_file); line_reder != EOF; line_reder = getc(the_file)){
		if (line_reder == '\n'){
			line_counter_file = line_counter_file + 1;
		}
	}
	fclose(the_file);
	///
	*/
		
	/// 
	//line_counter_file = 1;
	//sem_wait(&semaphore_1);
	double index;
	while (scanf("%lf", &index) != EOF){
		new_list[line_counter] = index;
		line_counter++;
		line_counter_file++;
	}
	//sem_post(&semaphore_1);
	///
	
	function_1();
	
	///
	pthread_t thread_id;
   	for (int i = 1; i <= number_threads_to_do; i++){

		pthread_create(&thread_id, NULL, function_thread_calling, NULL);
		pthread_join(thread_id, NULL);
	}
	///
	
	return 0;	
}
