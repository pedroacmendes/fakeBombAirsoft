#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

 

void setup()

{
  lcd.begin (16,2);
  lcd.setBacklight(HIGH);
  lcd.print("LAW");
  lcd.setCursor(0,1); 
  lcd.print("LAW");
}

 

void loop()

{

}
