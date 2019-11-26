
#include <Arduino.h>

void setup(){
    init();
    Serial.begin(9600);

}
//generates a random  k bit number between 2^k and 2^k+1
int customRand(int k){
    int ans = 0;
    for (int i = 0; i <= k-1; i++){
        int bit = analogRead(A0) & 1;
        ans += (bit << i);
    }
    ans += 1 << k;
    return ans;
}

uint32_t upper_sqrt(uint32_t n) {
    uint32_t d = sqrt((double) n);

    // should iterate at most once or twice
    // the second condition is to protect against overflow
    // if n is very close to the maximum 32-bit integer
    while (d*d <= n && d <= (1<<16)) {
        ++d;
    }

    return d;
}
bool isPrime(uint32_t value){
    bool isPrime = true;

    uint32_t bound_val = upper_sqrt(value);
    if (value == 1){
        isPrime = false;
    }
    for (uint32_t i = 2; i < bound_val; i++){
        if (value%i == 0){
            isPrime = false;
        }
    }
    return isPrime;
}
uint32_t testPrime(uint32_t val){
    bool prime = 0;
    if (isPrime(val)==true){
            return prime;
        }
    return !prime;
}

int main(){
    setup();
    bool notGoingToTakeIt = 1;
    uint32_t val = 0;
    uint32_t v2 = 0;
    while (notGoingToTakeIt){
        Serial.print("Testing ");
        val = customRand(14);
        Serial.println(val);
        if (testPrime(val) == 0){
            Serial.print("Val is prime ");
            Serial.println(val);
            notGoingToTakeIt = 0;
        }
        delay(50);
    }
    notGoingToTakeIt = 1;
    while(notGoingToTakeIt){
        Serial.print("Testing v2 ");
        v2 = customRand(14);
        Serial.println(v2);
        if (testPrime(v2) == 0){
            Serial.print("V2 is prime ");
            Serial.println(v2);
            notGoingToTakeIt = 0;
        }
        delay(50);
    }
    Serial.print("Phi(n) = ");  
    uint32_t p1 = (val-1);
    uint32_t q1 = (v2-1);
    uint32_t phi = p1*q1;
    Serial.println(phi);
    delay(500);
  
}
