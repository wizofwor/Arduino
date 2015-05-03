# Led Yakıp Söndürmek

Arduino ile kuracağım ilk devre yanıp sönen bir ledded ibaret olacak. İlk olarak devremizi kurmamız lazım.

Eğer daha önce *breadboard* kullanmadıysanız ve nasıl çalıştığını bilmiyorsanız. Öğrenme vakti geldi. Breadboard'ı elektronik bir deneme tahtası olarak düşünebilirsiniz. Breadboard üzerindeki deliklerin içindeki mekanik kıskaçlar yer alır. Bunlar yerleştirilen devre elemanlarını tutarak lehimsiz bir bağlantı sağlarlar. Delik aralıkları standarttır. Yani her türlü devra elamanı, entegre, mikrodenetleyi, sensör vb. bağlayabilirsiniz. Breadboard'un her iki yanında bulunan ikişer sıra, kımızı ve mavi işaretli pinler bir birine bağlıdır. İçerideki pinler ise kendi aralarında yatayda bağlıdırlar. Yalnız ortadaki yarığın sağı ve solunda gruplar arasında bağlantı yoktur. İlk başta biraz karışık geldiğini biliyorum ama biraz kullanınca bu dizilimin ne kadar pratik olduğunu göreceksiniz. 

## Devre elamanlarının bağlanması 

İlk devremde sadece bir adet LED ve 220 ohm'luk direnç kullanacağım. 

Basitçe anlatmak gerekirse 10 numaralı Digital pinden gelen sinyali led'i beslemek için kullanacağım. Led'i korumak için de arkasına 220 ohm'luk direncibağladım. Bu durumda eğer 10 numaralı Digital pin'i `HIGH` yaparsam led yanacak.

Elemanların breadboard üzerindeki yerleşimini aşağıda görüyorsunuz.

<img src=https://github.com/wizofwor/arduino/blob/master/01-led-yakip-sondurmece/led-blink_bb.png?raw=true width=500>

## İlk Arduino Taslağım

Arduino programlarına taslak (sketch) deniyor. Bu taslakları Arduino IDE üzerinde derleyip karta gönderiyoruz. Terimler aklınızı karıştırmasın IDE'nin kullanımı oldukça basit. Eğer hala indirip kurmadıysanız IDE'yi [arduino.org/downloads sayfasından][1] indirip kurabilirsiniz.

[1]: http://arduino.org/downloads 

Aşağıdaki kodu yazıp, yükle komutuyla Arduino'ya gönderiyorum. Kod yüklenir yüklenmez otomatik olarak çalışmaya başlıyor.

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

##Biraz da açıklama

Kodun void `setup()` ve `loop()` adlı iki bölümden oluştuğunu farkettiniz mi? Bütün Arduino kodları bu iki fonksiyonu barındırılar. `setup()`Arduino ilk çalışıtığında bir kereliğine çağrılır. `loop()` ise setup işini bitirdikten sonra sosuz döngüde çalışan fonksiyondur.

setup bölümünde `pinMode(10, OUTPUT);` komutuyla 10 dumaralı dijital pin'i çıkışa yönlendiriyorum.

Loop bölümünde ise `digitalWrite(10,HIGH);` ve `digitalWrite(10,LOW);` komutlarıyla ledi yakıp söndürüyorum. `delay()` komutuyla bekleme yaptığımı farketmişsinizdir. Buradaki gecikme değeriyle oynayarak çeşitli efektler yaratabilirsiniz.    



