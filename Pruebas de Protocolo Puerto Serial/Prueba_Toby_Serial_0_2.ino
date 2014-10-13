//Test moverse en angulo teta respecto al frente del robot, definiendo frente como contrario a la antena de blue to
//Negativo = izquierda visto desde arriba
//Este codigo puede fallar ya que al momento de medir las funciones V(wi) el robot tenia poca bateria
#include <LibreToby.h>
#define ESTADO_FINAL 5
#define ESTADO_BASE_INDICE 0
float pi = 3.141593;
/*
  int motor1_a = 3;
  int motor1_b = 5;
  int motor2_a = 6;
  int motor2_b = 9;
  int motor3_a = 10;
  int motor3_b = 11;
*/
int motor_a[3]={3,6,10};
int motor_b[3]={5,9,11};

byte tamano=5;
byte inByte[tamano];
byte estado=0;

// Setup
void setup() {
  Toby toby(motor_a,motor_b);
  //Inicia Conexión Serial
  Serial.begin(9600);
  toby.freno(1000);
}

// Loop
void loop() {
  delay(10);
  toby.setWMotor();
  toby.setVMotor();
}
//actualiza direccion y velocidad del robot
void serialEvent(){
  if (Serial.available()>0){
    byte ch = Serial.read();
    if (estado<ESTADO_FINAL){
      if(ch == 0xFF){
        estado = 0;
      }else{
        inByte[estado - ESTADO_BASE_INDICE] = ch;
        estado++;
      }
    }else{ // !(estado<ESTADO_FINAL)
      if(ch == 0xFF){
        switch inByte[0] {
          case 0x00:
            toby.setDir((float(inByte[1]+inByte[3]&0x01))*pi/255);
            toby.setSpd((float(inByte[2]+((inByte[3]&0x02) >> 1)))/255);
            break;
          default:
        }
      }
      estado = 0;
    }
  }
}
