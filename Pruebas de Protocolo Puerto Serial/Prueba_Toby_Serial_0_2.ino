//Test moverse en angulo teta respecto al frente del robot, definiendo frente como contrario a la antena de blue to
//Negativo = izquierda visto desde arriba
//Este codigo puede fallar ya que al momento de medir las funciones V(wi) el robot tenia poca bateria

#define ESTADO_FINAL 5
#define ESTADO_BASE_INDICE 0
const float pi = 3.141593;

int motor1_a = 3;
int motor1_b = 5;
int motor2_a = 6;
int motor2_b = 9;
int motor3_a = 10;
int motor3_b = 11;
int motor_a[3]={motor1_a, motor2_a, motor3_a};
int motor_b[3]={motor1_b, motor2_b, motor3_b};

float defase = 39.2255*(pi/180);//el motor 1 no esta alineado con el frente
float defase12=4*pi/3;    //defase entre ruedas 1 y 2, se espera 2pi/3
float defase13=2*pi/3;    //defase entre ruedas 1 y 3, se espera 4pi/3
float dir    = 0*(pi/180);//la direccion en que se movera
float velocidad=0;      //velocidad en pu (para la potencia de los motores)
float wm[3];              //velocidades angulares

byte tamano=5;
byte inByte[tamano];
byte estado=0;


float fwmax(float w1,float w2,float w3){
  if(w1<0){
    w1=-w1;
  }
  if(w2<0){   
    w2=-w2;
  }
  if(w3<0){
    w3=-w3;
  }
  if (w1<w2){
    w1=w2;
  }
  if (w1<w3){
    w1=w3;
  }
  return w1;
}

float voltaje(int motor,float w){  //solo para w positivo y motor = 1 2 o 3
  w=w*14.2419;      //wmaxima de los motores =14.2419
  switch (motor) {
    case 1:
    if(w>3.97){
      return 0.0789*w-0.125;
    }else{
      return 0.012565*w+0.15;
    }
      break;
      
    case 2:
    if(w>3.24){
      return 0.0741*w-0.0553;
    }else{
      return 0.0154*w+0.15;
    }
      break;
    
    case 3:
    if(w>3.97){
      return (0.0741*w-0.0553)*0.68;
    }else{
      return 0.0154*w+0.15;
    }
      break;
    
  }
}

void freno(int tiempo){
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, LOW);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, LOW);
  digitalWrite(motor3_a, LOW);
  digitalWrite(motor3_b, LOW);
  delay(tiempo);
}

void setEstateMotor(){
  int volt=0;    //variable auxiliar
  for (k=0,k<3,k++){
    if(wm[k]>0){
      volt=255*voltaje(k+1,wm[k]);
      digitalWrite(motor_b[k],LOW);
      analogWrite(motor_a[k],volt);
    }else{
      volt=255*voltaje(k+1,-1*wm[k]);
      digitalWrite(motor_a[k],LOW);
      analogWrite(motor_b[k],volt);
    }
  }
}

void setWmotor(){
  float wmax=0;  	//variable auxiliar
  wm[0]=sin(dir-defase);
  wm[1]=sin(dir-defase-defase12);
  wm[2]=sin(dir-defase-defase13);
  wmax=fwmax(wm[0],wm[1],wm[2]);
  wm[0]=velocidad*wm[0]/wmax;
  wm[1]=velocidad*wm[1]/wmax;
  wm[2]=velocidad*wm[2]/wmax;
}

// Setup
void setup() {
  // initialize the digital pin as an output.
  pinMode(motor1_a, OUTPUT);
  pinMode(motor1_b, OUTPUT);  
  pinMode(motor2_a, OUTPUT);  
  pinMode(motor2_b, OUTPUT);  
  pinMode(motor3_a, OUTPUT);  
  pinMode(motor3_b, OUTPUT);
  
  // set them to LOW for security
  digitalWrite(motor1_a, LOW);
  digitalWrite(motor1_b, LOW);
  digitalWrite(motor2_a, LOW);
  digitalWrite(motor2_b, LOW);
  digitalWrite(motor3_a, LOW);
  digitalWrite(motor3_b, LOW);
  
  //Inicia Conexión Serial
  Serial.begin(9600);
  tiempoant=1000;
  freno(tiempoant);
}

// Loop
void loop() {
  delay(10);
  setWmotor();
  setEstateMotor();
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
            dir = (float(inByte[1]+inByte[3]&0x01))*pi/255;
            //solucionar >>1
            velocidad = (float(inByte[2]+((inByte[3]&0x02) >> 1)))/255;
            break;
          default:
        }
      }
      estado = 0;
    }
  }
}
