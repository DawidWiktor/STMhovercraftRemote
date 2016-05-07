

/*----------------------------------------------------*/
//Funkcje konfigurujące USART
/* Sposób podłączenia domodułu BlueTooth
STM 		-	MODUŁ BT
PC10(TX)	-	5RX
PC11(RX)	-	TX

Moduł Bluetooth (HC-05) zasilany napięciem 5 V
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
//Funkcje konfigurujące potencjometry
//Sposób podłączenia potencjometrów:

void konfiguracja_potencjometr_1();
void konfiguracja_potencjometr_2();
/*----------------------------------------------------*/
//Funkcje konfigurująca diody
void ustawienia_diod();
/*----------------------------------------------------*/
//Funkcje konfigurująca przycisk
void przycisk();
void Config_EXTI();
void Init_EXTI();
/*----------------------------------------------------*/
