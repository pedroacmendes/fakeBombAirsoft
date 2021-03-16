#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

int GPActiveBuzzer = 13;

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

String teclado;
int tempo = 300; //300segundos = 5min

void setup() {
    //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    //Pinos ligados aos pinos 5, 6, 7 e 8 do teclado - Colunas
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10, INPUT);
    pinMode(11, INPUT);

    pinMode (GPActiveBuzzer, OUTPUT);

    lcd.begin (16,2);
    lcd.setBacklight(HIGH);
    lcd.print("Selecione modo de jogo -> A");
}

void loop() {
    readKeyboard();
}

void readKeyboard(){
    // ti-2 -> LINHA
    for (int ti = 3; ti<7; ti++) { //Alterna o estado dos pinos das linhas
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(ti, HIGH);

        //Verifica se alguma tecla da coluna 1 foi pressionada
        if (digitalRead(8) == HIGH) {
            lcd.clear();
            if(ti-2 == 1){
                lcd.print("1");
            } else if(ti-2 == 2){
                lcd.print("4");
            } else if(ti-2 == 3){
                lcd.print("7");
            } else {
                lcd.print("*");
            }
            while(digitalRead(8) == HIGH){}
        }

        //Verifica se alguma tecla da coluna 2 foi pressionada
        if (digitalRead(9) == HIGH) {
            lcd.clear();
            if(ti-2 == 1){
                lcd.print("2");
            } else if(ti-2 == 2){
                lcd.print("5");
            } else if(ti-2 == 3){
                lcd.print("8");
            } else {
                lcd.print("0");
            }
            while(digitalRead(9) == HIGH){};
        }

        //Verifica se alguma tecla da coluna 3 foi pressionada
        if (digitalRead(10) == HIGH) {
            lcd.clear();
            if(ti-2 == 1){
                lcd.print("3");
            } else if(ti-2 == 2){
                lcd.print("6");
            } else if(ti-2 == 3){
                lcd.print("9");
            } else {
                lcd.print("#");
            }
            while(digitalRead(10) == HIGH){}
        }

        //Verifica se alguma tecla da coluna 4 foi pressionada
        if (digitalRead(11) == HIGH) {
            lcd.clear();
            if(ti-2 == 1){
                lcd.print("A");
                game1();
            } else if(ti-2 == 2){
                lcd.print("B");
            } else if(ti-2 == 3){
                lcd.print("C");
            } else {
                lcd.print("D");
            }
            while(digitalRead(11) == HIGH){}
        }

    }
}

void game1(){
    // contagem regressiva de 5 minutos e mostrar contagem decrescente no ecra
    while (tempo >= 0) {
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("GAME TIME: 5 min");
        lcd.setCursor(6,1);
        lcd.print("00");
        lcd.print(":");
        lcd.print(tempo);
        tempo--;
    }
    // de 5 em 5 segundos apitar

    // digitalWrite (GPActiveBuzzer, HIGH);
    // digitalWrite (GPActiveBuzzer, LOW);

    // se estiver nos ultimos 30 segundos da contagem decrescente apitar de 2 em 2 segundos
}
