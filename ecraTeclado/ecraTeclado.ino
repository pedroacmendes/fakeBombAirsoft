#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
    Serial.begin(9600);

    lcd.begin (16,2);
    lcd.setBacklight(HIGH);
    lcd.print("Digite para aparecer no ecra.");
}

void loop(){
    char key = keypad.getKey();
    // just print the pressed key
    if (key){
        lcd.clear();
        lcd.print(key);
    }

    // this checkes if 4 is pressed, then do something. Here  we print the text but you can control something.
    if (key =='4'){
        lcd.clear();
        lcd.print("Key 4 is pressed");
    }
}
