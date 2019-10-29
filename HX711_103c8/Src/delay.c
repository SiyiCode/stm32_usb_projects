#include "delay.h"

static	uint32_t	fac_us = 0;

void	delay_init(uint8_t	Systick)
{
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	fac_us = Systick;
}

void	delay_us(uint32_t	nus)
{
	uint32_t	ticks;
	uint32_t	tOld,tNow,tCnt = 0;
	uint32_t	reload = SysTick->LOAD;
	ticks	= nus*fac_us;
	tOld	= SysTick->VAL;
	while(1)
	{
		tNow = SysTick->VAL;
		
		if(tNow != tOld)
		{	    
			if(tNow < tOld)
			{
				tCnt += tOld - tNow;	//SYSTICK��һ���ݼ��ļ�����.
			}
			else
			{
				tCnt += reload - tNow + tOld;	 
			}
			tOld = tNow;
			if(tCnt >= ticks)
				break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}
}

void	delay_ms(uint16_t	nms)
{
	uint32_t	i;
	for(i = 0; i < nms; i++)
	{
		delay_us(1000);
	}
}


