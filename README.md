# Safer RC Car
Breck O'Connor

Instructions to Use Project:
- Download the Receiver and Transmitter Arduino code from the repo
- Load the Receiver code onto the Arduino to be used on the vehicle
- Load the Transmitter code onto the Arduino to be used as the controller
- Setting up Controller
  - Connect to Joysticks with each one wired to a separate analog input pin
  - Connect the NRF24L01+ Module to the Arduino making sure to have the correct pins connected
- Setting up Vehicle
  - Connect the NRF24L01+ Module to the Arduino making sure to have the correct pins connected
  - Wire the photoresistor to a resistor connected to ground and to an analog input pin
  - Wire the two HCSR04 Ultrasonic Modules to the Arduino and connect the two data lines to the same pin
  - Connect the respective Arduino pins to the L293D motor driver
  - Connect the output pins of the motor driver to the two DC motors underneath the vehicle
  - Connect the 3.7V Li-ion battery to the external power source pin of the driver
- Using RC Car
  - Power up the controller via USB
  - Wait 10 seconds
  - Power up the vehicle via USB
  - On the controller, the right joystick controls the right wheel, and the left the left
  - Drive the vehicle forward or backward holding both joysticks in the same direction
  - Go towards a wall to see the vehicle slow down and try to not hit the wall you are going towards
  - Try turning on/off lights nearby to see the automatic lights turn on when needed

Test Scripts were used when initially trying out components, but have been added onto to create the final code that you see now.
