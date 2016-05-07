

/*----------------------------------------------------*/
//Funkcje konfiguruj¹ce USART
/* Sposób pod³¹czenia domodu³u BlueTooth
STM 		-	MODU£ BT
PC10(TX)	-	5RX
PC11(RX)	-	TX

Modu³ Bluetooth (HC-05) zasilany napiêciem 5 V
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
//Funkcje konfiguruj¹ce potencjometry
//Sposób pod³¹czenia potencjometrów:

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
