# Arduino

Arduino ile kuracağım ilk devre yanıp sönen bir ledded ibaret olacak. Aşağıda görünen devreyi kurarak işe başlıyorum.

<img src=https://github.com/wizofwor/arduino/blob/master/01-led-yakip-sondurmece/led-blink_bb.png?raw=true width=500>

Basitçe anlatmak gerekirse 10 numaralı Digital pinden gelen sinyal önce led'e ulaşıyor. Sonrasında 220 ohm'luk dirençten geçerek GND pinine varıyor. Bu durumda eğer 10 numaralı Digital pin'i `HIGH` yaparsam led yanacak.

Aşağıdaki kod işte tam da bu işi yapıyor.

````
void setup(){
  pinMode(10, OUTPUT); // 10 numaral pininin yönü çıkış olarak ayarlandı.
  }

void loop(){
  digitalWrite(10,HIGH);     // LED yansın
  delay(250);                // 250 ms bekleyelim
  digitalWrite(10,LOW);      // LED'i sondurelim
  delay(1000);               // 100 ms = 1 sn bekleyelim
  }
````

Kodun void `setup()` ve `loop()` adlı iki bölümden oluştuğunu farkettiniz mi? Bütün Arduino kodları bu iki fonksiyonu barındırılar. `setup()`Arduino ilk çalışıtığında bir kereliğine çağrılır. `loop()` ise setup işini bitirdikten sonra sosuz döngüde çalışan fonksiyondur.

`delay()` komutuyla bekleme yaptığımı farketmişsinizdir. Buradaki gecikme değeriyle oynayarak çeşitli efektler yaratabilirsiniz.    



