#include <mega128.h>
#include <delay.h>
#include <io.h>
#include <stdio.h>

int time_loop = 0, led_count = 0, led_flag = 0, time_count = 0;
char key4_flag = 0, key5_flag = 0, key6_flag = 0, key7_flag = 0;

#include "Counter.c"
#include "leddis.c"
#include "uart.c"
#include "fnd.c"
#include "ext_int.c"
#include "Glcd_func.c"

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
  
   time_loop++;
   if(time_loop >= 1000)
    {
        glcd_dis();
        if (key6_flag == 0)sec++;
        led_flag = ~led_flag;
        time_loop = 0; 
        Counter_add();
    }

    
   
  TCNT0 = 18;
}

void main(void)
{
    TCCR0 = 0x03;
    TCNT0 = 128;
    TIMSK = 01;
    EICRB = 0xaa;
    EIMSK = 0xf0;
    DDRD = 0xff;
    DDRE = 0x0f;
    DDRC = 0xff;
    DDRF = 0xff;
    SREG = 0x80;
    PORTA.6 = 1;
    uart0_init();
    Counter_add();
    func_init();


while (1)
      {   

          delay_ms(1);
          lcd_loop++;
          if(cnt1 > 60)fnd_dis((cnt1 - 60), 0x04, 0x08);
          else if(cnt1 > 0)fnd_dis(cnt1, 0x10, 0x20);
          else if(cnt2 > 60)fnd_dis((cnt2 - 60), 0x40, 0x80);
          else fnd_dis(cnt2, 0x01, 02);
          
          if(key4_flag == 1){
            key4_flag = 0;
            if(key6_flag == 1){
                switch(time_count)
                {
                    case 0:
                        hour++;
                        if(hour == 24)hour = 0;
                    break;
                    
                    case 1:
                        min++;
                        if(min == 60)min = 0;
                    break;
                    
                    case 2:
                        sec++;
                        if(sec == 60)sec = 0;
                    break;
                }
            }
            else{
                load++;
                if(load == 5) load = 1;
            }
          }
          
          if(key5_flag == 1){
            key5_flag = 0;
            if(key6_flag == 1){
                switch(time_count)
                {
                    case 0:
                        hour--;
                        if(hour == 24)hour = 0;
                    break;
                    
                    case 1:
                        min--;
                        if(min == 60)min = 0;
                    break;
                    
                    case 2:
                        sec--;
                        if(sec == 60)sec = 0;
                    break;
                }
            }
            else{
            led_count++;
                if(led_count == 4) led_count =0;
                if(led_count == 0){
                    cnt1 = 120;
                    cnt2 = 0;
                    Counter_add();
                }
                if(led_count == 1){
                    cnt1 = 60;
                    cnt2 = 0;
                    Counter_add();
                }
                if(led_count == 2){
                    cnt1 = 0;
                    cnt2 = 120;
                    Counter_add();
                }
                if(led_count == 3){
                    cnt1 = 0;
                    cnt2 = 60;
                    Counter_add();
                }
            }
            
           } 
          
          if(key7_flag == 1){
            key7_flag = 0;
            key6_flag = 0;
          }
                
          if(sec >= 60){
            sec = 0; min++;
            if(min >= 60){
                min = 0; hour++;
                if(hour >= 24) hour = 0;
            }
          }

          

      }
}
