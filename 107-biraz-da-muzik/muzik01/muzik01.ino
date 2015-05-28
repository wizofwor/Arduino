/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #07.2 - Muzik1
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
// SparkFun Inventor's Kit - Example sketch 11'de faydalanarak yapilmistir
// Orjinal yazar: D. Cuartielles 
//
// Sparkfun SIK Exprimant Guide for Arduino - V3.2
// Experiment11:Using a Piezo Buzzer
//
// https://learn.sparkfun.com/tutorials/
//
/////////////////////////////////////////////////////////////////////////


const int buzzerPin = 9;                                 //cikis pini
const int uzunluk = 18;                                  //calacagim parcanin kac notadan olustugunu tanimyliyorum.
char nota[] = "cdfda ag cdfdg gf ";                      // calinacak notalari dizi olarak giriyorum.
int vuruslar[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};  //Her nota icin vurus degerlerini giriyorum
int tempo = 150;                                         //Tempo degeri azaldikca muzik hizlanacak

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int i, sure;
  // Tempo ve vurus degerlerini kullanarak notalarin suresini hesaplayalim
  for (i = 0; i < uzunluk; i++) {
    sure = vuruslar[i] * tempo;  
    if (nota[i] == ' ')  {                              // eger bu bir es ise 
      delay(sure);                                      // bir sey yapmadan bekleyelim
    }
    else {                                              // degilse 
      tone(buzzerPin, frekans(nota[i]), sure);          // notayi calalim
      delay(sure);                                      // tone komutunun bitmesini beklemek lazim
    }
    //notalarin arasinde kisa bir bekleme
    delay(tempo/10);                                    
  }
  // Muzigin surekli calmamasi icin programi sonsuz donguye sokmam gerek
  while(true){}
}


/**
 * Bu fonksiyon notayi adini alip
 * frekansini donduruyor
 */
int frekans(char nota) 
{
  /**
    * Notalar icin bir lookup tablosu olusturmam lazim.
    * Nota adlarini ve karsilik gelen frekans degerlerini birer
    * dizi olarak giriyorum
    */
  char notalar[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frekanslar[] = {262, 294, 330, 349, 392, 440, 494, 523};
  /**
    * Boylece ilk diziden nata adini bulup
    * ikinci diziden frekans degerini cekebilirim.
    */
  for (int i = 0; i < 8; i++) {       // Butun notalari tariyorum
    if (notalar[i] == nota)        // aradigim notayi buldugumda
      return(frekanslar[i]);          // frekans degerini donduruyorum
  }
  //eger hic bir sey bulamamissam, 0 degerini donduruyorum.
  return(0);  
}
