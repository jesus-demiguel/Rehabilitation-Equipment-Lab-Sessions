#include <Servo.h>

//Pin to read the position sensor
#define MOTORANALOGPIN A0

// Variables to map the position in degrees with the analog values given by the position sensor
int adc_out_min_limit = 300; //adc value in 0 degrees
int adc_out_max_limit = 480; // adc value in 90 degrees
int min_byte_value = 0;
int max_byte_value = 255;

// Object associated to the motor
Servo mymotor;

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
 * Function: ReadMotorPosition
 *  Read data received from the position sensor
 *  
 * Inputs: void
 *  
 * Outputs:
 *  -(byte): Actual motor position in byte
 */
byte ReadMotorPosition(void){
  // Read position from the actuator
  int motor_analog_position = analogRead(MOTORANALOGPIN);

  // Map the read position to byte
  return map(motor_analog_position, adc_out_min_limit, adc_out_max_limit, min_byte_value, max_byte_value);
}
