#include <Thread.h>
#include <ThreadController.h>

//Processos para controle do robo
ThreadController cpu;
Thread leituraSensor1;
Thread leituraSensor2;
Thread controle;

//Portas para os sensores
const int sensor1 = A0; // Sonar
const int sensor2 = A1; // InfraVermelho

int sensorValor1 = 0;
int sensorValor2 = 0;

float distancia = 0.0;

//Portas para os motores
int pwm1 = 5; 
int pwm2 = 6;
int pwm3 = 9;
int pwm4 = 10;


void lerSonar(){
  
}

void lerInfra(){
  
}

void controlarRobo(){

}

void setup(){
  Serial.begin(9600);
  
  
}

void loop(){
}
