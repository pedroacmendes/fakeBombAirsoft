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

// RED & BLUE BUTTON
int redButtonPin = 11;
int blueButtonPin = 12;
int redButtonState = 0;
int blueButtonState = 0;

// VARIAVEIS COUNTDOWN
int minutos = 0;
int segundos = 0;
long secMillis = 0;
long interval = 1000;
int segundosSom = 0;

// variavel para ver se é o 1 ou 2 numero
int tempo = 0;

int led = 10;

// progressBar
byte zero[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000
};
byte one[] = {
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000
};

byte two[] = {
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000
};
byte three[] = {
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100,
    B11100
};
byte four[] = {
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110,
    B11110
};
byte five[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

int progress = 50;

unsigned long startMillis;
unsigned long currentMillis;


// pressbutton
int startPressed = 0;    // the moment the button was pressed


void setup() {
    lcd.begin (16,4);
    lcd.setBacklight(HIGH);
    pinMode (GPActiveBuzzer, OUTPUT);
    pinMode(led, OUTPUT);
    pinMode(redButtonPin, INPUT);
    pinMode(blueButtonPin, INPUT);

    lcd.createChar(0, zero);
    lcd.createChar(1, one);
    lcd.createChar(2, two);
    lcd.createChar(3, three);
    lcd.createChar(4, four);
    lcd.createChar(5, five);

    lcd.setCursor(1,0);
    lcd.print("Countdown Game:");
    lcd.setCursor(2, 1);
    lcd.print("BLUE = Start Game");
    lcd.setCursor(6, 2);
    lcd.print("RED = Defuse Bomb");
}

void loop() {
    char key = keypad.getKey();

    blueButtonState = digitalRead(blueButtonPin);
    redButtonState = digitalRead(redButtonPin);

    if (blueButtonState != HIGH) {

        if(minutos == 0 && segundos == 0){
            lcd.clear();
            lcd.print("Set game time");
            lcd.setCursor(0, 1);
            lcd.print("00:00");

            minutos = GetNumber();
            tempo = 1;
            segundos = GetNumber();

            lcd.clear();
            lcd.print("Starting game in");
            for (int i=3;i > 0; i--){
                lcd.setCursor(1, 1);
                lcd.print(i);
                delay(1000);
            }
            lcd.clear();
            lcd.setCursor(4,0);
            lcd.print("Active bomb");
        }else{            
        }

    }

    if(minutos >= 1 || segundos > 0){
        countdown();
    }

    startMillis = millis();

    if(redButtonState == 0){
        startPressed = millis();

        if(minutos == 0 && segundos == 0){
            lcd.clear();
            lcd.print("Start de game first.");
            lcd.print("BLUE = Start Game");
        } else {
            lcd.clear();
            lcd.print("Defusing bomb...");
            digitalWrite (GPActiveBuzzer, HIGH);
            digitalWrite(led, HIGH);

            updateProgressBar(progress, 100);
            progress++;
            delay(300);
            bombdefused();
        }

    }

}

void bombdefused(){
    digitalWrite(led, LOW);
    digitalWrite (GPActiveBuzzer, LOW);
    minutos = 0;
    segundos = 0;
    lcd.clear();
    lcd.print("Bomb Defused");
}

void updateProgressBar(unsigned long count, unsigned long totalCount){
    double factor = totalCount/80.0;
    int percent = (count+1)/factor;
    int number = percent/5;
    int j = 1;

    if(number > 0){
        while(j < 19){
            lcd.setCursor(j,1);
            delay(600);
            lcd.write(5);
            j++;
        }
    }
}

int GetNumber(){
    int num = 0;
    char key = keypad.getKey();

    while(key != '#') {
        switch (key){
            case NO_KEY:
            break;

            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            num = num * 10 + (key - '0');
            if(tempo == 0){
                if(num > 9){
                    lcd.setCursor(0, 1);
                } else {
                    lcd.setCursor(1, 1);
                }
            } else {
                if(num > 9){
                    lcd.setCursor(3, 1);
                } else {
                    lcd.setCursor(4, 1);
                }
            }
            lcd.print(num);
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
    lcd.setCursor (11,2);
    if (minutos < 10){
        lcd.write ("0");
        lcd.setCursor (12,2);
    }

    lcd.print (minutos);
    lcd.setCursor (13,2);
    lcd.print (":");

    if(segundos > 9){
        lcd.setCursor(14, 2);
    } else {
        lcd.print("0");
        lcd.setCursor(15, 2);
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
        digitalWrite(led, HIGH);
    } else {
        digitalWrite (GPActiveBuzzer, LOW);
        digitalWrite(led, LOW);
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
        lcd.print("The bomb has exploded!");
        segundosSom = 0;
        delay(1000);
    }

}
