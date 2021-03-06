int GPActiveBuzzer = 13;

// https://www.thegeekpub.com/wiki/sensor-wiki-ky-012-active-piezo-buzzer-module/

void setup ()
{
  pinMode (GPActiveBuzzer, OUTPUT); // set pin to output mode
}
  
void loop () //Main program loop
{
  digitalWrite (GPActiveBuzzer, HIGH); // sound the buzzer
  delay (3000); // pause code for 3 seconds
  digitalWrite (GPActiveBuzzer, LOW); // stop the buzzer
  delay (2000); // pause code for 2 seconds
}
