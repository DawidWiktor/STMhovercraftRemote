# *STMhovercraftRemote*

##Overview
The project of a simple remote control based on STM32F4-DISCOVERY board. It controls a hovercraft of the project [STMhovercraft] (https://github.com/PUT-PTM/STMhovercraft).

##Description
The project consists of:
- STM32F4-Discovery board,
- Two rotary potentiometers - logarithmic(10k ohm),
- Linear potentiometer(10k ohm),
- LCD display 2x16 with HD44780 controller,
- HC-05 module Bluetooth.

Due to one rotary potentiometer and one linear potentiometer we can control speed and direction of the engine's hovercraft. Second of the rotary potentiometer controls contrast of the LCD display. The LCD display shows information about speed(in percentages), direction(in angles), connection with hovercraft and distance from a barrier(in centimetres), which the hovercraft sends to the remote control.

#### Send data:
- xyzab~
- x - servos turn in the values between 40 and 80
- y - engine 1 speed in the values between 0 and 120
- z - engine 2 speed in the values between 0 and 120
- a - rotate direction of engine 1 in the values of 0 or 1
- b - rotate direction of engine 2 in the values of 0 or 1
- sign "~" means that this is the end of data
##Tools
CoCOX CoIDE

##How to run
1. Connect STM32F4-DISCOVERY board with LCD display in this way: 
  *  LCD display - STM32
  *  VDD  -  5V
  *  VSS  -  GND
  *  V0   -  connect with the rotary potentiometer
  *  D4   -  PD1
  *  D5   -  PD3
  *  D6   -  PD5
  *  D7   -  PD7
  *  RS   -  PD0
  *  RW   -  PD2
  *  E    -  PD4
  *  A    -  5V
  *  K    -  GND
 
2. Connect the linear potentiometer(GND, PA2, VDD).
3. Connect the rotary potentiometer(GND, PA1, VDD).
4. Bluetooth Settings (AT COMANDS in 6 steps):
 -AT+ROLE=1\r\n        
 -AT+CMODE=0\r\n 
 -AT+INIT\r\n
 -AT+PAIR=ADRES,20\r\n
 -AT+BIND=ADRES\r\n
 -AT+LINK=ADRES\r\n
 When ADRES is Hovercraft Bluetooth adres.
5. Connect STM32F4-DISCOVERY board with module Bluetooth in this way:
  * module Bluetooth - STM32
  * 3V  - 3V
  * GND - GND
  * RX  - PC10
  * TX  - PC11
  
##How to compile
Download the project and compile it with CooCox CoIDE.

##Attributions
* http://stm32f4-discovery.net/2015/07/hal-library-15-hd44780-for-stm32fxxx/
* http://elektronika327.blogspot.com/2015/12/4-stm32-m4f-discovery-wyswietlacz-ze.html

##License
MIT

##Credits
* Damian Filipowicz
* Dawid Wiktorski

The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.

Supervisor: Tomasz Mańkowski
