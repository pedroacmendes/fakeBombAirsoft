#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int GPActiveBuzzer = 13;

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

void setup() {
    // Buzzer   
    pinMode (GPActiveBuzzer, OUTPUT);

    digitalWrite (GPActiveBuzzer, HIGH);
    delay (2000);
    digitalWrite (GPActiveBuzzer, LOW);
  
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

    lcd.begin (16,2);
    lcd.setBacklight(HIGH);
    lcd.print("Pressione uma tecla...");
}

void loop() {
    for (int ti = 3; ti<7; ti++) { //Alterna o estado dos pinos das linhas
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(ti, HIGH);

        //Verifica se alguma tecla da coluna 1 foi pressionada
        if (digitalRead(8) == HIGH) {
            imprime_linha_coluna(ti-2, 1);
            while(digitalRead(8) == HIGH){}
        }

        //Verifica se alguma tecla da coluna 2 foi pressionada
        if (digitalRead(9) == HIGH) {
            imprime_linha_coluna(ti-2, 2);
            while(digitalRead(9) == HIGH){};
        }

        //Verifica se alguma tecla da coluna 3 foi pressionada
        if (digitalRead(10) == HIGH) {
            imprime_linha_coluna(ti-2, 3);
            while(digitalRead(10) == HIGH){}
        }

        //Verifica se alguma tecla da coluna 4 foi pressionada
        if (digitalRead(11) == HIGH) {
            imprime_linha_coluna(ti-2, 4);
            while(digitalRead(11) == HIGH){}
        }

    }
    delay(10);
}

void imprime_linha_coluna(int x, int y) {
    lcd.clear();
    lcd.print("Linha : ");
    lcd.print(x);
    lcd.setCursor(0,1);
    lcd.print("Coluna: ");
    lcd.print(y);
    delay(10);
}
