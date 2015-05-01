
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27
#define En 2
#define Rw 1
#define Rs 0
#define D4 4
#define D5 5
#define D6 6
#define D7 7

LiquidCrystal_I2C	lcd(I2C_ADDR,16,2);

void setup()
{
// activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklight(LOW);
  lcd.print("Hede hodo");
}


void loop()
{

}
