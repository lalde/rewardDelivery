/*
 Uno Pin    AT42QT101X Board  Function

 +5V        VDD               Power supply
 GND        GND               Ground
 2          OUT               Capacitive touch state output


 Written by Lucie Descamps and Elise Reppe Olsen 2020
 */


 // Task rules, change this
bool requiresLick = true;             // If true, requires animal to lick to deliver reward. If false, will deliver reward at random intervals.
int numberOfLicksRequired = 15;       // Number of lick(s) required to deliver reward
int openDuration = 500;               // Duration of solenoid opening (in ms) => quantity of reward delivered
int offDuration = 1500;               // Value in ms between solenoid openings => refraction period

// Constants
const int touch_sensor = 2;           // Input pin for state of touch sensor
int solenoid = 8;                     // Pinout for TTL to solenoid valve

int licksCount = 0;                   // Variable for counting number of licks
int var = 0;
long randOff = 0;                     // Initialize a variable for the OFF time


// Set-up
void setup() {
  // set pins
  pinMode(touch_sensor, INPUT);       // Configure touch sensor pin as input
  pinMode(solenoid, OUTPUT);          // Set ttl pin to output to signal solenoid valve when to open
  // randomize
  randomSeed (analogRead (0));
  // Set up serial port
  Serial.begin(9600);
  while (! Serial);
  Serial.println("No licks yet...");  // Message to send initially (no licks detected yet).
}

// Function to deliver reward *at random intervals*
void randomDelivery() {
   randOff = random (5000, 15000);    // generates OFF time between 5 and 15 seconds
   digitalWrite(solenoid, HIGH);      // Opens solenoid and deliver reward
   Serial.println("Reward delivered");
   delay(openDuration);
   digitalWrite(solenoid, LOW);
   delay(randOff);                    // Waits for a random time between two reward delivery
}

// Function to know if reward delivery should be active or passive
void requiresLicking() {
  if (requiresLick == true){
    deliversReward();
  }else if (requiresLick == false){
    randomDelivery();
  }
}

// Function to deliver reward
void deliversReward() {
     digitalWrite(solenoid, HIGH);
     Serial.println("Reward delivered");
     delay(openDuration);
     digitalWrite(solenoid, LOW);
     delay(offDuration);
}


// Function to count how many licks are registered
void countingLicks() {
    if(digitalRead(touch_sensor) > var)
  {
    var = 1;
    licksCount++;
    Serial.println(" Lick detected");
  }
  if(digitalRead(touch_sensor) == 0) {var = 0;}
  delay(1); // Delay for stability.

  if (licksCount == numberOfLicksRequired)
  { Serial.println("Lick threshold met");
  deliversReward();
  licksCount = 0;  // Reset the lick count after reward delivery
             }
}

// Running constantly
void loop() {
  countingLicks();
  requiresLicking();
  deliversReward();
}
