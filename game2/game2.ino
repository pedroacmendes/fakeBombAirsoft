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
int segundos = 0;
long secMillis = 0;
long interval = 1000;
int segundosSom = 0;


void setup() {
    lcd.begin (16,4);
    lcd.setBacklight(HIGH);
    pinMode (GPActiveBuzzer, OUTPUT);

    lcd.print("Game mode:");
    lcd.setCursor(2, 1);
    lcd.print("A = Countdown");
    lcd.setCursor(6, 2);
    lcd.print("C = Defuse Bomb");
}

void loop() {

    char key = keypad.getKey();

    if(key == 'A'){
        lcd.clear();
        lcd.print("Set game time!");
        lcd.setCursor(0, 1);
        lcd.print("00:00");

        segundos = GetNumber();
        // se tiver 2 numeros adiciona no quadrado correto
        if(segundos > 9){
            lcd.setCursor(3, 1);
        } else {
            lcd.setCursor(4, 1);
        }
        lcd.print(segundos);

        minutos = GetNumber();
        if(minutos > 9){
            lcd.setCursor(0, 1);
        } else {
            lcd.setCursor(1, 1);
        }
        lcd.print(minutos);

        lcd.clear();
        lcd.print("BOMBA ARMADA");
    }

    if(minutos >= 1 || segundos > 0){
        countdown();
    }

    // FALTA FAZER O TEMPO APARECER NO MOMENTO QUE CARREGO NAS TECLAS

    if(key == 'C'){
        minutos = 0;
        segundos = 0;
        lcd.clear();
        lcd.print("Bomb Defused");
    }

}

int GetNumber(){
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

void countdown() {
    lcd.setCursor (3,1);
    if (minutos < 10){
        lcd.write ("0");
        lcd.setCursor (4,1);
    }

    lcd.print (minutos);
    lcd.setCursor (5,1);
    lcd.print (":");

    if(segundos > 9){
        lcd.setCursor(6, 1);
    } else {
        lcd.print("0");
        lcd.setCursor(7, 1);
    }
    lcd.print(segundos);

    if(segundos > 60){
        segundos = 0;
        minutos++;
    }
    if(minutos >= 1 && segundos == 0){
        minutos--;
        segundos = 59;
    }

    if(segundosSom >= 5){
        digitalWrite (GPActiveBuzzer, HIGH);
    } else {
        digitalWrite (GPActiveBuzzer, LOW);
    }

    if(segundosSom == 6){
        segundosSom = 0;
    }

    if (segundos >= 0){
        long currentMillis = millis();

        if(currentMillis - secMillis > interval){
            secMillis = currentMillis;
            segundos --;
            segundosSom++;
        }
    }

    if(minutos == 0 && segundos <= 0){
        lcd.clear();
        lcd.print("The Bomb Has Exploded!");
        while(1);
    }

}
