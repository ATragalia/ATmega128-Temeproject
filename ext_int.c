

#ifndef _ext_int_
#define _ext_int_


#define G_INT_ON  #asm("sei")
#define G_INT_OFF #asm("cli")
//#define g_on  SREG = 0x80

#define key8  PINE.4
#define INT4_ON   bit_set(EIMSK, 4)
#define INT4_OFF  bit_clr(EIMSK, 4)
#define bit_set(ADDRESS, BIT) (ADDRESS |= (1<<BIT)) // bit hi 
#define bit_clr(ADDRESS, BIT) (ADDRESS &= ~(1<<BIT)) // bit low
#define bit_chk(ADDRESS, BIT) (ADDRESS & (1<<BIT))  // bit chak

#include "Counter.c"          

interrupt [EXT_INT4] void ext_int4_isr(void)
{
  INT4_OFF;
  if(key8 == 0) // if((PINE & 0x10) != 0x10) 
   {
     delay_ms(5);
     if(key8 == 0) // if((PINE & 0x10) != 0x10) 
      {
        delay_ms(2);
        if(key8 == 0) // if((PINE & 0x10) != 0x10) 
        {
          // key in ok
          key4_flag = 1;
        }
      } 
   }
  INT4_ON;
}


interrupt [EXT_INT5] void ext_int5_isr(void)
{
   bit_clr(EIMSK, 5);
  if(PINE.5 == 0) // if((PINE & 0x10) != 0x10) 
   {
     delay_ms(5);
     if(PINE.5 == 0) // if((PINE & 0x10) != 0x10) 
      {
        delay_ms(2);
        if(PINE.5 == 0) // if((PINE & 0x10) != 0x10) 
        {
          // key in ok
          key5_flag = 1;
        }
      } 
   }
  bit_set(EIMSK, 5);
  //printf("4");
}


interrupt [EXT_INT6] void ext_int6_isr(void)
{
   bit_clr(EIMSK, 6);
  if(PINE.6 == 0) // if((PINE & 0x10) != 0x10) 
   {
     delay_ms(5);
     if(PINE.6 == 0) // if((PINE & 0x10) != 0x10) 
      {
        delay_ms(2);
        if(PINE.6 == 0) // if((PINE & 0x10) != 0x10) 
        {
          // key in ok
          key6_flag = 1;
          time_count++;
          if(time_count == 3)time_count = 0;
        }
      } 
   }
  bit_set(EIMSK, 6);
}


interrupt [EXT_INT7] void ext_int7_isr(void)
{
    bit_clr(EIMSK, 7);
  if(PINE.7 == 0) // if((PINE & 0x10) != 0x10) 
   {
     delay_ms(5);
     if(PINE.7 == 0) // if((PINE & 0x10) != 0x10) 
      {
        delay_ms(2);
        if(PINE.7 == 0) // if((PINE & 0x10) != 0x10) 
        {
          // key in ok
          key7_flag = 1;
        }
      } 
   }
  bit_set(EIMSK, 7);
}



#endif
