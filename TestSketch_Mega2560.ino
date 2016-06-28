int i;
int nix=12;
int Pressed=nix;
bool aktiv;
int Kombination[]={1,2,3,4};
int Fortschritt=0;
int LEDTaste=1;
int LEDRichtig=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDTaste,OUTPUT);
  pinMode(LEDRichtig, OUTPUT);
  for (i=2;i<12;i++){
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  aktiv=false;
  //Prüfung, ob eine Taste gedrückt ist
  for (i=2;i<12;i++){
    if (digitalRead(i)==LOW && aktiv==false && i!=Pressed+2 ){
      aktiv=true;
      Pressed=i-2;
      ButtonClick(Pressed);
      digitalWrite(LEDTaste, HIGH);
    }
  }
  if (aktiv==false){Pressed=nix;delay(100);digitalWrite(LEDTaste,LOW);}
}

void ButtonClick(int Nummer){
  if (Nummer==Kombination[Fortschritt]){
    //Richtige Taste
    if (Fortschritt==sizeof(Kombination)){
      //Öffnen oder so
      AllesRichtig();
    }
    else{
    Fortschritt++;
    }
  }
  else{
    //Falsche Taste
   Fortschritt=0; 
  }
}

void AllesRichtig(){
  //Aktion nach Eingabe der richtigen Kombination
  digitalWrite(LEDRichtig, HIGH);
  delay(1000);
  digitalWrite(LEDRichtig, LOW);
}

