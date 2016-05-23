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
#include "configuration.h"

volatile int ADC_Result = 0;        // the value from the rotate potentiometer
volatile int ADC_Result2 = 0;		// the value from the linear potentiometer
volatile char send_data[6];			// data for send to control the hovercraft
volatile char receive_data; 		// receive data from the hovercraft
volatile int distance;				// receive the distance from the hovercraft
volatile int direction_servo; 		// 1200 is middle of value
volatile int speed_engine1;  		// the value for set speed the forward engine, max value = 120, min value = 0
volatile int speed_engine2 = 120; 	// the value for set speed the top-down engine, max value = 120, min value = 0
volatile int direction_engine1 = 34; 		// when the variable is 0, the hovercraft reverses, otherwise the hovercraft goes forward
volatile int direction_engine2 = 34; 		// when the variable is 0, the engine is off, otherwise is on
volatile int on_off = 0;					// the variable informs about connection with the hovercraft
volatile int check_signal = 0;				// the ancillary variable to check connection with the hovercraft
volatile char row1_lcd[15], row2_lcd[15]; 	// the variables store data, which is displayed
volatile int buffer_lcd, buffer2_lcd;		// the ancillary variables are used to show data on the display


void USART3_IRQHandler(void)	 	// handling interruption from USART
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {

		receive_data = USART3->DR;
		check_signal = 0;
		on_off = 1;

		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
	}
}
void read_adc()  					// read values from the potentiometers
{
	ADC_Result = ADC_GetConversionValue(ADC1) ;
	ADC_Result2 = ADC_GetConversionValue(ADC2);
}

void TIM3_IRQHandler(void)			// handling interruption from the timer 3
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET || ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);

		if (check_signal == 10) {
			on_off = 0;
		}
		if (check_signal < 10) {
			check_signal++;
		}

		read_adc();

		buffer_lcd = (ADC_Result2 - 2047) / 45.5;
		if (buffer_lcd > 45) {
			buffer_lcd = 45;
		}
		if (buffer_lcd < -45) {
			buffer_lcd = -45;
		}

		direction_servo=(ADC_Result2/82) +45;
		speed_engine1=ADC_Result/34;
		if(speed_engine1>120){
			speed_engine1=120;
		}
		buffer2_lcd = (ADC_Result)/40;
		if(buffer2_lcd>100){
			buffer2_lcd=100;
		}
		if(direction_engine1 == 33)
			{buffer2_lcd = 0-buffer2_lcd;}

		if (on_off == 0) {			 // show data when we don't have connection with the hovercraft
				lcd_cls();
				sprintf(row1_lcd, "OFF POWER %4d%%", buffer2_lcd);
				sprintf(row2_lcd, " angle %3d*", buffer_lcd);
				lcd_str_center(0, row1_lcd);
				lcd_str_center(1, row2_lcd);
		}
		else
		{						   			// show data when we have connection with the hovercraft
			distance=(int)receive_data;
			    lcd_cls();
				sprintf(row1_lcd, "ON POWER %4d%%", buffer2_lcd);
				sprintf(row2_lcd, "%3dcm angle %3d*", distance, buffer_lcd);
				lcd_str_center(0, row1_lcd);
				lcd_str_center(1, row2_lcd);
		}
		//sprintf(send_data,"=xx!!~");
		send_data[0] = (char) direction_servo;
		send_data[1] = (char) speed_engine1;
		send_data[2] = (char) speed_engine2;
		send_data[3] = (char) direction_engine1;
	//	send_data[3] = NULL;
		send_data[4] = (char) direction_engine2;
		send_data[5] = '~'; 			// means that this is the end of data
		send_string(send_data);			// send data to control the hovercraft

		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}



void TIM2_IRQHandler(void) 			// handling interruption from the timer 2
{

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{

		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
			if (direction_engine1 == 33){
				direction_engine1 = 34;					// change direction forward/rear
				GPIO_SetBits(GPIOD, GPIO_Pin_14);		// if direction is rear, the orange LED is on
			}
			else if (direction_engine1 == 34)
			{
				direction_engine1 = 33;
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			}
		}
		TIM_Cmd(TIM2, DISABLE);
		TIM_SetCounter(TIM2, 0);

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}



void EXTI0_IRQHandler(void) {  			// handling interruption from the button

		TIM_Cmd(TIM2, ENABLE);
		EXTI_ClearITPendingBit(EXTI_Line0);
}


int main(void)
{

	SystemInit();
	lcd_init();
	Config_potentiometer1();
	Config_potentiometer2();
	Config_LED();
	Config_TIM3();
	NIVC_TIM3();
	Config_TIM2();
	NIVC_TIM2();
	Config_button();
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
