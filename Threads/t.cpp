#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

#define NUM 5

void *wait(void *t)
{
  int i;
  long tid;

  tid = (long)t;

  sleep(1);
  std::cout << "Sleeping in thread " << std::endl;
  std::cout << "Thread with id " << tid << "... exiting" << std::endl;
  pthread_exit(NULL);
}

int main ()
{
  int rc;
  int i;
  pthread_t threads[NUM];
  pthread_attr_t attr;
  void *status;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(i=0; i < NUM; i++)
  {
   std::cout << "main(): creating thread, " << i <<std::endl;
   rc = pthread_create(&threads[i], NULL, wait, (void *)i );
   if (rc) 
   {
    std::cout << "Error: unable to create thread,  "<< rc << std::endl;
    return -1;
   }
  }
 
  pthread_attr_destroy(&attr);
  for (i=0; i< NUM; i++)
  {
   rc = pthread_join(threads[i], &status);
   if (rc)
   {
     std::cout << "Error: unable to join, " << rc << std::endl;
     return -1;
   }
    std::cout << "Main: completed thread id: " << i;
    std::cout << " exiting with status: " << status << std::endl;
   }
   std::cout << "Main: program exiting." << std::endl;
   pthread_exit(NULL);
 }
