#include <Arduino.h>

void setup()
{
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(13, INPUT);
    digitalWrite(13, LOW);
}
//Previous mulmod didn't like large values, This mulmod is the one taken from the
//working solutio on eclass
uint32_t mulmod(uint32_t a, uint32_t b, uint32_t m)
{
    uint32_t result = 0;
    uint32_t dblVal = a % m;
    uint32_t newB = b;
    // This is the result of working through the worksheet.
    // Notice the extreme similarity with powmod.
    while (newB > 0)
    {
        if (newB & 1)
        {
            result = (result + dblVal) % m;
        }
        dblVal = (dblVal << 1) % m;
        newB = (newB >> 1);
    }

    return result;
}

//Previous powmod did not like large numbers. This function is the one
//from the working solution off of eclass
uint32_t powMod(uint32_t a, uint32_t b, uint32_t m)
{
    uint32_t result = 1 % m;
    uint32_t sqrVal = a % m;  // stores a^{2^i} values, initially 2^{2^0}
    uint32_t newB = b;
    // See the lecture notes for a description of why this works.
    while (newB > 0)
    {
        if (newB & 1)    // evalutates to true iff i'th bit of b is 1 in the i'th iteration
        {
            result = mulmod(result, sqrVal, m);
        }
        sqrVal = mulmod(sqrVal, sqrVal, m);
        newB = (newB >> 1);
    }
    return result;
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
//Runs the main code required for encypted communication between
//the two arduino boards. Involving both encyption and decyrption
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
            uint32_t encypted2 = powMod(10, e, m);
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

/***********************************************

BEGGINING OF PART 2 CODE FUNCTION IMPLEMENETATION

************************************************/

//The function creates a (k+1) random bit number I.E if k = 14 it generates a
//15 bit number
uint32_t customRand(uint32_t k)
{
    uint32_t ans = 0;
    for (int i = 0; i <= k - 1; i++)
    {
        //Reads pin A0 and adds the least sig bit to ans
        uint32_t bit = analogRead(A0) & 1;
        ans += (bit << i);
    }
    ans += 1 << k;
    return ans;
}
//Upper sqrt function taken from the primality morning problem
uint32_t upper_sqrt(uint32_t n)
{
    uint32_t d = sqrt((double) n);
    // should iterate at most once or twice
    // the second condition is to protect against overflow
    // if n is very close to the maximum 32-bit integer
    while (d * d <= n && d <= (1 << 16))
    {
        ++d;
    }
    return d;
}
//A Boolean function to determine if a value is prime
//code based off of primality morning problem solution
bool isPrime(uint32_t value)
{
    bool isPrime = true;
    uint32_t bound_val = upper_sqrt(value);
    if (value == 1)
    {
        isPrime = false;
    }
    for (uint32_t i = 2; i < bound_val; i++)
    {
        if (value % i == 0)
        {
            isPrime = false;
        }
    }
    return isPrime;
}
//Repeatedly tests a random value to see if it is prime
//if not prime it will regenerate the random number and test again
uint32_t findPrime()
{   
    //Named isPrime_2 since isPrime is already used as a function
    bool isPrime_2 = 0;
    uint32_t val = 0;
    while (!isPrime_2)
    {
        val = customRand(14);
        if (isPrime(val) == 1)
        {
            isPrime_2 = 1;
        }
    }
    return val;
}
//GCD euclid fast taken from code given in class
uint32_t gcd_euclid_fast(uint32_t a, uint32_t b)
{
    while (b > 0)
    {
        a %= b;
        // now swap them
        uint32_t tmp = a;
        a = b;
        b = tmp;
    }
    return a; // b is 0
}
//Finds the value e where e*d = 1 mod(phi(n)). This function randomly picks a
//e that is co-prime to phi(n)
uint32_t findE (uint32_t phi)
{
    uint32_t e = customRand(14);
    while(gcd_euclid_fast(e, phi) != 1)
    {
        //Regenerates e if not co-prime
        e = customRand(14);
    }
    return e;
}
//Uses the extended eucildean algorithim to find a d such that e*d = 1 mod(phi(n))
int32_t findD(uint32_t phi, uint32_t e)
{
    int32_t r[40] = {0};
    int32_t s[40] = {0};
    int32_t t[40] = {0};
    int32_t q;
    r[0] = phi;
    r[1] = e;
    t[0] = 0;
    t[1] = 1;
    for (int i = 1; r[i] > 0; i++)
    {
        q = r[i - 1] / r[i];
        r[i + 1] = r[i - 1] - q * r[i];
        t[i + 1] = t[i - 1] - q * t[i];
    }
    for(int i = 0; i < 40; i++)
    {
        if (r[i] == 0)
        {
            return t[i - 1];
        }
    }
    return 0;
}
//Uses pass by reference to create one function to return all the keys
//and modulus values of the the source arduino.
uint32_t keyGeneration(int32_t &d, uint32_t &e, uint32_t &n)
{
    uint32_t p = findPrime();
    uint32_t q = findPrime();
    n = p * q;
    uint32_t p1 = (p - 1);
    uint32_t q1 = (q - 1);
    //Phi coresponds to phi(n)
    uint32_t phi = p1 * q1;
    e = findE(phi);
    d = findD(phi, e);
    if (d < 0)
    {
        int32_t z = ((-d) / (phi)) + 1;
        // correction if d ends up being negitive
        int32_t fix = -1;
        while(fix < 0)
        {
            fix = (d + z * phi) % phi;
        }
        d = fix % phi;
    }
    return d;
}

/**********************************************************************
The following few functions relate to the handshake between the
Client and the Server
************************************************************************/



/** Waits for a certain number of bytes on Serial3 or timeout
* @param nbytes : the number of bytes we want
* @param timeout : timeout period (ms); specifying a negative number
* turns off timeouts (the function waits indefinitely
* if timeouts are turned off).
* @return True if the required number of bytes have arrived .
*/
bool wait_on_serial3 ( uint8_t nbytes, long timeout )
{
    unsigned long deadline = millis() + timeout ;// wraparound not a problem
    while (Serial3.available() < nbytes && ( timeout < 0 || millis () < deadline ) )
    {
        delay (1) ; // be nice , no busy loop
    }
    return Serial3 . available () >= nbytes ;
}

//Code for client sided finite state machine handshake
void clientShake(uint32_t cPKey, uint32_t cMod, uint32_t &sPkey, uint32_t &sMod)
{
    enum clientState
    {
        sending, ready
    };
    //Ack tracks acknokledgment character
    uint32_t ack;
    bool ackFound = false;
    clientState state = sending;
    while (state != ready)
    {
        if (state == sending)
        {
            Serial3.write('C');
            uinnt32_to_serial3(cPKey);
            uinnt32_to_serial3(cMod);
            //This is used instead of the wait on serial 3 so it doesn't matter
            //if there is data in the buffer until 'A' is read, this will send keys every second
            delay(1000);
            ack = Serial3.read();
            Serial3.flush();

            if(ack == 'A')
            {   
                
                Serial3.write('A');
                //Delay simply to slow reading from buffer to ensure
                //key values are sitting in buffer
                delay(50);
                sPkey = uinnt32_from_serial3();
                sMod = uinnt32_from_serial3();
                ackFound = true;
                state = ready;
            }
        }
        if (state == ready)
        {
            Serial.println("Chat is Set. Enjoy your communictaion!");
            delay(50);
        }

    }

}
//Code for the server handshake
void serverShake(uint32_t sKey, uint32_t sMod, uint32_t &cKey, uint32_t &cMod )
{
    enum serverState
    {
        listen, keyWait, ackWait, ready
    };
    serverState state = listen;
    // keyrec keeps track of whether or not keys
    // have been recived
    bool keyRec = false;
    bool keySent = false;

    while (state != ready)
    {
        if (state == listen)
        {
            //resets to false incase of timout errors
            keySent = false;
            keyRec = false;
            Serial.println("Waiting for connection request...");
            uint32_t read = Serial3.read();
            // timeout time set to 999 instead of 1000 to prevent
            //a accidental perfect sync in which both devices are acting at the same
            //instant in time
            if (wait_on_serial3(1, 999) == false)
            {
                state = listen;
            }
            //Checks for C character moves state to key wait state 
            else if (read == 67)
            {
                state = keyWait;
                Serial.println("Request found!");
            }
        }
        if (state == keyWait)
        {
            Serial.println("Waiting for key and mod...");
            if(wait_on_serial3(4, 1000) == false)
            {
                // timeout
                state = listen;
            }
            if (keyRec == false)
            {
                if (Serial3.available() >= 8){
                    cKey = uinnt32_from_serial3();
                    cMod = uinnt32_from_serial3();
                    Serial3.write('A');
            }
                if (keySent == false)
                {
                    uinnt32_to_serial3(sKey);
                    uinnt32_to_serial3(sMod);
                    //Only allows for one copy of keys to be sent across buffer
                    keySent = true;
                }
                keyRec = true;
                state = ackWait;
            }
        }
        if (state == ackWait)
        {
            Serial.println("Waiting for acknowledgment...");

            // Our code refuses to work without
            // this wait_on_serial3 function call
            // for some reason

            uint32_t ack = 0;
            if (Serial3.available() >= 1){
                delay(25);
                ack = Serial3.read();
                Serial3.flush();
            }
            if (ack == 'A')
            {
                Serial.println("Acknowledgment found!");
                delay(50);
                state = ready;
            }
            else if (ack == 67)
            {
                Serial.println("CR received, waiting for keys");
                delay(50);
                keyRec = false;
                state = keyWait;
            }
            else if (ack >= 1)
            {
                Serial.println("Incorrect term recieved: restarting");
                delay(50);
                state = listen;
            }

            else if (wait_on_serial3(1, 1000) == false)
            {
                Serial.println("System Timed out: restarting");
                keyRec = false;
                state = listen;
            }
        }
        if (state == ready)
        {
            Serial.println("Chat is Set. Enjoy your communictaion!");
            delay(50);
        }
    }
}
int main()
{
    setup();
    int32_t d = 0;
    // pubkey is the public key of the
    // source arduino while e is the public key
    // of the other arduino
    uint32_t pubKey = 0;
    uint32_t n = 0;
    uint32_t e = 0;
    uint32_t m = 0;
    uint32_t val = digitalRead(13);
    if (val == 1)
    {
        Serial.println("Arduino chat: Server!");
        // For some reason we need this delay
        delay(25);
        keyGeneration(d, pubKey, n);
        serverShake(pubKey, n, e, m);
    }
    if (val == 0)
    {
        Serial.println("Arduino chat: Client!");
        // For some reason we need this delay
        delay(25);
        keyGeneration(d, pubKey, n);
        clientShake(pubKey, n, e, m);
    }
    //Devices cannot exit ready state once either recognizes a chat has begun both
    //will require reset to restablish connection
    while (true)
    {
        reader(e, d, m, n);
    }

}
