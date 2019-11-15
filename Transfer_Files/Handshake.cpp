#include <Arduino.h>
uint32_t d = 0;
uint32_t n = 0;
uint32_t e = 0;
uint32_t m = 0;

void setup()
{
    int val;
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(13, INPUT);
    digitalWrite(13, LOW);
    val = digitalRead(13);
    if (val == 1)
    {
        Serial.println("Arduino chat: Server!");
        // For some reason we need this delay IT IS SACRED CODE!
        delay(20);
        d = 27103;
        n = 95477;
        e = 11;
        m = 84823;

    }
    if (val == 0)
    {
        Serial.println("Arduino chat: Client!");
        // For some reason we need this delay IT IS SACRED CODE!
        delay(20);
        d = 38291;
        n = 84823;
        e = 7;
        m = 95477;
    }
}
uint32_t mulmod(uint32_t a, uint32_t b, uint32_t m){
uint32_t sum= 0;
//Keeps removing least significant bit of a until no bits remain
// If the ith bit in a is 1 it will add b*2^i to the sum mation
    while(a!=0){
        if (a&1){
            sum += (b);
        }
        a>>=1;
        b = b*2%m;
    }
}
uint32_t encryptDecyrpt( uint32_t e, uint32_t value, uint32_t modulus){
    //Intalized as 1 so subsequent multiplications do not fail
   uint32_t ans = 1; 
   while (e != 0){
        if (e & 1 != 0){
            ans = mulmod(ans,value,modulus);
        }
        value = mulmod(value,value,modulus);
        e = e/2;
    }
    return ans;
}

/* * Writes an uint32_t to Serial3 , starting from the least - significant
* and finishing with the most significant byte .
*/
void uinnt32_to_serial3 (uint32_t num)
{
    Serial3.write (( char ) ( num >> 0) ) ;
    Serial3.write (( char ) ( num >> 8) ) ;
    Serial3.write (( char ) ( num >> 16) ) ;
    Serial3.write (( char ) ( num >> 24) ) ;
}
/* * Reads an uint32_t from Serial3 , starting from the least - significant
* and finishing with the most significant byte .
*/
uint32_t uinnt32_from_serial3 ()
{
    uint32_t num = 0;
    num = num | (( uint32_t ) Serial3.read () ) << 0;
    num = num | (( uint32_t ) Serial3.read () ) << 8;
    num = num | (( uint32_t ) Serial3.read () ) << 16;
    num = num | (( uint32_t ) Serial3.read () ) << 24;
    return num ;
}


void reader()
{
    char myArray[20];
    if (Serial.available() > 0)
    {
        uint32_t byte_read = Serial.read();
        if (byte_read == 13)
        {
            Serial.write("\r\n");
            //Add the ASCII VALUE 10 and 13 to get encypted then sent to
            // the serial3
        }
        uinnt32_to_serial3(byte_read);
        Serial.write(byte_read);
    }
    if (Serial3.available() > 0)
    {
        Serial.write(uinnt32_from_serial3());

    }
}

int main()
{
    setup();
    //Creates a loop to infinetly read from the serial monitors
    while (true)
    {
        reader();
    }
}
