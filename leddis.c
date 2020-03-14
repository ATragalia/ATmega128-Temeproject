#ifndef _leddis_
#define _leddis_


char led_dis1[13] = {0,};
char led_dis2[13] = {0,};
int led_add[2][5] = {0,};
int i, k, cnt = 0;

void led_dis();

void led_init(){
    for(k=1 ; k<13 ; k++) {
        led_dis1[k] = 0;
        led_dis2[k] = 0;
    }
}


void led_change(char cnt1, char cnt2){
    led_init();
    if(cnt1 > 61){
    //printf("1");
        led_dis1[6] = 1;
        led_dis1[7] = 1;
        led_dis1[12] = 1;
        led_dis2[1] = 1;
        led_dis2[6] = 1;
        led_dis2[7] = 1;
        led_dis2[11] = 1;
        if(cnt1 > 63){ 
            led_dis1[3] = 1;
            led_dis1[4] = 1;
            led_dis();
        }
        else {
            led_dis1[2] = 1;
            led_dis();
        }
    }
    else if (cnt1 > 0){
        led_dis1[1] = 1;
        led_dis1[6] = 1;
        led_dis1[11] = 1;
        led_dis2[1] = 1;
        led_dis2[5] = 1;
        led_dis2[7] = 1;
        led_dis2[11] = 1;
        if(cnt1 > 2){
            led_dis1[9] = 1;
            led_dis1[10] = 1;
            led_dis();
        }
        else {
            led_dis1[8] = 1;
            led_dis();
        }
    }
    if(cnt2 > 61){
        led_dis2[6] = 1;
        led_dis2[7] = 1;        
        led_dis2[12] = 1;
        led_dis1[1] = 1;
        led_dis1[6] = 1;
        led_dis1[7] = 1;
        led_dis1[11] = 1;
        if(cnt2 > 63){
            led_dis2[3] = 1;
            led_dis2[4] = 1;
            led_dis();
        }
        else {
            led_dis2[2] = 1;
            led_dis();
        }
    }
    else if (cnt2 > 0){
        led_dis1[1] = 1;
        led_dis1[5] = 1;
        led_dis1[7] = 1;
        led_dis1[11] = 1;
        led_dis2[6] = 1;
        led_dis2[1] = 1;
        led_dis2[11] = 1;
        if(cnt2 > 2){
            led_dis2[9] = 1;
            led_dis2[10] = 1;
            led_dis();
        }
        else {
            led_dis2[8] = 1;
            led_dis();
        }
    }
}

void arr_init(){
    for(i = 0;i<2;i++){
        for(k = 0;k<5;k++){
            led_add[i][k] = 0;
        }
    }
}


void led_ad(){
    arr_init();
    for(i = 1; i<13;i++){
        if(led_dis1[i] == 1) {
            led_add[0][cnt] = i;
            cnt++;
        }
    }
    cnt = 0;
    for(i = 1; i<13;i++){
        if(led_dis2[i] == 1) {
            led_add[1][cnt] = i;
            cnt++;
        }
    }
    cnt = 0;
        
}

void led_dis(){
     for(i = 0; i<5; i++){
        if(i == 0){
            PORTA.7 = 1;
            PORTA.7 = 0;
        }
        PORTD = led_add[0][i] + (led_add[1][i]*16); 
     }
}
  
#endif   
        