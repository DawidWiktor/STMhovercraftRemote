/*----------------------------------------------------*/
//Funkcje konfigurujace USART
/* Sposob podlaczenia do modulu BlueTooth
STM 		-	MODU� BT
PC10(TX)	-	RX
PC11(RX)	-	TX

Modul Bluetooth (HC-05) zasilany napi�ciem 5 V

Komendy AT do ustawienia modulu HC-05(jednorazowo)
AT+NAME+HoverCraftRemote\r\n
AT+PSWD=1234\r\n
AT+UART=9600,1,2\r\n

PAROWANIE:
AT+ROLE=1\r\n     ustawia modul w tryb master
AT+CMODE=0\r\n
AT+INIT\r\n
AT+PAIR=ADRES,20\r\n
AT+BIND=ADRES\r\n
AT+LINK=ADRES\r\n
 --------------------------------------------*/

void Config_USART();
void Config_Tx();
void Config_Rx();
void Config_NVIC();
/*----------------------------------------------------*/
// funkcje odpowiedzialne za wysylanie stringow poprzez usart do modulu BT
void send_char(char c);
void send_string(const char* s);
/*----------------------------------------------------*/
void Config_TIM3();
void NIVC_TIM3();
void Config_TIM2();
void NIVC_TIM2();
/*----------------------------------------------------*/
//Funkcje konfiguruj�ce potencjometry
//Sposob podlaczenia potencjometrow:

void Config_potentiometer1();
void Config_potentiometer2();
/*----------------------------------------------------*/
//Funkcje konfiguruj�ca diody
void Config_LED();
/*----------------------------------------------------*/
//Funkcje konfiguruj�ca przycisk
void Config_button();
void Config_EXTI();
void Init_EXTI();
/*----------------------------------------------------*/
