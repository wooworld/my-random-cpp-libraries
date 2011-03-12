#include "../../lib/numeric_types.h"
#include "_4x4Matrix.h"

using namespace std;

int main( int argc, char * argv[] ) 
{
  _4x4Matrix m;
  
  for ( uint8 i = 0; i < 16; i++ )
  {
    m[i] = 42.42*(15-i);
  } 
  
  m.print();
  
  m = m - m;
  
  m.print();
  
  for ( uint8 i = 0; i < 16; i++ )
  {
    m[i] = i;
  } 
  
  m.print();
  
  m = m + m;
  
  m.print();
  
  m = m + m - m;
  
  m.print();
  
  _4x4Matrix n;
  
  n[0] = 1.0;
  n[5] = 1.0;
  n[10] = 1.0;
  n[15] = 1.0;
  
  n.print();
  
  m = m * n;
   
  m.print();
  
  return 0;
}
