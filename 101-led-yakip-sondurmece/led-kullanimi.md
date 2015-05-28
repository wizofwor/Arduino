#Led Kullanımı

<img src=led.png>

"**L**ight **E**mitting **D**iode", kısaca LED, diyot temelli, ışık yayan bir elektronik devre elemanıdır.

Farkettiyseniz ledlerin bir bacağı kısa diğerinin uzundur. Kısa bacak katod, uzun bacak anottur. Devrelerimizde her zaman uzun bacağı Vcc(+) kısa bacağı GND(-) tarafına bağlayacağız. 

Ledler besleme gerilimine hasas bileşenlerdir. Üzerlerinden geçen akımın kontrol edilmesi gerekir. Doğrudan güç kaynağına bağlandıklarında yanarlar.

##Led hesabı

Led hesabı yapabilmek için çalışma voltajı ve led gerilimi değerlerine ihtiyacımız var. Bu değerler üreticiye göre değişmekle birlikte menşeini bilmediğimiz 5mm'lik bir led için gerilim değerini **20 ma** olarak kabul edebiliriz.

Aşağıdaki tabloda ise tipik voltaj değerleri verilmiştir.

Renker| Çalışma Voltajı |
---|---|---
Kırmızı|1.8|
Turuncu|2.0| 
Sarı   |2.1| 
Yeşil  |2.2| 
Mavi   |3.3| 
Beyaz  |3.3|

Kırmızı bir led ve 5V'luk bir güç kaynağı için hesap yaparsak:

Vcc = Vl - Vd  
Vd = Vcc - Vl = 5V - 1.8V = 3.2V

Direncimizden 3.2V akım geçecek.

Vd = I x R
R = Vd/I = 3.2/20 = 160 ohm



