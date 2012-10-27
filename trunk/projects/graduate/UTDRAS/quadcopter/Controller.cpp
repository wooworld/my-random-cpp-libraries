#include "Controller.h"
#include "MatrixMath.h"

Controller::Controller() {
  // Nothing on constsruction
}

Controller::~Controller() {
  // Nothing on destsruction
}

void Controller::start() {
  m_state = CONT_RUN;
}

void Controller::stop() {
  m_state = CONT_STOP;
}

state_t Controller::get_run_state() const {
  return m_run_state;
} 

void Controller::set_run_state( state_t new_state ) {
  m_run_state = new_state;
}

boolean Controller::error() {
  // When checking for error, always assume there IS an error and prove otherwise. 
  boolean error = true;
  
  if ( m_reference - m_current_state is in [m_eps, M_EPS] ) {
    error = false;
  }
  
  return error;
}

boolean Controller::read_sensors() {
  boolean error = true;
  // Read sensor values and store into m_sensor_readings
  // if the reading is successful, flip error to false and return
  
  error = false;
  return error;
}

boolean Controller::update_current_state() {
  // Yes this is formatted in a weird way, but will allow us to expand it later
  // to log errors

  boolean error = true;
  
  error = calculate_current_state();
  
  if ( error ) {
    return true;
  }
  
  error = estimate_current_state();
  
  if ( error ) {
    return true;
  }
  
  return error;
}

boolean Controller::apply( const Matrix& reference ) {
  m_reference = reference; // is operator= defined for Matrix objs?
  
  // difference between current state and reference (amount of change
  // that needs to happen yet!)
  Matrix error;
  
  // Keep sending control signal changes until we reach the reference state
  while ( true ) {
  
    // Check if arrived at reference state
    if ( arrived( m_reference ) ) {
      return true;
    }
    
    // Or if there's an error
    else if ( error() ) {
      return false;
    }
    
    // Calculate how far off the controller is from the reference state
    error = m_reference - m_current_state;
    
    // Calculate the control signal needed to move toward reference state
    m_U_internal = ((K * error) * G) + C;
    
    // TODO send signals in m_U_internal to the four motors
    
    // Check the sensors and update the current state
    read_sensors();
    update_current_state();
    
    // And loop again to see if the new state says arrived at the reference state
  }
}

boolean Controller::calculate_current_state() {
  boolean error = true;
  
  // Do some integration over some delT for each of the elements in
  // m_current_state which can be derived from the sensor readings
  
  error = false;
  return error;
}

boolean Controller::estimate_current_state() {
  boolean error = true;
  
  // Do some estimation for each of the elements in m_current_state 
  // that we can't directly compute
  
  error = false;
  return error;
}

float Controller::relative_error( const Matrix& s1, const Matrix& s1, unsigned long t ) {
  float rel_error = 0.0f;
  // Check the percent differences between s1 and s2 over some time t and return the 
  // value
  
  return rel_error;
}

boolean Controller::arrived( const Matrix& reference ) {
  if ( relative_error( reference, m_current_state, 0 ) < m_CLOSE_ENOUGH ) {
    return true;
  }
  
  return false;
}