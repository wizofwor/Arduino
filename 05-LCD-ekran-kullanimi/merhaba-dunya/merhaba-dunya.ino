/**
 * LiquidCrystal_V1.2.1 kutuphanesi ile calisir.
 * https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
 * Diger LCD kutuphelerini silmelisiniz. 
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/**
 * LCD ayarlari 
 * Adres 0x27
 * en, rw, re, d4, d5, d6, d7, bl, blpol
 * 2,  1,  0,  4,  5,  6,  7,  3,  POSITIVE
*/ 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup(){
  //lcd'yi baslatalim
  Serial.begin(9600);
  lcd.begin(16,2);
  
  //arka aydintmayi acip kapatalim.
  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  
  //Mesajimizi yazalim
  lcd.setCursor(0,0);
  lcd.print("Merhaba Dunya!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Wizofwor");
  }
  
void loop(){
} 
