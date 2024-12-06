/*
 * AUTOV_CONFIG.h
 *
 * Created: 11/22/2024 9:48:22 AM
 *
 *  Author: Basel Mohamed Mostafa Sayed
 *  Email: baselmohamed802@gmail.com
 *  LinkedIn: www.linkedin.com/in/basel-sayed-b11534243
 *
 *  Description: This file is the Configuration file for the L293 Motor driver board module
 *  and the TCRT5000 module pins.
 *  
 */ 


#ifndef AUTOV_CONFIG_H_
#define AUTOV_CONFIG_H_

/*
*  TCRT5000 module boards configuration
*/

// Center Sensor
#define TCRT_CENTER_PORT_A DIO_PORTA
#define TCRT_CENTER_PIN_A DIO_PIN1
#define TCRT_CENTER_CHANNEL ADC_CHANNEL1
#define TCRT_CENTER_PORT DIO_PORTB
#define TCRT_CENTER_PIN DIO_PIN5

// Right Sensor
#define TCRT_RIGHT_PORT_A DIO_PORTA
#define TCRT_RIGHT_PIN_A DIO_PIN3
#define TCRT_RIGHT_CHANNEL ADC_CHANNEL3
#define TCRT_RIGHT_PORT DIO_PORTB
#define TCRT_RIGHT_PIN DIO_PIN6

// Left Sensor
#define TCRT_LEFT_PORT_A DIO_PORTA
#define TCRT_LEFT_PIN_A DIO_PIN2
#define TCRT_LEFT_CHANNEL ADC_CHANNEL2
#define TCRT_LEFT_PORT DIO_PORTB
#define TCRT_LEFT_PIN DIO_PIN7

/*
*  L293D motor driver board config
*/

// 1st L293D IC (Left motors)
#define IN1_MOTOR1_PORT DIO_PORTC
#define IN1_MOTOR1_PIN DIO_PIN3
#define IN2_MOTOR1_PORT DIO_PORTC
#define IN2_MOTOR1_PIN DIO_PIN4
#define IN1_MOTOR2_PORT DIO_PORTC
#define IN1_MOTOR2_PIN DIO_PIN5
#define IN2_MOTOR2_PORT DIO_PORTC
#define IN2_MOTOR2_PIN DIO_PIN6

// 2nd L293D IC (Right motors)
#define IN1_MOTOR3_PORT DIO_PORTC
#define IN1_MOTOR3_PIN DIO_PIN7
#define IN2_MOTOR3_PORT DIO_PORTD
#define IN2_MOTOR3_PIN DIO_PIN2
#define IN1_MOTOR4_PORT DIO_PORTB
#define IN1_MOTOR4_PIN DIO_PIN2
#define IN2_MOTOR4_PORT DIO_PORTD
#define IN2_MOTOR4_PIN DIO_PIN6

// PWM control using Timer 1 peripheral
#define PWM_MOTOR_PORT DIO_PORTB
#define PWM_MOTOR_PIN DIO_PIN3

/*
*  Buzzer 5 volt pin
*/

#define BUZZER_PORT DIO_PORTA
#define BUZZER_PIN DIO_PIN7

#endif /* AUTOV_CONFIG_H_ */