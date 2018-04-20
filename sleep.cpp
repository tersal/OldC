#include <iostream>
#include <unistd.h>
using namespace std;

int main ()
{
  string cat;
  cat = "\"Hello\"";
  cout << cat << endl;
  sleep(10);
  string dog("\'Goodbye\'");
  cout << dog << endl;
}
