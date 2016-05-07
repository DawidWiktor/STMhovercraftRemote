

/*----------------------------------------------------*/
//Funkcje konfiguruj�ce USART
/* Spos�b pod��czenia domodu�u BlueTooth
STM 		-	MODU� BT
PC10(TX)	-	5RX
PC11(RX)	-	TX

Modu� Bluetooth (HC-05) zasilany napi�ciem 5 V
 */
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
