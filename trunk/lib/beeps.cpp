#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

int main() {

  srand(time(NULL));

  int freq, length;

  do {
  
    freq = rand() % 50 + 2000;
    length = rand() % 50;
  
    Beep(freq,length);

  } while (0 != 1);

  return 0;

}