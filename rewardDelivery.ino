/*
This script is to control the delivery of a reward and is to be used with a
lickmetre circuit composed by:
- a capacitive lick sensor (Sparksfun Capacitive Touch Breakout, AT42QT101X)
- a solenoid valve to deliver the reward (NRValve, BP011-21IC)

The user can choose if rewards should be delivered automatically at random intervals, or upon licking.
The user can also choose how many times the mouse should lick before the reward is delivered.
The settings can be adjusted in the section "Task rules"

 Written by Lucie Descamps and Elise Reppe Olsen 2020

 ______________________________________________________________________________
| To-do   ༼∩☉ل͜☉༽⊃━☆ﾟ. * ･ ｡ﾟ                                                 |
| - add more lickports/solenoids to fit our need for the object reward task    |
| - add setting to chose which ports should deliver the reward                 |
|______________________________________________________________________________|
 */


 // Task rules, change this
bool requiresLick = true;              // If true, requires animal to lick to deliver reward. If false, will deliver reward at random intervals.
int numberOfLicksRequired = 15;        // Number of lick(s) required to deliver reward
int openDuration = 500;                // Duration of solenoid opening (in ms) => quantity of reward delivered
int offDuration = 1500;                // Value in ms between solenoid openings => refraction period
touch_sensor = lickIn_1                // Enter here which touch sensor/lick port should be the one delivering the reward.
solenoid = lickOut_1                   // Enter here which touch /lick port should be the one delivering the reward.


// Constants
//Lick Port 1
const int lickIn_1 = 2;                // Input pin for state of touch sensor
int lickOut_1 = 3;                     // Pinout for TTL to solenoid valve

//Lick Port 2
const int lickIn_2 = 4;                // Input pin for state of touch sensor
int lickOut_2 = 5;                     // Pinout for TTL to solenoid valve

//Lick Port 3
const int lickIn_3 = 6;                // Input pin for state of touch sensor
int lickOut_3 = 7;                     // Pinout for TTL to solenoid valve

//Lick Port 4
const int lickIn_4 = 8;                // Input pin for state of touch sensor
int lickOut_4 = 9;                     // Pinout for TTL to solenoid valve

int licksCount = 0;                    // Variable for counting number of licks
int var = 0;
long randOff = 0;                      // Initialize a variable for the OFF time


// Set-up
void setup() {
  // set pins
  pinMode(touch_sensor, INPUT);       // Configure touch sensor pin as input
  pinMode(solenoid, OUTPUT);          // Set ttl pin to output to signal solenoid valve when to open
  // randomize
  randomSeed (analogRead (0));
  // set up serial port
  Serial.begin(9600);
  while (! Serial);
  Serial.println("No licks yet...");  // Message to send initially (no licks detected yet).
}

// Function to deliver reward *at random intervals*
void randomDelivery() {
   randOff = random (5000, 15000);    // Generates OFF time between 5 and 15 seconds
   digitalWrite(solenoid, HIGH);      // Opens solenoid and deliver reward
   Serial.println("Reward delivered");
   delay(openDuration);
   digitalWrite(solenoid, LOW);
   delay(randOff);                    // Waits for a random time between two reward delivery
}

// Function to know if reward delivery should be active or passive
void requiresLicking() {
  if (requiresLick == true){
    countingLicks();
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
  delay(1);                           // Delay for stability.

  if (licksCount == numberOfLicksRequired)
  { Serial.println("Lick threshold met");
  deliversReward();
  licksCount = 0;                     // Reset the lick count after reward delivery
             }
}

// Running constantly
void loop() {
  countingLicks();
  requiresLicking();
}
