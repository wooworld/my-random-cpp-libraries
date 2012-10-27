#include "node.h"
#include "calculator.h"
#include "communication_server.h"
#include <iostream>

using std::cout;
using std::endl;

int main( int argc, char* argv[] ) {
  int error = 0;

  // Set the node ID
  error = node_set_id( argv[1] );
  if ( error != 0 ) {
    cout << "Error in setting node ID" << endl;
    return error;
  }
  
  // Start communications
  error = comm_start( argv[2] );
  if ( error != 0 ) {
    cout << "Error in starting communications" << endl;
    return error;
  }
  
  cout << "Communication server started" << endl;  
  
  // Start calculations
  error = calc_start();
  if ( error != 0 ) {
    cout << "Error in starting calculations" << endl;
    return error;
  }
  
  // Wait for calculations to complete
  calc_to_completion();
  
  // Calculate CS entry averages and store
  error = node_submit_results();
  if ( error != 0 ) {
    cout << "Error in submitting results" << endl;
    return error;
  }
  
  // Nothing...
  error = node_print_results();
  if ( error != 0 ) {
    cout << "Error in printing results" << endl;
    return error;
  }
  
  // Shuts down the node 
  error = node_clean_up();
  if ( error != 0 ) {
    cout << "Error cleaning up" << endl;
    return error;
  }

  return 0;
}