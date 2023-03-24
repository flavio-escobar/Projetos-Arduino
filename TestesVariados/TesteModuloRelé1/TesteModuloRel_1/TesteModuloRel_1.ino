#include "TimerOne.h"
#include "Arduino.h"

//Porta ligada ao pino IN do modulo
int porta_rele = 7;
//Porta ligada ao botao
int porta_botao = 2;
//Leds indicadores de status
int led_red = 8;
int led_blue = 12;
//Armazena o estado do rele - 0 (LOW) ou 1 (HIGH)
int estado_rele = 1;
//Armazena o valor lido dos botoes
int leitura = LOW;
int inversao = 1;
  
void setup(){
  
  Serial.begin(9600);
  
  //Inicia o Timer1 e define a função de chamada da interrupção.
  //Timer1.initialize(1000000);
  //Timer1.attachInterrupt();
  
  //Define pinos para o rele como saida
  pinMode(porta_rele, OUTPUT); //7
  pinMode(led_red, OUTPUT);    //8
  pinMode(led_blue, OUTPUT);   //12
  //Define pinos dos botoes como entrada
  pinMode(porta_botao, INPUT); //2
  
  //Estado inicial dos reles - desligados
  digitalWrite(porta_rele, HIGH);
  
}
 
void loop(){
  
  leitura = digitalRead(porta_botao);
  
  Serial.println(leitura);
  
  if(leitura == HIGH){
    while(leitura == HIGH){
      delay(100);
      Serial.println("teste laco");
      leitura = digitalRead(porta_botao);
    }
    Serial.println(inversao);
    inversao = !inversao;
    Serial.print("Inversao:");
    Serial.println(inversao);
  }
  if(inversao == 0){
    Serial.println("Teste mainBomba");
    leitura = digitalRead(porta_botao);
    mainBomba();
  }
  
  delay(100);
}

void mainBomba(){
  int cont;
  
  //LIGAR BOMBA
  estado_rele = 0;
  controladorLED(estado_rele);
  digitalWrite(porta_rele, estado_rele);
  Serial.println("Bomba ligada!!");
  delay(900000);//15min
  //delay(4000);//10sec teste
    
  leitura = digitalRead(porta_botao);
  
  if(leitura != 1){
    //DESLIGAR BOMBA
    estado_rele = 1;
    controladorLED(estado_rele);
    digitalWrite(porta_rele, estado_rele);
    Serial.println("Bomba desligada!!");
    delay(3600000);//1h
    //delay(4000);//10sec teste
  }  
  cont = cont + 1;
  Serial.println("Contador: ");
  Serial.print(cont);
}

void controladorLED(int estado){
  
  if(estado == 1){
    digitalWrite(led_blue, LOW);
    digitalWrite(led_red, HIGH);
  }else{
    digitalWrite(led_red, LOW);
    digitalWrite(led_blue, HIGH);
  }
}

