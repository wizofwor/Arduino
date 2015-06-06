/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #01 - Led Yakip Sondurmece
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
/////////////////////////////////////////////////////////////////////////

void setup(){
  pinMode(10, OUTPUT); // 10 numaral pininin yönü çıkış olarak ayarlandı.
  }

void loop(){
  digitalWrite(10,HIGH);     // LED yansın
  delay(250);                // 250 ms bekleyelim
  digitalWrite(10,LOW);      // LED'i sondurelim
  delay(1000);               // 100 ms = 1 sn bekleyelim
  }
