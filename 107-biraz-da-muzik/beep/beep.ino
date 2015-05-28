/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #07 - Beep
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
/////////////////////////////////////////////////////////////////////////

const int pmwValue = 200; //1 ile 255 arasnda bir deger verebilirsiniz. 
  
void setup()  { 
  // dijital pin 9'u cikis olarak ayarlayalim
  pinMode(9, OUTPUT);
  // 3 kisa beep
  beep(100);
  beep(100);
  beep(100);
} 

void loop()  {
  //bir saniye bekleyelim
  delay(1000);
  //10 uzun beep
  for(int i=0; i<10; i++) {
    beep(200);
  } 
}

/**
 * Buzzer'i calistiran fonksiyon
 * Verilen sure kadar sinyal gonderiyor
*/
void beep(int sure){
  analogWrite(9, pmwValue);   
  delay(sure);          
  analogWrite(9, 0);      
  delay(sure);           
}  
