# lamborguino

This repo contains the code used to test and develop "lamborguino", an arduino project that implements an RC bluetooth self-driving car with alarm system.
The final goal is to have a programmable wake-up alarm which triggers a self-driving car that goes around the room, forcing the user to get out of bed to stop the alarm.

## Wiring and Components

![wiring scheme]{https://raw.githubusercontent.com/giuliocandre/lamborguino/master/wiring.jpg
* 2x 9V batteries
* HC-06 bluetooth module
* L298n motor bridge
* 3x ultrasonic proximity sensors

To commmunicate with the bluetooth module, one can use the "Android HC-06 terminal" application, available on the Play Store.

## Code description

### main file: ProjectSveglia.ino

The final code that has to be loaded on the Arduino board is "ProjectSveglia.ino".
The user can communicate commands to the board by connecting to HC-06 from an android device (e.g. using "Android HC-06 Terminal") and sending ASCII strings:

#### List of commands
```
avanti!
```
It makes the car go forward
```
indietro!
```
It makes the car go back
```
destra!
```
It turns right - this function is implemented by setting an opposite behaviour to the wheels
```
sinistra!
```
it turns left
```
stop!
```
It stops the car.
```
drive!
```
The car goes in self-drive mode. It will start going forward and then it'll adjust its direction according to the distance measured by the sensors.
For a complete FSM diagram, refer to the project documentation (Report.pdf). Use any other command to exit from self-drive mode.
```
sveglia HH MM!
```
It sets the wake up time. The alarm will start in HH hours and MM minutes.
So actually one can only set the relative timer.
To stop the alarm the user will need to push the reset button.
To reset an alarm time, push the reset button and then use this command again

### project.ino
This was an intermediate version of the code. It implements all the functions described above apart from the "sveglia" command.
Use this to test whether the bluetooth commands are working or not. 
For debugging purposes, use the serial monitor tool provided in the arduino IDE to check messages printed by the board. Messages report:
* Strings received from the bluetooth module
* Current state of the FSM (if in self-drive mode)
* Distance measured by the three sensors (if in self-drive mode)

### selfDrive_test.ino
Contains a test code for the proximity sensors only. It doesn't implement any bluetooth or motor function, but it's used to check the proper operation o the proximity sensors and the FSM logic for self-drive mode.

### MachineFunctions.ino
This implements all the functions to pilot the four motors.
