#include <Arduino.h>
#include "Segments.h"
#include "USART.h"
#include "I2Cfunc.h"

void segments_setup(){
  i2c_send(0, 0x09, 0xFF); //decode mode
  Print("OK1\n");
  i2c_send(0, 0x0A, 0x0F); //brightness=max
  Print("OK2\n");
  i2c_send(0, 0x0B, 0x03); //scan limit: display digits 0-3
  Print("OK3\n");
  i2c_send(0, 0x0C, 0x01);  //shutdown: normal operation
  Print("OK4\n");
  segments_reset();
}

void segments_reset(){
  i2c_send(0, 0x01, 0);
  i2c_send(0, 0x02, 0);
  i2c_send(0, 0x03, 0);
  i2c_send(0, 0x04, 0);
}