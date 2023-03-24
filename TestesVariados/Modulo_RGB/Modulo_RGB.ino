int Red = 11;
int Green = 10;
int Blue = 9;
int reader = A0;
int valueReader = 0;;
char color = 'n';

void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  escolherCor();
  valueReader = analogRead(reader);
  valueReader = valueReader/4;

  if(color == 'r'){
    analogWrite(Red, valueReader);
  }else if(color == 'g'){
    analogWrite(Green, valueReader);
  }else if(color == 'b'){
    analogWrite(Blue, valueReader);
  }
  delay(100);
}

void escolherCor(){
  if(Serial.available() > 0){
    Serial.println("Digite a cor: b - Blue | r - Red | g - Green");
    color = Serial.read();
    Serial.println(color);
  }
}
