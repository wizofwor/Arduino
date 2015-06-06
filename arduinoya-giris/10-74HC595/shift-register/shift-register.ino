/////////////////////////////////////////////////////////////////////////
// 74CH595 kod ornegi
// 
// wizofwor - Mayis 2015
// https://github.com/wizofwor/arduino
//
/////////////////////////////////////////////////////////////////////////

/**
  * 74CH595'i bagladigimiz pinleri degiskenlere atayalim.
  * ve cikisa yonlendirelim
  */
static int latchPin = 12;
static int clockPin = 11;
static int dataPin = 10;
 
void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

/**
  * Ana dongu
  */
void loop() {
  /**
    * Ledlerin durumunu bir byte degiskeninde tutacagiz.
    * Her bit bir led'in durumunu belirtecek.
    */
  byte ledler = 0;

  //8 ledi sirayla yakalim
  for (int i = 0; i < 8; i++) {

    //bitSet komutuyla siradaki biti set ediyoruz.
    bitSet(ledler, i);

    //bitClear komutuyla bir onceki biti temizliyoruz.    
    if(i>0)
      bitClear(ledler, i-1);

    //Kaydirma yazmacini guncelleyelim.
    updateShiftRegister(ledler);
    delay(100);
  }
  
  //Ayni islemi bir de tersten yapalim. 
  for (int i = 8; i >= 0; i--) {
    bitSet(ledler, i);
    if(i<8)
      bitClear(ledler, i+1);
    updateShiftRegister(ledler);
    delay(100);
  }
}

 /**
  * Burada kaydirma yazmaci guncelleniyor.
  */
void updateShiftRegister(byte n){
   //latchPin'i LOW yapiyoruz ki veri gonderirken ledler yanip sonmesin
   digitalWrite(latchPin, LOW);
   //shiftOut komutuyla byte degerini gonderiyoruz. 
   shiftOut(dataPin, clockPin, LSBFIRST, n);
   //Veri gonderme islemi tamamlandktan sonra latcPin'i HIGH yapiyoruz.
   digitalWrite(latchPin, HIGH);
}
