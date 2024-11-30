## Autonomous Line Following Robot Vehicle

This project implements an autonomous line-following robot using an ATmega32A microcontroller. The robot is capable of detecting and following a line on the ground using TCRT5000 infrared sensors. It can move forward, turn left or right, and reverse based on the sensor inputs. Additionally, the robot is equipped with an HC-SR04 ultrasonic sensor for obstacle detection and an SG-90 servo motor to adjust the sensor's position for better obstacle avoidance.

### Features

- **Line Following**: Uses TCRT5000 infrared sensors to detect and follow a line.
- **Obstacle Detection**: Equipped with an HC-SR04 ultrasonic sensor to detect obstacles and avoid collisions.
- **Servo Motor Control**: Utilizes an SG-90 servo motor to adjust the position of the ultrasonic sensor for a broader range of detection.
- **Motor Control**: Controls DC motors using 2x L293D motor driver ICs for precise movement and direction control.
- **LCD Display**: Displays sensor readings, current direction, and status information (errors) on an LCD screen.

#### Project Flowchart
()[https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Project%20flow%20charts/AUTOV_FLOWCHART_V1.0.png?raw=true]

### Hardware Components

- ATmega32A Microcontroller
- TCRT5000 Infrared Sensors (3 units: left, center, right)
- HC-SR04 Ultrasonic Sensor
- SG-90 Servo Motor
- L293D Motor Driver ICs (2 units)
- DC Motors (4 units)
- LCD Display
- Resistors, Capacitors, and other passive components

### Software Components

- **MCAL (Microcontroller Abstraction Layer)**
  - GPIO (General Purpose Input/Output)
  - Timer (Timer0, Timer1)
  - ADC (Analog to Digital Converter)
  - USART (Universal Synchronous/Asynchronous Receiver/Transmitter)
  - Global Interrupt Enable (GIE)
  
- **HAL (Hardware Abstraction Layer)**
  - TCRT5000 Sensor Driver
  - HC-SR04 Ultrasonic Sensor Driver
  - SG-90 Servo Motor Driver
  - LCD Display Driver

### Functionality

1. **Initialization**: 
   - Initializes GPIO pins, ADC, Timers, USART, and sensors.
   - Sets up the servo motor and ultrasonic sensor for obstacle detection.

2. **Line Following**:
   - Continuously reads the analog and digital values from the TCRT5000 sensors.
   - Adjusts the motor speeds and directions to follow the detected line.

3. **Obstacle Detection and Avoidance**:
   - Uses the HC-SR04 sensor to measure distances to obstacles.
   - Adjusts the servo motor to scan the area.
   - Stops or changes direction if an obstacle is detected within a certain range.

4. **LCD Display**:
   - Displays the sensor readings and robot status on the LCD screen for monitoring.

### Usage

1. **Hardware Setup**:
   - Connect the TCRT5000 sensors, HC-SR04 sensor, SG-90 servo motor, L293D motor driver ICs, and DC motors to the ATmega32A microcontroller as per the circuit diagram.
  
    

2. **Software Setup**:
   - Clone the repository and open the project in your preferred IDE (e.g., Atmel Studio).
   - Flash the firmware to the ATmega32A microcontroller.

3. **Operation**:
   - Place the robot on a surface with a line to follow.
   - Power up the robot.
   - The robot will start following the line and avoid obstacles automatically.

### Files

- `main.c`: Main program file.
- `AUTOV_CONFIG.h`: Configuration file for the project.
- `AUTOV_INT.h`: Interface file with function prototypes and macros.
- `AUTOV_PROG.c`: Implementation file with the main logic for the autonomous vehicle functions.
- `TCRT_SENSOR.c`, `HCSR04_SENSOR.c`, `SERVO_MOTOR.c`: Driver files for the sensors and servo motor.

### Contributing

Tell me your thoughts and ideas on how to make this project even better or faster!.
You can contact me by email at:
baselmohamed802@gmail.com
[or message me at LinkedIn!](www.linkedin.com/in/basel-sayed-b11534243)

### License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
