# *STMhovercraftRemote*

##Overview
The project of a simple remote control based on STM32F4-DISCOVERY board. It controls a hovercraft of the project [STMhovercraft] (https://github.com/PUT-PTM/STMhovercraft).

##Description



##Tools
CoCOX CoIDE

##How to run
To run the project you should have hardware:
- STM32F4-DISCOVERY board
- Two rotary potentiometers - linear (10k ohm)
- Linear potentiometer (10k ohm)
- LCD display 2x16 with HD44780 controller 
- HC-05 module Bluetooth
 
 How to use
 
1. Connect STM32F4-DISCOVERY board with LCD display in this way: 
  *  LCD display <--->  STM32
  *  VDD  <--->  5V
  *  VSS  <--->  GND
  *  V0   <--->  connect with the rotary potentiometer
  *  D4   <--->  PD8
  *  D5   <--->  PD10
  *  D6   <--->  PD12
  *  D7   <--->  PD14
  *  RS   <--->  PD9
  *  RW   <--->  PD11
  *  E    <--->  PD13
  *  A    <--->  5V
  *  K    <--->  GND
  
2. Connect the linear potentiometer(GND, PA2, VDD).
3. Connect the rotary potentiometer(GND, PA1, VDD).
4. Connect STM32F4-DISCOVERY board with module Bluetooth in this way:
  * module Bluetooth <---> STM32
  * 3V  <---> 3V
  * GND <---> GND
  * RX  <---> PC10
  * TX  <---> PC11
  
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
