/*
    LibToby.h
    Libreria para controlar al robot Toby
    Creada por Jose Soto, Fecha 12/10/2014
    Ultima modificacion 08/01/2015
*/
#ifndef LibToby_h
#define LibToby_h
#include <Arduino.h>
class Toby {
    public:
        Toby(int pinA[3],int pinB[3]);
        void freno(int ftime);
        void setVMotor();
        void setWMotor();
        void setSpd(float spd);
        void setDir(float dir);
        void setMod(int mod);
        void setRot(int rot);
        //pines A son para girar con el reloj pines B contrario
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
        int _mod;
        int _rot;
};
#endif
