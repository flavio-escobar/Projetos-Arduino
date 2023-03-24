int led_red = 12;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_red, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led_red, HIGH);
  delay(1000);
  digitalWrite(led_red, LOW);
}
