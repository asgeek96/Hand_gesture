# Hand-gesture-control-car
This hand-gesture-control-car is based on arduino uno(Atmea32).
The project is based on wireless communication, where the data from the hand gestures is transmitted to the robot over RF link.
The purpose of project is to control a toy car using accelerometer sensors attached to a hand  glove.
The user just needs to wear a gesture device in which a sensor is included.
The sensor will record the movement of hand in a specific direction which will result in the motion of the robot in the respective directions.



working:-
The project is divided into transmitter and receiver section.
When the robot is powered on, the transmitter part, which consists of Arduino, sensor, Encoder and RF Transmitter, will continuously monitor the sensor.
This data is captured by the Arduino, which then transmits a corresponding data to the Encoder, based on the orientation of the  Sensor. The parallel data received by the encoder is converted into serial data and this serial data is transmitted by the RF Transmitter.
At the receiver section, the RF Receiver receives the serial data and transmits it to the Decoder IC. The Decoder will convert the serial data to parallel data and this parallel data is given to the motor driver IC.
Based on the data, the movement of the motors, and hence the movement of the robot is defined. 

tools used are:-
Arduino UNO,
Adxl335 accelerometer,
HT12E + HT12D Encoder Decoder IC,
RF Wireless Transmitter Receiver Module,
Few jumper wires,
Bread board,
L293D Motor Driving Module.

Applications
Wireless controlled robots are very useful in many applications like remote surveillance, military etc.
Hand gesture controlled robot can be used by physically challenged in wheelchairs.
