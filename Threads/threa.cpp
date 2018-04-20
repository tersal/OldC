#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <string>

#define NUM 5

struct thread_data
{
  int thread_id;
  std::string message;
};

void *PrintHello(void *threadarg)
{
 struct thread_data *data;
 data = (struct thread_data *) threadarg;
 
 std::cout << "Thread ID : " << data->thread_id << std::endl;
 std::cout << "Message : " << data->message << std::endl;

 pthread_exit(NULL); 

};

int main()
{
 
 pthread_t threads[NUM];
 struct thread_data td[NUM];

 int rc;
 int i;
 
 for( i=0; i < NUM; i++) 
 {
  std::cout << "main(): creating thread, " << i << std::endl;
  td[i].thread_id = i;
  td[i].message = "This is message \n";
  rc = pthread_create(&threads[i], NULL, PrintHello, (void *) &td[i]);
  if (rc) 
  {
    std::cout << "Error: unable to create thread, "<< rc << std::endl;
    exit(-1);
  }
 }
 pthread_exit(NULL);
}


