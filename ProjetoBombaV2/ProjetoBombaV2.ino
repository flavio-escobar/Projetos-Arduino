#include <DS3231.h>
#include <Wire.h>
#include <String.h>
 
//Modulo RTC DS3231 ligado as portas A4 e A5 do Arduino 
DS3231 rtc(SDA, SCL);

const int led_enchendo = 11;
const int led_erro = 10;
const int rele_bomba = 3;
const int rele_sobrecarga = 2;
const int tempo_ligado = 15; //minutos
const int tempo_desligado = 60; //minutos

const int boia = A1;
 
void setup(){

  //Aciona o relogio  
  rtc.begin();

  pinMode(led_enchendo,OUTPUT);
  pinMode(led_erro,OUTPUT);
  pinMode(rele_bomba,OUTPUT);
  pinMode(rele_sobrecarga, INPUT);
  
  digitalWrite(rele_bomba, HIGH);
   
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  //rtc.setDOW(FRIDAY);      //Define o dia da semana
  //rtc.setTime(21, 24, 00);     //Define o horario
  //rtc.setDate(15, 9, 2016);   //Define o dia, mes e ano
   
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);

  Serial.begin(9600);
 
}

int hora = 0;
int minuto = 0;
int segundo = 0;
int hora_aux = 0;
int min_aux = 0;
int sec_aux = 0;
int estado = 1; // inicialmente ligado
int result_sobrecarga = 0;
int result_boia = 0;
boolean check_time = false;
boolean check_adc = true;
boolean check_state = true;
Time t;

void loop(){
  
  result_sobrecarga = digitalRead(rele_sobrecarga);
  result_boia = analogRead(boia);
  
  //if(result_sobrecarga == HIGH){ //sem sobrecarga
    //digitalWrite(led_erro, LOW);
    if(result_boia > 1){  //nivel reservatorio vazio
      //Serial.println(result_boia);
      
      //Serial.println("----------------------------------");
      //Serial.println("Horario Atual");
      //Serial.println(rtc.getTimeStr());
      //Serial.println("----------------------------------");
      t = rtc.getTime();
      hora = t.hour;
      minuto = t.min;
      segundo = t.sec;
      
      if(estado == 1){
        if(check_adc == true){
          //Serial.println("teste adc tempo");
          adcTempo(tempo_ligado);
          //Mostra as informações no Serial Monitor
          Serial.print("Hora Inicial: ");
          Serial.print(rtc.getTimeStr());
          Serial.println(" ");
          Serial.print("Hora de Termino: ");
          Serial.print(hora_aux);
          Serial.print(":");
          Serial.print(min_aux);
          Serial.print(":");
          Serial.println(sec_aux);
          Serial.println("BOMBA LIGADA!!!");
        }
        if(hora != hora_aux || minuto != min_aux || segundo != sec_aux){
          /*Serial.print(minuto);
          Serial.print(":");
          Serial.println(segundo);
          Serial.print(min_aux);
          Serial.print(":");
          Serial.println(sec_aux);
          Serial.println("----------------");*/
          encher();
        }else{
          Serial.println("teste estados");
          estado = 0;
          check_adc = true;
        }
      }
      
      if(estado == 0){
        if(check_adc == true){
          //Serial.println("teste adc tempo");
          adcTempo(tempo_desligado);
          Serial.print("Hora Inicial: ");
          Serial.print(rtc.getTimeStr());
          Serial.println(" ");
          Serial.print("Hora de Termino: ");
          Serial.print(hora_aux);
          Serial.print(":");
          Serial.print(min_aux);
          Serial.print(":");
          Serial.println(sec_aux);
          Serial.println("BOMBA DESLIGADA!!!");
        }
        if(hora != hora_aux || minuto != min_aux || segundo != sec_aux){
          /*Serial.print(minuto);
          Serial.print(":");
          Serial.println(segundo);
          Serial.print(min_aux);
          Serial.print(":");
          Serial.println(sec_aux);
          Serial.println("----------------");*/
          desligarBomba();
        }else{
          estado = 1;
          check_adc = true;
        }
      }
    }else{
      desligarBomba();
      Serial.println("boia LOW");
    }
  //}else{
    //erro();
    //Serial.println("erro rele");
  //}

  //Mostra as informações no Serial Monitor
  //Serial.print("Hora : ");
  //Serial.print(rtc.getTimeStr());
  //Serial.print(" ");
  //Serial.print("Data : ");
  //Serial.print(rtc.getDateStr(FORMAT_SHORT));
  //Serial.print(" ");
  //Serial.println(rtc.getDOWStr(FORMAT_SHORT));
   
  //Aguarda 1 segundo e repete o processo
  delay (1000);
}

void adcTempo(int tempo){
  //Serial.println("teste adc pronfundo");
  t = rtc.getTime();
  hora = t.hour;
  minuto = t.min;
  segundo = t.sec;

  if(minuto + tempo > 60){
    min_aux = (minuto + tempo) - 60;
    hora_aux = hora + 1;
  }else{
    min_aux = minuto + tempo;  
    hora_aux = hora;
  }
  sec_aux = segundo;
  check_adc = false;
}

void erro(){
    digitalWrite(led_erro, HIGH);
    digitalWrite(rele_bomba, HIGH);
    digitalWrite(led_enchendo, LOW);
}

void desligarBomba(){
  digitalWrite(led_erro, HIGH);
  digitalWrite(rele_bomba, HIGH);
  digitalWrite(led_enchendo, LOW);
}

void encher(){
    digitalWrite(led_erro, LOW);
    digitalWrite(rele_bomba, LOW);
    digitalWrite(led_enchendo, HIGH);
}
