/*
 * AUTOV_CONFIG.h
 *
 * Created: 11/22/2024 9:48:22 AM
 *
 *  Author: Basel Mohamed Mostafa Sayed
 *  Email: baselmohamed802@gmail.com
 *  LinkedIn: www.linkedin.com/in/basel-sayed-b11534243
 *
 *  Description: This file contains all the source code for the Autonomous vehicle project
 *  Line-Follower robot project Using ATmega32A.
 *  
 */ 
#define F_CPU 16000000UL

/* UTILS */
#include "UTILS/STD_TYPES.h"
#include "UTILS/Bit_operation.h"
#include "UTILS/VECTOR.h"

/* MCAL */
#include "ATmega32_DIO/DIO_REG.h"
#include "ATmega32_DIO/DIO_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_PROGRAM.h"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_PROGRAM.c"
#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_PROGRAM.h"
#include <util/delay.h>

/* HAL */
#include "AUTOV_CONFIG.h"
#include "AUTOV_INT.h"
#include "../../../HAL/SG-90 Servo motor/SG-90 Servo motor/SERVO_INT.h"
#include "../../../HAL/HC-SR04 sensor/HC-SR04 sensor/HCSR04_INT.h"

/*
*
*            LCD custom characters
*
*/

u8 arrowUP[] = {
	0b00100,
	0b01110,
	0b01110,
	0b11111,
	0b00100,
	0b00100,
	0b00100,
	0b00100
};

u8 arrowDOWN[] = {
	0b00100,
	0b00100,
	0b00100,
	0b00100,
	0b11111,
	0b01110,
	0b01110,
	0b00100
};

u8 arrowRIGHT[] = {
	0b00000,
	0b00000,
	0b00100,
	0b00110,
	0b11111,
	0b00110,
	0b00100,
	0b00000
};

u8 arrowLEFT[] = {
	0b00000,
	0b00000,
	0b00100,
	0b01100,
	0b11111,
	0b01100,
	0b00100,
	0b00000
};

/*
*
*            L293D Motor driver board functions:
*
*/

void L293D_init(void) {
	// Peripheral Initialization
	TMR0_init(TMR0_FASTPWM_MODE, TMR0_PRELOAD_CLR, TMR0_PWM_NON_INVERT);
	
	// Back left motor (Motor 1)
	DIO_setPinDirection(IN1_MOTOR1_PORT, IN1_MOTOR1_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(IN2_MOTOR1_PORT, IN2_MOTOR1_PIN, DIO_PIN_OUTPUT);
	// Front left motor (Motor 2)
	DIO_setPinDirection(IN1_MOTOR2_PORT, IN1_MOTOR2_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(IN2_MOTOR2_PORT, IN2_MOTOR2_PIN, DIO_PIN_OUTPUT);
	
	// Back right motor (Motor 3)
	DIO_setPinDirection(IN1_MOTOR3_PORT, IN1_MOTOR3_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(IN2_MOTOR3_PORT, IN2_MOTOR3_PIN, DIO_PIN_OUTPUT);
	// Front right motor (Motor 4)
	DIO_setPinDirection(IN1_MOTOR4_PORT, IN1_MOTOR4_PIN, DIO_PIN_OUTPUT);
	DIO_setPinDirection(IN2_MOTOR4_PORT, IN2_MOTOR4_PIN, DIO_PIN_OUTPUT);
	
	// PWM pin for L293D EN (Motor Speed)
	DIO_setPinDirection(PWM_MOTOR_PORT, PWM_MOTOR_PIN, DIO_PIN_OUTPUT);
}

void Motors_forward(u8 copy_u8Speed) {
	// Starting PWM signal from Timer 0 to EN pin of L293D board (speed condition 0-100)
	if (copy_u8Speed >= 0 || copy_u8Speed <= 100) {
		TMR0_generatePWM(copy_u8Speed, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);
	}
	else {
		TMR0_generatePWM(HALT, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);  // Error 1 (Not receiving correct speed)
	}
	
	// Motor control FORWARD
	DIO_setPinVal(IN1_MOTOR1_PORT, IN1_MOTOR1_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR1_PORT, IN2_MOTOR1_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN1_MOTOR2_PORT, IN1_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR2_PORT, IN2_MOTOR2_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN1_MOTOR3_PORT, IN1_MOTOR3_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR3_PORT, IN2_MOTOR3_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN1_MOTOR4_PORT, IN1_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR4_PORT, IN2_MOTOR4_PIN, DIO_PIN_OUTPUT_HIGH);
}

void Motors_reverse(u8 copy_u8Speed) {
	// Starting PWM signal from Timer 0 to EN pin of L293D board (speed condition 0-100)
	if (copy_u8Speed >= 0 || copy_u8Speed <= 100) {
		TMR0_generatePWM(copy_u8Speed, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);
	}
	else {
		TMR0_generatePWM(HALT, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);  // Error 1 (Not receiving correct speed)
	}
	
	// Motor control Reverse direction
	DIO_setPinVal(IN1_MOTOR1_PORT, IN1_MOTOR1_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN2_MOTOR1_PORT, IN2_MOTOR1_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN1_MOTOR2_PORT, IN1_MOTOR2_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN2_MOTOR2_PORT, IN2_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN1_MOTOR3_PORT, IN1_MOTOR3_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN2_MOTOR3_PORT, IN2_MOTOR3_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN1_MOTOR4_PORT, IN1_MOTOR4_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN2_MOTOR4_PORT, IN2_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);	
}

void Motors_left(u8 copy_u8Speed) {
	// Starting PWM signal from Timer 0 to EN pin of L293D board (speed condition 0-100)
	if (copy_u8Speed >= 0 || copy_u8Speed <= 100) {
		TMR0_generatePWM(copy_u8Speed, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);
	}
	else {
		TMR0_generatePWM(HALT, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);  // Error 1 (Not receiving correct speed)
	}
	// Turn on back right motor to steer left (Motor 3)
	DIO_setPinVal(IN1_MOTOR3_PORT, IN1_MOTOR3_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR3_PORT, IN2_MOTOR3_PIN, DIO_PIN_OUTPUT_HIGH);
	
	// Turn on back left motor on reverse to help steering (Motor 1)
	DIO_setPinVal(IN1_MOTOR1_PORT, IN1_MOTOR1_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN2_MOTOR1_PORT, IN2_MOTOR1_PIN, DIO_PIN_OUTPUT_LOW);
	
	// Turn off all other motors
	DIO_setPinVal(IN1_MOTOR4_PORT, IN1_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR4_PORT, IN2_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN1_MOTOR2_PORT, IN1_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR2_PORT, IN2_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
}

void Motors_right(u8 copy_u8Speed) {
	// Starting PWM signal from Timer 0 to EN pin of L293D board (speed condition 0-100)
	if (copy_u8Speed >= 0 || copy_u8Speed <= 100) {
		TMR0_generatePWM(copy_u8Speed, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);
	}
	else {
		TMR0_generatePWM(HALT, TMR0_PWM_NON_INVERT, TMR0_PRESCALER_1);  // Error 1 (Not receiving correct speed)
	}
	
	// Turn on back left motor to steer right (Motor 1)
	DIO_setPinVal(IN1_MOTOR1_PORT, IN1_MOTOR1_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR1_PORT, IN2_MOTOR1_PIN, DIO_PIN_OUTPUT_HIGH);
	
	// Turn on back right motor on reverse to help steer right (Motor 3)
	DIO_setPinVal(IN1_MOTOR3_PORT, IN1_MOTOR3_PIN, DIO_PIN_OUTPUT_HIGH);
	DIO_setPinVal(IN2_MOTOR3_PORT, IN2_MOTOR3_PIN, DIO_PIN_OUTPUT_LOW);
	
	// Turn off all other motors
	DIO_setPinVal(IN1_MOTOR2_PORT, IN1_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR2_PORT, IN2_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN1_MOTOR4_PORT, IN1_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR4_PORT, IN2_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);
}

void Motors_off(void) {
	// Turn off CLK to timer 0 peripheral
	TMR0_stop();
	
	// Turn off Left side Motors
	DIO_setPinVal(IN1_MOTOR1_PORT, IN1_MOTOR1_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR1_PORT, IN2_MOTOR1_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN1_MOTOR2_PORT, IN1_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR2_PORT, IN2_MOTOR2_PIN, DIO_PIN_OUTPUT_LOW);
	
	// Turn off Right side Motors
	DIO_setPinVal(IN1_MOTOR3_PORT, IN1_MOTOR3_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR3_PORT, IN2_MOTOR3_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN1_MOTOR4_PORT, IN1_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);
	DIO_setPinVal(IN2_MOTOR4_PORT, IN2_MOTOR4_PIN, DIO_PIN_OUTPUT_LOW);
}

/*
*
*            Servo motor functions (SG-90):
*
*/

void SERVO_centerHead(void) {
	SG90_move(90); // Centering the servo motor
}

void SERVO_lookLeft(u8 copy_u8Speed) {
	// Local For loop variable
	u8 local_u8ForLoop = 0;
	SERVO_centerHead();
	
	// Option to look Left fast or slow
	switch (copy_u8Speed) {
		case MOVE_HEAD_SLOW:
		for (local_u8ForLoop = 90; local_u8ForLoop <= 180; local_u8ForLoop++) {
		    SG90_move(local_u8ForLoop);
			_delay_ms(75);
		}
		break;
		case  MOVE_HEAD_QUICK:
		for (local_u8ForLoop = 90; local_u8ForLoop <= 180; local_u8ForLoop++) {
			SG90_move(local_u8ForLoop);
			_delay_ms(10);
		}
		break;
		default: // Add error state here
		break;
	}
}

void SERVO_lookRight(u8 copy_u8Speed) {
	// Local For loop variable
	u8 local_u8ForLoop = 0;
	SERVO_centerHead();
	
	// Option to look Right fast or slow
	switch (copy_u8Speed) {
		case MOVE_HEAD_SLOW:
		for (local_u8ForLoop = 90; local_u8ForLoop >= 0; local_u8ForLoop--) {
			SG90_move(local_u8ForLoop);
			_delay_ms(75);
		}
		break;
		case  MOVE_HEAD_QUICK:
		for (local_u8ForLoop = 90; local_u8ForLoop >= 0; local_u8ForLoop--) {
			SG90_move(local_u8ForLoop);
			_delay_ms(10);
		}
		break;
		default: // Add error state here
		break;
	}
}

void SERVO_survey(u8 copy_u8Speed) {
	// Local For loop variable
	u8 local_u8ForLoop = 0;
	SG90_move(0); // Moving the servo motor to starting position
	
	// Option to Survey around area, fast or slow
	switch (copy_u8Speed) {
		case MOVE_HEAD_SLOW:
		for (local_u8ForLoop = 0; local_u8ForLoop <= 180; local_u8ForLoop++) {
			SG90_move(local_u8ForLoop);
			_delay_ms(75);
		}
		break;
		case  MOVE_HEAD_QUICK:
		for (local_u8ForLoop = 0; local_u8ForLoop <= 180; local_u8ForLoop++) {
			SG90_move(local_u8ForLoop);
			_delay_ms(10);
		}
		break;
		default: // Add error state here
		break;
	}
}

/*
*
*            TCRT5000 modules functions:
*
*/

void TCRT_init(void) {
	// Left sensor initialize
	DIO_setPinDirection(TCRT_LEFT_PORT_A, TCRT_LEFT_PIN_A, DIO_PIN_INPUT); // A0
	DIO_setPinDirection(TCRT_LEFT_PORT, TCRT_LEFT_PIN, DIO_PIN_INPUT); // D0
	
	// Right sensor initialize
	DIO_setPinDirection(TCRT_RIGHT_PORT_A, TCRT_RIGHT_PIN_A, DIO_PIN_INPUT); // A0
	DIO_setPinDirection(TCRT_RIGHT_PORT, TCRT_RIGHT_PIN, DIO_PIN_INPUT); // D0
	
	// Center sensor initialize
	DIO_setPinDirection(TCRT_CENTER_PORT_A, TCRT_CENTER_PIN_A, DIO_PIN_INPUT); // A0
	DIO_setPinDirection(TCRT_CENTER_PORT, TCRT_CENTER_PIN, DIO_PIN_INPUT); // D0
}

void TCRT_getAnalog(u8 copy_u8SensorPosition, u16 *copy_u16Reading) {
	// Option to read from specified sensor
	switch (copy_u8SensorPosition) {
		case CENTER_SENSOR:
		*copy_u16Reading = ADC_getValue(TCRT_CENTER_CHANNEL);
		break;
		case LEFT_SENSOR:
		*copy_u16Reading = ADC_getValue(TCRT_LEFT_CHANNEL);
		break;
		case RIGHT_SENSOR:
		*copy_u16Reading = ADC_getValue(TCRT_RIGHT_CHANNEL);
		break;
		default: // Add error state
		break;
	}
}

void TCRT_getDigitalVal(u8 copy_u8SensorPosition, u8 *copy_u8State) {
	// Reading state of the Digital value of sensors
	switch (copy_u8SensorPosition) {
		case CENTER_SENSOR:
		*copy_u8State = DIO_readPinVal(TCRT_CENTER_PORT, TCRT_CENTER_PIN);
		break;
		case LEFT_SENSOR:
		*copy_u8State = DIO_readPinVal(TCRT_LEFT_PORT, TCRT_LEFT_PIN);
		break;
		case RIGHT_SENSOR:
		*copy_u8State = DIO_readPinVal(TCRT_RIGHT_PORT, TCRT_RIGHT_PIN);
		break;
		default: // Add error state
		break;
	}
}

/*
*
*            Autonomous vehicle main Functions:
*
*/

// Function to initialize pins connected, modules, and peripherals.
void AUTOV_init(void) {
	// Calling function to setup L293D module board functions
	L293D_init();
	// Calling initialization of HC-SR04 ultrasonic sensor
	HCSR04_init();
	// Initializing Servo motor
	SG90_init();
	// Start ADC peripheral
	/*ADC_init(ADC_REFERENCE_AVCC);*/
	// Initializing all pins of the Infrared tracking sensors
	TCRT_init();
	// Global interrupts
	GIE_enable();
	// LCD initialize
	LCD_init();
	
	// Loading start robot
	LCD_clear();
	LCD_displayString((u8*) "Starting.");
	_delay_ms(20);
	LCD_displayString((u8*)".");
	_delay_ms(20);
	LCD_displayString((u8*)".");
	_delay_ms(20);
	LCD_displayString((u8*)".");
	_delay_ms(20);
	LCD_displayString((u8*)".!");
	
	// Initialize Buzzer connection
	DIO_setPinDirection(BUZZER_PORT, BUZZER_PIN, DIO_PIN_OUTPUT);
}

// This is the second main function of the Autonomous vehicle where if an obstacle is detected
// at less than 30cm, it is activated. This function checks the right direction and left direction
// And if both are clear, then the Autonomous robot is free to swerve at any direction then return back on track
void AUTOV_obstacleAvoidance(void) {
	// Turning off motors
	Motors_off();
	
	// Display warning on screen
	LCD_clear();
	LCD_displayString((u8*) "Obstacle is");
	LCD_moveCursor(1, 0);
	LCD_displayString((u8*) "detected.");
	_delay_ms(450);
	LCD_clear();
	LCD_displayString((u8*) "Please remove");
	LCD_moveCursor(1, 0);
	LCD_displayString((u8*) "the obstacle");
	_delay_ms(250);
	
	// Sound off buzzer as an alarm sound
	AUTOV_buzzerAlarm();
}

// Main line following function, this function simply follows the line on ground by reading
// output of 3 TCRT sensors and constantly checking for obstacles using the Ultrasonic sensor
// And taking the appropriate action should an obstacle appear
void AUTOV_lineFollowing(void) {
	// Sensor variables
	u8 local_u8CenterState = 0, local_u8LeftState = 0, local_u8RightState = 0;
	/*u16 local_u16CenterSensAnalog = 0, local_u16RightSensAnalog = 0, local_u16LeftSensAnalog = 0;*/
	
	// Error Variable
	u8 local_u8ErrVar = 0;
	
	// Checking for TCRT sensor values digital readings
	TCRT_getDigitalVal(RIGHT_SENSOR, &local_u8RightState);
	TCRT_getDigitalVal(CENTER_SENSOR, &local_u8CenterState);
	TCRT_getDigitalVal(LEFT_SENSOR, &local_u8LeftState);
	
	// Checking for TCRT analog readings
	/*TCRT_getAnalog(RIGHT_SENSOR, &local_u16RightSensAnalog);
	TCRT_getAnalog(CENTER_SENSOR, &local_u16CenterSensAnalog);
	TCRT_getAnalog(LEFT_SENSOR, &local_u16LeftSensAnalog);*/
	
	/* Debug for TCRT sensors reading(s) */
	/*LCD_displayString((u8*) "A Value: ");
	LCD_displayNumber(local_u16CenterSensAnalog, 2);
	LCD_moveCursor(1, 0);
	LCD_displayString((u8*) "D State: ");
	LCD_displayNumber(local_u8CenterState, 1);
	_delay_ms(400);
	LCD_clear();*/
	
	
	/* Debug for ultrasonic distance reading */
	/*LCD_clear();
	LCD_displayString((u8*) "Distance: ");
	LCD_moveCursor(1, 0);
	LCD_displayNumber(local_f32DistMeasured, 2);
	_delay_ms(400);*/
	
	// Main Line following conditions
	if (local_u8RightState == RIGHT_LOW && local_u8LeftState == LEFT_LOW) {
		Motors_forward(FULL_SPEED);
		LCD_clear(); 
		LCD_displayString((u8*) "Direction: ");
		LCD_moveCursor(1, 0);
		LCD_displayString((u8*) "Forward ");
		LCD_createAndDisplayChar(0, arrowUP, 1, 9);
	}
	else if (local_u8RightState == RIGHT_HIGH && local_u8LeftState == LEFT_LOW) {
		Motors_right(FULL_SPEED);
		LCD_clear();
		LCD_displayString((u8*) "Direction: ");
		LCD_moveCursor(1, 0);
		LCD_displayString((u8*) "Right ");
		LCD_createAndDisplayChar(1, arrowRIGHT, 1, 7);
	}
	else if (local_u8RightState == RIGHT_LOW && local_u8LeftState == LEFT_HIGH) {
		Motors_left(FULL_SPEED);
		LCD_clear();
		LCD_displayString((u8*) "Direction: ");
		LCD_moveCursor(1, 0);
		LCD_displayString((u8*) "Left ");
		LCD_createAndDisplayChar(1, arrowLEFT, 1, 6);
	}
	else {
		local_u8ErrVar = 1; // Error in reading sensor values
		Motors_off();
		LCD_clear();
		LCD_displayString((u8*) "Error type 1");
		LCD_moveCursor(1, 0);
		LCD_displayString((u8*) "Reading sensors");
		}
}

void AUTOV_buzzerAlarm(void) {
	// Generating a tone for the buzzer
	DIO_setPinVal(BUZZER_PORT, BUZZER_PIN, DIO_PIN_OUTPUT_HIGH);
	_delay_ms(100);
	DIO_setPinVal(BUZZER_PORT, BUZZER_PIN, DIO_PIN_OUTPUT_LOW);
	_delay_ms(100);
	DIO_setPinVal(BUZZER_PORT, BUZZER_PIN, DIO_PIN_OUTPUT_HIGH);
	_delay_ms(100);
	DIO_setPinVal(BUZZER_PORT, BUZZER_PIN, DIO_PIN_OUTPUT_LOW);
	_delay_ms(100);
	DIO_setPinVal(BUZZER_PORT, BUZZER_PIN, DIO_PIN_OUTPUT_HIGH);
	_delay_ms(100);
	DIO_setPinVal(BUZZER_PORT, BUZZER_PIN, DIO_PIN_OUTPUT_LOW);	
}
