#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

long j;
void *hilo (void *datos)
{
  j = (long)datos;
 while (j < 70)
 {
  j++;
  std::cout << j << std::endl;
  sleep(1);
 }
 pthread_exit(&j);
 return 0;
}

int main()
{
 pthread_t thread;
 pthread_attr_t attr;
 int rc;
 long *status;
 j=0;
 pthread_attr_init(&attr);
 pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

 std::cout << "Creando Hilo." << std::endl;
 rc = pthread_create(&thread, &attr, hilo, (void *)j);
 if (rc)
 {
  std::cout << "Error creando el hilo, " << rc << std::endl;
  return -1;
 }

 pthread_attr_destroy(&attr);
 j=100;

 while (j != 50)
 {
  j--;
  std::cout << j << std::endl;
  sleep(2);
 }
 
 std::cout << "Hemos llegado al: " << j << std::endl;
 rc = pthread_join(thread, (void**)&status);
 if (rc)
 {
  std::cout << "Imposible unirse" << std::endl;
  return -1;
 }
 
 std::cout << "Saliendo con resultado de thread: " << *status << std::endl;
 return 0;
}


