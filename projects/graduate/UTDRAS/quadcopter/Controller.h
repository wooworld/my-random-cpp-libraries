#ifndef CONTROLLER_H
#define CONTROLLER_H

/* @file Controller.h
 * @auth Gary Steelman
 * @edit 10/26/2012
 */
 
/*
  @fun Controller
  @des Constructor for the controller class
   
  @fun ~Controller
  @des Destructor for the controller class
  
  @fun error
  @des Checks the controller's running state and performance for errors
  @ret TRUE if an error in the controller
  @ret FALSE if no error in the controller
  
  @fun start
  @des Sets the controller's running state to CONT_RUN
  
  @fun stop
  @des Sets the controller's running state to CONT_STOP
  
  @fun read_sensors
  @des Reads the sensor values and stores them
  @ret TRUE if the read was OK
  @ret FALSE if the read errored
  
  @fun update_current_state
  @des Updates the controller's current state based on the stored readings
  @note You should call read_sensors and ensure it returns true before calling 
      this function. Otherwise the current state will be out of date or corrupt.
      This function also estimates the 8 states which cannot be directly computed
  @ret TRUE if the update went OK
  @ret FALSE if the udpate errored
  
  @fun apply
  @des Makes the controller try to transition to the reference state
  @note This function BLOCKS until the transition is completed or until there
      is an error trying to transition
  @ret TRUE if the transition went OK
  @ret FALSE if the transition errored
  
  @fun calculate_current_state
  @des Calculates the states which can be directly calculated given sensor readings
  @ret TRUE if the calculation went OK
  @ret FALSE if the calculation errored
  
  @fun estimate_current_state
  @des Estimates the states which cannot be directly calculated given sensor readings
  @note Call calculate_current_state before calling this otherwise your estimations
      will be incorrect
  @ret TRUE if the estimation went OK
  @ret FALSE if the estimation errored
  
  @fun relative_error 
  @des Calculates the relative error between two states 
  @note Essentially calculates how close two states are and returns a numeric indicator
  @ret Number representing how close the two states are (ie returns .05 means 5% apart)
  
  @fun arrived
  @des Checks if the controller's current state has transitioned to the reference state
  @ret TRUE if the controller has transitioned to the reference state
  @ret FALSE if the controller has not transitioned to the reference state
 */
 
// Running state values
typedef enum {
  CONT_INIT,      // Initialization
  CONT_RUN,       // Running
  CONT_STOP,      // Stopped  
  CONT_KILL,      // Killed
  CONT_ERROR,     // Error in execution
  
  CONT_FINAL      // Used only for looping
} state_t;

// Matrix accessor constants for the states
enum {
  C_POS_X,
  C_VEL_X,
  C_POS_Y,
  C_VEL_Y,
  C_POS_Z,
  C_VEL_Z,
  C_ANG_YAW,
  C_SPD_YAW,
  C_ANG_PITCH,
  C_SPD_PITCH,
  C_ANG_ROLL,
  C_SPD_ROLL,
  C_SPD_MOT_1,
  C_SPD_MOT_2,
  C_SPD_MOT_3,
  C_SPD_MOT_4,
  C_CUR_MOT_1,
  C_CUR_MOT_2,
  C_CUR_MOT_3,
  C_CUR_MOT_4
};

class Controller {
public:
  Controller();
  ~Controller();
  
  boolean error();
  
  void    start();
  void    stop();
  state_t get_state() const;
  
  boolean read_sensors();

  boolean update_current_state();
  
  boolean apply( const Matrix& reference );
  
private:
  boolean calculate_current_state();
  boolean estimate_current_state();
  
  float   relative_error( const Matrix& s1, const Matrix& s1, float t );
  boolean arrived( const Matrix& reference );

  // Stores readings from the sensors and time of last read
  Matrix        m_sensor_readings;
  unsigned long m_sensor_last_read;

  // All 20x1 column vectors
  Matrix        m_current_state;
  Matrix        m_previous_state;
  Matrix        m_reference;
  unsigned long m_current_last_update;
  
  float  m_eps; // Min the copter's state must change to be OK for some given delT
  float  m_EPS; // Max the copter's state is allowed to change to be OK for some given delT
  static float m_CLOSE_ENOUGH = 0.05;
  
  state_t m_run_state;  
  
  // Intermediate matrices for state calculations
  Matrix m_U_internal;
  Matrix m_K;
  Matrix m_A11;
  Matrix m_A12;
  Matrix m_A22;
  Matrix m_B2;
  Matrix m_L;
  Matrix m_Y;
  Matrix m_Ydot;
  float  m_G;
  Matrix m_C;
}

#endif