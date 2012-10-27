#ifndef COMMUNICATION_SERVER_H
#define COMMUNICATION_SERVER_H

#include <pthread.h>
#include "ConditionVariable.h"
#include "Mutex.h"
#include "NaiveConcurrentQueue.h"
#include "thread_constructs.h"

#include "network_constructs.h"
#include "CriticalSectionTracker.h"

#include <vector>
using std::vector;

// The threads for the communication server
extern recv_thread_t           comm_listen_thread_id;
extern thread_t                comm_recv_parse_thread_id;
extern vector<recv_thread_t>   comm_recv_thread_ids;
extern thread_t                comm_send_thread_id;

// Queues for message passing between threads
extern concurrent_queue<msg_t> comm_send_q;
extern concurrent_queue<msg_t> comm_recv_q;
extern CriticalSectionTracker  comm_cs;
extern concurrent_queue<cs_stat_entry_t> comm_cs_log;

// Port the network is communicating on
extern int                     comm_port;

// List of contact information for other nodes
extern vector<node_contact_t>  comm_contacts;
extern ConditionVariable       comm_network_joined;
extern Mutex                   comm_network_joined_mutex;
extern ConditionVariable       comm_computation_complete;
extern Mutex                   comm_computation_complete_mutex;

// Communication server setup
int comm_start( char* config_file_path );
int comm_add_contact( const node_contact_t& contact );
int comm_open_connection_once( string address );
int comm_close_connection( unsigned int n );
int comm_open_connection_until( string address );
int comm_open_connections();
int comm_bind_once( int port );
int comm_join_network();

// Thread entry functions
void* comm_listen_thread_start( void* data );
void* comm_recv_thread_start( void* data );
void* comm_recv_parse_thread_start( void* data );
void* comm_send_thread_start( void* data );

// Server interaction functions
int comm_send( msg_t msg );
int comm_broadcast( msg_t msg );
msg_t comm_recv();

int comm_stop();

// Requests and releases control of the critical section
int comm_request_cs();
int comm_release_cs();

#endif