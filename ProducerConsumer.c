#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
# define size 5

pthread_mutex_t mutex;
pthread_t t_prod,t_cons;
int s_full = 0;
int s_empty = 5;
int count=0;
int list[size];


void *produce_item(void *x ){

	pthread_mutex_lock(&mutex); //protect the cs

	int input_reps;
	input_reps = rand()% (5 + 1 - 0) + 0; //Generate random repetion(0~5)
	for (int i=0; i<input_reps; i++){
  
		if (s_empty !=0){
  	  	//add new value into buffer
	  	int input;
	  	input = rand()% (10 + 1 - 0) + 0; //Generate number from 0-10
	  	printf("\nNumber adding to stack is %d\n",input );
	  	list[count]=input;
	  	count = count + 1;
	  	s_empty = s_empty - 1;
	  	s_full = s_full + 1;
	  
	  	printf("Current counts of element in buffer is %d, avaliable space is %d\n", s_full, s_empty);	
		}
	  
		else if(s_empty == 0){
		printf("Currently there's no empty space for addtional value\n");
		}
	}	

 	pthread_mutex_unlock(&mutex);
 	pthread_exit(NULL);
}


void *consume_item(void *x)
{

	pthread_mutex_lock(&mutex); //protect the cs
  
	int output_reps;
	output_reps = rand()% (5 + 1 - 0) + 0; //Generate random repetion(0~5)
	for (int i=0; i<output_reps; i++){
  
		if (s_full !=0){
  
  			int output;
	  		output = list[count-1];
	  		count = count - 1;
  			printf("Number consumed is %d\n",output);
  			s_empty = s_empty + 1;
  			s_full = s_full - 1;
  			printf("Current element in buffer is %d, avaliable space is %d\n", s_full, s_empty);
  		}

  		else if (s_full == 0){
			printf("Currently there's no extra element to consume\n");
  		}
	}
  	pthread_mutex_unlock(&mutex);
  	pthread_exit(NULL);
}


int main (){

while(1){ 
  	pthread_create(&t_prod,NULL,produce_item,NULL); //create producer thread
  	pthread_create(&t_cons,NULL,consume_item,NULL); //create consumer thread
  	
  	pthread_join(t_prod,NULL); //Waiting for producer thread done
  	pthread_join(t_cons,NULL); //Waiting for consumer thread done
  	}

  	return 0;
}
