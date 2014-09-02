//Test moverse en angulo teta respecto al frente del robot, definiendo frente como contrario a la antena de blue to
//Negativo = izquierda visto desde arriba
//Este codigo puede fallar ya que al momento de medir las funciones V(wi) el robot tenia poca bateria

int motor1_a = 3;
int motor1_b = 5;
int motor2_a = 6;
int motor2_b = 9;
int motor3_a = 10;
int motor3_b = 11;

float pi=3.141593;
float defase = 39.2255*(pi/180);//el motor 1 no esta alineado con el frente
float defase12=4*pi/3;    //defase entre ruedas 1 y 2, se espera 2pi/3
float defase13=2*pi/3;    //defase entre ruedas 1 y 3, se espera 4pi/3
float dir    = 10*(pi/180);//la direccion en que se movera
float velocidad=1;      //velocidad en pu (para la potencia de los motores)
float wm1=0;              //velocidades angulares
float wm2=0;              //    ||
float wm3=0;              //    ||
float wmax=0;  	//variable auxiliar
int volt=0;    		//variable auxiliar
int contador=1;
unsigned long tiempo=0;
unsigned long tiempoant=0;

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
  wm1=sin(dir-defase);
  wm2=sin(dir-defase-defase12);
  wm3=sin(dir-defase-defase13);
  wmax=fwmax(wm1,wm2,wm3);
  wm1=velocidad*wm1/wmax;
  wm2=velocidad*wm2/wmax;
  wm3=velocidad*wm3/wmax;
  
  if(wm1>0){
    volt=255*voltaje(1,wm1);
    digitalWrite(motor1_b,LOW);
    analogWrite(motor1_a,volt);
  }else{
    volt=255*voltaje(1,-1*wm1);
    digitalWrite(motor1_a,LOW);
    analogWrite(motor1_b,volt);
  }
  
  if(wm2>0){
    volt=255*voltaje(2,wm2);
    digitalWrite(motor2_b,LOW);
    analogWrite(motor2_a,volt);
  }else{
    volt=255*voltaje(2,-1*wm2);
    digitalWrite(motor2_a,LOW);
    analogWrite(motor2_b,volt);
  }
  
  if(wm3>0){
    volt=255*voltaje(3,wm3);
    digitalWrite(motor3_b,LOW);
    analogWrite(motor3_a,volt);
  }else{
    volt=255*voltaje(3,-1*wm3);
    digitalWrite(motor3_a,LOW);
    analogWrite(motor3_b,volt);
  }  

  Serial.print("\nLos motores tienen w: ");
  Serial.print(wm1);
  Serial.print("  ");
  Serial.print(wm2);
  Serial.print("  ");
  Serial.print(wm3);

  //Hacer N-agono(N=4) en T=15000 tiempo en ms
  tiempo=millis();
  if(tiempo-tiempoant > 8000/4){
    tiempoant=tiempo;
    dir+=(2*pi)/4;
    freno(150);
  }
}

