#include "dodrio.h"
#include "scheduler.h"

int  main(void) {  
  //Initialize the robit
  initRobit();
  
  // Make some aperiodic tasks
  approachTrack(); 
	
  while (1) {
    scheduler();
  }
 
  return 0;  
}
