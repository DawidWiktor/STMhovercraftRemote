#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "LCD/lcd_hd44780.h"
#include <stdio.h>
#include "stm32f4xx_usart.h"
#include "konfiguracje.h"

volatile  int ADC_Result=0;
volatile int ADC_Result2=0;
volatile char wyslanie[5];
volatile char odleglosc[3]; // odebrana odleglosc
volatile int dane_serwo = 1200; // wartosc srodkowa serwa
volatile int dane_silnik1 = 0; // silnik napedzajacy, wylaczony, maks 120, min 0
volatile int dane_silnik2 = 0; // silnik unoszacy, wylaczony, wlaczony 120
volatile int kierunek_silnik1 = 1; // silnik napedzajacy, kierunek w przod
volatile int kierunek_silnik2 = 1; // silnik unoszacy, kierunek unoszacy
volatile char BTData; //zmienna przechowujaca odebrane dane
volatile int licznik=0;
volatile char linia1[15], linia2[15];
volatile int on_off=0;
volatile int wartownik=0; //sygnalizuje ze zostaly dane odebrane
volatile int bufor, bufor2,odlegl;
volatile int wysylana_kierunek,wysylana_obroty;
static __IO uint32_t TimingDelay;

// funkcje inicjalizujace zegar SysTick
void Delay(__IO uint32_t nTime) {
	TimingDelay = nTime;
	while (TimingDelay != 0)
		;
}
void TimingDelay_Decrement(void) {
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}
}
void SysTick_Handler(void) {
	TimingDelay_Decrement();
}





void USART3_IRQHandler(void) { // obs�uga przerwania dla USART
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {

		BTData = USART3->DR;
		wartownik=1;
		licznik=0;
		on_off=1;

		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}

}
}
void odadc()
{
	ADC_Result = ADC_GetConversionValue(ADC1) ;
	ADC_Result2 = ADC_GetConversionValue(ADC2);

}

void TIM3_IRQHandler(void)
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET || ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);

if(licznik==10){on_off=0;}
if(licznik<10)
{
licznik++;
}
		if(wartownik==1)
		{
			bufor=BTData;
			//odleglosc[0]=bufor/100;
		//	bufor=bufor-odleglosc[0];
		//	odleglosc[1]=bufor/10;
	//		bufor=bufor-odleglosc[1];
	//		odleglosc[2]=bufor;
	//		bufor=0;
			//obs�u�enei odebranych danych
			//uruchomienie buzzera
			//ewentualny komunikat na wyswietlaczu
			//zmienna z odebranymi danymi to BTData w postaci jednego znaku zapenwe tzreba przerobic to na 3 znaki do tablicy odleglosc
			wartownik=0;
		}
		odadc();

		bufor = (ADC_Result2 - 2047) / 45.5; //wyliczenie czy skr�tw lewoczy w prawo i stopni
		if (bufor > 45) {
			bufor = 45;
		}
		if (bufor < -45) {
			bufor = -45;
		}

					wysylana_kierunek=(ADC_Result2/82) +45;
					wysylana_obroty=ADC_Result/34;
					if(wysylana_obroty>120){wysylana_obroty=120;}
					bufor2 = (ADC_Result)/40;
					if(bufor2>100){bufor2=100;}
		if(kierunek_silnik1 == 0)
			{bufor2 = 0-bufor2;}

		if (on_off == 0) {
				lcd_cls();
				sprintf(linia1, "OFF POWER %4d%%", bufor2); // przeliczenie wartosci na procenty
				sprintf(linia2, " angle %3d*", bufor);
				lcd_str_center(0, linia1);
				lcd_str_center(1, linia2);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);


		} else
		{
			odlegl=(int)BTData;
			    lcd_cls(); // wyczyszczenie ekranu
				sprintf(linia1, "ON POWER %4d%%", bufor2);
				sprintf(linia2, "%3dcm angle %3d*", odlegl, bufor);
				lcd_str_center(0, linia1);
				lcd_str_center(1, linia2);
		}

			sprintf(wyslanie, "%c%c%c%c%c", wysylana_kierunek, wysylana_obroty, 120,
					kierunek_silnik1, kierunek_silnik2);
			send_string(wyslanie);

		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}


void EXTI0_IRQHandler(void) {
	//Delay(200);
	int i=0;
	for(i=0;i<1000000;i++){}
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		if(kierunek_silnik1 == 1)
					kierunek_silnik1 = 0;
		else if(kierunek_silnik1 == 0)
			kierunek_silnik1 = 1;
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}


// przerwanie od przycisku (tryb jazdy)
void EXTI4_IRQHandler(void) {
	//Delay(200);
	int i=0;
		for(i=0;i<1000000;i++){}
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

		// tutaj wysla� odpowiedni� informacj� do poduszkowca i zmieni� zmienn� odpowiadaj�c� za tryb jazdy

		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

int main(void)
{

	SystemInit();
	lcd_init();
	konfiguracja_potencjometr_1();
	konfiguracja_potencjometr_2();
	ustawienia_diod();
	tim3_konf();
	NIVC_TIM3();
	przycisk();
	Init_EXTI();
	Config_EXTI();
	Config_Tx();
	Config_Rx();
	Config_USART();
	Config_NVIC();
	USART_Cmd(USART3, ENABLE);
	NVIC_EnableIRQ(USART3_IRQn);
	przycisk2();
	Init_EXTI2();
	Config_EXTI2();

	//if (SysTick_Config(SystemCoreClock / 1000)) {
		//	while (1)
			//	;
		//}


while(1){

}

}
