#include <Arduino.h>
#include "DisplayFunc.h"
#include "I2Cfunc.h"
#include "Segments.h"

void display(int nr[], int poz){
  segments_reset();
  for(int i=0;i<displays;i++)
    i2c_send(0, poz+i+1, nr[i]);
}