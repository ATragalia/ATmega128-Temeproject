#ifndef __Glcd_func__
#define __Glcd_func__

int lcd_loop = 0;
char sec = 0, min = 0, hour = 0, load = 1;
char buf[3];

#include "glcd_128.h"


void func_init(){
    GLCD_Init();
    MCU_Init();
    hour = 8;   
    min = 30;
    sec = 30;
}

void disp()         
{
  sprintf(buf,"%2d",hour);
  if(key6_flag == 1){
    if(led_flag == 0 & time_count == 0){
        Write_Char(12, 0, ' '); Write_Char(13, 0, ' '); Write_Char(14, 0, ':');
    }
    else {
        Write_Char(12, 0, buf[0]); Write_Char(13, 0, buf[1]); Write_Char(14, 0, ':');
        }
  }
  else {
    Write_Char(12, 0, buf[0]); Write_Char(13, 0, buf[1]); Write_Char(14, 0, ':');
  } 
  
  sprintf(buf,"%2d",min);
  
  if(key6_flag == 1){
    if(led_flag == 0 & time_count == 1){
        Write_Char(15, 0, ' '); Write_Char(16, 0, ' '); Write_Char(17, 0, ':');
    }
    else {
        Write_Char(15, 0, buf[0]); Write_Char(16, 0, buf[1]); Write_Char(17, 0, ':');
        }
  }
  else {
    Write_Char(15, 0, buf[0]); Write_Char(16, 0, buf[1]); Write_Char(17, 0, ':');
  }
  
  //Write_Char(15, 0, buf[0]); Write_Char(16, 0, buf[1]); Write_Char(17, 0, ':');
  
  sprintf(buf,"%2d",sec);
  
  if(key6_flag == 1){
    if(led_flag == 0 & time_count == 2){
        Write_Char(18, 0, ' '); Write_Char(19, 0, ' ');
    }
    else {
        Write_Char(18, 0, buf[0]); Write_Char(19, 0, buf[1]);
        }
  }
  else {
    Write_Char(18, 0, buf[0]); Write_Char(19, 0, buf[1]); 
  }
  
  //Write_Char(18, 0, buf[0]); Write_Char(19, 0, buf[1]);
}

void glcd_dis(){
    lcd_loop = 0;
    switch(load)
    {
        case 1:
            if(hour >= 9 & hour <= 18) GLCD_Print_Picture(1);
            if(hour >= 12 & hour <= 14) GLCD_Print_Picture(2);
            else if((hour >= 8 & hour < 9) | (hour >18 & hour <= 20)) GLCD_Print_Picture(3);
            disp();
            Write_String_6x8(10, 1, "Gajang");
            Write_String_6x8(10, 3, "Limit 60Km");
            Write_String_6x8(10, 2, "STREET");
            Write_String_6x8(9, 4, "->Sintanjin");
            Write_String_6x8(10, 5, "^Dongsedae");
            Write_String_6x8(9, 6, "<-Hanbatdae");
        break;
        
        case 2:
            if(hour >= 10 & hour <= 18) GLCD_Print_Picture(1);
            if(hour >= 12 & hour <= 14) GLCD_Print_Picture(2);
            else if((hour >= 7 & hour < 9) | (hour >18 & hour <= 20)) GLCD_Print_Picture(3);
            disp();
            Write_String_6x8(10, 1, "Sintanjin");
            Write_String_6x8(10, 3, "Limit 50Km");
            Write_String_6x8(10, 2, "STREET");
            Write_String_6x8(9, 4, "->Dongsedae");
            Write_String_6x8(10, 5, "^Hanbatdae");
            Write_String_6x8(9, 6, "<-Gajang");
        break;
        
        case 3:
            if(hour >= 9 & hour <= 18) GLCD_Print_Picture(1);
            if(hour >= 11 & hour <= 13) GLCD_Print_Picture(2);
            else if((hour >= 7 & hour < 9) | (hour >18 & hour <= 20)) GLCD_Print_Picture(3);
            disp();
            Write_String_6x8(10, 1, "Dongsedae");
            Write_String_6x8(10, 3, "Limit 80Km");
            Write_String_6x8(10, 2, "STREET");
            Write_String_6x8(9, 4, "->Hanbatdae");
            Write_String_6x8(10, 5, "^Gajang");
            Write_String_6x8(9, 6, "<-Sintanjin");
        break;
        
        case 4:
            if(hour >= 9 & hour <= 18) GLCD_Print_Picture(1);
            if(hour >= 12 & hour <= 14) GLCD_Print_Picture(2);
            else if((hour >= 8 & hour < 9) | (hour >18 & hour <= 20)) GLCD_Print_Picture(3);
            disp();
            Write_String_6x8(10, 1, "Hanbatdae");
            Write_String_6x8(10, 3, "Limit 80Km");
            Write_String_6x8(10, 2, "STREET");
            Write_String_6x8(9, 4, "->Gajang");
            Write_String_6x8(10, 5, "^Sintanjin");
            Write_String_6x8(9, 6, "<-Dongsedae");
        break;
    }                                                 

           
}
#endif 