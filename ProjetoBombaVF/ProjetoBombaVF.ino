const int led_enchendo = 13;
const int led_nivelMin = 12;
const int led_nivelMax = 11;
const int led_erro = 10;
const int rele_bomba = 3;
const int rele_sobrecarga = 2;

const int boia = 5;
const int bMax = 6;
const int bMin = 7;

void setup() {

  pinMode(bMax,INPUT);
  pinMode(bMin,INPUT);
  pinMode(rele_sobrecarga, INPUT);
  
  pinMode(led_enchendo,OUTPUT);
  pinMode(led_nivelMin,OUTPUT);
  pinMode(led_nivelMax,OUTPUT);
  pinMode(led_erro,OUTPUT);
  pinMode(rele_bomba,OUTPUT);
  
  digitalWrite(rele_bomba, HIGH);
  
  Serial.begin(9600);

}

int resultMax = 0;
int resultMin = 0;
int result_sobrecarga = 0;
int result_boia = 0;
int estado = 0;

void loop(){

  result_sobrecarga = digitalRead(rele_sobrecarga);
  result_boia = digitalRead(boia);
  resultMax = digitalRead(bMax);
  resultMin = digitalRead(bMin);
  
  Serial.print(resultMax);
  Serial.print("-");
  Serial.println(resultMin);
  
  if(result_sobrecarga == HIGH){ //sem sobrecarga
    digitalWrite(led_erro, LOW);
    if(resultMax == 1 && resultMin == 0){ // boia max sim, boia min nao == erro
      erro();
      Serial.print("Erro Boias");
    }else{
      
      if(result_boia == HIGH){  //nivel reservatorio vazio
        //Serial.println(result_boia);
        //poço nivel max
        if(resultMax==1 && resultMin==1){
          digitalWrite(led_nivelMax, HIGH);
          digitalWrite(led_nivelMin, HIGH);
          encher();
          estado = 1;  
        }
        //poço vazio
        if(resultMax==0 && resultMin==0){
          digitalWrite(led_nivelMax, LOW);
          digitalWrite(led_nivelMin, LOW);
          desligarBomba();
          estado = 2;
        }
        //poço nivel minimo
        if (resultMax == 0 && resultMin == 1){
          if(estado == 0){
            digitalWrite(led_nivelMax, LOW);
            digitalWrite(led_nivelMin, HIGH);
          }
          if(estado == 1){
            digitalWrite(led_nivelMax, LOW);
            digitalWrite(led_nivelMin, HIGH);
            encher();
          }
          if(estado == 2){
            digitalWrite(led_nivelMax, LOW);
            digitalWrite(led_nivelMin, HIGH);
            desligarBomba();
          }
      }
      }else{
        desligarBomba();
        Serial.println("boia LOW");
      }
    }
  }else{
    erro();
    Serial.println("erro rele");
  }
}

void erro(){
    digitalWrite(led_erro, HIGH);
    digitalWrite(led_nivelMax, LOW);
    digitalWrite(led_nivelMin, LOW);
    digitalWrite(rele_bomba, HIGH);
    digitalWrite(led_enchendo, LOW);
}

void desligarBomba(){
  digitalWrite(rele_bomba, HIGH);
  digitalWrite(led_enchendo, LOW);
}

void encher(){
  //while(result_boia == HIGH){
  //  result_boia = digitalRead(boia);
    digitalWrite(rele_bomba, LOW);
    digitalWrite(led_enchendo, HIGH);
  //}  
}

