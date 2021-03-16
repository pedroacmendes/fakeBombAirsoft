#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

int tempo = 20;

void setup() {
    lcd.begin(16, 2);
    Serial.begin(9600);
    countdown();
}

void loop() {

}

void countdown() {

    while (tempo >= 0) {
        delay(1000);
        lcd.clear();
        lcd.print("00");
        lcd.print(":");
        lcd.print(tempo);
        tempo--;
    }

}
