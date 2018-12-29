/*
 * ws2812.c
 *
 *  Created on: 2018Äê10ÔÂ7ÈÕ
 *      Author: az199
 */
#include "ws2812.h"
#define NUMOFLED 32

#define TYPEA

uint32_t ColorTable[16] = {BLUE,GREEN,RED,CYAN,MAGENTA,YELLOW,LIGHTBLUE,LIGHTGREEN,\
												LIGHTRED,LIGHTCYAN,LIGHTMAGENTA,LIGHTYELLOW,LIGHTGRAY,BROWN,\
												ORANGE,WHITE};

uint8_t const BitToByteTable[2] = {0x70,0x7c};

typedef struct{
	uint8_t Init[40];
	uint8_t Data[NUMOFLED*24];
	//uint8_t End[10];
	
}_WS2812Buff;
_WS2812Buff WS2812Buff = {0};


//RGB & The index of light 
void SetLightRGB(uint8_t Red,uint8_t Green,uint8_t Blue,uint8_t Index)
{
	if(Index >= NUMOFLED)
		return;
	
//	Red >>=3;
//	Green >>=3;
//	Blue >>=3;
	#ifdef TYPEA
	uint8_t * pRedBaseIndex   =  WS2812Buff.Data+Index*24;
	uint8_t * pGreenBaseIndex =  WS2812Buff.Data+Index*24+8;
	uint8_t * pBlueBaseIndex  =  WS2812Buff.Data+Index*24+16;
	#else
	uint8_t * pRedBaseIndex   =  WS2812Buff.Data+Index*24+8;
	uint8_t * pGreenBaseIndex =  WS2812Buff.Data+Index*24;
	uint8_t * pBlueBaseIndex  =  WS2812Buff.Data+Index*24+16;
	#endif
	
	uint8_t i = 7;
	while(1)
	{
		*(pRedBaseIndex+i) = BitToByteTable[(Red%2)];
		*(pGreenBaseIndex+i) = BitToByteTable[(Green%2)];
		*(pBlueBaseIndex+i) = BitToByteTable[(Blue%2)];
		
		Red   >>= 1;
		Green >>= 1;
		Blue  >>= 1;
		if(i == 0)break;
		i--;
		
	}
}

//COLOR & The index of light 
void SetLightColor(uint32_t Color,uint8_t Index)
{
	SetLightRGB(Color,Color>>8,Color>>16,Index);
}


void SetAllLightRGB(uint8_t Red,uint8_t Green,uint8_t Blue)
{
	for(uint8_t i = 0; i < NUMOFLED ;i++)
	{
		SetLightRGB(Red,Green,Blue,i);
	}
}


void SetAllLightColor(uint32_t Color)
{
	for(uint8_t i = 0; i < NUMOFLED ;i++)
	{
		SetLightColor(Color,i);
	}
}


void LightUpdate()
{
	uint8_t *pSend = (uint8_t *)&WS2812Buff;
	//HAL_SPI_Transmit(&hspi1,pSend,NUMOFLED * 24 +20,1000);
	HAL_SPI_Transmit_DMA(&hspi1,pSend,NUMOFLED * 24 +40);
}

SPI_HandleTypeDef hspi4;
DMA_HandleTypeDef hdma_spi4_tx;

void LightInit()
{
	
	SetAllLightRGB(0,0,0);
	LightUpdate();
}

_LightStatus LightStatus  = {1,1,1,1};
void SmartLight()
{
	
		uint8_t i = 0;
	  static uint8_t ToggleFlag = 1,ToggleCNT = 0;
		for(i = 0; i < 4 ; i++)
		{
			SetLightColor((LightStatus.MainLight)?WHITE:BLACK,i);
			SetLightColor((LightStatus.LEFT && ToggleFlag)?YELLOW:BLACK,i+4);
			SetLightColor((LightStatus.LEFT && ToggleFlag)?YELLOW:BLACK,i+8);
			SetLightColor((LightStatus.BrakeLight)?RED:BLACK,i+12);
			SetLightColor((LightStatus.BrakeLight)?RED:BLACK,i+16);
			SetLightColor((LightStatus.Right && ToggleFlag)?YELLOW:BLACK,i+20);
			SetLightColor((LightStatus.Right && ToggleFlag)?YELLOW:BLACK,i+24);
			SetLightColor((LightStatus.MainLight)?WHITE:BLACK,i+28);
		}
		if(LightStatus.Right || LightStatus.LEFT)
		{
			if(ToggleCNT%8 == 0)
			{	
				ToggleFlag = !ToggleFlag;
			}
			ToggleCNT++;
		}else
		{
			ToggleFlag = 1;
			ToggleCNT  = 0;
		}
}