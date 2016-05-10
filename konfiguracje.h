/*----------------------------------------------------*/
//Funkcje konfigurujace USART
/* Sposob podlaczenia do modulu BlueTooth
STM 		-	MODU£ BT
PC10(TX)	-	RX
PC11(RX)	-	TX

Modul Bluetooth (HC-05) zasilany napiêciem 5 V

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
void tim3_konf();
void NIVC_TIM3();
/*----------------------------------------------------*/
//Funkcje konfiguruj¹ce potencjometry
//Sposob podlaczenia potencjometrow:

void konfiguracja_potencjometr_1();
void konfiguracja_potencjometr_2();
/*----------------------------------------------------*/
//Funkcje konfiguruj¹ca diody
void ustawienia_diod();
/*----------------------------------------------------*/
//Funkcje konfiguruj¹ca przycisk
void przycisk();
void Config_EXTI();
void Init_EXTI();
/*----------------------------------------------------*/
