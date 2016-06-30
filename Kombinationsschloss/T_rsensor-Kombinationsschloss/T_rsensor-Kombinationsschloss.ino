int i;
int nix=12;
int Pressed=nix;
bool Eingabe_aktiv;
int Kombination[]={1,4,2,2,3,5};
int Fortschritt=0;
int LEDTaste=2;
int LEDRichtig=12;
int LEDStatus=11;
int Inputs[]={3,4,5,6,7};
int Sensor_Open=13;
int AnzInp=sizeof(Inputs)/sizeof(int);
int AnzKomb=sizeof(Kombination)/sizeof(int);
bool opened=false;
int WarteZeit=10000;
int ZeitGew=0;
bool eingeschalten=false;

void setup() {
  // put your setup code here , to run once:
  Serial.begin(9600);
  for (i=0;i<AnzInp;i++){
    pinMode(Inputs[i], INPUT);
    digitalWrite(Inputs[i], HIGH);
  }
  pinMode(Sensor_Open, INPUT);
  digitalWrite(Sensor_Open, HIGH);

  pinMode(LEDTaste, OUTPUT);
  pinMode(LEDRichtig, OUTPUT);
  pinMode(LEDStatus, OUTPUT);
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
  if(digitalRead(Sensor_Open) && opened==false && eingeschalten){DoorOpened();}
  Eingabe_aktiv=false;
  //Prüfung, ob eine Taste gedrückt ist
  for (i=0;i<AnzInp;i++){
    if (digitalRead(Inputs[i])==LOW){
      if(Eingabe_aktiv==false && i!=Pressed-1){
        Pressed=i+1;
        digitalWrite(LEDTaste, HIGH);
        ButtonClick(Pressed);
      }
      Eingabe_aktiv=true;
    }
  }
  if (Eingabe_aktiv==false){Pressed=nix;digitalWrite(LEDTaste,LOW);}
  delay(100);
  if(opened==true){
    ZeitGew+=100;
    if (ZeitGew>=WarteZeit){
      Alarm();
    }
    }
}

void ButtonClick(int Nummer){
  if (Nummer==Kombination[Fortschritt]){
    //Richtige Taste
    Fortschritt++;
    if (Fortschritt==AnzKomb){
      //Öffnen oder so
      Kombination_richtig();
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

void Kombination_richtig(){
  Serial.print("Kombination Eingegeben");
  if (eingeschalten==false){
    eingeschalten=true;
    digitalWrite(LEDStatus, HIGH);
    Serial.print("Alarmanlage scharf");
    return;
  }
  if(eingeschalten==true){
    eingeschalten=false;
    opened=false;
    digitalWrite(LEDRichtig, LOW);
    digitalWrite(LEDStatus, LOW);
    Serial.print("Alarmanlage stumpf");
    return;
  }
}

void DoorOpened(){
  Serial.print("Sensor opened. Starte Countdown");
  opened=true;
  ZeitGew=0;
}

void Alarm(){
  Serial.print("Alarm!!");
  if(digitalRead(LEDRichtig)==HIGH){digitalWrite(LEDRichtig, LOW);}
  else {digitalWrite(LEDRichtig, HIGH);}
}

