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

// VARIAVEIS
char password[4]; // number of characters in our password
int currentLength = 0; //defines which number we are currently writing
int i = 0;
char entered[4];

long secMillis = 0; // store last time for second add
long interval = 1000; // interval for seconds

int Scount = 12; // count seconds
int Mcount = 5; // count minutes
int Hcount = 0; // count hours
int DefuseTimer = 0; // set timer to 0

void setup(){
    lcd.begin(16, 4);
    lcd.setBacklight(HIGH);

    lcd.print("Enter Code: ");
    while (currentLength < 4)
    {
        lcd.setCursor(currentLength + 6, 1);
        lcd.cursor();
        char key = keypad.getKey();
        key == NO_KEY;
        if (key != NO_KEY)
        {
            if ((key != '*')&&(key != '#'))
            {
                lcd.print(key);
                password[currentLength] = key;
                currentLength++;
            }
        }
    }

    if (currentLength == 4)
    {
        delay(500);
        lcd.noCursor();
        lcd.clear();
        lcd.home();
        lcd.print("You've Entered: ");
        lcd.setCursor(6,1);
        lcd.print(password[0]);
        lcd.print(password[1]);
        lcd.print(password[2]);
        lcd.print(password[3]);
        delay(3000);
        lcd.clear();
        currentLength = 0;
    }
}

void loop()
{
    timer();
    char key2 = keypad.getKey(); // get the key

    if (key2 == '*')
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Code: ");

        while (currentLength < 4)
        {

            timer();

            char key2 = keypad.getKey();
            if (key2 == '#')
            {
                currentLength = 0;
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Code: ");
            }
            else
            if (key2 != NO_KEY)
            {
                lcd.setCursor(currentLength + 7, 0);
                lcd.cursor();

                lcd.print(key2);
                entered[currentLength] = key2;
                currentLength++;
                delay(100);
                lcd.noCursor();
                lcd.setCursor(currentLength + 6, 0);
                lcd.print("*");
                lcd.setCursor(currentLength + 7, 0);
                lcd.cursor();
            }
        }

        if (currentLength == 4) {
            if (entered[0] == password[0] && entered[1] == password[1] && entered[2] == password[2] && entered[3] == password[3]) {
                lcd.noCursor();
                lcd.clear();
                lcd.home();
                lcd.print("Bomb Defused");
                currentLength = 0;
                delay(2500);
                lcd.setCursor(0,1);
                lcd.print("Reset the Bomb");
                delay(1000000);
            } else {
                lcd.noCursor();
                lcd.clear();
                lcd.home();
                lcd.print("Wrong Password!");
                delay(1500);
                currentLength = 0;
            }
        }
    }
}

void timer() {
    Serial.print(Scount);
    Serial.println();

    if (Hcount <= 0) {
        if ( Mcount < 0 ) {
            lcd.noCursor();
            lcd.clear();
            lcd.home();
            lcd.print("The Bomb Has ");
            lcd.setCursor (0,1);
            lcd.print("Exploded!");
        }
    }

    lcd.setCursor (0,1); // sets cursor to 2nd line
    lcd.print ("Timer:");

    if (Hcount >= 10)
    {
        lcd.setCursor (7,1);
        lcd.print (Hcount);
    }
    if (Hcount < 10)
    {
        lcd.setCursor (7,1);
        lcd.write ("0");
        lcd.setCursor (8,1);
        lcd.print (Hcount);
    }

    lcd.print (":");

    if (Mcount >= 10)
    {
        lcd.setCursor (10,1);
        lcd.print (Mcount);
    }
    if (Mcount < 10)
    {
        lcd.setCursor (10,1);
        lcd.write ("0");
        lcd.setCursor (11,1);
        lcd.print (Mcount);
    }

    lcd.print (":");

    if (Scount >= 10)
    {
        lcd.setCursor (13,1);
        lcd.print (Scount);
    }
    if (Scount < 10)
    {
        lcd.setCursor (13,1);
        lcd.write ("0");
        lcd.setCursor (14,1);
        lcd.print (Scount);
    }

    if (Hcount <0)
    {
        Hcount = 0;
    }

    if (Mcount <0)
    {
        Hcount --;
        Mcount = 59;
    }

    if (Scount <1) // if 60 do this operation
    {
        Mcount --; // add 1 to Mcount
        Scount = 59; // reset Scount
    }

    if (Scount > 0) // do this oper. 59 times
    {
        unsigned long currentMillis = millis();

        if(currentMillis - secMillis > interval)
        {
            secMillis = currentMillis;
            Scount --; // add 1 to Scount
        }
    }
}
