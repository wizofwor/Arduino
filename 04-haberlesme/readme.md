# Arduino ile haberleşmek

USB kalosu üzerinden Arduino ile haberleşmemiz mümkün. Bunun için `Serial` kütüphanesini ve IDE'nin seri port ekranını kullanmamız yeterli.

### Veri Almak
Buton örneğinde kurduğum devreyi değiştirmeden. Bir iki ekleme yapıyorum. Önce setup kısmına `Serial.begin(9600);` satırını ekliyorum. Bu komut haberleşmeyi başlatıyor.

Artık butona her basıldığınıda bilgisayara bir mesaj gönderebilirim. Eğer buton denetleyen kodu aşağıdaki gibi değiştirirsem, butona her basıldığında bilgisayara bir mesaj gönderebilirim.  
  
   ```
  if (buttonState == LOW) {
     Serial.println("Butona Basildi.");
     doFlash();
   }
   ```
 Peki Ardunio'ya butona kaç defa basıldığını saydırabilir miyiz?
 
 Bunun için bir sayaç tanımlamamız lazım. Programına başına `int sayac = 0;`satırını ekleyerek sayacı tanımladıktan sonra butona denetleyen kodu bir iki ilave daha yaparsak Arduino bunu bunu yapacaktir.
 
 ````
  if (buttonState == LOW) {
    sayac++;
    Serial.print("Butona ");
    Serial.print(sayac);
    Serial.println(" defa baslidi.");
    doFlash();
  }
  ````
Veri alma kısmı tamam. Şimdi de serial kütüphanesi kullanılarak Arduino'ya nasıl veri gönderildiğine bakalım.

### Veri Göndermek

Öncelikle programın başlangıcında `int okunanDeger;` ile yeni bir değişken tanımladım. Daha sonra aşağıdaki kodu `loop()`'un sonuna ekledim.

````
  //Tamponda veri olup olmadigina bakalim
  while(Serial.available() > 0) {
       //Tampondaki veriyi integer olarak alalim
       okunanDeger = Serial.parseInt();            
       //Okunan sayiyi 1 ile 5 arasinda daraltalim
       hedef = constrain(okunanDeger, 1, 5);       
       //Mesaji gnderelim
       Serial.print(hedef,DEC);
       Serial.println(". led yakildi.");
       //Hedeflenen ledi yakalim
       digitalWrite(hedef+1,HIGH);
  }
  ````
  
Artık seri port ekranında 1 ile 5 arasında bir değer girerek istediğim ledi yakabiliyorum. Kodun doğru çalışabilmesi için monitör penceresinde `Satır sonu yok` seçeneğinin saçili olmasını gerekiyor. Aksi halde girilen sayıyla birlikte `\n` yani newline karakteri de gönderiliyor. Bu `Serial.parseInt();` karşılaştığı numerik olmayan her değeri 0 olarak yorumladığı için sorun olacaktır.  