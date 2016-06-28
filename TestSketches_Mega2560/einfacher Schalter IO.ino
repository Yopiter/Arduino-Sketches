void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT); //Sensor? XD
  pinMode(2,OUTPUT); //LED
  digitalWrite(3, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(3)==LOW){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2,LOW);
  }
}
