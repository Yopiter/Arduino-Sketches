int i;
int nix=12;
int Pressed=nix;
bool aktiv;
int Kombination[]={1,4,2,2,3,5};
int Fortschritt=0;
int LEDTaste=2;
int LEDRichtig=12;
int Inputs[]={3,4,5,6,7};
int AnzInp=sizeof(Inputs)/sizeof(int);
int AnzKomb=sizeof(Kombination)/sizeof(int);

void setup() {
  // put your setup code here , to run once:
  Serial.begin(9600);
  for (i=0;i<AnzInp;i++){
    pinMode(Inputs[i], INPUT);
    digitalWrite(Inputs[i], HIGH);
  }

  pinMode(LEDTaste, OUTPUT);
  pinMode(LEDRichtig, OUTPUT);
  digitalWrite(LEDTaste, HIGH);
  delay(500);
  digitalWrite(LEDRichtig, HIGH);
  delay(500);
  digitalWrite(LEDTaste, LOW);
  delay(500);
  digitalWrite(LEDRichtig, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  aktiv=false;
  //Prüfung, ob eine Taste gedrückt ist
  for (i=0;i<AnzInp;i++){
    if (digitalRead(Inputs[i])==LOW){
      if(aktiv==false && i!=Pressed-1){
        Pressed=i+1;
        digitalWrite(LEDTaste, HIGH);
        ButtonClick(Pressed);
      }
      aktiv=true;
    }
  }
  if (aktiv==false){Pressed=nix;delay(100);digitalWrite(LEDTaste,LOW);}
}

void ButtonClick(int Nummer){
  Serial.print(Nummer);
  if (Nummer==Kombination[Fortschritt]){
    //Richtige Taste
    Fortschritt++;
    if (Fortschritt==AnzKomb){
      //Öffnen oder so
      AllesRichtig();
    }
    else{
    String Nachricht="Stelle ";
    Serial.print(Nachricht+Fortschritt);
    }
  }
  else{
    //Falsche Taste
   Fortschritt=0;
   if(Nummer==Kombination[0]){Fortschritt=1;}
  }
}

void AllesRichtig(){
  Serial.print("Kombination richtig");
  digitalWrite(LEDRichtig, HIGH);
  delay(3000);
  digitalWrite(LEDRichtig, LOW);
}

