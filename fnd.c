
#ifndef _fnd_
#define _fnd_

char scan = 0; 


// fnd comm k type

const unsigned char fnd_font[] = 
{
   // 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   H,   L,   E,   o,   P,  F,
   0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x76,0x38,0x79,0x5c,0x73,0x71,

   // C,    d,    A,    u,    T,    r,   b, 
   0x39, 0x5e, 0x77, 0x1c, 0x44, 0x50, 0x7c 
};

            
// fnd maseg display             
#define O   0x0d   //o display
#define F   0x0f    // F display  
#define H   0x0a    // H   "
#define L   0x0b    // L   "
#define E   0x0c    // E   "
#define P   0x0e    // P   " 
#define C   16 //0x10    // C   "
#define D   0x11    // d   "
#define A   0x12    // A   "  
#define U   0x13    // u   "
#define T   0x14    // t   "
#define R   0x15    // r   "    
#define b   0x16    // b   "
#define BLK 0x00   // fnd blk display


#define fnd_out(val) PORTC = val



void fnd_dis(char data, char port_data1, char port_data2)                //모드 0~3, 6 에서의 FND 출력 
{ 
  
  scan++;
  if(scan > 2) scan = 1;
  
  switch(scan)
   {
     case 1:
            PORTF = 0x00;
     
            fnd_out(~fnd_font[data/10]); 
            
            PORTF = port_data1;
                                          
     break; 
     
    case 2:
            PORTF = 0x00;
            
            fnd_out(~fnd_font[data%10]);
            
            PORTF = port_data2;                              
     break;
        
   }
}

#endif
