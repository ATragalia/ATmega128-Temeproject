#ifndef _Clock_
#define _Clock_


int hour = 0, min = 0, sec = 0;
int Time_loop = 0;

void clock_use(){
    delay_ms(1);
    Time_loop++;
    if(Time_loop == 500){
        Time_loop = 0;
        sec++;
        
        if(sec == 60){
            sec = 0;
            min++;
            
            if(min == 60){
                hour++;
                if(hour == 24) hour = 0;
            }
        }
    }
}



#endif 