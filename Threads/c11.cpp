#include <iostream>
#include <unistd.h>
#include <thread>

void hilo (int& num)
{
 std::cout << num;
 while (num < 70)
 {
  num++;
  std::cout << num << std::endl;
  sleep(1);
 }
};

int main()
{
 int i;
 i=0;
 std::cout << "Creando Hilo" << std::endl;
 std::thread hil;
 hil =std::thread(hilo, std::ref(i));
 
 
 while (i != 50)
 {
  i--;
  std::cout << i << std::endl;
  sleep(2);
 }
 
 std::cout << "Hemos llegado al: " << i << std::endl;
 hil.join();
 std::cout << "Valor final de variable: " << i << std::endl;
 return 0;

}
