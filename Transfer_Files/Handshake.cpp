#include <Arduino.h>
uint32_t d = 0;
uint32_t n = 0;
uint32_t e = 0;
uint32_t m = 0;
int status = 0;

void setup(){
    int val;
    init();
    Serial.begin(9600);
    pinMode(13, INPUT);
    digitalWrite(13, LOW);
    val = digitalRead(13);
    if (val == 1){
        Serial.println("Arduino chat: Server!");
        delay(20);
        d = 27103;
        n = 95477;
        e = 11;
        m = 84823;
   
    }
    if (val == 0){
        Serial.println("Arduino chat: Client!");
        delay(20);
        d = 38291;
        n = 84823;
        e = 7;
        m = 95477;
    }
}
int main(){
    setup();
    Serial.println();
    Serial.print(e);
    delay(10);
}
