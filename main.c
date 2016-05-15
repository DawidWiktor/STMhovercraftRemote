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

volatile int ADC_Result=0;      // zmienna przechowujaca wartosc z potencjometru obrotowego
volatile int ADC_Result2=0;		// zmienna przechowujaca wartosc z potenjometru liniowego
volatile char wyslanie[6];		// wyslanie danych
volatile char odleglosc[3];		// odebrana odleglosc
volatile int dane_serwo = 1200; // wartosc srodkowa serwa
volatile int dane_silnik1 = 0;  // silnik napedzajacy, wylaczony, maks 120, min 0
volatile int dane_silnik2 = 0;  // silnik unoszacy, wylaczony, wlaczony 120
volatile int kierunek_silnik1 = 1; 		// silnik napedzajacy, kierunek w przod
volatile int kierunek_silnik2 = 1; 		// silnik unoszacy, kierunek unoszacy
volatile char BTData; 		    //zmienna przechowujaca odebrane dane
volatile int licznik = 0;				// zmienna pomocnicza do ustalania polaczenia z poduszkowcem
volatile char linia1[15], linia2[15]; 	// zmienne przechowujace wyswietlany tekst
volatile int on_off = 0;				// zmienna informujaca czy jest polaczenie z poduszkowcem
volatile int bufor, bufor2, odlegl;		// zmienne pomocnicze wykorzystywane przy wyswietlaniu danych
volatile int wysylana_kierunek, wysylana_obroty;




void USART3_IRQHandler(void)	 	// obs³uga przerwania dla USART
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {

		BTData = USART3->DR;
		licznik = 0;			 	// gdy odebrana jest dana, licznik jest zerowany
		on_off = 1;

		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
	}
}
void odczyt_z_potencjometrow()  	// odczytywanie wartosci z potencjometrow
{
	ADC_Result = ADC_GetConversionValue(ADC1) ;
	ADC_Result2 = ADC_GetConversionValue(ADC2);

}

void TIM3_IRQHandler(void)			// obluga przerwania od timera 3
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET || ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);

		if (licznik == 10) {
			on_off = 0;
		}
		if (licznik < 10) {
			licznik++;
		}

		odczyt_z_potencjometrow();

		bufor = (ADC_Result2 - 2047) / 45.5; 	// przeliczanie wartosci, ktore beda wyswietlane
		if (bufor > 45) {
			bufor = 45;
		}
		if (bufor < -45) {
			bufor = -45;
		}

		wysylana_kierunek=(ADC_Result2/82) +45;
		wysylana_obroty=ADC_Result/34;
		if(wysylana_obroty>120){
			wysylana_obroty=120;
		}
		bufor2 = (ADC_Result)/40;
		if(bufor2>100){
			bufor2=100;
		}
		if(kierunek_silnik1 == 0)
			{bufor2 = 0-bufor2;}

		if (on_off == 0) {			// wyswietlenie danych, gdy nie ma polaczenia z poduszkowcem
				lcd_cls(); 			// wyczyszczenie ekranu
				sprintf(linia1, "OFF POWER %4d%%", bufor2);
				sprintf(linia2, " angle %3d*", bufor);
				lcd_str_center(0, linia1);
				lcd_str_center(1, linia2);
		}
		else
		{						    // wyswietlenie danych, gdy jest polaczenie z poduszkowcem
			odlegl=(int)BTData;
			    lcd_cls();
				sprintf(linia1, "ON POWER %4d%%", bufor2);
				sprintf(linia2, "%3dcm angle %3d*", odlegl, bufor);
				lcd_str_center(0, linia1);
				lcd_str_center(1, linia2);
		}

		wyslanie[0] = (char) wysylana_kierunek;
		wyslanie[1] = (char) wysylana_obroty;
		wyslanie[2] = (char) 120;
		wyslanie[3] = (char) kierunek_silnik1;
		wyslanie[4] = (char) kierunek_silnik2;
		wyslanie[5] = "~";
			//sprintf(wyslanie, "%c%c%c%c%c~", wysylana_kierunek, wysylana_obroty, 120,
			//		kierunek_silnik1, kierunek_silnik2);
		send_string(wyslanie);			// wyslanie danych do sterowania poduszkowcem

		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}



void TIM2_IRQHandler(void) 			//obsluga przerwania od timera 2
{

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{

		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
			if (kierunek_silnik1 == 1)
				kierunek_silnik1 = 0;					// zmiana kierunku silnika
			else if (kierunek_silnik1 == 0)
				kierunek_silnik1 = 1;
			GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
		}
		TIM_Cmd(TIM2, DISABLE);
		TIM_SetCounter(TIM2, 0);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}



void EXTI0_IRQHandler(void) {  			// obluga przerwania od przycisku

		TIM_Cmd(TIM2, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line0);
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
	tim2_konf();
	NIVC_TIM2();
	przycisk();
	Init_EXTI();
	Config_EXTI();
	Config_Tx();
	Config_Rx();
	Config_USART();
	Config_NVIC();
	USART_Cmd(USART3, ENABLE);
	NVIC_EnableIRQ(USART3_IRQn);


while (1) {

	}

}
