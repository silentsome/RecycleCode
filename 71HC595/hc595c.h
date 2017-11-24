#include "hc595.h"
#include "stm32l0xx_hal.h"
#include "timer.h"
u8 show_ch=1;
u8 wei_table[]={ 0x7f,0xbf,0xdf};
u8 seg_table[]={ 0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void hc595_init()
{
	
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	/////////////////////////////////////
	/////////////////////////////////////
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_9, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	/////////////////////////////////////
	/////////////////////////////////////
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void hc595_out(void)
{
STL; //并行输出时钟
delay_us(5);	
STH;
delay_us(5);
STL;		
}

void hc595_write(u8 temp)
{		
u8 i;
for(i=0;i<8;i++)
{
	SHIFTL;
	if((temp&0x80) == 0x80)	{ SDAH; }//串行数据输出
	else { SDAL; } 
SHIFTH; //移位输入时钟，上升沿输入
temp<<=1;
delay_us(5);
SHIFTL;
}
}

void hc595_show(u8 ch,u16 number)
{
static u8 status=0;
switch(status)
{
	case 0:
	{
		status++;
		hc595_write(seg_table[number/100]);//第一位显示的写入显示的内容
		hc595_out(); 
		DISPEN1L; DISPEN2H; DISPEN3H; 
		delay_us(500);
	}break;

	case 1:
	{
		status++;
		hc595_write(seg_table[number/10%10]);
		hc595_out(); 
		DISPEN1H; DISPEN2L; DISPEN3H; 
		delay_us(250);
	}break;

	case 2:
	{
		status=0;
		hc595_write(seg_table[number%10]);
		hc595_out();
		DISPEN1H; DISPEN2H; DISPEN3L;			
		delay_us(500);
	}break;
}
 DISPEN1H; DISPEN2H; DISPEN3H;
}
