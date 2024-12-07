## Autonomous Line Following Robot Vehicle

This project implements an autonomous line-following robot using an ATmega32A microcontroller. The robot is capable of detecting and following a line on the ground using TCRT5000 infrared sensors. It can move forward, turn left or right, and reverse based on the sensor inputs. Additionally, the robot is equipped with an HC-SR04 ultrasonic sensor for obstacle detection and an SG-90 servo motor to adjust the sensor's position for better obstacle avoidance.

### Features

- **Line Following**: Uses TCRT5000 infrared sensors to detect and follow a line.
- **Obstacle Detection**: Equipped with an HC-SR04 ultrasonic sensor to detect obstacles and avoid collisions.
- **Servo Motor Control**: Utilizes an SG-90 servo motor to adjust the position of the ultrasonic sensor for a broader range of detection.
- **Motor Control**: Controls DC motors using 2x L293D motor driver ICs for precise movement and direction control.
- **LCD Display**: Displays sensor readings, current direction, and status information (errors) on an LCD screen.

#### Project Flowchart
![](https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Project%20flow%20charts/Flowchart%20Final%20(2).png?raw=true)

- A higher detailed Flowchart PDF and image can be found in the "Project flow charts" file uploaded in the repository.

### Hardware Components

- ATmega32A Microcontroller
- TCRT5000 Infrared Sensors (3 units: left, center, right)
- HC-SR04 Ultrasonic Sensor
- SG-90 Servo Motor
- L293D Motor Driver ICs (2 units)
- DC Motors (4 units)
- LCD Display (16x2)
- Resistors, Capacitors, and other passive components

![](https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Components%20list.jpg?raw=true)

### Software Components

- **MCAL (Microcontroller Abstraction Layer)**
  - DIO (General Purpose Input/Output)
  - Timer (Timer0, Timer1)
  - ADC (Analog to Digital Converter)
  - USART (Universal Synchronous/Asynchronous Receiver/Transmitter)
  - Global Interrupt Enable (GIE)
  
- **HAL (Hardware Abstraction Layer)**
  - TCRT5000 Sensor Driver
  - HC-SR04 Ultrasonic Sensor Driver
  - SG-90 Servo Motor Driver
  - LCD Display Driver
 
### Proteus simulation circuit

  - **Simulation circuit**: In the folder uploaded to the repository named "Line-following robot", where I've created a circuit
  to simulate what the project would look like in real life as close as possible using libraries provided by syedzainnasir over [at this link!](https://www.theengineeringprojects.com/2021/05/infrared-tracker-sensor-library-for-proteus.html)

  ![](https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Line-following%20robot/Proteus%20schematic%20V1.1.png?raw=true)

  - A higher quality image can be found inside the same folder mentioned above.

### Functionality

1. **Initialization**: 
   - Initializes GPIO pins, ADC, Timers, USART, and sensors.
   - Sets up the servo motor and ultrasonic sensor for obstacle detection.
   - Microcontroller controls the Motors and has 3 functions for them:
     1) Steer vehicle right by turning on the 2 right motors.
     2) Steer vehicle left by turning on the 2 left motors.
     3) Move vehicle forward by turning on all motors.
     4) Reverse vehicle backwards by reversing signals on all motors (not used in the project but the function is there and working).

2. **Line Following**:
   - Continuously reads the analog and digital values from the TCRT5000 sensors.
   - Adjusts the motor speeds and directions to follow the detected line.
   - Microcontroller constantly reads analog and digital values from the 3 TCRT sensors:
     1) If the left sensor digital value is 1 and the right sensor digital value is zero, then the vehicle turns left.
     2) If the right sensor digital value is 1 and the left sensor digital value is zero, then the vehicle turns right.
     3) If the middle sensor digital value is 0, the vehicle moves forward.

3. **Obstacle Detection and Avoidance**:
   - Uses the HC-SR04 sensor to measure distances to obstacles.
   - Adjusts the servo motor to scan the area.
   - When an obstacle is detected in range (<20CM), the MCU writes to LCD screen a warning and a Buzzer alarm sounds off.

4. **LCD Display**:
   - Displays the sensor readings and robot status on the LCD screen for monitoring. !!!(For debugging only)!!!
   - Displays current direction the vehicle is going, Obstacles detected when ultrasonic distance is <20CM, and errors when they occur. 

### Usage

1. **Hardware Setup**:
   - Connect the TCRT5000 sensors, HC-SR04 sensor, SG-90 servo motor, L293D motor driver ICs, and DC motors to the ATmega32A microcontroller as per the circuit diagram.
![](https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Autonomous%20Vehicle%20-%20KiCad/PDF%20files/Schematic%20V1.0.png?raw=true)

- A higher quality Schematic can be found inside the "PDF files" in the "KiCAD" schematic folder uploaded in the repository.
  
2. **Software Setup**:
   - Clone the repository and open the project in your preferred IDE (e.g., Atmel Studio Microchip).
   - Flash the firmware to the ATmega32A microcontroller (using Extreme Burner).

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

### Final project picture - FRONT
![Finished form - Front](https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Final%20Shape%20-%20Front.jpg?raw=true)

### Final project picture - TOP
![Finished form - Top](https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Finished%20Form%20-%20Top.jpg?raw=true)

### Final project picture - SIDE
![Finsihed form - Side](https://github.com/RattleBrattle/Autonomous-Line-following-Vehicle-/blob/main/Finished%20Form%20-%20Side.jpg?raw=true)

### Contributing

Tell me your thoughts and ideas on how to make this project even better or faster.

You can contact me by email at: baselmohamed802@gmail.com.

Or message me on my LinkedIn! www.linkedin.com/in/basel-sayed-b11534243

### License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
