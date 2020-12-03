#include <Servo.h>

//Pin to read the position sensor
#define MOTORANALOGPIN A0

//Pin to send pulses to the motor
#define MOTORPWMPIN 3

// Variables to map the position in degrees with the analog values given by the position sensor
#define MINPOSLIMIT 0.0f //degrees
#define MAXPOSLIMIT 90.0f //degrees
int adc_out_min_limit = 300; //adc value in 0 degrees
int adc_out_max_limit = 480; // adc value in 90 degrees
int min_byte_value = 0;
int max_byte_value = 255;


// Variables to map motor frame with sensor frame
int pos_motor1 = 0;
int pos_motor2 = 100;
int pos_sensor1 = 111;
int pos_sensor2 = 320;

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
  mymotor.attach(MOTORPWMPIN);
  //Serial.println("Motor enable!");
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
  mymotor.detach();
  //Serial.println("Motor disable!");
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
  Serial.println("Move the EduExo to 0 degrees. Press C to continue");
  while (Serial.available() == 0);
  if (Serial.read() == 'C' || Serial.read() == 'c') {
    adc_out_min_limit = analogRead(MOTORANALOGPIN);
    Serial.print("ADC Value at 0 degrees: ");
    Serial.println(adc_out_min_limit);
    Serial.println("Move the EduExo to 90 degrees. Press C to continue");
    while (Serial.available() == 0);
    if (Serial.read() == 'C' || Serial.read() == 'c') {
      adc_out_max_limit = analogRead(MOTORANALOGPIN);
      Serial.print("ADC Value at 90 degrees: ");
      Serial.println(adc_out_max_limit);
      Serial.println("Position sensor calibrated!");
    }
    else Serial.println("Exit from calibration");
  }
  else Serial.println("Exit from calibration");
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
  EnableMotor();
  
  mymotor.write(pos_motor1);
  delay(2000);
  pos_sensor1 = analogRead(MOTORANALOGPIN);
  Serial.print("Internal motor position associated to position 1: ");
  Serial.println(pos_sensor1);
  mymotor.write(pos_motor2);
  delay(2000);
  pos_sensor2 = analogRead(MOTORANALOGPIN);
  Serial.print("Internal motor position associated to position 2: ");
  Serial.println(pos_sensor2);
  
  Serial.println("Sensor and motor position mapped!");
}

/*
 * Function: ReadMotorPosition
 *  Read data received from the position sensor
 *  
 * Inputs: void
 *  
 * Outputs:
 *  -(byte): Actual motor position in byte
 */
byte ReadMotorPositionInByte(void){
  // Read position from the actuator
  int motor_analog_position = analogRead(MOTORANALOGPIN);

  // Map the read position to byte
  return map(motor_analog_position, adc_out_min_limit, adc_out_max_limit, min_byte_value, max_byte_value);
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
  // Read position from the actuator
  int motor_analog_position = analogRead(MOTORANALOGPIN);

  // Convert it to degrees
  return map(motor_analog_position, adc_out_min_limit, adc_out_max_limit, MINPOSLIMIT, MAXPOSLIMIT);
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
  // Software limits
  if(target_position < MINPOSLIMIT) target_position = MINPOSLIMIT;
  else if (target_position > MAXPOSLIMIT) target_position = MAXPOSLIMIT;
  
  // Map to the desired position to the sensor frame
  int conv_des_pos = map(target_position, MINPOSLIMIT, MAXPOSLIMIT, adc_out_min_limit, adc_out_max_limit);

  // Map from the sensor frame to the motor frame
  int desired_position_analog = map(conv_des_pos, pos_sensor1, pos_sensor2, pos_motor1, pos_motor2);

  // Send position to the motor in the motor frame
  mymotor.write(desired_position_analog);
}
