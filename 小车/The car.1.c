#include<reg52.h>
#include<intrins.h>
#define	char  unsigned char 
#define int unsigned int 
sbit ENA=P1^2;//���ʹ�ܶ� 
sbit ENB=P1^3;//���ʹ�ܶ�
sbit IN1=P1^7;//ǰ�� ���� ���
sbit IN2=P1^6;// ǰ�� ���� ���
sbit IN3=P1^5;//��ת ��ת ���
sbit IN4=P1^4;//��ת  ��ת ���
sbit IN5=P1^0;//��̨ ��ת ��ת ���
sbit IN6=P1^1;//��̨��ת ��ת ���
sbit trig=P2^0;//������ģ��������
sbit echo=P0^1;//������ģ�����ݽ��ն�
void L298_init();//����оƬ��ʼ�� 
void motion_init();//�˶���ʼ�� 
void forword();//ǰ������ 
void backoff();//���˺��� 
void right();//��ת���� 
void left();//��ת���� 
void stop();//ֹͣǰ�� ����  ���� 
void direction_stop();//ֹͣ ��ת ��ת���� 
void ptz_left();//��̨��ת 
void ptz_right();//��̨��ת 
void ptz_judge();//��̨ת���ж� �Լ��˶���ʽ�ж� 
void trig_start();//������ģ�鿪ʼ���� �ź� 
void HC_SR04_init();//������ģ���ʼ�� 
void ptz_init();//��̨ת���ʼ�� 
void echo_handle();//������ģ�����ݴ��� 

int n=0;//������ģ�����ݴ������ 
//////////��ʱ����  ��λ ����
void daley_ms(int i)         //��ʱ����  ��λ ����
{
 char x,y;
 for(x=0;x<i;x++)
  for(y=1000;y>0;y--);
}
void daley_us(char i)         // ��ʱ���� ��λ ΢��
{  char x;
  for(x=0;x<=i;x++);
}
void L298_init()           // L298����оƬ��ʼ������ �����ʹ�� 
{
	ENA=1;
	ENB=1;		
}
void motion_init()//С��ǰ�����˳�ʼ��
{
IN1=1;
IN2=1;
} 
void forword()//С��ǰ������
{
 IN1=0;
 IN2=1;
}
void backoff()//С�����˺��� 
{
 IN1=1;
 IN2=0;
}
void right()//С����ת���� 
{
IN3=0; 
IN4=1;
}
void left()//С����ת����
{
IN3=1; 
IN4=0;

} 
void stop()//С��ֹͣǰ��  ���˶���
{
 IN1=1;
 IN2=1;
}
void direction_stop()//С��ת����ֹͣ ��  ת������ʼ�� 
{
IN3=1; 
IN4=1;
}
void ptz_right()//��̨��ת����
{
  IN5=0;
  IN6=1;
} 
void ptz_left()//��̨��ת����
{
  IN5=1;
  IN6=0;
}
void ptz_init()
{
  IN5=1;
  IN6=1;
} 
void trig_start()//������ģ�鿪ʼ���� �ź�
{

	trig=1;
	daley_us(15);
	trig=0; 

}
void HC_SR04_init()//������ģ���ʼ��
{
  trig=0;
  echo=1;
}
void echo_handle()//������ģ�����ݴ���
{  
   while(!echo);
   while(echo)
   {
			n++;
   }
}
void  ptz_judge()//��̨ת���жϺ��� �Լ�ת�� ֹͣ 
{ 
	while(echo);
  if(n<573)
  { 
		n=0;
   ptz_left();
   trig_start();
   echo_handle();
   while(echo);
   if(n<278)//����� ���ϰ����� �� 
    {  n=0;
       ptz_right();
       trig_start();
       echo_handle();
	   while(echo);
       if(n<278)//����Ҳ��ϰ��� �� �����ϰ��������ת ��ʱ1000ms 
       { 
       n=0;
       backoff();
       left(); 
       daley_ms(1000);
       forword();
       ptz_init();
       direction_stop();
       }
       else//�Ҳ����ϰ�ʱ ����ת ǰ�� ��ʱ1000ms 
	   { n=0;
	   	forword();
	   	right();
	   	daley_ms(1000);
	   	ptz_init();
	   	direction_stop();
	   }
   	} 
	  else//������ϰ��� �� 
      { 
	  n=0;
	   forword();//	ǰ�� 
	   left();//��ת 
	   daley_ms(1000);//��ʱ 
	   ptz_init();//��̨�ָ�����ʼλ�� 
	   direction_stop();//ת��ֹͣ    
	  } 	  	  
   }
   forword();
   direction_stop();
   ptz_init();

} 
void main()
{
 HC_SR04_init();//������ģ���ʼ�� 
 L298_init();//����ģ���ʼ�� 
 motion_init();//ǰ�� ����  ��ʼ��
 direction_stop();//ת���ʼ�� �� ת���ʼ�� 
 ptz_init();//��̨ת���ʼ��
 while(1)
 {
 forword();//ǰ������������
 trig_start();//��ʼ���
 echo_handle();//���������ݴ��� 
 ptz_judge();//��̨ת���� �Լ�  ���˶���ʽ���� 
 }  
}