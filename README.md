# rewardDelivery

This script is to control the delivery of a reward.

The user can choose if rewards should be delivered automatically at random intervals, or upon licking. The user can also choose how many times the mouse should lick before the reward is delivered.

**The settings can be adjusted in the section "Task rules"**
* requiresLick can be set on false for automatic delivery at random intervals, or true if the animal needs to lick
* numberOfLicksRequired sets the threshold for active reward delivery
* The amount of reward delivered is controlled by the duration of the solenoid opening with openDuration
* The refraction period between to rewards is set with offDuration
