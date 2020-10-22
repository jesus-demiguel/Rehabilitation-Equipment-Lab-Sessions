#include <Servo.h>

//Pin to read the position sensor
#define MOTORANALOGPIN A0

//Pin to send pulses to the motor
#define MOTORPWMPIN 3

// Variable to map the position in degrees with the analog values given by the position sensor
#define MINPOSLIMIT 0.0f //degrees
#define MAXPOSLIMIT 90.0f //degrees
int adc_out_min_limit;
int adc_out_max_limit;


// Variables to map motor frame with sensor frame
int pos_motor1 = 0;
int pos_motor2 = 100;
int pos_sensor1;
int pos_sensor2;

// Object associated to the motor
Servo mymotor;

/*
 * Function: EnableMotor
 *  Sends the message to enter in enable mode.
 *  
 * Inputs: void
 *  
 * Outputs: void
 */
void EnableMotor(){
  
}

/*
 * Function: DisableMotor
 *  Sends the message to enter in disable mode.
 *  
 * Inputs: void
 *  
 * Outputs: void
 */
void DisableMotor(){
  
}

/*
 * Function: CalibratePositionSensor
 *  The user is required to move the EduExo to the position limits and then the values
 *  read by the analog channel are stored in the variables adc_out_min_limit (int) and
 *  adc_out_max_limit (int).
 *  
 * Inputs: void
 *  
 * Outputs: void
 */
void CalibratePositionSensor(void){
  
}

/*
 * Function: MappingSensorAndMotorPosition
 *  Associates the position sensor frame with the motor position frame
 *  
 * Inputs: void
 *  
 * Outputs: void
 */
void MappingSensorAndMotorPosition(void){
  
}

/*
 * Function: ReadMotorPosition
 *  Read data received from the position sensor
 *  
 * Inputs: void
 *  
 * Outputs:
 *  -(float): Actual motor position in degrees
 */
float ReadMotorPosition(void){
  
}

/*
 * Function: SetMotorPosition
 *  Sends the desired position to the motor
 *  
 * Inputs:
 *  - target_position (float): Desired position to be sent to the acutator in degrees.
 *  
 * Outputs: void
 *  
 */
void SetMotorPosition(float target_position){
  
}
