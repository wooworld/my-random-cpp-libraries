#include "../../lib/numeric_types.h"
#include "../../lib/numeric_constants.h"
#include "_4x4Matrix.h"
#include "_4x4Matrix_Identity.h"
#include "_3x3Matrix.h"


#include "_3DFrame.h"

#include <cstdio>

using namespace std;

int main( int argc, char * argv[] ) 
{
  /* 
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
  
  _4x4Matrix_Identity I;
  
  I.print();
  
  m = m * I;
  
  m.print();
  
  _3x3Matrix t;
  
  t.print();
  
  for ( uint8 i = 0; i < 9; i++ )
  {
    t[i] = i;
  } 
  
  t.print();
  
  _3x3Matrix t_i;
  t_i[0] = 1.0;
  t_i[4] = 1.0;
  t_i[8] = 1.0;
  
  t = t * t_i;
  
  t.print(); 
  */
  
  printf( "-------------------------------------------------\n" );
  
  _3DFrame F;
  
  F.print();
  
  F = F * F;
  
  F.print();
  
  F.get_rotation_matrix().print();
  
  F.print_rot();
  
  F.print_trans();  
  
  F.trans_curr( 1.0, 2.0, 3.0 );
  
  F.print();
  
  F.trans_x_curr( 5.0 );
  
  F.print();
  
  F.trans_y_curr( 5.0 );
  
  F.print();
  
  F.trans_z_curr( 5.0 );
  
  F.print();
  
  F.rot_curr_rad( _PI/2, _PI/2, _PI/2 );
  
  F.print();
  
  F.rot_curr_deg( -90.0, -90.0, -90.0 );
  
  F.print();
  
  
  return 0;
}
