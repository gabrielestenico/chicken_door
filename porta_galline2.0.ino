#include <LowPower.h>

#include <CheapStepper.h>

const int lightLimitDown = 300;
const int lightLimitUp = 300;
int door = 0  ; //0 closed, 1 opened
int light;

CheapStepper stepper (8,9,10,11);

void setup() {
  stepper.setRpm(13); //stepper makes 13 spins per minute
  pinMode(LED_BUILTIN,OUTPUT); 
  digitalWrite(LED_BUILTIN, LOW); //Turn off the builtin led for power saving
  //Serial.begin(9600);
  // (Optional)
  // if you want to save even more electricity you can uncomment these two lines that slow down the clock speed of the arduino.
  // Obviously the stepper speed is also slowed down and it will go slower.
  // Be careful if you use the delay statement in your code that slowing down the clock in half, 1000 ms will correspond to 2000 ms
  
  //CLKPR = 0x80;
  //CLKPR = 0x01; //clock speed half //0x02 -> 1/4 speed .... 0x08 1/256 speed (1/256 is the minimum speed ATmega328P can reach)
}

void loop() {
  // Read the light
  light = analogRead(A0);
  //Serial.println(light);
  if (light > lightLimitUp && door == 0 ){
    openClose();
  } else if (light < lightLimitDown && door == 1){
    openClose();
  }
    
  //power down for 2 minutes (8 seconds for 15 times = 120 seconds -> 2 minutes)
  // You can change the 15 as you want (eg: if you use 75 the arduino sleeps for 10 minutes)
  for (int i = 0 ;  i < 15 ; i++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void openClose(){
  if (door == 0){
    spin(true); // counterclockwise
  } else {
    spin(false); // clockwise
  }
  door = 1 - door;
}

void spin(boolean way){
  // I split the stepper spins because it doesn't work all together (17 spins in total)
  stepper.moveDegrees (way,  2700);  // 7.5 spins
  stepper.moveDegrees (way,  2700);  // 7.5 spins
  stepper.moveDegrees (way,  720);   // 2 spins

  //Turn off the stepper leds
  digitalWrite (8,LOW);
  digitalWrite (9,LOW);
  digitalWrite (10,LOW);
  digitalWrite (11,LOW);
}
