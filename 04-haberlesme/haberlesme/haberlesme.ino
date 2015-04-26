/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #04 - Haberlesme
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
// Not: Kodun dogru calismasi icin seri port ekraninda 'Satir sonu yok'
// secili olmasi gerekiyor 
/////////////////////////////////////////////////////////////////////////

int sayac = 0;
int okunanDeger;
int hedef;

void setup(){
  
  // Ledleri bagladigimiz 2-6 arasindaki pinleri
  // cikisa yonlendirelim
  for(int i=2;i<=6;i++) 
    pinMode(i,OUTPUT);
    
  // Butonu bagladigimiz 8 numarali pini ise
  // girise yonlendirelim ve dahili pull_up
  // direncini devreye alalim
  pinMode(8,INPUT_PULLUP);
  
  //Haberlemeyi baslatalim
  Serial.begin(9600);
}

void loop(){
  int buttonState;
  
  // Butonu kontrol edelim
  buttonState = digitalRead(8);
  // Eger buton basiliysa ledleri yakalim
  if (buttonState == LOW) {
    sayac++;
    Serial.print("Butona ");
    Serial.print(sayac);
    Serial.println(" defa baslidi.");
    doFlash();
  }
  
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
}

void doFlash() {
    int i;
    for (i=2;i<=6;i++) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW); 
  }   
    for (i=6;i>=2;i--) {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW); 
  }
}
