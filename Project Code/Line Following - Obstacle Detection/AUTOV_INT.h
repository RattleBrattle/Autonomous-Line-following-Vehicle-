/*
 * AUTOV_INT.h
 *
 * Created: 11/22/2024 9:48:22 AM
 *
 *  Author: Basel Mohamed Mostafa Sayed
 *  Email: baselmohamed802@gmail.com
 *  LinkedIn: www.linkedin.com/in/basel-sayed-b11534243
 *
 *  Description: This file contains all the Function prototypes and 
 *  MACROS for the Autonomous vehicle project using the HC-SR04 and TCRT-5000 module board.
 *  
 */ 


#ifndef AUTOV_INT_H_
#define AUTOV_INT_H_

/* MACROS */

/*
*  L293D motor speeds
*/

#define FULL_SPEED 100
#define QUICK 75
#define MEDIUM 50
#define SLOW_DOWN 25
#define HALT 0

/*
*  TCRT sensors
*/

#define CENTER_SENSOR 0
#define RIGHT_SENSOR 1
#define LEFT_SENSOR 2

// Sensors states
#define CENTER_HIGH 1
#define RIGHT_HIGH 1
#define LEFT_HIGH 1

#define CENTER_LOW 0
#define RIGHT_LOW 0
#define LEFT_LOW 0

/*
*  Servo SG-90 Macros
*/

// servo moving the head (ultrasonic sensor) either quickly or slowly
#define MOVE_HEAD_SLOW 0
#define MOVE_HEAD_QUICK 1

/*
*  HC-SR04 ultrasonic sensor Macros
*/

// Samples to read
#define HCSR04_SAMPLES 3
// minimum distance of an obstacle
#define HCSR04_MIN_DISTANCE 30

/* Function Headers */

/*
* Main functions for Autonomous vehicle 
*/

// Startup function to initialize all pins connected
void AUTOV_init(void);

// Main loop For Line following
void AUTOV_lineFollowing(void);

// Loop for obstacle avoidance and getting back on track
void AUTOV_obstacleAvoidance(void);

// Buzzer alarm
void AUTOV_buzzerAlarm(void);

/*  
* L293D Motor Control Functions (Steer left or right, and Go straight or reverse)
*/

// Initializing the pins connected to the L293D module board
void L293D_init(void);

// Function to only enable the left motors, using the 1st L293D (steer the Vehicle left)
void Motors_left(u8 copy_u8Speed);

// Function to only enable the right motors, using the 2nd L293D (steer the vehicle right)
void Motors_right(u8 copy_u8Speed);

// This function turns on all motors connected to the two L293D to go forward
void Motors_forward(u8 copy_u8Speed);

// This function turns on all motors connected to the two L293D and reverses the direction to go backwards
void Motors_reverse(u8 copy_u8Speed);

// Turn off motors
void Motors_off(void);

/*
* Functions for the Servo motor (SG-90) to move the head and scan around
*/

// Center servo head (90 degree)
void SERVO_centerHead(void);

// Steer the head (ultrasonic sensor) towards left
void SERVO_lookLeft(u8 copy_u8Speed);

// Steer the head (ultrasonic sensor) towards right
void SERVO_lookRight(u8 copy_u8Speed);

// Survey the head (ultrasonic sensor) from 0 to 180 (Left to Right)
void SERVO_survey(u8 copy_u8Speed);

/*
* Functions for the TCRT5000 modules (Right, left, and center)
*/

// Function to initialize the pins connected for the three modules
void TCRT_init(void);

// Return reading from selected sensor
void TCRT_getAnalog(u8 copy_u8SensorPosition, u16 *copy_u8Reading);

// Read digital value
void TCRT_getDigitalVal(u8 copy_u8SensorPosition, u8 *copy_u8State);

#endif /* AUTOV_INT_H_ */