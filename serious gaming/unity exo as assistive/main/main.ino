#define ASSISTIVEANGLE 40 //degrees
void setup() {
  Serial.begin(19200);
  
  // Just do it the first time to know the values of the ADC for the desired limits
  //CalibratePositionSensor();
  //MappingSensorAndMotorPosition();

  // Set the initial position as the initial position of the bar in the game
  EnableMotor();
  SetMotorPosition(45);
  delay(1000);
  DisableMotor();
}

void loop() {

   
}
