# Karaşimşek Devresi

Led denince ilk akla gelen devre kara şimşek devresidir. Ben de kendi kara şimşek devremi oluşturacağım. Bu sefer işe sefer kodlamayla başladım. 

Ledleri 2-6 arasındaki dijital pinlere bağlamayı planlıyorum. Önce bu pinleri `OUTPUT` olarak ayarlamalıyım.

````
void setup(){
  // 2-6 arasndaki pinleri cikisa yonlendirelim
  for(int i=2;i<=6;i++) 
    pinMode(i,OUTPUT);
}
````

Şimdi bu ledleri sırayla yakmam gerek. Bunu için `for` döngüsü kullanacağım. Ledleri sırayla yakıp 100 ms bekledikten sonra söndürüyorum.

````
void loop(){
  int i;
  for (i=2;i<=6;i++) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW); 
  } 

````
Efektin daha güzel görünmesi için geri dönüşünü de yapmak lazım. Bunun için ikinci bir döngü daha ilave ettim.

````
    for (i=6;i>=2;i--) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW); 
  }
}
````

Kodum hazır. Son olarak aşağıdaki devreyi kurmam gerekli. Aslında bir önceki derste kurduğumuz devrenin aynısı. Tek farkı bir yerine beş led var. 

![Breadbord](https://github.com/wizofwor/arduino/blob/master/02-led-flash/led-flash_bb.png?raw=true)


