#include "TimerOne.h"
#include "Arduino.h"

//Tempo anterior para auxilio da função millis
long tempo_anterior = 0;
//Pino do relé para ligar e desligar a bomba
int porta_rele = 7;
//Pino boia para averiguar o nivel do reservatorio
int porta_boia = 10;
//Leds indicadores de status
int led_red = 8;
int led_green = 12;
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estado_rele = 0;
//variaveis gerais
int leitura = LOW;

void setup(){
  
  Serial.begin(9600);
  
  //Inicia o Timer1 e define a função de chamada da interrupção.
  //Timer1.initialize(1000000);
  //Timer1.attachInterrupt();
  
  //Define pinos para o rele como saida
  pinMode(porta_rele, OUTPUT); //7
  pinMode(led_red, OUTPUT);    //8
  pinMode(led_green, OUTPUT);   //12
  pinMode(porta_boia, INPUT); // 10
  
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele, HIGH);
  controladorLED();
}

void loop(){
  unsigned long tempo_atual = millis();     
  leitura = digitalRead(porta_boia);
    
  if(leitura != LOW){
    if(tempo_atual - tempo_anterior > intervalo()){
      tempo_anterior = tempo_atual;
      bomba();
    }
  }else{
    Serial.println("Interrupcao Ativa - Reservatorio Cheio");
    if(estado_rele == 0){
      desligarBomba();
      delay(10000);
    }
    tempo_anterior = tempo_atual;
  }
}

int intervalo(){
  
  int retorno = 0;
  
  if(estado_rele == 1){
    retorno = 100000;//1h desligada 
  }else{
    retorno = 16000;//15min ligada
  }
  
  return(retorno);
}

void bomba(){
  
  if(estado_rele == 1){
    ligarBomba();
  }else{
    desligarBomba();
  }
}

void ligarBomba(){
  
  //LIGAR BOMBA
  estado_rele = 0;
  controladorLED();
  digitalWrite(porta_rele, estado_rele);
  Serial.println("Bomba ligada!!");
}

void desligarBomba(){
  
  //DESLIGAR BOMBA
  estado_rele = 1;
  controladorLED();
  digitalWrite(porta_rele, estado_rele);
  Serial.println("Bomba desligada!!");
}

void controladorLED(){
  
  if(estado_rele == 1){
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, HIGH);
  }else{
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, HIGH);
  }
}

