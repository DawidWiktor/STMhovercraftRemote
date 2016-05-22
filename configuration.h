/*----------------------------------------------------*/
/* Connection STM with the module Bluetooth
STM 		-	module Bluetooth
PC10(TX)	-	RX
PC11(RX)	-	TX
GND			-   GND
3V			-	3V

AT commands to set the HC-05 module Bluetooth
AT+NAME+HoverCraftRemote\r\n
AT+PSWD=1234\r\n
AT+UART=9600,1,2\r\n

Binding:
AT+ROLE=1\r\n     set the module in master mode
AT+CMODE=0\r\n
AT+INIT\r\n
AT+PAIR=ADRES,20\r\n
AT+BIND=ADRES\r\n
AT+LINK=ADRES\r\n
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
