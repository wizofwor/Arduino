/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #01 - Led Flash
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
/////////////////////////////////////////////////////////////////////////

void setup(){
  // 2-6 arasndaki pinleri cikisa yonlendirelim
  for(int i=2;i<=6;i++) 
    pinMode(i,OUTPUT);
}

void loop(){
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
  
  
 
