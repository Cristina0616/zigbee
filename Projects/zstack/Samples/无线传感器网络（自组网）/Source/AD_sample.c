

#include "DS18B20.h"




unsigned int  M_wendu=0;
float temperture=0;



/**************************
��ȡ�¶Ⱥ���
**************************/ 
void IO_initial()
{ 
  P0DIR |= 0xff;     //P0 Ϊ���
  P1DIR |= 0xff;     //P1 Ϊ���  
//  P1SEL &= 0xfd;
  /*
  P1=0x0f;
  
  
  P1IEN |= 0X02;  // P11 ����Ϊ�жϷ�ʽ 
  PICTL &=~ 0X02; // �½��ش���   
  IEN2 |= 0Xff;   // ����P1���ж�;
  P1   |= 0X0f;
  P1IFG = 0x00;   // ��ʼ���жϱ�־λ
  EA = 1; 
 */
  
}

void int_init(void)
{
   
  P0IEN |= 0X15;   
  PICTL &=~ 0X01; 
  IEN1 |= 0X20;   
 // P1   |= 0X0f;
  P0IFG = 0x00;   
  EA = 1; 
}


unsigned int read_data1(unsigned char *buffer )
{
  unsigned char temh,teml; 
  unsigned int wendu;
  
  init_1820();  //��λ18b20  
//  Match_DS18B20(temp) ; // 
  write_1820(0xcc); 
  write_1820(0x44); 
  Delay_nus(50000);
  init_1820();  
  write_1820(0xcc);  
  write_1820(0xbe); 
       
  teml=read_1820();  //������  
  temh=read_1820();
  wendu=temh*256+teml;
  return(wendu);   //�����¶�����
}
unsigned int read_data0(unsigned char *buffer )
{
  unsigned char temh,teml; 
  unsigned int wendu;
  
  init0_1820();  //��λ18b20  
//  Match_DS18B20(temp) ; // 
  write0_1820(0xcc); 
  write0_1820(0x44); 
  Delay_nus(50000);
  init0_1820();  
  write0_1820(0xcc);  
  write0_1820(0xbe); 
       
  teml=read0_1820();  //������  
  temh=read0_1820();
  wendu=temh*256+teml;
  return(wendu);   //�����¶�����
}

void Delayms(unsigned int xms)   //i=xms ����ʱi����
{
 unsigned int i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

#pragma vector = P1INT_VECTOR    //��ʽ��#pragma vector = �ж����������������жϴ������
  __interrupt void P1_ISR(void) 
 { 
 // Delayms(10);            //ȥ������
  Yellow_LED=~Yellow_LED;    //�ı�LED1״̬
  Delayms(10);  
  if(SoundSensor){
 //   SoundSensor = 0;
    sound = 1;
  }
  if(VibrationSensor){
 //   VibrationSensor = 0;
    vibrat = 1;
  }
  if(InfraredSensor){
    infra = 1;
    }
  P0IFG = 0;             //���жϱ�־ 
  P0IF = 0;              //���жϱ�־ 
  Delayms(10); 
 } 