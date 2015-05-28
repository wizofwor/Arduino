/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #01 - Button
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
/////////////////////////////////////////////////////////////////////////

void setup(){
  
  // Ledleri bagladigimiz 2-6 arasindaki pinleri
  // cikisa yonlendirelim
  for(int i=2;i<=6;i++) 
    pinMode(i,OUTPUT);
    
  // Butonu bagladigimiz 8 numarali pini ise
  // girise yonlendirelim ve dahili pull_up
  // direncini devreye alalim
  pinMode(8,INPUT_PULLUP);
}

void loop(){
  int buttonState;
  
  // Butonu kontrol edelim
  buttonState = digitalRead(8);
  // Eger buton basiliysa ledleri yakalim
  if (buttonState == LOW)
    doFlash();
}

void doFlash() {
    int i;
    for (i=2;i<=6;i++) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW); 
  }   
    for (i=6;i>=2;i--) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW); 
  }
}
