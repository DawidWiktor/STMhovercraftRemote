#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include <stdio.h>
#include "stm32f4xx_usart.h"
#include "konfiguracje.h"


void Config_USART() {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate =9600;       // 38400 predkoæ do trybu AT
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

}

//PC10
void Config_Tx() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	// konfiguracja linii Tx do wysylania
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//PC11
void Config_Rx() {
	// konfiguracja linii Rx do odbierania
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Config_NVIC() {    // przerawnie dla USART
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



void send_char(char c) {

	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	USART_SendData(USART3,  c);


}
// funkcja odpowiedzialna za wysylanie danych poprzez usart
void send_string(const char* s) {
	while (*s) {
		send_char(*s++);
	}
}

void tim3_konf()
{

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period =8399;
		TIM_TimeBaseStructure.TIM_Prescaler =999;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_Cmd(TIM3, ENABLE);
}


void NIVC_TIM3()
{
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
			NVIC_InitTypeDef NVIC_InitStructure;
			NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;
			NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
			TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
}




// pin PA1
void konfiguracja_potencjometr_1()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

// pin PA2
void konfiguracja_potencjometr_2()
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure2;

	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure2);

	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC2, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_84Cycles);
	ADC_Cmd(ADC2, ENABLE);
	ADC_SoftwareStartConv(ADC2);
}


void ustawienia_diod()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void przycisk()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void Config_EXTI() {
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);
}

void Init_EXTI() {
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
