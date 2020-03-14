


/* 
=============================================
prj name : car ÃßÂ÷Àå Á¶¸í Á¦¾î  ½Ã½ºÅÛ
  program : ¼Û¸í±Ô
  
  job day : 2008, 06, 16
  
  file name : car_dis.h
================================================
*/  
  
    
#ifndef _CAR_DIS_
#define _CAR_DIS_       
                  

 // CAR USER ¿ë ÆùÆ®    
flash unsigned char time_font[] = "¯¡ˆe";    // ½Ã°£  
flash unsigned char set_font[]  = " ¬é¸÷";    // ¼³Á¤ 
flash unsigned char stop_font[] = "¸÷»¡ ";  // Á¤Áö 
flash unsigned char run_font[]  = "ˆñÂ‰ ";  // °ËÃâ    
flash unsigned char senser_font[] = "­E¬á "; // ¼¾¼­ 

  
// g lcd display                  
void logo(void)
{  
  char j,h=1;
   for(j = 0; j <= 2; j++)
    {
     font_ke_wr(1,1,0,"µAá»¡ ¸é´¢Ñw");  // ¿¡³ÊÁö Àý¾àÇü
     font_ke_wr(2,3,h,"ES-Ver-02");     // 2009, 02, 13 ¼öÁ¤
     h = (~(h));
     delay_ms(1000);
     all_clr();
     delay_ms(1000);
    }
}  

void logo1(void)
{     
   all_clr();
   font_ke_wr(1,1,0,"µAá»¡ ¸é´¢Ñw");  // ¿¡³ÊÁö Àý¾àÇü
   font_ke_wr(2,3,1,"ES-Ver-02");     // 2009, 02, 13 ¼öÁ¤
}
 
void lamp_out(char ch, char con)
{
  // lamp output control func
  switch(ch)
   {
    case 1: out_ch1 = con; break;
    case 2: out_ch2 = con; break;
    case 3: out_ch3 = con; break;
    case 4: out_ch4 = con; break;    
   } 
}
   
void key_bz(uchar loop)
{
  // key input bz output
  bz_on;
  exio_out(exio_buf);
  delay_ms(loop);
  
  bz_off;
  exio_out(exio_buf);
}
                  
void digi_dis(char x, char tg, unsigned char font)
{      
 uchar buf;
 
 //if(pass_dis_flag == 1) tg = 0;
 
 glcd_xy(3, x);     
 efont_8x16_wr(tg, font | 0x30); 
}

void sub_menu(char am_pm, unsigned char buf, char time_env) 
{ 
  unsigned char smg; char x;
   
  // setting mode display x point set   
  if((cur_flag == 0) && (set_flag == 1))
   { 
     if((set_mode_cnt == 1) || (set_mode_cnt == 2) || (sub_set_mode_cnt == 29)) cur_x = 12;
     else if(sub_set_mode_cnt == 32) cur_x = 11;  // year
     else  cur_x = 10; 
   }  
            
  cur_flag = 1;
  
  // Àü»óÅÂ          
  if(sub_set_mode_cnt == 50) x = 3; //// am /pm ¸¦ 4 Line ¿¡ Ç¥½ÃÇÏ±â À§ÇØ¼­ 
  else x = 2;                       
  if(am_pm == 0) font_ke_wr(x,7,0,"µ¡¸å"); // ¿ÀÀü 
  else if(am_pm == 1) font_ke_wr(x,7,0,"µ¡Ò"); // ¿ÀÈÄ  
                                  
  if(sub_set_mode_cnt == 50) sub_set_mode_cnt = 29;  // am /pm ¸¦ 4 Line ¿¡ Ç¥½ÃÇÏ±â À§ÇØ¼­ 
  
    if((set_mode_cnt == 4) || (sub_set_mode_cnt >= 30)) x = 10;
    else x = 12;
    if(sub_set_mode_cnt == 32) x = 11;  //2008³â Ç¥½Ã¶«
    
    glcd_xy(2, x);  
    
    smg = (buf & 0xf0);
    smg >>= 4;      
    efont_8x16_wr(0, smg | 0x30);  // ½ÊÀÚ¸® Ç¥½Ã
    
    smg = (buf & 0x0f);
    efont_8x16_wr(0, smg | 0x30);  // ÀÏÀÚ¸®Ç¥½Ã 
    
    if((set_mode_cnt == 4) || (sub_set_mode_cnt >= 30)) x = 13;  // ¶óÀÎº° ¼³Á¤ 
    else x = 14;
                       
    switch(time_env)
     {
       case time_hour: font_ke_wr(2,x,0,"¯¡");   break;  // ½Ã  
       case time_min:  font_ke_wr(2,x,0,"¦…");  break;  // ºÐ 
       case time_sec:  font_ke_wr(2,x,0,"Á¡");  break;  // ÃÊ
       case time_year: font_ke_wr(2,x,0,"‘e");  break;  // ³â
       case time_mon:  font_ke_wr(2,x,0,"¶©");  break;  // ¿ù    
       case time_date: font_ke_wr(2,x,9,"·©");  break;  // ÀÏ
     }
           
    // ¼³Á¤Ä¡   
    if((sub_set_mode_cnt == 32) || (sub_set_mode_cnt == 29)) xy_x_clr(3,11,13);
    else xy_x_clr(3,10,13);  
    
   ///////// if(sub_set_mode_cnt == 32) font_ke_wr(2,9,0,"20");
         
    if(sub_set_mode_cnt != 29) // am /pm ¸¦ 4 Line ¿¡ Ç¥½ÃÇÏ±â À§ÇØ¼­ 
     {
      if(am_pm == 0) font_ke_wr(3,7,0,"µ¡¸å"); // ¿ÀÀü 
      else if(am_pm == 1) font_ke_wr(3,7,0,"µ¡Ò"); // ¿ÀÈÄ  
     }
     
    switch(time_env)
     {
       case time_hour: font_ke_wr(3,x,0,"¯¡");   break;  // ½Ã  
       case time_min:  font_ke_wr(3,x,0,"¦…");  break;  // ºÐ 
       case time_sec:  font_ke_wr(3,x,0,"Á¡");  break;  // ÃÊ
       case time_year: font_ke_wr(3,x,0,"‘e");  break;  // ³â
       case time_mon:  font_ke_wr(3,x,0,"¶©");  break;  // ¿ù    
       case time_date: font_ke_wr(3,x,9,"·©");  break;  // ÀÏ
     } 
     
    if(sub_set_mode_cnt == 29) cur_x = 12;  
}                 

void time_set_dis(char tg)
{         
  unsigned char x = 6; char xx = 10;
                                 
  all_clr();
  
  // main ¸Þ´º
  switch(set_mode_cnt)
   {
     case 1: font_ke_wr(0,1,tg,"Â‰‹e ");   break;     // Ãâ±Ù 
     case 2: font_ke_wr(0,1,tg,"ÊA‹e ");    break;     // Åð±Ù 
     case 3: font_ke_wr(0,1,tg,"Ñe¸ ");    break;     // ÇöÀç
     case 4: font_ke_wr(0,0,tg,"œa·¥¥i "); break;     // ¶óÀÎº° 
   }
   
  if(set_mode_cnt == 4) {x = 7; xx = 11;}
  font_ke_wr(0,x,tg,time_font);   // ½Ã°£
  font_ke_wr(0,xx,tg,set_font);   // ¼³Á¤ 
  
  // sub ¸Þ´º
  // Ãâ±Ù½Ã°£, Åð±Ù½Ã°£, ¶óÀÎº° ½Ã°£ ¼³Á¤
if(sub_set_mode_cnt != 0)
 { // if-1 
  if((set_mode_cnt == 4) || (sub_set_mode_cnt >= 30)) x = 2; // ¶óÀÎº°, ÇöÀç½Ã°£ ºÐ ÀÌ»ó ¼³Á¤½Ã ¸¸ Àû¿ë
  else x = 0;
  
  if(sub_set_mode_cnt != 27)
   {  
     if(sub_set_mode_cnt >= 29) font_ke_wr(2,x,0,"Ñe¬wÈ: "); // Çö»óÅÂ    
     else font_ke_wr(2,x,0,"¸å¬wÈ: ");   // Àü»óÅÂ   
    font_ke_wr(3,x,0,"¬é¸÷Ã¡: ");   // ¼³Á¤Ä¡  
   }  
    
  switch(sub_set_mode_cnt)
   {
     case 1: // Ãâ±Ù½Ã°£ÀÇ ¼¾¼­ Á¤Áö ½Ã°£ÀÇ ½Ã  ¼³Á¤ 
             sub_menu(AM, set_out_hour, time_hour);                                
         break; 
          
     case 2: // Ãâ±Ù½Ã°£ ÀÇ ¼¾¼­ µ¿ÀÛ °ËÃâ ½Ã°£ ¼³Á¤ ¸ðµå      
             sub_menu(AM, set_run_hour, time_hour);
        break;  
        
     case 3: // Åð±Ù½Ã°£ÀÇ ¼¾¼­ Á¤Áö ½Ã°£ÀÇ ½Ã  ¼³Á¤ 
             sub_menu(PM, end_stop_time_set.hour, time_hour);                                
         break; 
          
     case 4: // Åð±Ù½Ã°£ ÀÇ ¼¾¼­ µ¿ÀÛ °ËÃâ ½Ã°£ ¼³Á¤ ¸ðµå      
             sub_menu(PM, end_run_time_set.hour, time_hour);
        break; 
     
     case 5:  // Ã¼³Î 1 ½Ã°£¼³Á¤
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch1_hour, time_hour);
        break; 
        
     case 8:  // Ã¼³Î 2 ½Ã°£¼³Á¤
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch2_hour, time_hour);
        break; 
        
     case 11:  // Ã¼³Î 3 ½Ã°£¼³Á¤
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch3_hour, time_hour);
        break;  
        
     case 14:  // Ã¼³Î 4 ½Ã°£¼³Á¤
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch4_hour, time_hour);
        break;
        
     case 27:
               // ÇöÀç½Ã°£ÀÇ ½Ã ¼³Á¤
               font_ke_wr(1,0,1,"µ¡¸å, µ¡Ò ¬é¸÷"); 
               font_ke_wr(3,1,0,"8:µ¡¸å"); // ¿ÀÀü 
               font_ke_wr(3,9,0,"9:µ¡Ò");  // ¿ÀÈÄ   
               
               sub_set_mode_cnt = 28;  
        break; 
        
     case 29:
              // ÇöÀç ½Ã°£ÀÇ ½Ã ¼³Á¤ 
              font_ke_wr(1,4,1,"¯¡ˆe ¬é¸÷");  // ½Ã°£¼³Á¤    
              
               // ¼³Á¤Ä¡ Ç¥½Ã 
               sub_set_mode_cnt = 50; // am /pm ¸¦ 4 Line ¿¡ Ç¥½ÃÇÏ±â À§ÇØ¼­ 
               sub_menu(am_pm_set_flag, set.hour, time_hour);
               sub_set_mode_cnt = 29; // am /pm ¸¦ 4 Line ¿¡ Ç¥½ÃÇÏ±â À§ÇØ¼­ 
                     
              // Çö »óÅÂ ½Ã Ç¥½Ã     
              rd.hour = rtc_read_cmd(HOUR_R); //now time rtcc read 
              
              x = (rd.hour & 0x3f); //0x30
              if((x & 0x20) == 0x20) am_pm_rd_flag = 1; // pm = ¿ÀÈÄ = 1  
              else am_pm_rd_flag = 0; // am = ¿ÀÀü = 0
              
              x &= 0x1f;    
              sub_menu(am_pm_rd_flag, x, time_hour); 
              
              cur_x = 12;
        break; 
        
     case 30:    
               // ÇöÀç ½Ã°£ÀÇ ºÐ  ¼³Á¤ 
              font_ke_wr(1,5,1,"¦… ¬é¸÷");  // ºÐ ¼³Á¤    
              
              // ºÐ ¼³Á¤ Ä¡ Ç¥½Ã 
              sub_menu(HOUR_24_NO_APM_MODE, set.min, time_min);      
                                            
              // ºÐ ÇöÀç »óÅÂ Ç¥½Ã  
              rd.min = rtc_read_cmd(MIN_R); //now time rtcc read 
              
              x = (rd.min & 0x7f);                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_min);     
        break;  
        
     case 31:    
               // ÇöÀç ½Ã°£ÀÇ ÃÊ ¼³Á¤ 
              font_ke_wr(1,5,1,"Á¡ ¬é¸÷");  // ÃÊ ¼³Á¤    
              
              // ÃÊ ¼³Á¤ Ä¡ Ç¥½Ã 
              sub_menu(HOUR_24_NO_APM_MODE, set.sec, time_sec);      
                                            
              // ÃÊ ÇöÀç »óÅÂ Ç¥½Ã  
              rd.sec = rtc_read_cmd(SEC_R); //now time rtcc read 
              
              x = (rd.sec & 0x7f);                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_sec);     
        break; 
        
     case 32:    
               // ÇöÀç ½Ã°£ÀÇ ³â  ¼³Á¤ 
              font_ke_wr(1,5,1,"‘e ¬é¸÷");  // ³â  ¼³Á¤    
              
              // ³â ¼³Á¤ Ä¡ Ç¥½Ã      
              font_ke_wr(2,9,0,"20");
              sub_menu(HOUR_24_NO_APM_MODE, set.year, time_year);      
                                            
              // ³â ÇöÀç »óÅÂ Ç¥½Ã  
              font_ke_wr(3,9,0,"20");
              rd.year = rtc_read_cmd(YEAR_R); //now time rtcc read 
              
              x = rd.year;                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_year);     
        break;                                          
        
     case 33:    
               // ÇöÀç ½Ã°£ÀÇ ¿ù  ¼³Á¤ 
              font_ke_wr(1,5,1,"¶© ¬é¸÷");  // ¿ù  ¼³Á¤    
              
              // ¿ù ¼³Á¤ Ä¡ Ç¥½Ã 
              sub_menu(HOUR_24_NO_APM_MODE, set.mon, time_mon);      
                                            
              // ¿ù ÇöÀç »óÅÂ Ç¥½Ã  
              rd.mon = rtc_read_cmd(MONTH_R); //now time rtcc read 
              
              x = (rd.mon & 0x7f);                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_mon);     
        break;                                          
             
     case 34:    
               // ÇöÀç ½Ã°£ÀÇ ÀÏ  ¼³Á¤ 
              font_ke_wr(1,5,1,"·© ¬é¸÷");  // ÀÏ  ¼³Á¤    
              
              // ÀÏ ¼³Á¤ Ä¡ Ç¥½Ã 
              sub_menu(HOUR_24_NO_APM_MODE, set.date, time_date);      
                                            
              // ÀÏ ÇöÀç »óÅÂ Ç¥½Ã  
              rd.date = rtc_read_cmd(DATE_R); //now time rtcc read 
              
              x = (rd.date & 0x7f);                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_date);     
        break;                                          
   }
  }// if-1 end 
}

        
void out_stop_time_set_dis(char y, char x, char tg, char dis)
{
  if(dis == 0) font_ke_wr(y,0,0,"1: ");
  font_ke_wr(y,x,tg,senser_font);    // ¼¾¼­ 
  font_ke_wr(y,x+5,tg,stop_font);    // Á¤Áö  
  font_ke_wr(y,x+10,tg,time_font);   // ½Ã°£   
}                                       
  
void out_run_time_set_dis(char y, char x, char tg, char dis)
{  
  if(dis == 0) font_ke_wr(y,0,0,"2: ");
  font_ke_wr(y,x,tg,senser_font);   // ¼¾¼­
  font_ke_wr(y,x+5,tg,run_font);    // °ËÃâ 
  font_ke_wr(y,x+10,tg,time_font);  // ½Ã°£ 
}
                  
void now_time_set_dis(void)
{
  font_ke_wr(1,2,0,"1: ¯¡  4: ‘e");  // ½Ã   ³âÃ
  font_ke_wr(2,2,0,"2: ¦…  5: ¶©");  // ºÐ   ¿ùÐ
  font_ke_wr(3,2,0,"3: Á¡  6: ·©");  // ÃÊ   ÀÏÃ
}
     
void line_time_set_dis(void)
{
  font_ke_wr(2,0,0,"1:ÁAéA, 2:ÁAéB");  // Ã¼³Î 1, 2
  font_ke_wr(3,0,0,"3:ÁAéC, 4:ÁAéD");  // Ã¼³Î 3, 4
} 
 
void ch_dis(char ch)
{
  font_ke_wr(1,0,1,"¯¡ˆe¬é¸÷: ");  // ½Ã°£¼³Á¤
  efont_8x16_wr(1,ch + 0x30); 
  font_ke_wr(1,11,1," ÁAé");     // Ã¼³Î  
}
      
void line_dis(char nb)
{  
  char buf_sec, buf_hour, buf_min, buf;
 
 one_line_clr(0);
 glcd_xy(0, 1);
 efont_8x16_wr(0,nb + 0x30);   
 font_ke_wr(0,2,0,"¤å œa·¥ ˆq»¡!");  // ?¹ø ¶óÀÎ °¨Áö 
 
 if(nb == 1)  // ch1
  {
   buf_hour = ch_time_set.ch1_hour; 
    buf_min = ch_time_set.ch1_min;
     buf_sec = ch_time_set.ch1_sec;   
  }
 else if(nb == 2) // ch2
  {
    buf_hour = ch_time_set.ch2_hour; 
     buf_min = ch_time_set.ch2_min;
      buf_sec = ch_time_set.ch2_sec;     
  } 
 else if(nb == 3) // ch3
  {
    buf_hour = ch_time_set.ch3_hour; 
     buf_min = ch_time_set.ch3_min;
      buf_sec = ch_time_set.ch3_sec;   
  } 
 else  // ch4
  {
    buf_hour = ch_time_set.ch4_hour; 
     buf_min = ch_time_set.ch4_min;
      buf_sec = ch_time_set.ch4_sec;   
  }  
  
 // Ã¼³Î ¶óÀÎ ¼³Á¤Ä¡ Ç¥½Ã 
 glcd_xy(2,0);

 buf = (buf_hour & 0xf0);
 buf >>=4;
 efont_8x16_wr(0, buf + 0x30);
 efont_8x16_wr(0, (buf_hour & 0x0f) + 0x30);                     
 font_ke_wr(2,2,0,"¯¡");    // ½Ã   
          
 // ºÐ Ç¥½Ã 
 buf = (buf_min & 0xf0);
 buf >>=4;
 efont_8x16_wr(0, buf + 0x30);
 efont_8x16_wr(0, (buf_min & 0x0f) + 0x30);   
 font_ke_wr(2,6,0,"¦…");    // ºÐ            
                      
         
 // ÃÊ  Ç¥½Ã 
 buf = (buf_sec & 0xf0);
 buf >>=4;
 efont_8x16_wr(0, buf + 0x30);
 efont_8x16_wr(0, (buf_sec & 0x0f) + 0x30);   
 font_ke_wr(2,10,0,"Á¡");    // ÃÊ            
                                             
 font_ke_wr(2,12,0,"¬é¸÷"); //¼³Á¤ 
}
        
void year_dis(void)
{
  rtc_rd_date();
       
     // ³âµµ Ç¥½Ã = 2008³â 
     font_ke_wr(0,0,0,"20"); 
     buf = (rd.year & 0xf0);
     buf >>= 4;
     efont_8x16_wr(0, buf +'0');  //0  ³â ½Ê ÀÚ¸® 
     
     buf = (rd.year & 0x0f);
     efont_8x16_wr(0, buf + '0'); //8  ³â ÀÏÀÚ¸® 
     font_ke_wr(0,4,0,"‘e ");    // ³â   
     
     // ¿ù Ç¥½Ã
     buf = (rd.mon & 0xf0);
     buf >>= 4;  
     efont_8x16_wr(0, buf + 0x30);  // ¿ù ½ÊÀÚ¸® 
     
     buf = (rd.mon & 0x0f);
     efont_8x16_wr(0, buf + '0');  // ¿ù ÀÏÀÚ¸® 
     font_ke_wr(0,9,0,"¶© ");    // ¿ù 
      
     // ÀÏ  Ç¥½Ã
     buf = (rd.date & 0xf0);
     buf >>= 4;  
     efont_8x16_wr(0, buf + 0x30);  // ÀÏ  ½ÊÀÚ¸® 
     
     buf = (rd.date & 0x0f);
     efont_8x16_wr(0, buf + '0');  // ÀÏ  ÀÏÀÚ¸® 
     font_ke_wr(0,14,0,"·©");    // ÀÏ    
}

// key input error
void key_error_dis(void)
{ 
  char j;
    
   error_flag = 1;
   
   set_mode_cnt = 0;
   sub_set_mode_cnt = 0; 
   set_flag = 0; 
   cur_flag = 0;  
   buf_d = 0x55;
   cur_cnt_flag = 0; 
   hi = low = in_key_buf = song = 0;
          
   all_clr();  
   
   key_bz(50);
   delay_ms(50);
   key_bz(50); 
      
  for(j = 0; j<= 1; j++)
   {
    font_ke_wr(1,0,1,"* Ç¡ ·³b µAœá *");  // *Å° ÀÔ·Â ¿¡·¯ *
    font_ke_wr(2,0,0," ·³b¤ñ¶á Á¡‰Á! ");  // ÀÔ·Â¹üÀ§ ÃÊ°ú!
    
    delay_ms(1000);
    all_clr();
    delay_ms(500);  
   } 
   
   error_flag = 0;
   
  if((ch1_run_flag ==1) || (ch2_run_flag == 1) || (ch3_run_flag == 1) || (ch4_run_flag == 1)) 
     {
      all_clr();
      line_dis(main_dis_cnt); 
     } 
}
    
void pass_dis(void)
{          
  font_ke_wr(1,0,1,"§¡£©¤åÑ¡·³bÐ¶a"); //  ºñ¹Ð¹øÈ£ ÀÔ·ÂÇØ¿ä.
  font_ke_wr(3,1,0,"§¡£©¤åÑ¡: ");       // ¤²¹Ð¹øÈ£        
  
  // lcd_bak led on == 2008, 08, 22 = ¿ì¸® ¹ø°³ ÅÂ¾î³­³¯ ¼öÁ¤ = Å×¾î³­ ±â³äÀ¸·Î
  lcd_bak_led_on;
  exio_out(exio_buf);
} 

void pass_ok_dis(void)
{
 font_ke_wr(1,0,1,"§¡£©¤åÑ¡ ÑÂ·¥ –Q");  // ºñ¹Ð¹øÈ£ È®ÀÎµÊÎ
 font_ke_wr(2,2,0,"Ç¡ ¹¡¸b Ð¶a!");  // Å° Á¶ÀÛÇØ¿ä   

  key_bz(50);
  delay_ms(50);
  key_bz(50);
  
  m_sec = m_min = 0;  
}

void pass_no_dis(void)
{
 font_ke_wr(0,0,1,"§¡£©¤åÑ¡·³bµ¡ŸA"); // ºñ¹Ð¹øÈ£ÀÔ·Â¿À·ù Î
 font_ke_wr(2,0,0,"”a¯¡ ·³bÐa­A¶a!");     // ´Ù½ÃÀÔ·ÂÇÏ¼¼¿ä   
 
  key_bz(250);
}

void key_lock(void)
{
  all_clr();
  font_ke_wr(1,1,0,"* Key Lock ! *");  // 
  font_ke_wr(2,2,1,"Ç¡ ·³b ¦‰ˆa");    // Å° ÀÔ·ÂºÒ°¡
  delay_ms(1200);  
}
          
void data_dis(char tg, uchar time)
{                   
  uchar buf;
  
  
   buf = (time & 0xf0);   
   buf >>= 4;
  
  efont_8x16_wr(tg, buf + 0x30);  // hi = ½Ã ½ÊÀÚ¸® 
  efont_8x16_wr(tg, (time & 0x0f) + '0');  // ½Ã ÀÏÀÚ¸® 
}    
             
void time_dn_cnt(unsigned char buf_hour, unsigned char buf_min, unsigned char buf_sec, char dis_nb)
{              
       if(buf_sec == 0) 
        {        
         // sec = 0 ÀÏ °æ¿ì
          if(buf_min != 0) 
           {
            buf_sec = 0x59;
            
            buf_min--; 
            
            if((buf_min & 0x0f) > 0x09) buf_min -= 0x06; // hex to grcmol
            if((buf_min & 0xf0) > 0x90) buf_min -= 0x60;   
           }
          else
           {
             // min = 0ÀÏ°æ¿ì
             if(buf_hour != 0)
              {
                buf_min = 0x59;
                
                buf_hour--;   
                
                if((buf_hour & 0x0f) > 0x09) buf_hour -= 0x06; // hex to grcmol
                if((buf_hour & 0xf0) > 0x90) buf_hour -= 0x60;   
              }
             else
              {  
                // hour = 0 ÀÏ °æ¿ì = sec = min = hour
                // Lamp off
                if((ch1_run_flag == 1) && (dis_nb == 1))// ch1 lamp off;
                 {
                   ch1_run_flag = 0; 
                   lamp_out(1, OFF); //1 lamp off
                   ch1_led_off;
                   exio_out(exio_buf); // ex port 574 out
                 } 
                              
                if((ch2_run_flag == 1) && (dis_nb == 2)) // ch2 lamp off;
                 {
                   ch2_run_flag = 0; 
                   lamp_out(2, OFF); //2 lamp off        
                   ch2_led_off;
                   exio_out(exio_buf); // ex port 574 out
                 }    
                 
                if((ch3_run_flag == 1) && (dis_nb == 3)) // ch3 lamp off;
                 {
                   ch3_run_flag = 0; 
                   lamp_out(3, OFF); //3 lamp off
                   ch3_led_off;
                   exio_out(exio_buf); // ex port 574 out
                 }  
                     
                if((ch4_run_flag == 1) && (dis_nb == 4))// ch4 lamp off;
                 {
                   ch4_run_flag = 0; 
                   lamp_out(4, OFF); //4 lamp off
                   ch4_led_off;
                   exio_out(exio_buf); // ex port 574 out
                 }           
                 
                if(dis_nb == main_dis_cnt)
                 {
                  year_dis();
                  
                  one_line_clr(3);
                  glcd_xy(3, 0);
                  efont_8x16_wr(1,main_dis_cnt + 0x30);   
                  font_ke_wr(3,1,1,"¤åœa·¥ ¹¡¡w OFF");  // ?¹ø¶óÀÎ Á¶¸í ²û
                  
                 // key_bz(250);
                 } 
                
                key_bz(250);  // 2008, 8,  22 ¹ø°³ ÅÂ¾î³­ ±â³äÀ¸·Î ³¡³À´Ï´Ù. µ·ÀÌ³ª ¸¹ÀÌ ¹ú¾úÀ¸¸é...
                goto kc1;
              }            
           }  
        }
       else  
        {
          buf_sec--;
            
          if((buf_sec & 0x0f) > 0x09) buf_sec -= 0x06; // hex to dec converser
          if((buf_sec & 0xf0) > 0x90) buf_sec -= 0x60;   
        } 
        
        
       if(dis_nb == main_dis_cnt)
        {
          // lcd display
          font_ke_wr(3,0,1,"¸eµa");    // ÀÜ¿©
       
          // Ã¼³Î ¶óÀÎ ÇöÀçÄ¡ Ç¥½Ã 
          glcd_xy(3,4);
          data_dis(1, buf_hour);    
          font_ke_wr(3,6,1,"¯¡");    // ½Ã   
          
          // ºÐ Ç¥½Ã 
          data_dis(1, buf_min);
          font_ke_wr(3,10,1,"¦…");    // ºÐ            
                      
          // ÃÊ  Ç¥½Ã 
          data_dis(1, buf_sec); 
          font_ke_wr(3,14,1,"Á¡");    // ÃÊ                             
        }
kc1:       
   time_bufk[0] = buf_hour;
   time_bufk[1] = buf_min;
   time_bufk[2] = buf_sec;    
}         

void lamp(void)
{       
   if(tg == 0)
    {   
     one_line_clr(0);
     glcd_xy(0, 1);
     efont_8x16_wr(0,main_dis_cnt + 0x30);   
     font_ke_wr(0,2,0,"¤å œa·¥ ˆq»¡!");  // ?¹ø ¶óÀÎ °¨Áö 
    }
   else
    {  
     one_line_clr(0);
     glcd_xy(0, 0);
     efont_8x16_wr(1,main_dis_cnt + 0x30);   
     font_ke_wr(0,1,1,"¤å œa·¥ ¹¡¡w ON");  // ?¹ø¶óÀÎ Á¶¸í Å´ 
    }   
}
        
void ch_chk_run(void)
{        
    // Ã¼³Î time count  
    if(ch1_run_flag == 1) // ch1 Line-1
     { 
       time_dn_cnt(ch_time_cnt.ch1_hour, ch_time_cnt.ch1_min, ch_time_cnt.ch1_sec, 1);
                     
       ch_time_cnt.ch1_hour = time_bufk[0];
        ch_time_cnt.ch1_min = time_bufk[1];
         ch_time_cnt.ch1_sec = time_bufk[2];  
     } 
     
    if(ch2_run_flag == 1) // ch2 Line -2
     { 
       time_dn_cnt(ch_time_cnt.ch2_hour, ch_time_cnt.ch2_min, ch_time_cnt.ch2_sec, 2);
                     
       ch_time_cnt.ch2_hour = time_bufk[0];
        ch_time_cnt.ch2_min = time_bufk[1];
         ch_time_cnt.ch2_sec = time_bufk[2];  
     }       
     
    if(ch3_run_flag == 1) // ch2 Line -3
     { 
       time_dn_cnt(ch_time_cnt.ch3_hour, ch_time_cnt.ch3_min, ch_time_cnt.ch3_sec, 3);
                     
       ch_time_cnt.ch3_hour = time_bufk[0];
        ch_time_cnt.ch3_min = time_bufk[1];
         ch_time_cnt.ch3_sec = time_bufk[2];  
     }       
     
    if(ch4_run_flag == 1) // ch2 Line -4
     { 
       time_dn_cnt(ch_time_cnt.ch4_hour, ch_time_cnt.ch4_min, ch_time_cnt.ch4_sec, 4);
                     
       ch_time_cnt.ch4_hour = time_bufk[0];
        ch_time_cnt.ch4_min = time_bufk[1];
         ch_time_cnt.ch4_sec = time_bufk[2];  
     }
}
                                     
void rtc_time_dis(void)
{
 rtc_rd_time();  
 
 if(rd.clk_sec != rd.sec) // if-1
  {
   rd.clk_sec = rd.sec;  // sec bak-up        
  
  
   // ½Ã Ç¥½Ã     
   glcd_xy(1,1); //1
   buf = (rd.hour & 0x30);
   buf >>= 4;  
               
        // 12 hour mode am / pm chk
        if((buf & 0x02) == 0x02)// {efont_8x16_wr(0,'P'); efont_8x16_wr(0, 'M'); efont_8x16_wr(0, 0x20);} // 12 hour pm mode display
         { 
           // pm ¿ÀÈÄ 
           font_ke_wr(1,0,tg,"µ¡Ò");  // ¿ÀÈÄ 
           out_am_pm_flag = 1;
         }
        else //{efont_8x16_wr(0,'A'); efont_8x16_wr(0, 'M'); efont_8x16_wr(0, 0x20);} // 12 hour am mode display
         {  
           // am ¿ÀÀü
           font_ke_wr(1,0,tg,"µ¡¸å"); // ¿ÀÀü   
           out_am_pm_flag = 0;
         }                                  
         
        // ½Ã ½ÊÀÚ¸® Ç¥½Ã
        efont_8x16_wr(tg,(buf & 0x01) + '0');     
     
     buf = (rd.hour & 0x0f);
     efont_8x16_wr(tg, buf + '0');  // ½Ã ÀÏÀÚ¸® 
     font_ke_wr(1,6,tg,"¯¡");    // ½Ã   
          
     // ºÐ Ç¥½Ã 
      glcd_xy(1,8);
     buf = (rd.min & 0x70);
     buf >>= 4;  
     efont_8x16_wr(tg, buf + 0x30);  // ºÐ    ½ÊÀÚ¸® 
     
     buf = (rd.min & 0x0f);
     efont_8x16_wr(tg, buf + '0');  // ºÐ    ÀÏÀÚ¸® 
     font_ke_wr(1,10,tg,"¦…");    // ºÐ            
                      
         
     // ÃÊ  Ç¥½Ã 
      glcd_xy(1,12);
     buf = (rd.sec & 0x70);
     buf >>= 4;  
     efont_8x16_wr(tg, buf + 0x30);  // ÃÊ    ½ÊÀÚ¸® 
     
     buf = (rd.sec & 0x0f);
     efont_8x16_wr(tg, buf + '0');  // ÃÊ    ÀÏÀÚ¸® 
     font_ke_wr(1,14,tg,"Á¡");    // ÃÊ            
//----------------------------------------------------------------     

// Á¦ÀÏ ¾î·Á¿î ºÎºÐÀÓ 
if((no_set_am_flag == 1) && (no_set_pm_flag == 1)) ch_chk_run(); // ÃâÅð±Ù½Ã°£ ¹Ì ¼³Á¤½Ã 
else if(out_am_pm_flag == 0) //am, ¿ÀÀü, Ãâ±Ù
{ //if-1
  // Ãâ±Ù½Ã°£
  // Ãâ±Ù½Ã°£ ¼¾¼­ Á¤Áö ½Ã Ã¼Å© 
  time_end_flag = 0;
  
  if(no_set_am_flag == 1) ch_chk_run(); // Ãâ±Ù½Ã°£ ¹Ì ¼³Á¤½Ã 
  else if(((rd.hour & 0x1f) == set_out_hour) && (time_out_flag == 0)) // Ãâ±Ù½Ã°£ Á¤Áö ½Ã Ã¼Å© 
   { //if-2 
     set_out_min  = ram_read(out_stop_min_r);       
     // Ãâ±Ù½Ã°£ ¼¾¼­ Á¤Áö ºÐ Ã¼Å© 
     if(((rd.min & 0x7f) == set_out_min) && (time_chk_flag == 0)) //Ãâ±Ù½Ã°£ ¼¾¼­ Á¤Áö ºÐ Ã¼Å©
      { //if-3 
        // all ch lamp output
        out_ch1 = out_ch2 = out_ch3 = out_ch4 = ON; // 1 
        ch1_run_flag = ch2_run_flag = ch3_run_flag = ch4_run_flag = 1; 
                                                
         // led out = v2 2008,8,21
          ch1_led_on;
          ch2_led_on;
          ch3_led_on;
          ch4_led_on;
          exio_out(exio_buf); // ex port 574 out
       
        font_ke_wr(3,0,1,"Â‰‹e¯¡ˆe ·³“¡”a."); //Ãâ±Ù½Ã°£ ÀÔ´Ï´Ù
        time_chk_flag = 1;
      } //if-3 end
     else if(time_chk_flag == 1)
      { // if-4
        if((rd.hour & 0x1f) <= set_run_hour) // µ¿ÀÛ ½Ã Ã¼Å©
         { //if-5
           if((rd.min & 0x7f) >= set_run_min)
            { //if-6
             font_ke_wr(3,0,1,"­E¬á ˆñÂ‰ Ðs“¡”a"); //¼¾¼­ °ËÃâÇÕ´Ï´Ù Ù
             delay_ms(3000);
                   
             time_chk_flag = 0; 
             time_out_flag = 1;
             ch_chk_run();             
            } // if-6-end
           else  font_ke_wr(3,0,1,"Â‰‹e¯¡ˆe ·³“¡”a."); //Ãâ±Ù½Ã°£ ÀÔ´Ï´Ù  
         } //if-5-end 
      } //if-4-end 
     else ch_chk_run();    
   } //if-2-end 
  else ch_chk_run();
} //if-1-end--------------------------------------------------------------------
else if(out_am_pm_flag == 1) // pm, ¿ÀÈÄ, Åð±Ù
{ //if-7    
  // Åð±Ù½Ã°£
  // Åð±Ù½Ã°£ ¼¾¼­ Á¤Áö ½Ã Ã¼Å©  
  time_out_flag = 0;
  
  if(no_set_pm_flag == 1) ch_chk_run(); // Åð±Ù½Ã°£ ¹Ì ¼³Á¤½Ã 
  else if(((rd.hour & 0x1f) == end_stop_time_set.hour) && (time_end_flag == 0)) // Åð±Ù½Ã°£ Á¤Áö ½Ã Ã¼Å© 
   { //if-2
     end_stop_time_set.min  = ram_read(end_stop_min_r);       
     // Åð±Ù½Ã°£ ¼¾¼­ Á¤Áö ºÐ Ã¼Å© 
     if(((rd.min & 0x7f) == end_stop_time_set.min) && (time_chk_flag == 0)) //Åð±Ù½Ã°£ ¼¾¼­ Á¤Áö ºÐ Ã¼Å©
      { //if-3 
        // all ch lamp output
        out_ch1 = out_ch2 = out_ch3 = out_ch4 = ON; // 1 
        ch1_run_flag = ch2_run_flag = ch3_run_flag = ch4_run_flag = 1; 
        
        // led out = v2 2008,8,21
        ch1_led_on;
        ch2_led_on;
        ch3_led_on;
        ch4_led_on;
        exio_out(exio_buf); // ex port 574 out
        
        font_ke_wr(3,0,1,"ÊA‹e¯¡ˆe ·³“¡”a."); //Åð±Ù½Ã°£ ÀÔ´Ï´Ù
        time_chk_flag = 1;
      } //if-3 end
     else if(time_chk_flag == 1)
      { // if-4
        if((rd.hour & 0x1f) <= end_run_time_set.hour) // µ¿ÀÛ ½Ã Ã¼Å©
         { //if-5
           if((rd.min & 0x7f) >= end_run_time_set.min)
            { //if-6
             font_ke_wr(3,0,1,"­E¬á ˆñÂ‰ Ðs“¡”a"); //¼¾¼­ °ËÃâÇÕ´Ï´Ù Ù
             delay_ms(3000);
                   
             time_chk_flag = 0; 
             time_end_flag = 1;
             ch_chk_run();             
            } // if-6-end
           else font_ke_wr(3,0,1,"ÊA‹e¯¡ˆe ·³“¡”a."); //Åð±Ù½Ã°£ ÀÔ´Ï´Ù 
         } //if-5-end           
      } //if-4-end 
     else ch_chk_run();    
   } //if-2-end 
  else ch_chk_run();
} //if-7-end
//----------------------------------------------------------------
   
      tg = (~(tg)); 
                           
      // sec led togle
     if(tg == 1) sec_led_on;
    else sec_led_off;
    exio_out(exio_buf);
    
   //-------------------------------------
   if((ch1_run_flag == 1) && (main_dis_cnt == 1)) lamp(); 
   else if((ch2_run_flag == 1) && (main_dis_cnt == 2)) lamp();  
   else if((ch3_run_flag == 1) && (main_dis_cnt == 3)) lamp(); 
   else if((ch4_run_flag == 1) && (main_dis_cnt == 4)) lamp();               
  }  // if-1 end          

} 



 
#endif
   