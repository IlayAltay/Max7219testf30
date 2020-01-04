#include "ds18b20.h"
//--------------------------------------------------
__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
{
//micros *= (SystemCoreClock / 1000000) / 9;
micros *= (SystemCoreClock / 1000000)/4;
/* Wait till done */
while (micros--) ;
}
//--------------------------------------------------
void port_init(void)
{
  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

  //GPIOA->CRH |= GPIO_CRH_MODE11;
  GPIOA->OSPEEDR|=GPIO_OSPEEDR_OSPEEDR4_0;
  GPIOA->OSPEEDR |=GPIO_OSPEEDR_OSPEEDR4_1;
  //GPIOA->CRH |= GPIO_CRH_CNF11_0;
  GPIOA->MODER|=GPIO_MODER_MODER4_0;
 // GPIOA->CRH &= ~GPIO_CRH_CNF11_1;
}
//--------------------------------------------------
uint8_t ds18b20_Reset(void)
{
  uint16_t status;
	GPIOA->ODR &= ~GPIO_ODR_4;//������ �������
  DelayMicro(485);//�������� ��� ������� �� 480 �����������
  GPIOA->ODR |= GPIO_ODR_4;//������� �������
  DelayMicro(65);//�������� ��� ������� �� 60 �����������
  status = GPIOA->IDR & GPIO_IDR_4;//��������� �������
  DelayMicro(500);//�������� ��� ������� �� 480 �����������
  //(�� ������ ������ ������� ��������, ��� ��� ����� ���� ���������� � ��������)
  return (status ? 1 : 0);//����� ���������
}
//----------------------------------------------------------
uint8_t ds18b20_ReadBit(void)
{
  uint8_t bit = 0;
  GPIOA->ODR &= ~GPIO_ODR_4;//������ �������
  DelayMicro(2);
	GPIOA->ODR |= GPIO_ODR_4;//������� �������
	DelayMicro(13);
	bit = (GPIOA->IDR & GPIO_IDR_4 ? 1 : 0);//��������� �������
	DelayMicro(45);
  return bit;
}
//-----------------------------------------------
uint8_t ds18b20_ReadByte(void)
{
  uint8_t data = 0;
  for (uint8_t i = 0; i <= 7; i++)
  data += ds18b20_ReadBit() << i;
  return data;
}
//-----------------------------------------------
void ds18b20_WriteBit(uint8_t bit)
{
  GPIOA->ODR &= ~GPIO_ODR_4;
  DelayMicro(bit ? 3 : 65);
  GPIOA->ODR |= GPIO_ODR_4;
  DelayMicro(bit ? 65 : 3);
}
//-----------------------------------------------
void ds18b20_WriteByte(uint8_t dt)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    ds18b20_WriteBit(dt >> i & 1);
    //Delay Protection
    DelayMicro(5);
  }
}
//-----------------------------------------------
uint8_t ds18b20_init(uint8_t mode)
{
	if(ds18b20_Reset()) return 1;
  if(mode==SKIP_ROM)
  {
		//SKIP ROM
		ds18b20_WriteByte(0xCC);
		//WRITE SCRATCHPAD
		ds18b20_WriteByte(0x4E);
		//TH REGISTER 100 ��������
		ds18b20_WriteByte(0x64);
		//TL REGISTER - 30 ��������
		ds18b20_WriteByte(0x9E);
		//Resolution 12 bit
		ds18b20_WriteByte(RESOLUTION_12BIT);
  }
  return 0;
}
//----------------------------------------------------------
void ds18b20_MeasureTemperCmd(uint8_t mode, uint8_t DevNum)
{
  ds18b20_Reset();
  if(mode==SKIP_ROM)
  {
    //SKIP ROM
    ds18b20_WriteByte(0xCC);
  }
  //CONVERT T
  ds18b20_WriteByte(0x44);
}
//----------------------------------------------------------
void ds18b20_ReadStratcpad(uint8_t mode, uint8_t *Data, uint8_t DevNum)
{
  uint8_t i;
  ds18b20_Reset();
  if(mode==SKIP_ROM)
  {
    //SKIP ROM
    ds18b20_WriteByte(0xCC);
  }
  //READ SCRATCHPAD
  ds18b20_WriteByte(0xBE);
  for(i=0;i<8;i++)
  {
    Data[i] = ds18b20_ReadByte();
  }
}
//----------------------------------------------------------
uint8_t ds18b20_GetSign(uint16_t dt)
{
  //�������� 11-� ���
  if (dt&(1<<11)) return 1;
  else return 0;
}
//----------------------------------------------------------
//myconvert
float ds18b20_Convert(uint16_t dt)
{
	 float t;
	 if (dt & 0x8000) {
	 	dt = ~dt + 1;
	         t = 0.0 - (dt / 16.0);
	         return t;
	    }
	     t = dt / 16.0;





	//t = (float) ((dt&0x07FF)>>4); //��������� �������� � ������� ����
	//  �������� ������� �����
	//  t += (float)(dt&0x000F) / 16.0f;
	  return t;




}
//------------------------------------------------------------
//float ds18b20_Convert(uint16_t dt)
//{
 // float t;
 // t = (float) ((dt&0x07FF)>>4); //��������� �������� � ������� ����
  //�������� ������� �����
 // t += (float)(dt&0x000F) / 16.0f;
  //return t;
//}
//----------------------------------------------------------
