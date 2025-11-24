#include "USART.h"
#include "Segments.h"
#include "DisplayFunc.h"
#include "I2Cfunc.h"

void setup() {
  USART_Init(MYUBRR);
  i2c_setup();
  Print("TOP\n");
  segments_setup();
  Print("SETUP\n");
  Print("END\n");
}

int cnt = 0; //nr cate cifre modulo nr_displays apar
int nr[displays];

int poz = -1;

void loop() {
  unsigned char input=USART_Receive();
  if(input>='0' && input<='9'){
    nr[displays-cnt-1] = input - '0';
    cnt = (cnt + 1) % displays;
  }
  if(input==' '){
    input=USART_Receive();
    poz=input-'0';
  }
  if((input=='\n' || input==' ') && cnt){
    for(int i=0;i<=cnt-1;i++)
      nr[i] = nr[i+displays-cnt];
    for(int i=cnt;i<displays;i++)
      nr[i] = 0;
  }
  if(input=='\n'){
    if(poz<1)
      poz=1;
    display(nr, poz-1);
    cnt=0;
    poz=-1;
  }
}
