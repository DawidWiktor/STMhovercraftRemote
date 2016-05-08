

/*----------------------------------------------------*/
//Funkcje konfiguruj�ce USART
/* Spos�b pod��czenia domodu�u BlueTooth
STM 		-	MODU� BT
PC10(TX)	-	5RX
PC11(RX)	-	TX

Modu� Bluetooth (HC-05) zasilany napi�ciem 5 V

Komendy AT do ustawienia modu�u HC-05(jednorazowo)
AT+NAME+HoverCraftRemote\r\n
AT+PSWD=1234\r\n
AT+UART=9600,1,2\r\n

PAROWANIE:
AT+ROLE=1\r\n     ustawia modu� w tryb master
AT+CMODE=0\r\n
AT+INIT\r\n
AT+PAIR=ADRES,20\r\n
AT+BIND=ADRES\r\n
AT+LINK=ADRES\r\n
 --------------------------------------------*/

//priorytety przerwan:
//			priority   subpriority
//timer		0			0
//przyciks	0			1
//lcd		?			?
//usart		1			0

void Config_USART();
void Config_Tx();
void Config_Rx();
void Config_NVIC();
/*----------------------------------------------------*/
// funkcje odpowiedzialne za wysylanie stringow poprzez usart do modulu BT
void send_char(char c);
void send_string(const char* s);
/*----------------------------------------------------*/
void tim3_konf();
void NIVC_TIM3();
/*----------------------------------------------------*/
//Funkcje konfiguruj�ce potencjometry
//Spos�b pod��czenia potencjometr�w:

void konfiguracja_potencjometr_1();
void konfiguracja_potencjometr_2();
/*----------------------------------------------------*/
//Funkcje konfiguruj�ca diody
void ustawienia_diod();
/*----------------------------------------------------*/
//Funkcje konfiguruj�ca przycisk
void przycisk();
void Config_EXTI();
void Init_EXTI();
/*----------------------------------------------------*/
