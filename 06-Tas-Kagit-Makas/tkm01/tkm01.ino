/////////////////////////////////////////////////////////////////////////
// Arduino Kodlari #06 - Tas, kagit, makas oyunu
// 
// wizofwor - Nisan 2015
// https://github.com/wizofwor/arduino
//
/////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LCD ekrani tanimlayalim
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Global degisken ve sabitleri tanimlayalim
static int buton1 = 8;
static int buton2 = 9;
static int buton3 = 10;
int butonState[3];

// oyuncu ve cpu secimlerinde {0,1,2} = {"tas","kagit","makas"};
int oyuncuSecimi = -1;
int cpuSecimi = -1;
/**
  * tas ve kagit ve makas'in kazandigi secimleri bir arrayde saklayalim
  * {tas > makas, kagit-> tas, makas->kagit}
  */
int kriter[3] = {2,0,1}; 

/** 
 * karsilastirma sonuclari
 * dizinin ilk elemani oyuncu ikinci elemani CPU'nun skoru iin
 */
int sonuc; 

/**
 * Oyunda kullanacagimiz ozel karakterleri tanimlayalim
 * Ve LCD'yi baslatalim
 */
static byte customChar0[8] = {0b00001,0b00011,0b00110,0b01101,0b01010,0b01101,0b01110,0b00111,};
static byte customChar1[8] = {0b11000,0b01100,0b11010,0b10110,0b10110,0b10110,0b11110,0b11100,};
static byte customChar2[8] = {0b00011,0b00101,0b01001,0b01111,0b01000,0b01000,0b01000,0b00111,};
static byte customChar3[8] = {0b11000,0b00100,0b00100,0b00100,0b00100,0b00100,0b00100,0b11000,};
static byte customChar4[8] = {0b01000,0b10100,0b01111,0b00011,0b01111,0b10100,0b01000,0b00000,};
static byte customChar5[8] = {0b00000,0b00110,0b11000,0b00000,0b11000,0b00110,0b00000,0b00000,};  



/////////////////////////////////////////////////////////////////////////
// Setup
//
/////////////////////////////////////////////////////////////////////////
void setup() {
  /**
   * Butonlari bagladigimiz pinleri girise yonlendirelim
   * ve dahili pull_up direnclerini devreye alalim
   */
  pinMode (buton1,INPUT_PULLUP);
  pinMode (buton2,INPUT_PULLUP);
  pinMode (buton3,INPUT_PULLUP);
  
  lcd.begin(16,2);
  lcd.backlight();
  
  lcd.createChar(0,customChar0);
  lcd.createChar(1,customChar1);
  lcd.createChar(2,customChar2);
  lcd.createChar(3,customChar3);
  lcd.createChar(4,customChar4);
  lcd.createChar(5,customChar5);
    
  //Random sayi kaynagini ayarliyorum.
  randomSeed(analogRead(0));
  
  //Karsilama ekranini hazirlayalim
  lcd.setCursor(0,0);
  lcd.print("?");
  
}

/////////////////////////////////////////////////////////////////////////
// Ana dongu
//
/////////////////////////////////////////////////////////////////////////
void loop() {
  //Butonlari oku
  butonState[0] = digitalRead(buton1);
  butonState[1] = digitalRead(buton2);
  butonState[2] = digitalRead(buton3);
  
  //bir butona basildiginda buton degerini oyunu secimi olarak ata
  for (int i = 0; i<3; i++) {
   if (butonState[i] == LOW) {
   oyuncuSecimi = i; 
   }
  }
  
  /**
    * Asagidaki kod sadece oyuncu secim
    * yaptiktan sonra calisacak
    */
  if (oyuncuSecimi != -1) {
    
    //oyuncu secimini ekrana yaz
    lcd.setCursor(1,1);
    lcd.write((uint8_t)oyuncuSecimi*2);
    lcd.write((uint8_t)oyuncuSecimi*2+1);
    delay(500);
    
    lcd.print(" v.s. ");
    delay(500);
    
    //cpu secimini hesapla ve ekrana yaz
    cpuSecimi = random(0,3);
    lcd.write((uint8_t)cpuSecimi*2);
    lcd.write((uint8_t)cpuSecimi*2+1);
    delay(500);
    
    //sonucu bul
    sonuc = secimleriKarsilastir();
    
    //sonuca gore bir mesaj gosterelim
    switch (sonuc) {
      case -1:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" CPU Kazandi");
        break;
      
      case 0:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Berabere");
        break;
      
      case 1:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Sen kazandin");
        break;
      }
      delay(2000);
      /**
        * mesaji gosterdikten sonra oyuncu secimini tekrar -1 yapalim
        * ve ekrani temizleyelim boylece oyun tekrar baslasin.
        */
      oyuncuSecimi = -1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("?");
   }
}
  
/////////////////////////////////////////////////////////////////////////
// Fonksiyonlar
//
/////////////////////////////////////////////////////////////////////////  
/**
* Oyuncu ve cpu secimlerini karsilastir. 
* 0: berabere
* 1: oyuncu kazanir
* -1: cpu kazanir
*/
int secimleriKarsilastir() {
    if (oyuncuSecimi == cpuSecimi)
      return 0;
    else if (kriter[oyuncuSecimi] == cpuSecimi)
      return 1;
    else
      return -1;
  }
