#Temel Arduino Dersleri

![image](https://github.com/wizofwor/arduino/blob/master/arduino-uno.png?raw=true)

Bu sayfalarda hep beraber Arduino öğreniyoruz! İsterseniz derslere başlamadan önce [Arduino nedir][1] yazıma bir göz atmak isteyebilirisiniz. Eğer henüz Arduino için gerekli malzemeleri almadıysanız, alışverişe çıkmadadan önce [gerekli şeyler][2] sayfama bir göz gezdirmenizde fayda var.

Dersleri takip edebilmek için biraz programa alt yapısı gerekecek. C dilini (veya C söz dizimine sahip başka bir dil) biliyor olmanız gerekiyor. Elektronik konusunda sıkıntı yok. Onu beraber öğreneceğiz.

[1]: https://github.com/wizofwor/arduino/tree/master/arduino-nedir.md "Arduino nedir?"
[2]: https://github.com/wizofwor/arduino/blob/master/gerekli-seyler.md "Gerekli şeyler"

##Temel Yazılımlar

Derslere başlamadan önce kullandığım iki yazılımdan bahsetmek istiyorum. Arduino sketchlerini hazırlamak ve yüklemek için [Arduino IDE][3], devre şemalarını hazırlamak için [Fritzing][4] kullanıyorum. Devre şemalaları için bir yazılım kullanmak zorunda dağilsiniz. Ama programları derlemek için bir IDE'ye ihtiyacınız olacak. Arduino IDE basitliğiyle yeni başlayanlar için idealdir. Tavsiye ederim.

[3]: http://www.arduino.cc/en/main/Software
[4]: http://fritzing.org/home/

##Örnek Devre ve Kodlar

###Arduino'ya giriş: Işık ve Ses

Yeni başlayanlar için hazırlanan dökümanların genellikle led devreleri üzerine olması tesadüf değil. Işık ve ses devreleri en az bileşenle sonuç edelde edebileceğin pratik devrelerdir. Biz de Arduino öğrenmeye led ve buzzer ile başlayacağız.

1. [Led Yakıp Söndürmece][5]
2. [Led Flash:][6] Nam-ı diğer Karaşimşek devresi
3. [Buton kontrolü][7]
4. [LCD ekran kullanımı][8]
5. *[Oyun Molası:][9] Taş-kağıt-makas oyunu*
6. [7 segmentli gösterge:][10] 7 segmentli gösterge (7 segment display) kullanımı
7. [74HC595:][11] Shift register kullanımı
8. [Biraz da müzik:][12] Buzzer kullanımı
9. [Biraz daha müzik][13] Notalar

[5]: arduinoya-giris/01-led-yakip-sondurmece
[6]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/02-led-flash
[7]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/03-button
[8]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/05-LCD-ekran-kullanimi
[9]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/06-Tas-Kagit-Makas
[11]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/10-74HC595
[12]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/07-biraz-da-muzik
[13]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/08-biraz-daha-muzik
[10]:https://github.com/wizofwor/arduino/tree/master/arduinoya-giris/09-7-segmentli-gosterge

###Ek bilgiler
1. [Led kullanimi ve led hesabı][21]

[21]:arduinoya-giris/01-led-yakip-sondurmece/led-kullanimi.md


###İkinci Bölüm: Haberleşme

21. [Arduino ile haberleşme:][31] Bilgisayarla Arduino arasında veri alış-verişi

[31]:https://github.com/wizofwor/arduino/tree/master/haberlesme/01-haberlesme