#ifndef Toby_H
#define Toby_H

#include "Arduino.h"




typedef union{
			byte Val_Byte[2];
			word Val_Word;
		}DATA;

class Protocolo
{
  public:
  void wInData(word Dato,byte data_salida[]);
  byte bOutData(word *Dato, byte data_entrada[]);
};

class Toby
{
  public:
  void test();
};


#endif

