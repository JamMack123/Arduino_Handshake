#include <Arduino.h>
uint32_t serverPublicKey = 7;
uint32_t serverPrivateKey = 27103;
uint32_t serverModulus = 95477;
uint32_t clientPublicKey = 11;
uint32_t clientPrivateKey = 38291;
uint32_t clientModulus = 84823;
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
    }
    if (val == 0){
        Serial.println("Arduino chat: Client!");
        delay(20);
    }
}
int main(){
    setup();
}