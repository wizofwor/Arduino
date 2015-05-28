#Biraz daha Müzik

İlk örnek programda ancak bip sesi çıkartabilmiştim. Şimdi biraz daha güzel bir şeyler yapabilmek için işleri kolaylaştıran bir araçtan faydalanacağım. `tone()` komutu. Tone komutu bizi PWM değerleriyle uğraştırmadan nota çalabilmemizi sağlayacak.

Tek bilmemiz gereken notaların frekans degerleri. Onlar da aşağıdaki tabloda yazıyor.  

  note|  frequency
  ---|---
  c  |   262 Hz
  d  |   294 Hz
  e  |   330 Hz
  f  |   349 Hz
  g  |   392 Hz
  a  |   440 Hz
  b  |   494 Hz
  C  |   523 Hz
  
Anlatmaya başlamadan önce, unutmadan söyleyeyim örnek kodu [muzik01/][1] klasöründen alabilirsiniz. Kullandığım devre ise [bir önceki][2] örnekle aynı.

[1]:muzik01/
[2]:../107-biraz-da-muzik

Programın başında çalınacak notaları, vuruş degerlerini ve tempoyu girerek çalacağim müziği tanımlıyorum. 
  
````
const int buzzerPin = 9;     //cikis pini
const int uzunluk = 18;      //calacagim parcanin kac notadan olustugunu tanimyliyorum.
char nota[] = "cdfda ag cdfdg gf ";  //calinacak notalar
int vuruslar[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2}; //vurus degerleri
int tempo = 150; //Tempo degeri azaldikca muzik hizlanacak
````
Setup kısmında sadece çıkış pinini ayarlıyorum.
  
````
void setup() {
  pinMode(buzzerPin, OUTPUT);
}
````  
Gelelim ana döngüye. Muzik burada calinacak. Her bir nota icin ayni islemleri tekrarlamam lazım. 

İlk olarak calinacak notanin suresini hesapliyorum. 

````
  for (i = 0; i < uzunluk; i++) {
    sure = vuruslar[i] * tempo;  
    }  
````
Sonra nota değerini kontrol ediyorum. Eğer boşluk değeri görürsem es vereceğim.

````
  if (nota[i] == ' ')  {     // eger bu bir es ise 
      delay(sure);           // bir sey yapmadan bekleyelim
    }
 ````

Diğer durumda notayi çalacağım. Bunun için `tone()` komutunu kullanıyorum.
 
 ````
     else {                                               
      tone(buzzerPin, frekans(nota[i]), sure);  // notayi calalim
      delay(sure); // tone komutunun bitmesini beklemek lazim
    }
````

Ana döngünün gerisini için açıklamaya gerek yok. Kodun içersindeki açıklamar yeterli olacaktır.
 
Gelelim frekans değerini hesaplayan fonksiyonumuza. Burada önce iki ayrı dizi kullanarak notalar ve karşılık gelen frekans değerleri için bir karşılaştırma tablosu hazırlıyorum. Daha sonra bu iki diziyi aynı anda tarayarak notayı bulduğum indexteki frekans değerini döndürüyorum.
 
````
/**
 * Bu fonksiyon notayi adini alip
 * frekansini donduruyor
 */
int frekans(char nota) 
{
  /**
    * Notalar icin bir lookup tablosu olusturmam lazim.
    * Nota adlarini ve karsilik gelen frekans degerlerini birer
    * dizi olarak giriyorum
    */
  char notalar[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frekanslar[] = {262, 294, 330, 349, 392, 440, 494, 523};
  /**
    * Boylece ilk diziden nata adini bulup
    * ikinci diziden frekans degerini cekebilirim.
    */
  for (int i = 0; i < 8; i++) {       // Butun notalari tariyorum
    if (notalar[i] == nota)        // aradigim notayi buldugumda
      return(frekanslar[i]);          // frekans degerini donduruyorum
  }
  //eger hic bir sey bulamamissam, 0 degerini donduruyorum.
  return(0);  
}
````
Program müziği sadece bir kez çalıyor. Eğer sıkılmazsanız 44. satırdaki `while(true){}` ifadesini kaldırarak sürekli çalmasını da sağlayabilirsiniz. 
 
  
  