int bMax = 7;
int bMin = 6;
int ledMax = 12;
int ledMin = 11;

void setup() {

  pinMode(bMax,INPUT);
  pinMode(bMin,INPUT);
  pinMode(ledMax,OUTPUT);
  pinMode(ledMin,OUTPUT);
  Serial.begin(9600);
}

int resultMAX = 0;
int resultMIN = 0;

void loop() {

  resultMAX = digitalRead(bMax);
  resultMIN = digitalRead(bMin);
  
  Serial.print(resultMAX);
  Serial.print("/");
  Serial.println(resultMIN);
  
  if(resultMAX == HIGH){
    digitalWrite(ledMax, HIGH);
  }else{
    digitalWrite(ledMax, LOW);
  }
  if(resultMIN == HIGH){
    digitalWrite(ledMin, HIGH);
  }else{
    digitalWrite(ledMin, LOW);
  }
}
