/*
 * Autonomous Vehicle.c
 *
 * Created: 11/22/2024 9:47:22 AM
 * Author : Basel Mohamed Mostafa Sayed
 */ 

#define F_CPU 16000000UL

/* UTILS */
#include "UTILS/STD_TYPES.h" 
#include "UTILS/Bit_operation.h"
#include "UTILS/VECTOR.h"

/* MCAL */
#include "ATmega32_DIO/DIO_REG.h"
#include "ATmega32_DIO/DIO_PROGRAM.h"
#include "../../../MCAL/GIE_DRIVER/GIE_DRIVER/GIE_PROGRAM.h"
#include "../../../MCAL/GIE_DRIVER/GIE_DRIVER/GIE_PROGRAM.c"
#include "../../../MCAL/TIMER/TMR0_INTERRUPT/TIMER_INTERRUPT/TMR0_PROGRAM.h"
#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_PROGRAM.h"
#include "../../../MCAL/ADC_DRIVER/ADC_DRIVER/ADC_PROGRAM.c"
#include "../../../MCAL/USART/USART/USART_PROGRAM.h"
#include "../../../MCAL/USART/USART/USART_PROGRAM.c"
#include <util/delay.h>

/* HAL */
#include "AUTOV_CONFIG.h"
#include "AUTOV_INT.h"
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_PROGRAM.h"
#include "../../../HAL/LCD_DRIVER/LCD_DRIVER/LCD_PROGRAM.c"
#include "../../../HAL/HC-SR04 sensor/HC-SR04 sensor/HCSR04_INT.h"
#include "../../../HAL/HC-SR04 sensor/HC-SR04 sensor/HCSR04_PROG.C"
#include "../../../HAL/SG-90 Servo motor/SG-90 Servo motor/SERVO_INT.h"
#include "../../../HAL/SG-90 Servo motor/SG-90 Servo motor/SERVO_PROG.C"

int main(void) {
    // Calling startup function to initialize program
	AUTOV_init();
	
	// Ultrasonic distance variable
	f32 local_f32DistMeasured = 0.0;
	
    while (1) {
		// Checking Ultrasonic sensor reading
		HCSR04_getAverageDistance(HCSR04_SAMPLES, &local_f32DistMeasured);
		
		/* debug to ensure distance is being read correctly */
        /*LCD_clear();
		LCD_displayString((u8*) "Distance: ");
		LCD_moveCursor(1, 0);
		LCD_displayNumber(local_f32DistMeasured, 2);
		_delay_ms(400);*/
		
		if (local_f32DistMeasured > HCSR04_MIN_DISTANCE) {
			// Main program
			AUTOV_lineFollowing();
		}
		else {
			// Calling the function responsible for going into obstacle avoidance mode
			AUTOV_obstacleAvoidance();
		}
    }
	
	return 0;
}

