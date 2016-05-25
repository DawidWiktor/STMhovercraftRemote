# *STMhovercraftRemote*

##Overview
The project of a simple remote control based on STM32F4-DISCOVERY board. It controls a hovercraft of the project [STMhovercraft] (https://github.com/PUT-PTM/STMhovercraft). [The movies] (https://drive.google.com/folderview?id=0B-LZLyx-e6vsSm80X2F5YXJQZ0U&usp=sharing) show the hovercraft and the remote control.

##Description
The project consists of:
- STM32F4-Discovery board,
- Two rotary potentiometers - logarithmic(10k ohm),
- Linear potentiometer(10k ohm),
- LCD display 2x16 with HD44780 controller,
- HC-05 module Bluetooth.

Due to one rotary potentiometer and one linear potentiometer we can control speed and direction of the engine's hovercraft. Second of the rotary potentiometer controls contrast of the LCD display. The LCD display shows information about speed(in percentages), direction(in degrees), information about connection with hovercraft and distance from a barrier(in centimetres), which the hovercraft sends to the remote control.

The remote control sends data in this way:
- xyzab~
- x - servo turns in the values between 40 and 80
- y - engine 1 speed in the values between 0 and 120
- z - engine 2 speed in the values between 0 and 120
- a - rotate direction of engine 1 in the values of 33 or others
- b - rotate direction of engine 2 in the values of 33 or others
- sign '~' means that this is the end of data
##Tools
CoCOX CoIDE

##How to run
1. Connect STM32F4-DISCOVERY board with the LCD display in this way: 
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
4. Connect STM32F4-DISCOVERY board with the module Bluetooth in this way:
  * module Bluetooth - STM32
  * VCC  - 3V
  * GND - GND
  * RX  - PC10
  * TX  - PC11
5. Bluetooth settings (AT comands in 4 steps):
 - AT+ROLE=1\r\n              set name of the module Bluetooth
 - AT+CMODE=0\r\n             use a predefined address
 - AT+INIT\r\n                initialize the SPP profile lib
 - AT+LINK=ADRES\r\n          set addres to connect

##How to compile
Download the project and compile it with CooCox CoIDE.

##Future improvements
- sometimes, after set connection with the hovercraft, the remote control freezes and we need to press the reset key in the STM board
- we have an idea to use DMA for reading values from potentiometers

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
