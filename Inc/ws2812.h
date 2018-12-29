/*
 * ws2812.h
 *
 *  Created on: 2018Äê10ÔÂ7ÈÕ
 *      Author: az199
 */

#ifndef INC_WS2812_H_
#define INC_WS2812_H_
#include "spi.h"
#include "gpio.h"
#include "dma.h"
#include "stm32f0xx_hal.h"

#define  BLUE          0x00FF0000
#define  GREEN         0x0000FF00
#define  RED           0x000000FF
#define  CYAN          0x00FFFF00
#define  MAGENTA       0x00FF00FF
#define  YELLOW        0x0000FFFF
#define  LIGHTBLUE     0x00FF8080
#define  LIGHTGREEN    0x0080FF80
#define  LIGHTRED      0x008080FF
#define  LIGHTCYAN     0x00FFFF80
#define  LIGHTMAGENTA  0x00FF80FF
#define  LIGHTYELLOW   0x0080FFFF
#define  DARKBLUE      0x00800000
#define  DARKGREEN     0x00008000
#define  DARKRED       0x00000080
#define  DARKCYAN      0x00808000
#define  DARKMAGENTA   0x00800080
#define  DARKYELLOW    0x00008080
#define  WHITE         0x00FFFFFF
#define  LIGHTGRAY     0x00D3D3D3
#define  GRAY          0x00808080
#define  DARKGRAY      0x00404040
#define  BLACK         0x00000000
#define  BROWN         0x002A2AA5
#define  ORANGE        0x0000A5FF

typedef struct{
	uint8_t MainLight;
	uint8_t LEFT;
	uint8_t Right;
	uint8_t BrakeLight;
	
}_LightStatus;

void SetLightRGB(uint8_t Red,uint8_t Green,uint8_t Blue,uint8_t Index);
void SetAllLightRGB(uint8_t Red,uint8_t Green,uint8_t Blue);
void SetAllLightColor(uint32_t Color);
void SetLightColor(uint32_t Color,uint8_t Index);
void LightUpdate();
void LightInit();
void SmartLight();
extern uint32_t ColorTable[16];
extern _LightStatus LightStatus;
#endif /* INC_WS2812_H_ */
