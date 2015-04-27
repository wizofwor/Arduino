#Button Kullanımı

Led flash (nam-ı diğer Kara Şimşek) effektini çalıştırdığıma göre. Devreye bir de düğme ekleyerek bunu etkileşimli hale getirmemek için bir sebep yok.

Yapmam gereken devreyi alttaki gibi değiştirmek ve [yeni sketchi ](https://github.com/wizofwor/arduino/blob/master/03-button/button/button.ino) yüklemek.

<img src="https://github.com/wizofwor/arduino/blob/master/03-button/button_bb.png?raw=true" width=500>

Anlık çalışan butonlar iki farklı şekilde bağlanarak kullanılabiliyor. Pull-up ve Pull-down yöntemiyle. Ben Ardunio'nun kendi içindeki pull-up direncini kullanacağım. Bu durumda butonun bağlandığı pin normal durumda `HIGH` ben butona bastığımda `LOW` olacak.  

