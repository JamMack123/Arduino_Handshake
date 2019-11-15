#include <Arduino.h>

void setup()
{
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(13, INPUT);
    digitalWrite(13, LOW);
}
uint32_t mulmod(uint32_t a, uint32_t b, uint32_t m)
{
    uint32_t sum = 0;
    //Keeps removing least significant bit of a until no bits remain
    // If the ith bit in a is 1 it will add b*2^i to the sum mation
    while(a != 0)
    {
        if (a & 1)
        {
            sum += (b);
        }
        //Removes the least significant bit of a to decrease
        //a total value
        a >>= 1;
        //Multiplies b by 2 i times i being the number of bits
        //in a
        b = b * 2 % m;
    }
    return sum % m;
}
/* Calculates the value to the power of e using fast exponetiation*/
uint32_t powMod(uint32_t value, uint32_t e, uint32_t modulus)
{
    //Intalized as 1 so subsequent multiplications do not fail
    uint32_t ans = 1;
    while (e != 0)
    {
        if (e & 1 != 0)
        {
            ans = mulmod(ans, value, modulus);
        }
        value = mulmod(value, value, modulus);
        e = e / 2;
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

void reader(uint32_t e, uint32_t d, uint32_t m, uint32_t n)
{
    uint32_t tempByte = 0;
    if (Serial.available() > 0)
    {
        uint32_t byte_read = Serial.read();
        //IF key is ENTER send the carriage
        //and newline character
        if (byte_read == 13)
        {
            Serial.write("\r\n");
            uint32_t encypted1 = powMod(13, e, m);
            uint32_t encypted2 = powMod(10, e, m);
            uinnt32_to_serial3(encypted1);
            uinnt32_to_serial3(encypted2);
        }
        //Sends inputted text to Serial 3 after encyrption
        tempByte = powMod(byte_read, e, m);
        uinnt32_to_serial3(tempByte);
        Serial.write(byte_read);
    }
    if (Serial3.available() >= 4)
    {
        //Reads 4 bytes from serial3 and decyrpts
        uint32_t bit = uinnt32_from_serial3();
        tempByte = powMod(bit, d, n);
        Serial.write(tempByte);
    }
}

int main()
{
    //We could not get a val from setup without passing some
    uint32_t somethingToPass = 0;
    setup();
    uint32_t val =digitalRead(13);
    if (val == 1)
    {
        Serial.println("Arduino chat: Server!");
        // For some reason we need this delay IT IS SACRED CODE!
        delay(20);
    }
    if (val == 0)
    {
        Serial.println("Arduino chat: Client!");
        // For some reason we need this delay IT IS SACRED CODE!
        delay(20);
    }
    //Creates a loop to infinetly read from the serial monitors
    while (true)
    {
        //Using state given from setup
        //intialize values the device needs
        if (val == 1)
        {
            //intializes the server side values
            uint32_t d1 = 27103;
            uint32_t n1 = 95477;
            uint32_t e1 = 11;
            uint32_t m1 = 84823;
            reader(e1, d1, m1, n1);
        }
        else
        {
            //intializes the client side values
            uint32_t d1 = 38291;
            uint32_t n1 = 84823;
            uint32_t e1 = 7;
            uint32_t m1 = 95477;
            reader(e1, d1, m1, n1);
        }

    }
}
