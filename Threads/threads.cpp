#include <string>
#include <iostream>
#include <thread>

void task1 (std::string msg)
{
    std::cout << "task 1 says: " << msg;
}

int main()
{
  std::thread t1(task1, "hello");
 
  t1.join();
  return 1;
}
