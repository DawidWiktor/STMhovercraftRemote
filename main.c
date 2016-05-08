
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "LCD/lcd_hd44780.h"
#include <stdio.h>
#include "stm32f4xx_usart.h"
#include "konfiguracje.h"

int ADC_Result=0;
int ADC_Result2=0;
int inicjalizacja = 1;
char wyslanie[16];
char odleglosc[3];
int dane_serwo = 1200;
volatile int dane_silnik1 = 0; // silnik napedzajacy, wylaczony, maks 65500, min 0
int dane_silnik2 = 0; // silnik unoszacy, wylaczony, wlaczony 65500
int kierunek_silnik1 = 1; // silnik napedzajacy, kierunek w przod
int kierunek_silnik2 = 1; // silnik unoszacy, kierunek unoszacy
char BTData[5]; //zmienna przechowujaca odebrane dane
int licznik=0;
char linia1[15], linia2[15];
int on_off=0;
int wartownik=0; //sygnalizuje ze zostaly dane odebrane

//wpisuje 0 w calej tablicy
void wyzerowanie()
{
	int i=0;
	for( i=0;i<5;i++){BTData[i]="0";}

}

void USART3_IRQHandler(void) { // obs³uga przerwania dla USART
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {

		if (inicjalizacja == 1) {
			char odebrana_dana = USART3->DR;

			// przekroczono licznik (ilosc znakow bez konca lini lub dostal znak poczatku to zeruje tablice
			if (licznik == 6 || odebrana_dana == "A") {
				licznik = 0;
				wyzerowanie();
				BTData[licznik] = odebrana_dana;
				licznik++;
			} else {

				BTData[licznik] = odebrana_dana;
								licznik++;
				}

			}
		//sprawdzenie poprawnosci danych
			if(licznik==5 && BTData[0]=="A" && BTData[4]=="Z" && wartownik==0)
			{
				odleglosc[0]=BTData[1];
				odleglosc[1]=BTData[2];
				odleglosc[2]=BTData[3];
				wartownik=1;
			}

	}

		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {
		}

}
void odadc()
{
	ADC_Result = ADC_GetConversionValue(ADC1) * 16;
		if (ADC_Result > 65500) {
			ADC_Result = 65500;
		}

		ADC_Result2 = ADC_GetConversionValue(ADC2) * 0.6 - 29;
		if (ADC_Result2 > 2400) {
			ADC_Result2 = 2400;
		}
		if (ADC_Result2 < 0) {
			ADC_Result2 = 0;
		}
}

void TIM3_IRQHandler(void)

{
	int bufor, bufor2;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)

	{
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET || ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);



		if(wartownik==1)
		{
			//obs³u¿enei odebranych danych
			//uruchomienie buzzera
			//ewentualny komunikat na wyswietlaczu
			wartownik=0;
		}
		odadc();

		bufor = (ADC_Result2 - 1200) / 13.3; //wyliczenie czy skrêtw lewoczy w prawo i stopni (1200/13,3=90,23)
		if (bufor > 90) {
			bufor = 90;
		}
		if (bufor < -90) {
			bufor = -90;
		}

		bufor2 = (ADC_Result) / 6550;
		bufor2 = bufor2 * 10;
		if(kierunek_silnik1 == 0)
			bufor2 = 0-bufor2;

		if (on_off == 0) {
				lcd_cls();
				sprintf(linia1, "OFF POWER %4d%%", bufor2); // przeliczenie wartosci na procenty
				sprintf(linia2, " angle %3d*", bufor);
				lcd_str_center(0, linia1);
				lcd_str_center(1, linia2);
				GPIO_ToggleBits(GPIOD, GPIO_Pin_14);

		} else
				sprintf(linia1, "ON POWER %4d%%", bufor2);
				sprintf(linia2, "%3scm angle %3d*", odleglosc, bufor);
				lcd_cls(); // wyczyszczenie ekranu
				lcd_str_center(0, linia1);
				lcd_str_center(1, linia2);

			sprintf(wyslanie, "%d%d%d%d%d", ADC_Result2, ADC_Result, 65500,
					kierunek_silnik1, 1);
			send_string(wyslanie);

		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}


void EXTI0_IRQHandler(void) {
	int i;
	for(i=0; i < 10000; i++){;}
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		if(kierunek_silnik1 == 1)
					kierunek_silnik1 = 0;
		else if(kierunek_silnik1 == 0)
			kierunek_silnik1 = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}


// przerwanie od przycisku (tryb jazdy)
void EXTI4_IRQHandler(void) {
	int i;
	for(i=0; i < 10000; i++){;}
	if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

		// tutaj wyslaæ odpowiedni¹ informacjê do poduszkowca i zmieniæ zmienn¹odpowiadaj¹c¹za tryb jazdy

		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}
int wartosc;
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


while(1){
		GPIO_SetBits(GPIOD,GPIO_Pin_15);
}
}
