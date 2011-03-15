#include "../../lib/numeric_types.h"
#include "BitArray.h"
#include <bitset>
#include <string>
#include <iostream>

#include <cstdio>

using namespace std;

int main( int argc, char * argv[] ) 
{
  // proejct abandonded becasue bitset

  printf( "%d\n", sizeof( uint8 ) );
  
  BitArray B;
  
  BitArray C( 15 );
  
  // printf( "sizeof(B.m_data) = %d\n", sizeof(B.m_data) );
  // printf( "sizeof(*(B.m_data)) = %d\n", sizeof(*(B.m_data)) );
  // printf( "sizeof(C.m_data) = %d\n", sizeof(C.m_data) );
  // printf( "sizeof(*(C.m_data)) = %d\n", sizeof(*(C.m_data)) );
  
  printf( "%d\n", B.int_size() );
  printf( "%d\n", B.bit_size() );
  
  printf( "%d\n", C.int_size() );
  printf( "%d\n", C.bit_size() );   
  
  bitset<50> Z;
  
  string ostring = Z.to_string<char,char_traits<char>,allocator<char> >();
  printf( ostring.c_str() );
  printf( "\n" );
  
  Z[10] = 1;
  Z[15] = 1;
  
  Z[58] = 1;
  
  ostring = Z.to_string<char,char_traits<char>,allocator<char> >();
  printf( ostring.c_str() );
  printf( "\n" );
  
  return 0;
}
