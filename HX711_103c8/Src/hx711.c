#include "hx711.h"
#include "delay.h"

uint32_t HX711_Buffer;
uint32_t Weight_Maopi;
int32_t Weight_Shiwu;
uint8_t Flag_Error = 0;

//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
#define GapValue 100.5//374.4 //1//813//40.5//



//****************************************************
//��ȡHX711
//****************************************************
uint32_t HX711_Read(void)	//����128
{
	uint32_t ulcount; 
	unsigned char i; 
	delay_us(1);
	HX711_SCK(0); 
	ulcount=0; 
	while(HX711_DOUT);
	for(i=0;i<24;i++)
	{ 
		HX711_SCK(1); 
		ulcount=ulcount<<1; 
		delay_us(1);
		HX711_SCK(0); 
		if(HX711_DOUT)
		ulcount++; 
		delay_us(1);
	} 
//	printf("count:%d\n",ulcount);
	HX711_SCK(1); 
	ulcount=ulcount^0x800000;//��25�������½�����ʱ��ת������
	delay_us(1);
	HX711_SCK(0);
	return(ulcount);
}

//****************************************************
//��ȡëƤ����
//****************************************************
void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read();	
} 

//****************************************************
//����
//****************************************************
void Get_Weight(void)
{
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				//��ȡʵ���AD������ֵ��
	
		Weight_Shiwu = (int32_t)((double)Weight_Shiwu/GapValue); 	//����ʵ���ʵ������
																		//��Ϊ��ͬ�Ĵ������������߲�һ������ˣ�ÿһ����������Ҫ���������GapValue���������
																		//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
																		//������Գ���������ƫСʱ����С����ֵ��
	}
	if(Weight_Shiwu < 0)
	{
		Weight_Shiwu = 0;
	}

	
}
