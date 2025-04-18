# Elevator-System-Intro-to-Mechatronics-Mid-Project-
This project is a simplified simulation of a 3-floor elevator system developed as a midterm project for the Intro to Mechatronics course. It utilizes an Arduino Uno and various sensors and actuators to replicate core elevator functionalities such as floor selection, movement control, floor indication, and door simulation.

#🔧 Components Used
Arduino Uno

3x Push Buttons (for floor selection)

Infrared (IR) Sensor (for detecting obstacles at the door)

LCD Display with I2C module (for displaying status)

Servo Motor (for simulating the door)

DC Motor (for simulating the elevator movement)

L298N Motor Driver (for driving the DC motor)

7-Segment Display + BCD to 7-Segment Decoder (7447) (for displaying the current floor)

External power supply (for motors)

🧠 Features
Floor Selection: Press any of the 3 buttons to move the elevator to the selected floor.

Obstacle Detection: The IR sensor checks for objects blocking the door, preventing it from closing.

LCD Display: Displays elevator status, such as current floor or door state.

7-Segment Display: Shows the current floor number.

Servo-Controlled Door: Simulates automatic door opening/closing with delay and obstacle logic.

Motorized Movement: DC motor simulates elevator motion between floors.

🔌 Circuit Overview
The project uses:

Digital pins for push buttons and servo motor.

Analog or digital pins for the IR sensor.

I2C pins (A4, A5) for the LCD.

Digital pins for the BCD input to the 7447 decoder.

PWM-enabled pins for motor control through L298N.
