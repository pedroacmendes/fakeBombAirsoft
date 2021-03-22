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

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

int GPActiveBuzzer = 13;

// VARIAVEIS
int minutos = 0;

void setup() {
    lcd.begin (16,2);
    lcd.setBacklight(HIGH);
    pinMode (GPActiveBuzzer, OUTPUT);

    lcd.print("Game mode:");
    lcd.setCursor(2, 1);
    lcd.print("A = Countdown");
}

void loop() {
    char key = keypad.getKey();

    if(key == 'A'){
        lcd.clear();
        int tempoinicial=(millis())/1000;
        lcd.print("Set game time!");
        lcd.setCursor(0, 1);
        lcd.print("00:00:00");

        minutos = GetNumber();
        // se tiver 2 numeros adiciona no quadrado correto
        if(minutos > 9){
            lcd.setCursor(3, 1);
        } else {
            lcd.setCursor(4, 1);
        }
        lcd.print(minutos);
        delay(1000);
        countdown(tempoinicial);
    }

}

void countdown (int tempoinicial) { //rotina de acionamento da bomba
    lcd.clear();
    lcd.print("BOMBA ARMADA");

    while(minutos >= 0){
        lcd.setCursor(2, 1);

        for(minutos; minutos>0; minutos--){
            lcd.clear();
            lcd.print("00:00:00");
            if(minutos > 9){
                lcd.setCursor(3, 0);
            } else {
                lcd.setCursor(4, 0);
            }
            lcd.print(minutos);
            delay(1000);
        }

        if(minutos <= 0){
            lcd.clear();
            lcd.print("Terminou o tempo.");
            while(1);
        }

    }
    return;
}


int GetNumber()
{
    int num = 0;
    char key = keypad.getKey();
    while(key != '#')
    {
        switch (key)
        {
            case NO_KEY:
            break;

            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            num = num * 10 + (key - '0');
            break;

            case '*':
            num = 0;
            lcd.clear();
            break;
        }

        key = keypad.getKey();
    }

    return num;
}
