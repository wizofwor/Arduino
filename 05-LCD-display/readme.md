# LCD ekran kullanımı

## LCD Tipleri

Arduino ile kullanabileceğimiz karakter ve grafik tabanlı olanlı LCD'ler mevcut. Karakter tabanlı LCD'leri kullanmak nispeten daha kolay. Grafik tabanlılar biraz daha karışık. Bu örnekte ben karakter tabanlı bir LCD kullandım. 

Ardunio'ya LCD ekran bağlamanın iki yöntemi var. Seri ve paralel bağlantı. Hobicilerin sıklıkla başvurduğu 16x2 karakterlik LCD ekranlar paralel bağlantı kullanıyorlar. Bu bir sürü kablo demek. Alternatif olarak backpak denilen LCD denetleyicileri ile seri bağlantı kullanmak ve kablo sayısını 4'e indirmek mümkün.

## Port numarası ve pin konfigurasyonu
Şansıma benim aldığım LCD'nin arkasında PCF8574T denetleyici çıktı. Bu işimi çok kolaylaştıracak. Bu chip ile i2c protokolü üzerinden iletişim kuracağım.

Ancak bunun için biraz hazırlık yapmak gerekiyor. Çin malı 1602 LCD ekranların pin bağlantılarının standart olmadığını öğrendim. Arduino IDE ile beraber gelen LiquidCrystal kütüphanesi önceden belirlenmiş bir pin dizilimine sabitlenmiş olduğu için kullanılamıyor. 

Aşağıdaki adresten **LiquidCrystal_V1.2.1** kütüphanesini indirdim, kurdum ve çakışma olmaması için standart kütüphaneleri (LCD ile ilgili herşeyi) sildim. 

[https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads](http://https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads)

Not:
OSX altında IDE'ye kütüphane eklemek için kütüphane dosyasını `~/Documents/Arduino/libraries/` yoluna kopyalamak gerekiyor. Bu adres Windows kullanıcıları için:`My Documents\Arduino\libraries\` şeklinde. 

İkinci aşamada ise port adresini ve doğru pinleri bulmak gerekli. Bunun için arduino.cc forumlarından Bill Perry'nin hazırladığı **i2cLCDguesser** taslağını kullandım. Bu program i2c cihazının adresini buluyor ve en çok kullanılan pin konfigürasyonlarını sırayla deniyor.

## Bağlantı

i2c için sadece 4 kablo bağlantı yapacağımı söylemiştim ama iş o kadar da basit değil. Sağlıklı bir haberleşme için SDL ve SCL hatlarına pull-up dirençleri bağlamak gerekiyor. Ben aşağıdaki gibi bir devre kurdum. 

<img src=i2c-lcd_bb.png width=600>

Benim cihazım için ayarlar aşağıdaki şekilde çıktı. 
`LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);`

## i2cLCDguesser

i2cLCDguesser kodunu 



    