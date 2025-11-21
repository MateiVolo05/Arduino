#include <Arduino.h>
#include "Mode.h"
#include "USART.h"
#include "Segments.h"

int cnt = 0; //nr cate cifre modulo nr_displays apar
int nr[displays];

int poz = -1;
int disp = -1;

void modeA(unsigned char input){
  if(input>='0' && input<='9'){
    nr[displays-cnt-1] = input - '0';
    cnt = (cnt + 1) % displays;
  }
  if(input=='\n' && cnt){
    for(int i=0;i<=cnt-1;i++)
      nr[i] = nr[i+displays-cnt];
    for(int i=cnt;i<displays;i++)
      nr[i] = 0;
  }
  if(input=='\n'){
    for(unsigned int i=0;i<displays;i++)
      i2c(0, i+1, nr[i]);
    cnt = 0;
  }
}

void modeB(unsigned char input){ 
  if(input>='0' && input<='9'){
    if(disp==-1)
      disp = input - '0';
    else
      if(poz==-1)
        if(input>='1' && input<='0'+displays)
          poz=input - '0';
        else
          poz = displays;
  }
  if(input=='\n'){
    i2c(0, poz, disp);
    poz=disp=-1;
  }
}