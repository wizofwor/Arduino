# LCD ekran kullanımı

Arduino ile kullanabileceğimiz karakter ve grafik tabanlı LCD'ler mevcut. Karakter tabanlı LCD'leri kullanmak nispeten daha kolay. Grafik tabanlılar biraz daha karışık. Bu örnekte ben karakter tabanlı bir LCD kullandım. 

Ardunio'ya LCD ekran bağlamanın iki yöntemi var. Seri ve paralel bağlantı. Hobicilerin sıklıkla başvurduğu 16x2 karakterlik LCD ekranlar paralel bağlantı kullanıyorlar. Bu bir sürü kablo demek. Alternatif olarak backpak denilen LCD denetleyicileri ile seri bağlantı kullanmak ve kablo sayısını 4'e indirmek mümkün.

## Port numarası ve pin konfigurasyonu
Şansıma benim aldığım LCD'nin arkasında PCF8574T denetleyici çıktı. Bu işimi çok kolaylaştıracak. Bu chip ile i2c protokolü üzerinden iletişim kuracağım.

Ancak bunun için biraz hazırlık yapmak gerekiyor. Çin malı 1602 LCD ekranların pin bağlantılarının standart olmadığını öğrendim. Arduino IDE ile beraber gelen LiquidCrystal kütüphanesi önceden belirlenmiş bir pin dizilimine sabitlenmiş olduğu için kullanılamıyor. 

[https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads](http://https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads) adresinden **LiquidCrystal_V1.2.1** kütüphanesini indirdim, kurdum ve çakışma olmaması için standart kütüphaneler (LCD ile ilgili herşeyi) sildim. 

OSX altında IDE'ye kütüphane eklemek için kütüphane dosyasını `~/Documents/Arduino/libraries/` yoluna kopyalamak gerekiyor. Bu adres Windows kullanıcıları için:`My Documents\Arduino\libraries\` şeklinde. 

İkinci aşamada ise port adresini ve doğru pinleri bulmak gerekli. LCD beraberinde herhangi bir datasheet gelmediği için kullanılan pin konfigurasyonu bilemiyoruz. Bunun için arduino.cc forumlarından Bill Perry'nin hazırladığı **i2cLCDGuesser** taslağını kullandım. Bu program i2c cihazının adresini buluyor ve en çok kullanılan pin konfigürasyonlarını sırayla deniyor.

## Bağlantı

i2c için sadece 4 kablo bağlantı yapacağımı söylemiştim ama iş o kadar da basit değil. Sağlıklı bir haberleşme için SDL ve SCL hatlarına 4.7 k ohm'luk pull-up dirençleri bağlamak gerekiyor. Ben aşağıdaki gibi bir devre kurdum. 

<img src=i2c-lcd_bb.png width=600>

i2cLCDguesser'ı yükledikten sonra seri port ekranından komut vererek olasılıkları taradım ve cihazımı için doğru ayarları buldum. Program doğru ayarları hem seri port ekranından hem de LCD üzerinden bildiriyor. Benim için doğru parametreler
`0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE`

Ufak bir not, backpack'in arkasındaki kontrast potunu ayarlamayı unutmayın. Ben bu yüzden ilk denememde LCD'nin çalıştığını farkedemedim.

## Merhaba Dünya!

Bu kadar hazırlıktan sonra, sonunda sıra Hello World programını yazmaya geldi.

İlk olarak haberleşme için kullanacağım kütüphaneleri ekledim.

````
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
````

Biraz önce öğrendiğim parametreleri kullanarak lcd'yi tanımladım.

````
/**
 * LCD ayarlari 
 * Adres 0x27
 * en, rw, re, d4, d5, d6, d7, bl, blpol
 * 2,  1,  0,  4,  5,  6,  7,  3,  POSITIVE
*/ 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
````
LCD ekranı kullanmadan önce başlatmam gerekiyor.

````
void setup(){
  //lcd'yi baslatalim
  Serial.begin(9600);
  lcd.begin(16,2);
  ````

Arka aydınlatmayı yakıp söndürmek için gerekli kodları ekledim. 

````
  //arka aydintmayi acip kapatalim.
  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  ````
  
Son olarak mesajımı yazdım.  
  
````  
  //Mesajimizi yazalim
  lcd.setCursor(0,0);
  lcd.print("Merhaba Dunya!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Wizofwor");
  }
  
void loop(){
} 
````

Bu şekilde Merhaba Dünya programı bu şekilde tamamlanmış oldu.





    