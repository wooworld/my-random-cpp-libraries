#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

int main() 
{    
  int N = 11;    // dimension
  int c = N*N;   // number that goes in each spot. Starts at N*N, goes down to 1
  int A[11][11]; // the spiral to fill
  int i, j, k;   // loop indices

  // The idea for constructing the spiral is to fill one "shell level" at a time.
  // That is, one ring around the array at a time. From the outside in.
  // From the top right, to the top left, to the bottom left, to the top right.
  // To do this we keep a number, j, that tracks how many columns in from the right
  // side we are and a number, i, that tracks how many rows below the top we are.
  // We start each shell level fill (each iteration of the big for loop) at 
  // i,j which represent the top right corner of each shell level. Then fill 
  // the shell, rinse and repeat. 

  // i tracks how many rows down from the top side we are
  // j tracks how many columns from the right side we are
  for ( i = 0, j = N-1; j > i; i++, j-- )
  {
    // leftward fill of the current row, i, between the columns for this shell
    // with c, then decrement c
    for ( k = j; k > N-1-j; k-- )
    {
      A[i][k] = c;
      c--;
    }

    // downward fill of the current column, N-1-j, between the rows for this shell
    // with c, then decrement c
    for ( k = i; k < N-1-i; k++ )
    {
      A[k][N-1-j] = c;
      c--;
    }

    // rightward fill of the current row, N-1-i, between the columns for this shell
    // with c, then decrement c
    for ( k = N-1-j; k < j; k++ )
    {
      A[N-1-i][k] = c;
      c--;
    }

    // upward fill of the current column, j, between the rows for this shell
    // with c, then decrement c
    for ( k = N-1-i; k > i; k-- )
    {
      A[k][j] = c;
      c--;
    }
  }

  // The loop above doesn't catch the center element. CATCH IT!
  A[N/2][N/2] = 1;

  // Print out the array
  for ( i = 0; i < N; i++ ) 
  {
    for ( j = 0; j < N; j++ )
    {
      cout << A[i][j] << " ";
    }
    cout << endl;
  }

  cin.get();
}