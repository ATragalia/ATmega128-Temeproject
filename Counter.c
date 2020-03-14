#ifndef _Counter_
#define _Counter_

char cnt1 = 121;
char cnt2 = 0;


#include "leddis.c"


void Counter_add() 
{
        if(cnt1 > 0){
            cnt1--;
            if(cnt1 >60){
                printf("Green  %d sec", cnt1-60);
                printf("\r");
            }
            if(cnt1 <= 60){
                printf("Red  %d sec", 120+cnt1);
                printf("\r");
            }
            if(cnt1 == 0)cnt2 = 121;
            led_change(cnt1, cnt2);
            led_ad();
            return;
        }
        if(cnt2 > 0){
            cnt2--;
            printf("Red  %d sec", cnt2);
            printf("\r");
            if(cnt2 == 0)cnt1 = 121;
            led_change(cnt1, cnt2);
            led_ad();
            return;
        }
              
}

#endif 