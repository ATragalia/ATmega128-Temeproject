#ifndef __GLCD_HEADER__
#define __GLCD_HEADER__

#define   E PORTA.2
#define  RW PORTA.1
#define  RS PORTA.0
#define CS2 PORTA.4
#define CS1 PORTA.3

#define HIGH 1
#define  LOW 0

#include "glcd_font.h"
#include "glcd_Image.h"



void MCU_Init(void);
void GLCD_Init(void);
void E_Pulse(void);
void GLCD_Print_Picture(unsigned char Picture_Select);
void lcd_clear(void);
void Write_Data(unsigned char Write_Data);
void lcd_gotox(unsigned char lcd_gotox);
void lcd_gotopage(unsigned char Page);
void lcd_gotoxy(unsigned char x, unsigned char y);
void Write_String_6x8(unsigned char x, unsigned char y, flash char *string);
void Write_Char(unsigned char x, unsigned char y, unsigned char Byte);

void GLCD_Print_Picture(unsigned char Picture_Select)			/* draw a GLCD screen */
{
  unsigned char x = 0, y = 0;
  unsigned int Count = 0;

  CS1 = HIGH; CS2 = LOW;

  for(x = 0; x <= 63; x++)
  {
        for(y = 0; y <= 7; y++)
        {
         lcd_gotoxy(x, 7 - y);

            if(Picture_Select == 1) {Write_Data(screen1[Count]);}
       else if(Picture_Select == 2) {Write_Data(screen2[Count]);}
       else if(Picture_Select == 3) {Write_Data(screen3[Count]);}
       //else if(Picture_Select == 4) {Write_Data(screen4[Count]);}
      // else if(Picture_Select == 5) {Write_Data(screen5[Count]);}
         Count++;
        }
  }

  CS1 = LOW; CS2 = HIGH;

  for(x = 0; x <= 63; x++)
  {
        for(y = 0; y <= 7; y++)
        {
         lcd_gotoxy(x, 7 - y);

            if(Picture_Select == 1) {Write_Data(screen1[Count]);}
       else if(Picture_Select == 2) {Write_Data(screen2[Count]);}
       else if(Picture_Select == 3) {Write_Data(screen3[Count]);}
      // else if(Picture_Select == 4) {Write_Data(screen4[Count]);}
      // else if(Picture_Select == 5) {Write_Data(screen5[Count]);}
         Count++;
        }
  }


}
void Write_String_6x8(unsigned char x, unsigned char y, flash char *string)
{
 CS1 = HIGH; CS2 = LOW;

 while(*string != '\0')
     { Write_Char(x, y, *string);
       string++;
       x++;
     }
}
void Write_Char(unsigned char x, unsigned char y, unsigned char Byte) // x = 0 ~ 19, y = 0 ~ 7
{
 unsigned char i;

   if(x > 9) {CS1 = LOW; CS2 = HIGH;}
 else        {CS1 = HIGH; CS2 = LOW;}

 for(i = 4; i < 9; i++)
  {
   lcd_gotoxy(i + (x * 6) , y);

   Write_Data(font[Byte-0x20][i-4]);
  }
}
void lcd_clear(void)
{
 unsigned char x,y;

 CS1 = HIGH; CS2 = HIGH;

 for(y = 0; y < 8; y++)
 {
  for(x = 0; x < 64; x++)
  {
   lcd_gotoxy(x, y);

   Write_Data(0x00);
  }
 }
}
void lcd_gotox(unsigned char lcd_gotox)
{
 RS = LOW;
 RW = LOW;
 PORTB = 0x40 | lcd_gotox;
 E_Pulse();
}
void lcd_gotopage(unsigned char Page)
{
 RS = LOW;
 RW = LOW;
 PORTB = 0b10111000 | Page;
 E_Pulse();
}
void lcd_gotoxy(unsigned char x, unsigned char y)
{
 lcd_gotox(x);
 lcd_gotopage(y);
}
void Write_Data(unsigned char Write_Data)
{
 RS = 1;
 RW = 0;
 PORTB = Write_Data;
 E_Pulse();
}
void GLCD_Init(void)
{
 RW = LOW;
 RS = LOW;
 PORTB = 0b00111111;
 E_Pulse();
}
void E_Pulse(void)
{
 E = HIGH;
 E = LOW;
}
void MCU_Init(void)
{
 DDRB = 0xFF;
 DDRA = 0xFF;

 CS1 = HIGH;

}
#endif
