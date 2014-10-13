/*
    LibreToby.h
    Libreria para controlar al robot Toby
    Creada por Jose Soto, Fecha 12/10/2014
*/
#ifndef LibreToby_h
#define LibreToby_h
#include "arduino.h"
class Toby {
    public:
        Toby(int pinA[3],int pinB[3]);
        void setVMotor();
        void setWMotor();
        void setSpd(float spd);
        //pines A son para girar con el reloj pines B contrario
        void freno(int ftime);
    private:
        int _pinA[3];
        int _pinB[3];
        float _defase[3];
        /*el motor 1 no esta alineado con el frente por eso tiene un defase
        el valor _defase[k-1] es el defase de la rueda k respecto al frente definido en el .cpp
        */
        float _wm[3];
        float _dir;
        float _spd;
};
#endif
