int GPActiveBuzzer = 13;

void setup () {
    pinMode (GPActiveBuzzer, OUTPUT);
}

void loop () {
    digitalWrite (GPActiveBuzzer, HIGH);
    delay (3000);
    digitalWrite (GPActiveBuzzer, LOW);
    delay (2000);
}
