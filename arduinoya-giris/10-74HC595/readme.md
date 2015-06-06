#74HC595 Shift Register

Hatırlarsanız Karaşimşek devresini kurarken her led için bir dijital çıkış  pinlerinden birini kullanmıştım. Arduino Uno kartı üzerinde sadece 14 adet dijital çıkış oluduğunu* hatırlarsak bu ciddi bir israf. Aynı işi 74HC595 kullarak çok daha az bağlantıyla yapmak mümkün.

**0 ve 1 numaraları pinlerin RX ve TX sinyalleri için ayrılmış olduğunu da unutmamak lazım.*

##74HC595 nedir?

74HC595 8 bit kaydırma yazmacı (shift register) ve 8 bit saklama yazmacı (storage register) ve çıkışları süren 8 adet transistordan oluşur. Kaydırma yazmacına seri olarak yazılan veriyi saklama yazmacına aktarır, oradan da  çıkışlara aktarır. Aşağıdaki zamanlama diyagramını beraber inceleyelim.

<img src=timing-diagram.jpg width=400>

74CH595'in `DS` pini veri girişi için kullanılır. `SH_CP` her tetiklendiğinde `DS` pininin durumu saklama yazmacına aktarılır. `ST_CP` pini tetiklendiğinde ise saklama yazmacındaki değerler Q0-7 pinlerine yönlendirilir.

Aşağıda 74CH595'in pinout diyagramı ve açıklamaları var.

<img src=74HC595.jpg width=150>


Sembol|Pin|Tanım
------|------|------
Q1-7   |1-7  |paralel data output 1-7
GND    |8    |ground (0 V)
Q7'    |9    |serial data output
MR     |10   |master reset (active LOW)
SH_CP  |11   |shift register clock input (**clockPin**)
ST_CP  |12   |storage register clock input (**LatchPin**)
OE     |13   |output enable input (active LOW)
DS     |14   |serial data input (**dataPin**)
Q0     |15   |parallel data output 0
VCC    |16   |supply voltage 

##8 Ledli Kara Şimşek Devresi

Daha önce 5 ledle kurduğum led flash devresini bu kez 8 ledle hazırladım.
Data, latch ve clock pinlerini Arduino'nun 10,11 ve 12. dijital pinleri kullandım. Diğer pinleri boş kalmış oldu.

<img src=74HC595_bb.png>

##Kod

````
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
````

##Sonuç
74HC595 sayesinde sadece 3 pin kullanarak 8 ledi sürmüş oldum. Aslında `serial data output` bacağını kullanarak birden fazla 74HC595'i birbirine de bağlayabilirdim ancak bunu elimde yeterli malzeme olmadığı için daha sonraya bırakıyorum.

Bu gün öğrendiğim yeni komutlar:

* bitSet(değer,byte)
* bitClear(değer,byte)
* shiftOut(dataPin,clockPin,LSBFIRST/MSBFIRST,değer)

[Sonucun neye benzediğini linkteki videodan görebilirsiniz.](https://vine.co/v/ebDdYqgtaKB)



