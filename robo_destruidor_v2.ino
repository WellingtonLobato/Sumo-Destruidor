#include <Thread.h>
#include <ThreadController.h>

//Processos para controle do robo
ThreadController cpu;
Thread leituraSensor1;
Thread leituraSensor2;
Thread controle;

//Portas para os sensores
const int sensor1 = A0; // Sonar
const int sensor2 = A2; // InfraVermelho

int sensorValor1 = 0;
int sensorValor2 = 0;
float distancia = 0.0;

#define BRANCO 150

//Portas para os motores
int pwm1 = 5; 
int pwm2 = 6;
int pwm3 = 9;
int pwm4 = 10;

//Funcoes
void lerSonar(){
  sensorValor1 = analogRead(sensor1);
  distancia = (sensorValor1 / 2) * 2.4;
  Serial.print("Valor em cm: ");
  Serial.print(distancia);
  Serial.println();  
}

void lerInfra(){
  sensorValor2 = analogRead(sensor2);
  Serial.print("Valor do INFRA: ");
  Serial.print(sensorValor2);
  Serial.println();  
  if(sensorValor2 <= BRANCO){
    //Pra tras
    Serial.println("Motor indo pra tras!!!");
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,50); //1
    analogWrite(pwm4,50); //1
    
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,75); //1
    analogWrite(pwm4,75); //1
    
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,100); //1
    analogWrite(pwm4,100); //1
    
    delay(200);
    
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,0); //0
    analogWrite(pwm4,100); //1    
    
  }
}

void controlarRobo(){
  sensorValor2 = analogRead(sensor2);
  if(distancia <= 25 && sensorValor2 > BRANCO){
    //Pra frente
    Serial.println("Motor indo pra frente!!!");
    analogWrite(pwm1,100); //1
    analogWrite(pwm2,100); //0
    analogWrite(pwm3,0); //1
    analogWrite(pwm4,0); //0
  }
  else if(sensorValor2 <= BRANCO){
    //Pra tras
    Serial.println("Motor indo pra tras!!!");
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,50); //1
    analogWrite(pwm4,50); //1
    
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,75); //1
    analogWrite(pwm4,75); //1
    
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,100); //1
    analogWrite(pwm4,100); //1
    
    delay(200);

    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,0); //0
    analogWrite(pwm4,100); //1    
  }
  else{
    Serial.println("Motor parado");
    analogWrite(pwm1,0); //0
    analogWrite(pwm2,0); //0
    analogWrite(pwm3,0); //0
    analogWrite(pwm4,0); //0
  }
}


//Funcoes principais
void setup(){
  Serial.begin(9600);
  
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
  
  leituraSensor1.setInterval(300);
  leituraSensor1.onRun(lerSonar);

  leituraSensor2.setInterval(500);
  leituraSensor2.onRun(lerInfra);  
  
  controle.setInterval(200);
  controle.onRun(controlarRobo);
  
  cpu.add(&leituraSensor1);
  cpu.add(&leituraSensor2);
  cpu.add(&controle);
}

void loop(){
  cpu.run();
}
