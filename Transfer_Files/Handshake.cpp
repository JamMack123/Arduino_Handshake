#include <Arduino.h>
uint32_t d = 0;
uint32_t n = 0;
uint32_t e = 0;
uint32_t m = 0;

void setup(){
    int val;
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(13, INPUT);
    digitalWrite(13, LOW);
    val = digitalRead(13);
    if (val == 1){
        Serial.println("Arduino chat: Server!");
        // For some reason we need this delay IT IS SACRED CODE!
        delay(20);
        d = 27103;
        n = 95477;
        e = 11;
        m = 84823;
   
    }
    if (val == 0){
        Serial.println("Arduino chat: Client!");
        // For some reason we need this delay IT IS SACRED CODE!
        delay(20);
        d = 38291;
        n = 84823;
        e = 7;
        m = 95477;
    }
}
void reader(){
    char myArray[20];
    if (Serial.available()>0){
        uint8_t byte_read =Serial.read();
            Serial3.write(byte_read);
    }
    if (Serial3.available() > 0) {
      uint8_t byte_read = Serial3.read();
      Serial.write(byte_read);
}
}
int main(){
    setup();
   
    while (true){
        reader();
    }
}
