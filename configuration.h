/*----------------------------------------------------*/
/* Connection STM with the module Bluetooth
STM 		-	module Bluetooth
PC10(TX)	-	RX
PC11(RX)	-	TX
GND			-   GND
3V			-	3V

AT commands to set the HC-05 module Bluetooth
AT+NAME+HoverCraftRemote\r\n        set name of the module Bluetooth
AT+PSWD=1234\r\n					set password to connect with the module Bluetooth
AT+UART=9600,1,2\r\n				set speed of transmition data

Binding:
AT+ROLE=1\r\n     					set the module in master mode
AT+CMODE=0\r\n						use a predefined address
AT+INIT\r\n							initialize the SPP profile lib
AT+LINK=ADRES\r\n					set addres to connect
 --------------------------------------------*/
//Configuration USART, TX, RX and interruption for its
void Config_USART();
void Config_Tx();
void Config_Rx();
void Config_NVIC();
/*----------------------------------------------------*/
// send data using USART
void send_char(char c);
void send_string(const char* s);
/*----------------------------------------------------*/
//Configuration the timers and interruptions for them
void Config_TIM3();
void NIVC_TIM3();
void Config_TIM2();
void NIVC_TIM2();
/*----------------------------------------------------*/
//Configuration the potentiometers
void Config_potentiometer1();
void Config_potentiometer2();
/*----------------------------------------------------*/
//Configuration the diods LED
void Config_LED();
/*----------------------------------------------------*/
//Configuration the button
void Config_button();
void Config_EXTI();
void Init_EXTI();
/*----------------------------------------------------*/
