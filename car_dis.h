


/* 
=============================================
prj name : car 추차장 조명 제어  시스템
  program : 송명규
  
  job day : 2008, 06, 16
  
  file name : car_dis.h
================================================
*/  
  
    
#ifndef _CAR_DIS_
#define _CAR_DIS_       
                  

 // CAR USER 용 폰트    
flash unsigned char time_font[] = "�죭e";    // 시간  
flash unsigned char set_font[]  = " ч몹";    // 설정 
flash unsigned char stop_font[] = "몹빨 ";  // 정지 
flash unsigned char run_font[]  = "덎혟 ";  // 검출    
flash unsigned char senser_font[] = "쵦п "; // 센서 

  
// g lcd display                  
void logo(void)
{  
  char j,h=1;
   for(j = 0; j <= 2; j++)
    {
     font_ke_wr(1,1,0,"킕먤빨 면뇨�w");  // 에너지 절약형
     font_ke_wr(2,3,h,"ES-Ver-02");     // 2009, 02, 13 수정
     h = (~(h));
     delay_ms(1000);
     all_clr();
     delay_ms(1000);
    }
}  

void logo1(void)
{     
   all_clr();
   font_ke_wr(1,1,0,"킕먤빨 면뇨�w");  // 에너지 절약형
   font_ke_wr(2,3,1,"ES-Ver-02");     // 2009, 02, 13 수정
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
  
  // 전상태          
  if(sub_set_mode_cnt == 50) x = 3; //// am /pm 를 4 Line 에 표시하기 위해서 
  else x = 2;                       
  if(am_pm == 0) font_ke_wr(x,7,0,"덧멨"); // 오전 
  else if(am_pm == 1) font_ke_wr(x,7,0,"덧��"); // 오후  
                                  
  if(sub_set_mode_cnt == 50) sub_set_mode_cnt = 29;  // am /pm 를 4 Line 에 표시하기 위해서 
  
    if((set_mode_cnt == 4) || (sub_set_mode_cnt >= 30)) x = 10;
    else x = 12;
    if(sub_set_mode_cnt == 32) x = 11;  //2008년 표시땜
    
    glcd_xy(2, x);  
    
    smg = (buf & 0xf0);
    smg >>= 4;      
    efont_8x16_wr(0, smg | 0x30);  // 십자리 표시
    
    smg = (buf & 0x0f);
    efont_8x16_wr(0, smg | 0x30);  // 일자리표시 
    
    if((set_mode_cnt == 4) || (sub_set_mode_cnt >= 30)) x = 13;  // 라인별 설정 
    else x = 14;
                       
    switch(time_env)
     {
       case time_hour: font_ke_wr(2,x,0,"��");   break;  // 시  
       case time_min:  font_ke_wr(2,x,0,"쫭");  break;  // 분 
       case time_sec:  font_ke_wr(2,x,0,"점");  break;  // 초
       case time_year: font_ke_wr(2,x,0,"멷");  break;  // 년
       case time_mon:  font_ke_wr(2,x,0,"땐");  break;  // 월    
       case time_date: font_ke_wr(2,x,9,"랭");  break;  // 일
     }
           
    // 설정치   
    if((sub_set_mode_cnt == 32) || (sub_set_mode_cnt == 29)) xy_x_clr(3,11,13);
    else xy_x_clr(3,10,13);  
    
   ///////// if(sub_set_mode_cnt == 32) font_ke_wr(2,9,0,"20");
         
    if(sub_set_mode_cnt != 29) // am /pm 를 4 Line 에 표시하기 위해서 
     {
      if(am_pm == 0) font_ke_wr(3,7,0,"덧멨"); // 오전 
      else if(am_pm == 1) font_ke_wr(3,7,0,"덧��"); // 오후  
     }
     
    switch(time_env)
     {
       case time_hour: font_ke_wr(3,x,0,"��");   break;  // 시  
       case time_min:  font_ke_wr(3,x,0,"쫭");  break;  // 분 
       case time_sec:  font_ke_wr(3,x,0,"점");  break;  // 초
       case time_year: font_ke_wr(3,x,0,"멷");  break;  // 년
       case time_mon:  font_ke_wr(3,x,0,"땐");  break;  // 월    
       case time_date: font_ke_wr(3,x,9,"랭");  break;  // 일
     } 
     
    if(sub_set_mode_cnt == 29) cur_x = 12;  
}                 

void time_set_dis(char tg)
{         
  unsigned char x = 6; char xx = 10;
                                 
  all_clr();
  
  // main 메뉴
  switch(set_mode_cnt)
   {
     case 1: font_ke_wr(0,1,tg,"혟땎 ");   break;     // 출근 
     case 2: font_ke_wr(0,1,tg,"�A땎 ");    break;     // 퇴근 
     case 3: font_ke_wr(0,1,tg,"�e툈 ");    break;     // 현재
     case 4: font_ke_wr(0,0,tg,"쏿램쩳 "); break;     // 라인별 
   }
   
  if(set_mode_cnt == 4) {x = 7; xx = 11;}
  font_ke_wr(0,x,tg,time_font);   // 시간
  font_ke_wr(0,xx,tg,set_font);   // 설정 
  
  // sub 메뉴
  // 출근시간, 퇴근시간, 라인별 시간 설정
if(sub_set_mode_cnt != 0)
 { // if-1 
  if((set_mode_cnt == 4) || (sub_set_mode_cnt >= 30)) x = 2; // 라인별, 현재시간 분 이상 설정시 만 적용
  else x = 0;
  
  if(sub_set_mode_cnt != 27)
   {  
     if(sub_set_mode_cnt >= 29) font_ke_wr(2,x,0,"�e촻��: "); // 현상태    
     else font_ke_wr(2,x,0,"멨촻��: ");   // 전상태   
    font_ke_wr(3,x,0,"ч몹찼: ");   // 설정치  
   }  
    
  switch(sub_set_mode_cnt)
   {
     case 1: // 출근시간의 센서 정지 시간의 시  설정 
             sub_menu(AM, set_out_hour, time_hour);                                
         break; 
          
     case 2: // 출근시간 의 센서 동작 검출 시간 설정 모드      
             sub_menu(AM, set_run_hour, time_hour);
        break;  
        
     case 3: // 퇴근시간의 센서 정지 시간의 시  설정 
             sub_menu(PM, end_stop_time_set.hour, time_hour);                                
         break; 
          
     case 4: // 퇴근시간 의 센서 동작 검출 시간 설정 모드      
             sub_menu(PM, end_run_time_set.hour, time_hour);
        break; 
     
     case 5:  // 체널 1 시간설정
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch1_hour, time_hour);
        break; 
        
     case 8:  // 체널 2 시간설정
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch2_hour, time_hour);
        break; 
        
     case 11:  // 체널 3 시간설정
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch3_hour, time_hour);
        break;  
        
     case 14:  // 체널 4 시간설정
               sub_menu(HOUR_24_NO_APM_MODE, ch_time_set.ch4_hour, time_hour);
        break;
        
     case 27:
               // 현재시간의 시 설정
               font_ke_wr(1,0,1,"덧멨, 덧�� ч몹"); 
               font_ke_wr(3,1,0,"8:덧멨"); // 오전 
               font_ke_wr(3,9,0,"9:덧��");  // 오후   
               
               sub_set_mode_cnt = 28;  
        break; 
        
     case 29:
              // 현재 시간의 시 설정 
              font_ke_wr(1,4,1,"�죭e ч몹");  // 시간설정    
              
               // 설정치 표시 
               sub_set_mode_cnt = 50; // am /pm 를 4 Line 에 표시하기 위해서 
               sub_menu(am_pm_set_flag, set.hour, time_hour);
               sub_set_mode_cnt = 29; // am /pm 를 4 Line 에 표시하기 위해서 
                     
              // 현 상태 시 표시     
              rd.hour = rtc_read_cmd(HOUR_R); //now time rtcc read 
              
              x = (rd.hour & 0x3f); //0x30
              if((x & 0x20) == 0x20) am_pm_rd_flag = 1; // pm = 오후 = 1  
              else am_pm_rd_flag = 0; // am = 오전 = 0
              
              x &= 0x1f;    
              sub_menu(am_pm_rd_flag, x, time_hour); 
              
              cur_x = 12;
        break; 
        
     case 30:    
               // 현재 시간의 분  설정 
              font_ke_wr(1,5,1,"쫭 ч몹");  // 분 설정    
              
              // 분 설정 치 표시 
              sub_menu(HOUR_24_NO_APM_MODE, set.min, time_min);      
                                            
              // 분 현재 상태 표시  
              rd.min = rtc_read_cmd(MIN_R); //now time rtcc read 
              
              x = (rd.min & 0x7f);                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_min);     
        break;  
        
     case 31:    
               // 현재 시간의 초 설정 
              font_ke_wr(1,5,1,"점 ч몹");  // 초 설정    
              
              // 초 설정 치 표시 
              sub_menu(HOUR_24_NO_APM_MODE, set.sec, time_sec);      
                                            
              // 초 현재 상태 표시  
              rd.sec = rtc_read_cmd(SEC_R); //now time rtcc read 
              
              x = (rd.sec & 0x7f);                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_sec);     
        break; 
        
     case 32:    
               // 현재 시간의 년  설정 
              font_ke_wr(1,5,1,"멷 ч몹");  // 년  설정    
              
              // 년 설정 치 표시      
              font_ke_wr(2,9,0,"20");
              sub_menu(HOUR_24_NO_APM_MODE, set.year, time_year);      
                                            
              // 년 현재 상태 표시  
              font_ke_wr(3,9,0,"20");
              rd.year = rtc_read_cmd(YEAR_R); //now time rtcc read 
              
              x = rd.year;                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_year);     
        break;                                          
        
     case 33:    
               // 현재 시간의 월  설정 
              font_ke_wr(1,5,1,"땐 ч몹");  // 월  설정    
              
              // 월 설정 치 표시 
              sub_menu(HOUR_24_NO_APM_MODE, set.mon, time_mon);      
                                            
              // 월 현재 상태 표시  
              rd.mon = rtc_read_cmd(MONTH_R); //now time rtcc read 
              
              x = (rd.mon & 0x7f);                              
              sub_menu(HOUR_24_NO_APM_MODE, x, time_mon);     
        break;                                          
             
     case 34:    
               // 현재 시간의 일  설정 
              font_ke_wr(1,5,1,"랭 ч몹");  // 일  설정    
              
              // 일 설정 치 표시 
              sub_menu(HOUR_24_NO_APM_MODE, set.date, time_date);      
                                            
              // 일 현재 상태 표시  
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
  font_ke_wr(y,x,tg,senser_font);    // 센서 
  font_ke_wr(y,x+5,tg,stop_font);    // 정지  
  font_ke_wr(y,x+10,tg,time_font);   // 시간   
}                                       
  
void out_run_time_set_dis(char y, char x, char tg, char dis)
{  
  if(dis == 0) font_ke_wr(y,0,0,"2: ");
  font_ke_wr(y,x,tg,senser_font);   // 센서
  font_ke_wr(y,x+5,tg,run_font);    // 검출 
  font_ke_wr(y,x+10,tg,time_font);  // 시간 
}
                  
void now_time_set_dis(void)
{
  font_ke_wr(1,2,0,"1: ��  4: 멷");  // 시   년�
  font_ke_wr(2,2,0,"2: 쫭  5: 땐");  // 분   월�
  font_ke_wr(3,2,0,"3: 점  6: 랭");  // 초   일�
}
     
void line_time_set_dis(void)
{
  font_ke_wr(2,0,0,"1:핤먬A, 2:핤먬B");  // 체널 1, 2
  font_ke_wr(3,0,0,"3:핤먬C, 4:핤먬D");  // 체널 3, 4
} 
 
void ch_dis(char ch)
{
  font_ke_wr(1,0,1,"�죭eч몹: ");  // 시간설정
  efont_8x16_wr(1,ch + 0x30); 
  font_ke_wr(1,11,1," 핤먬");     // 체널  
}
      
void line_dis(char nb)
{  
  char buf_sec, buf_hour, buf_min, buf;
 
 one_line_clr(0);
 glcd_xy(0, 1);
 efont_8x16_wr(0,nb + 0x30);   
 font_ke_wr(0,2,0,"ㅵ 쏿램 늫빨!");  // ?번 라인 감지 
 
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
  
 // 체널 라인 설정치 표시 
 glcd_xy(2,0);

 buf = (buf_hour & 0xf0);
 buf >>=4;
 efont_8x16_wr(0, buf + 0x30);
 efont_8x16_wr(0, (buf_hour & 0x0f) + 0x30);                     
 font_ke_wr(2,2,0,"��");    // 시   
          
 // 분 표시 
 buf = (buf_min & 0xf0);
 buf >>=4;
 efont_8x16_wr(0, buf + 0x30);
 efont_8x16_wr(0, (buf_min & 0x0f) + 0x30);   
 font_ke_wr(2,6,0,"쫭");    // 분            
                      
         
 // 초  표시 
 buf = (buf_sec & 0xf0);
 buf >>=4;
 efont_8x16_wr(0, buf + 0x30);
 efont_8x16_wr(0, (buf_sec & 0x0f) + 0x30);   
 font_ke_wr(2,10,0,"점");    // 초            
                                             
 font_ke_wr(2,12,0,"ч몹"); //설정 
}
        
void year_dis(void)
{
  rtc_rd_date();
       
     // 년도 표시 = 2008년 
     font_ke_wr(0,0,0,"20"); 
     buf = (rd.year & 0xf0);
     buf >>= 4;
     efont_8x16_wr(0, buf +'0');  //0  년 십 자리 
     
     buf = (rd.year & 0x0f);
     efont_8x16_wr(0, buf + '0'); //8  년 일자리 
     font_ke_wr(0,4,0,"멷 ");    // 년   
     
     // 월 표시
     buf = (rd.mon & 0xf0);
     buf >>= 4;  
     efont_8x16_wr(0, buf + 0x30);  // 월 십자리 
     
     buf = (rd.mon & 0x0f);
     efont_8x16_wr(0, buf + '0');  // 월 일자리 
     font_ke_wr(0,9,0,"땐 ");    // 월 
      
     // 일  표시
     buf = (rd.date & 0xf0);
     buf >>= 4;  
     efont_8x16_wr(0, buf + 0x30);  // 일  십자리 
     
     buf = (rd.date & 0x0f);
     efont_8x16_wr(0, buf + '0');  // 일  일자리 
     font_ke_wr(0,14,0,"랭");    // 일    
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
    font_ke_wr(1,0,1,"* 퐈 럼쓇 킕쒊 *");  // *키 입력 에러 *
    font_ke_wr(2,0,0," 럼쓇ㆁ뜬 점돿! ");  // 입력범위 초과!
    
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
  font_ke_wr(1,0,1,"㎕）ㅵ朞럼쓇�겤a"); //  비밀번호 입력해요.
  font_ke_wr(3,1,0,"㎕）ㅵ朞: ");       // ㅂ밀번호        
  
  // lcd_bak led on == 2008, 08, 22 = 우리 번개 태어난날 수정 = 테어난 기념으로
  lcd_bak_led_on;
  exio_out(exio_buf);
} 

void pass_ok_dis(void)
{
 font_ke_wr(1,0,1,"㎕）ㅵ朞 豈램 뻈");  // 비밀번호 확인됨�
 font_ke_wr(2,2,0,"퐈 묀퇬 �겤a!");  // 키 조작해요   

  key_bz(50);
  delay_ms(50);
  key_bz(50);
  
  m_sec = m_min = 0;  
}

void pass_no_dis(void)
{
 font_ke_wr(0,0,1,"㎕）ㅵ朞럼쓇덧욨"); // 비밀번호입력오류 �
 font_ke_wr(2,0,0,"봞�� 럼쓇�a쵡턠!");     // 다시입력하세요   
 
  key_bz(250);
}

void key_lock(void)
{
  all_clr();
  font_ke_wr(1,1,0,"* Key Lock ! *");  // 
  font_ke_wr(2,2,1,"퐈 럼쓇 쫱늏");    // 키 입력불가
  delay_ms(1200);  
}
          
void data_dis(char tg, uchar time)
{                   
  uchar buf;
  
  
   buf = (time & 0xf0);   
   buf >>= 4;
  
  efont_8x16_wr(tg, buf + 0x30);  // hi = 시 십자리 
  efont_8x16_wr(tg, (time & 0x0f) + '0');  // 시 일자리 
}    
             
void time_dn_cnt(unsigned char buf_hour, unsigned char buf_min, unsigned char buf_sec, char dis_nb)
{              
       if(buf_sec == 0) 
        {        
         // sec = 0 일 경우
          if(buf_min != 0) 
           {
            buf_sec = 0x59;
            
            buf_min--; 
            
            if((buf_min & 0x0f) > 0x09) buf_min -= 0x06; // hex to grcmol
            if((buf_min & 0xf0) > 0x90) buf_min -= 0x60;   
           }
          else
           {
             // min = 0일경우
             if(buf_hour != 0)
              {
                buf_min = 0x59;
                
                buf_hour--;   
                
                if((buf_hour & 0x0f) > 0x09) buf_hour -= 0x06; // hex to grcmol
                if((buf_hour & 0xf0) > 0x90) buf_hour -= 0x60;   
              }
             else
              {  
                // hour = 0 일 경우 = sec = min = hour
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
                  font_ke_wr(3,1,1,"ㅵ쏿램 묀죟 OFF");  // ?번라인 조명 끔
                  
                 // key_bz(250);
                 } 
                
                key_bz(250);  // 2008, 8,  22 번개 태어난 기념으로 끝냅니다. 돈이나 많이 벌었으면...
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
          font_ke_wr(3,0,1,"퇯킳");    // 잔여
       
          // 체널 라인 현재치 표시 
          glcd_xy(3,4);
          data_dis(1, buf_hour);    
          font_ke_wr(3,6,1,"��");    // 시   
          
          // 분 표시 
          data_dis(1, buf_min);
          font_ke_wr(3,10,1,"쫭");    // 분            
                      
          // 초  표시 
          data_dis(1, buf_sec); 
          font_ke_wr(3,14,1,"점");    // 초                             
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
     font_ke_wr(0,2,0,"ㅵ 쏿램 늫빨!");  // ?번 라인 감지 
    }
   else
    {  
     one_line_clr(0);
     glcd_xy(0, 0);
     efont_8x16_wr(1,main_dis_cnt + 0x30);   
     font_ke_wr(0,1,1,"ㅵ 쏿램 묀죟 ON");  // ?번라인 조명 킴 
    }   
}
        
void ch_chk_run(void)
{        
    // 체널 time count  
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
  
  
   // 시 표시     
   glcd_xy(1,1); //1
   buf = (rd.hour & 0x30);
   buf >>= 4;  
               
        // 12 hour mode am / pm chk
        if((buf & 0x02) == 0x02)// {efont_8x16_wr(0,'P'); efont_8x16_wr(0, 'M'); efont_8x16_wr(0, 0x20);} // 12 hour pm mode display
         { 
           // pm 오후 
           font_ke_wr(1,0,tg,"덧��");  // 오후 
           out_am_pm_flag = 1;
         }
        else //{efont_8x16_wr(0,'A'); efont_8x16_wr(0, 'M'); efont_8x16_wr(0, 0x20);} // 12 hour am mode display
         {  
           // am 오전
           font_ke_wr(1,0,tg,"덧멨"); // 오전   
           out_am_pm_flag = 0;
         }                                  
         
        // 시 십자리 표시
        efont_8x16_wr(tg,(buf & 0x01) + '0');     
     
     buf = (rd.hour & 0x0f);
     efont_8x16_wr(tg, buf + '0');  // 시 일자리 
     font_ke_wr(1,6,tg,"��");    // 시   
          
     // 분 표시 
      glcd_xy(1,8);
     buf = (rd.min & 0x70);
     buf >>= 4;  
     efont_8x16_wr(tg, buf + 0x30);  // 분    십자리 
     
     buf = (rd.min & 0x0f);
     efont_8x16_wr(tg, buf + '0');  // 분    일자리 
     font_ke_wr(1,10,tg,"쫭");    // 분            
                      
         
     // 초  표시 
      glcd_xy(1,12);
     buf = (rd.sec & 0x70);
     buf >>= 4;  
     efont_8x16_wr(tg, buf + 0x30);  // 초    십자리 
     
     buf = (rd.sec & 0x0f);
     efont_8x16_wr(tg, buf + '0');  // 초    일자리 
     font_ke_wr(1,14,tg,"점");    // 초            
//----------------------------------------------------------------     

// 제일 어려운 부분임 
if((no_set_am_flag == 1) && (no_set_pm_flag == 1)) ch_chk_run(); // 출퇴근시간 미 설정시 
else if(out_am_pm_flag == 0) //am, 오전, 출근
{ //if-1
  // 출근시간
  // 출근시간 센서 정지 시 체크 
  time_end_flag = 0;
  
  if(no_set_am_flag == 1) ch_chk_run(); // 출근시간 미 설정시 
  else if(((rd.hour & 0x1f) == set_out_hour) && (time_out_flag == 0)) // 출근시간 정지 시 체크 
   { //if-2 
     set_out_min  = ram_read(out_stop_min_r);       
     // 출근시간 센서 정지 분 체크 
     if(((rd.min & 0x7f) == set_out_min) && (time_chk_flag == 0)) //출근시간 센서 정지 분 체크
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
       
        font_ke_wr(3,0,1,"혟땎�죭e 럼뱻봞."); //출근시간 입니다
        time_chk_flag = 1;
      } //if-3 end
     else if(time_chk_flag == 1)
      { // if-4
        if((rd.hour & 0x1f) <= set_run_hour) // 동작 시 체크
         { //if-5
           if((rd.min & 0x7f) >= set_run_min)
            { //if-6
             font_ke_wr(3,0,1,"쵦п 덎혟 �s뱻봞"); //센서 검출합니다 �
             delay_ms(3000);
                   
             time_chk_flag = 0; 
             time_out_flag = 1;
             ch_chk_run();             
            } // if-6-end
           else  font_ke_wr(3,0,1,"혟땎�죭e 럼뱻봞."); //출근시간 입니다  
         } //if-5-end 
      } //if-4-end 
     else ch_chk_run();    
   } //if-2-end 
  else ch_chk_run();
} //if-1-end--------------------------------------------------------------------
else if(out_am_pm_flag == 1) // pm, 오후, 퇴근
{ //if-7    
  // 퇴근시간
  // 퇴근시간 센서 정지 시 체크  
  time_out_flag = 0;
  
  if(no_set_pm_flag == 1) ch_chk_run(); // 퇴근시간 미 설정시 
  else if(((rd.hour & 0x1f) == end_stop_time_set.hour) && (time_end_flag == 0)) // 퇴근시간 정지 시 체크 
   { //if-2
     end_stop_time_set.min  = ram_read(end_stop_min_r);       
     // 퇴근시간 센서 정지 분 체크 
     if(((rd.min & 0x7f) == end_stop_time_set.min) && (time_chk_flag == 0)) //퇴근시간 센서 정지 분 체크
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
        
        font_ke_wr(3,0,1,"�A땎�죭e 럼뱻봞."); //퇴근시간 입니다
        time_chk_flag = 1;
      } //if-3 end
     else if(time_chk_flag == 1)
      { // if-4
        if((rd.hour & 0x1f) <= end_run_time_set.hour) // 동작 시 체크
         { //if-5
           if((rd.min & 0x7f) >= end_run_time_set.min)
            { //if-6
             font_ke_wr(3,0,1,"쵦п 덎혟 �s뱻봞"); //센서 검출합니다 �
             delay_ms(3000);
                   
             time_chk_flag = 0; 
             time_end_flag = 1;
             ch_chk_run();             
            } // if-6-end
           else font_ke_wr(3,0,1,"�A땎�죭e 럼뱻봞."); //퇴근시간 입니다 
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
   