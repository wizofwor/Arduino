i2C LCD ekran kullanımı



Ardunio'ya LCD ekran bağlamanın iki yöntemi var. Seri ve paralel bağlantı. Hobicilerin sıklıkla başvurduğu 16x2 karakterlik LCD ekranlar paralel bağlantı kullanıyorlar. Bu bir sürü kablo demek. Alternatif olarak backpak denilen LCD denetleyicileri seri bağlantı kullanmak ve kablo sayısını 4'e indirmek mümkün. 

Şansıma benim aldığım LCD'nin arkasında PCF8574T denetleyici çıktı. Bu işimi çok kolaylaştıracak. SCL, SDL, GND ve Vcc Bağlantılarını yaptığımda ekranın ışığı yanıverdi.

http://playground.arduino.cc/Code/LCDi2c

Liquid Crystal I2C kütüphenasini indirip,

> OSX altında IDE'ye kütüphane eklemek için kütüphane dosyasını `~/Documents/Arduino/libraries/` youluna kopyalamak gerekiyor.
>
> Bu adres Windows kullanıcıları `My Documents\Arduino\libraries\` şeklinde. 

0x27 adresinde buldum 


    