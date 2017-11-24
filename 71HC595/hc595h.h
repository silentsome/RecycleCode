#ifndef _HC595_H
#define _HC595_H
#include "main.h"
#include "stm32l0xx_hal.h"

#define NOP __asm("nop")

#define sda_port GPIOA
#define shift_port GPIOA 
#define st_port GPIOA 
#define sda_pin   GPIO_PIN_4
#define shift_pin  GPIO_PIN_2
#define st_pin     GPIO_PIN_3

#define SDAH                   HAL_GPIO_WritePin(sda_port,sda_pin,GPIO_PIN_SET)
#define SDAL                 HAL_GPIO_WritePin(sda_port,sda_pin,GPIO_PIN_RESET)
#define SHIFTH             HAL_GPIO_WritePin(shift_port,shift_pin,GPIO_PIN_SET)
#define SHIFTL           HAL_GPIO_WritePin(shift_port,shift_pin,GPIO_PIN_RESET)
#define STH                      HAL_GPIO_WritePin(st_port,st_pin,GPIO_PIN_SET)
#define STL                    HAL_GPIO_WritePin(st_port,st_pin,GPIO_PIN_RESET)
#define DISPEN1H     HAL_GPIO_WritePin(disp_en1_port,disp_en1_pin,GPIO_PIN_SET)
#define DISPEN1L   HAL_GPIO_WritePin(disp_en1_port,disp_en1_pin,GPIO_PIN_RESET)
#define DISPEN2H     HAL_GPIO_WritePin(disp_en2_port,disp_en2_pin,GPIO_PIN_SET)
#define DISPEN2L   HAL_GPIO_WritePin(disp_en2_port,disp_en2_pin,GPIO_PIN_RESET)
#define DISPEN3H     HAL_GPIO_WritePin(disp_en3_port,disp_en3_pin,GPIO_PIN_SET)
#define DISPEN3L   HAL_GPIO_WritePin(disp_en3_port,disp_en3_pin,GPIO_PIN_RESET)



extern u8 show_ch;
void hc595_init(void);
void hc595_out(void);
void hc595_show(u8 ch,u16 number);
void hc595_write(u8 temp);

#endif
