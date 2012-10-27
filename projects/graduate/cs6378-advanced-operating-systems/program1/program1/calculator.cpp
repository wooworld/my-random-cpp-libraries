#include "calculator.h"

#include "communication_server.h"
#include "str_manip.h"
#include <iostream>
#include <string>
#include <fstream>
#include "globals.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

thread_t calc_thread_id;
concurrent_queue<msg_t> calc_msg_q;

// Calculator setup
int calc_start() {
  int error = -1;

  // Spawn calculation thread
  error = pthread_create( &(calc_thread_id.id),
                          NULL,
                          calc_thread_start,
                          &calc_thread_id );
  if ( error != 0 ) {
    calc_thread_id.state = T_STATE_STOP;
    cout << "calculator: failed to create calculator thread" << endl;
    return -1;
  }
  calc_thread_id.state = T_STATE_ACTIVE;
  
  return 0;
}

// Thread entry functions
void* calc_thread_start( void* data ) {
  thread_t* my_info = reinterpret_cast<thread_t*>(data);
  
  unsigned int num_iters = 20;
  unsigned int min_wait  = 10;
  unsigned int max_wait  = 20;
  unsigned int cs_wait   = 3;
  
  // Request critical section num_iters times
  for ( unsigned int i = 0; (i < num_iters) && (my_info->state == T_STATE_ACTIVE); i++ ) {
    wait_ms_between( min_wait, max_wait );
    comm_request_cs();
    //cout << "Calculator is in cs" << endl;
    wait_ms_duration( cs_wait );
    comm_release_cs();
  }
  
  // Even numbered node, alter the wait intervals
  if ( !(NODE_ID & 1) ) {
    min_wait = 40;
    max_wait = 50;
  }
  
  // Request critical section num_iters times
  for ( unsigned int i = 0; (i < num_iters) && (my_info->state == T_STATE_ACTIVE); i++ ) {
    wait_ms_between( min_wait, max_wait );
    comm_request_cs();
    //cout << "Calculator is in cs" << endl;
    wait_ms_duration( cs_wait );
    comm_release_cs();
  }

  return NULL;
}

void calc_to_completion() {
  pthread_join ( calc_thread_id.id, NULL );
  
  node_computation_complete = true;
  
  // Wait for all other nodes to finish calculations
  if ( NODE_ID == 0 ) {
    if ( network_nodes_completed != comm_contacts.size() ) {
      comm_computation_complete.wait( comm_computation_complete_mutex );
    }
    
    // Now broadcast that the network is done
    msg_t outgoing;
    outgoing.msg_type = MSG_T_NETWORK_COMPUTATION_COMPLETE;
    outgoing.ts = comm_cs.seq_num;
    comm_broadcast( outgoing );
  }
  
  // Send message to node 0 indicating completion then wait for rest of network
  else {
    msg_t outgoing;
    outgoing.msg_type = MSG_T_NODE_COMPUTATION_COMPLETE;
    outgoing.ts = comm_cs.seq_num;
    outgoing.dest_ID = 0;
    comm_send( outgoing );
    comm_computation_complete.wait( comm_computation_complete_mutex );
  } 
}

// Calculator interaction functions
int calc_stop() {
  calc_thread_id.state = T_STATE_STOP;
  
  pthread_join( calc_thread_id.id, NULL );
  
  return 0;
}