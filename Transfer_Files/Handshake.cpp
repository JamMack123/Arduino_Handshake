/Keeps removing least significant bit of a until no bits remain
// If the ith bit in a is 1 it will add b*2^i to the sum mation
    while(a!=0){
        if (a&1){
            sum += (b);
        }
        a>>=1;
        b = b*2%m;
    }
}
uint32_t powMod( uint32_t e, uint32_t value, uint32_t modulus){
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


void reader(uint32_t e, uint32_t d, uint32_t m, uint32_t n)
{
    if (Serial.available() > 0)
    {
        uint32_t byte_read = Serial.read();
        if (byte_read == 13)
        {
            Serial.write("\r\n");
            uint32_t encypted1 = powMod(e,13,m);
            uint32_t encypted2 = powMod(e,10,m);
            Serial3.write(encypted1);
            Serial3.write(encypted2);
        }
        uinnt32_to_serial3(byte_read);
        Serial.write(powMod(e,byte_read,m));
    }
    if (Serial3.available() > 0)
    {
        Serial.write(encryptDecyrpt(e,uinnt32_from_serial3(),m) );

    }
}

int main()
{
    //We could not get a val from setup without passing some
    uint32_t somethingToPass =0;
    int val = setup(somethingToPass);

    //Creates a loop to infinetly read from the serial monitors
    while (true)
    {
    if (val==1){
       uint32_t d1 = 27103;
       uint32_t n1 = 95477;
       uint32_t e1 = 11;
       uint32_t m1 = 84823;
       reader(e1,d1,m1,n1);
    }else{
        uint32_t d1 = 38291;
        uint32_t n1 = 84823;
        uint32_t e1 = 7;
        uint32_t m1 = 95477;
        reader(e1,d1,m1,n1);
    }
        
    }
}
