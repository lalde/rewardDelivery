/*
 Uno Pin    AT42QT101X Board  Function

 +5V        VDD               Power supply
 GND        GND               Ground
 2          OUT               Capacitive touch state output


 Written by Lucie Descamps and Elise Reppe Olsen 2020
 */



int touch_sensor = 2;           // Input pin for state of touch sensor
int solenoid = 8;               // Pinout for TTL to solenoid valve 
int offDuration = 1500;         // Value in ms between solenoid openings
int openDuration = 500;         // Duration of solenoid opening (in ms)
bool requiresLick = true;       // If True, requires animal to lick to deliver reward. If False, will deliver reward at random intervals. 
bool countLicks = true;         // If true, will count how many times animal is licking and will display it in the serial monitor
int numberOfLicksRequired = 1;  // Number of lick(s) required to deliver reward
int licksCount = 0;             // Variable for counting number of licks
int var = 0;
long randOff = 0;               // Initialize a variable for the OFF time



void countingLicks() {
    if(digitalRead(touch_sensor) > var)
  {
    var = 1;
    licksCount++;
    Serial.println(" Lick detected");
  }  
  if(digitalRead(touch_sensor) == 0) {var = 0;}
  delay(1); // Delay for stability.
  
  if (licksCount == numberOfLicksRequired){ licksCount = 0;  // reset the count
             } 
}


void deliversReward() {
  if (licksCount ==  numberOfLicksRequired) {
     digitalWrite(solenoid, HIGH);
     Serial.println("Reward delivered");
     delay(openDuration);
     digitalWrite(solenoid, LOW); 
     delay(offDuration);
     
  } else if (licksCount < numberOfLicksRequired) {
    digitalWrite(solenoid, LOW);
  }
}

void randomDelivery() {
   randOff = random (5000, 15000);    // generates OFF time between 5 and 15 seconds
   digitalWrite(solenoid, HIGH);   
   Serial.println("Reward delivered");
   delay(openDuration);                // opens solenoid and delivers reward
   digitalWrite(solenoid, LOW);   
   delay(randOff);               // waits for a random time while OFF
}

void requiresLicking() {
  if (requiresLick == true){
    deliversReward();
  }else if (requiresLick == false){
    randomDelivery();
  }   
}


void setup() {
  // set pins
  pinMode(touch_sensor, INPUT); // Configure touch sensor pin as input
  pinMode(solenoid, OUTPUT); // Set ttl pin to output to signal solenoid valve 
  // randomize
  randomSeed (analogRead (0));   
  //
  Serial.begin(9600);
  while (! Serial);
  Serial.println("No licks yet..."); // Message to send initially (no licks detected yet).
} 


void loop() {
  requiresLicking();
}
