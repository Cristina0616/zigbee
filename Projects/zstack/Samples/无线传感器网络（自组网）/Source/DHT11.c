//---------------��ʪ�ȴ����� DHT11----------------//
/*                  Creat By ES                       */
/*           http://es-tech.taobao.com          */
/******************************************************
ʵ�����ݣ�
1.������ʪ�ȴ��������¶Ⱥ�ʪ�����ݲ���ʾ��Һ���ϡ�

ע�⣺
DHT11��Vcc��������CC2530ģ���VCC��GND����CC2530ģ���GND������
��������CC2530ģ���P00���š�

******************************************************/

#include <ioCC2530.h>
//#include "JLX12864.h" 
#include "DHT11.h" 







void halMcuWaitUs(unsigned short usec)
{
    usec>>= 1;
    while(usec--)
    {
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
    }
}

//��ʪ�ȶ���
U8 U8FLAG,U8temp;
U8 ShiDu_H,ShiDu_L;//����ʪ�ȴ�ű���
U8 WenDu,ShiDu;//�����¶ȴ�ű���
U8 U8T_data_H,U8T_data_L,U8RH_data_H,U8RH_data_L,U8checkdata;
U8 U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
U8 U8comdata;







/****************************
//��ʱ����
*****************************/
void Delay_us(void) //1 us��ʱ

{
    halMcuWaitUs(1);   
}

void Delay_10us(void) //10 us��ʱ
{
   halMcuWaitUs(10);
}

void Delay_ms(uint Time)//n ms��ʱ
{
  unsigned char i;
  while(Time--)
  {
    for(i=0;i<100;i++)
     Delay_10us();
  }
}


/***********************
   ��ʪ�ȴ���
***********************/
void COM(void)	// ��ʪд��
{     
    U8 i;         
    for(i=0;i<8;i++)    
    {
     U8FLAG=2; 
     DATA_PIN=0;
     DATA_PIN=1;
     while((!DATA_PIN)&&U8FLAG++);
     Delay_10us();
     Delay_10us();
     Delay_10us();
     U8temp=0;
     if(DATA_PIN)U8temp=1;
     U8FLAG=2;
     while((DATA_PIN)&&U8FLAG++);   
     if(U8FLAG==1)break;    
     U8comdata<<=1;
     U8comdata|=U8temp; 
     }    
}

//-------------------------------- ����
//-----ʪ�ȶ�ȡ�ӳ��� ------------ ����
//-------------------------------- ����
//----���±�����Ϊȫ�ֱ���-------- ����
//----�¶ȸ�8λ== U8T_data_H------ ����
//----�¶ȵ�8λ== U8T_data_L------ ����
//----ʪ�ȸ�8λ== U8RH_data_H----- ����
//----ʪ�ȵ�8λ== U8RH_data_L----- ����
//----У�� 8λ == U8checkdata----- ����
//----��������ӳ�������---------- ����
//---- Delay();, Delay_10us();COM(); ����
//-------------------------------- 

unsigned char * DHT11(void)   //��ʪ��������
{ 
    unsigned char *data2;
    data2 = 0;
    DATA_PIN=0;
    Delay_ms(19);  //��������18ms
    DATA_PIN=1;     //������������������ ������ʱ40us 
    P0DIR &= ~0x01; //��������IO�ڷ���
    Delay_10us();
    Delay_10us();						
    Delay_10us();
    Delay_10us();  
    //�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ���������� 
     if(!DATA_PIN) 
     {
      U8FLAG=2; //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ���� 
      while((!DATA_PIN)&&U8FLAG++);
      U8FLAG=2;//�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
      while((DATA_PIN)&&U8FLAG++); 
      COM();//���ݽ���״̬ 
      U8RH_data_H_temp=U8comdata;
      COM();
      U8RH_data_L_temp=U8comdata;
      COM();
      U8T_data_H_temp=U8comdata;
      COM();
      U8T_data_L_temp=U8comdata;
      COM();
      U8checkdata_temp=U8comdata;
      DATA_PIN=1; 
      //����У�� 
      U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
       if(U8temp==U8checkdata_temp)
      {
          U8RH_data_H=U8RH_data_H_temp;
          U8RH_data_L=U8RH_data_L_temp;
          U8T_data_H=U8T_data_H_temp;
          U8T_data_L=U8T_data_L_temp;
          U8checkdata=U8checkdata_temp;
       }
       WenDu=U8T_data_H;
       ShiDu=U8RH_data_H;
    } 
    else 
    {  
      WenDu=0;
      ShiDu=0;
    } 
    P0DIR |= 0x01;
    
 //   *data2 = WenDu;
   *data2 = ShiDu;
//   *(data2+2) = U8T_data_L;
 //   data[3] = 0;
    return data2;
}


