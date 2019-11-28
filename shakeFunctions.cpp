#include "Arduino.h"

void setup()
{
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    pinMode(13, INPUT);
    digitalWrite(13, LOW);
}





/** Waits for a certain number of bytes on Serial3 or timeout
* @param nbytes : the number of bytes we want
* @param timeout : timeout period (ms); specifying a negative number
* turns off timeouts (the function waits indefinitely
* if timeouts are turned off).
* @return True if the required number of bytes have arrived .
*/
bool wait_on_serial3 ( uint8_t nbytes , long timeout ) {
	unsigned long deadline = millis () + timeout ;// wraparound not a problem
	while ( Serial3 . available () < nbytes && ( timeout < 0 || millis () < deadline ) )
	{
	delay (1) ; // be nice , no busy loop
	}
	return Serial3 . available () >= nbytes ;
}





void clientShake(){
	enum clientState {
		sending, ready
	};

	while (state != ready){
		if (state == sending){
			uinnt32_to_serial3('C');
			uinnt32_to_serial3(cKey);
			uinnt32_to_serial3(cMod);
			uint32_t time = millis();
			wait_on_serial3(1,1);

			if (millis()-time >= 1){
				state = sending;
			}
			else if(uinnt32_from_serial3() == 'A'){
				state = ready;
			}
		}

	}

}


void serverShake(){
	enum serverState {
		listen, keyWait, ackWait, ready
	};
	serverState state = listen;
	uint32_t cKey;
	uint32_t cMod;
	bool keySent = false;
	uint32_t time;

	while (state != ready){
		if (state == listen){
			keySent = false;
			Serial.println("Waiting for connection request...");

			time = millis()
			wait_on_serial3(1,1);

			// timeout check, will be seeing this alot
			if (  (millis() - time) => 1000){
				state = listen;
			}

			else if (Serial3.read() == 67) {
				state = keyWait;
				Serial.println("Request found!");
			}
			
		}

		if (state == keyWait){
			Serial.println("Waiting for key and mod...");


			// waiting for the key
			time = millis();
			wait_on_serial3(4,1);
			if (  (millis() - time) >= 1000){
				state = listen;
			}
			else {
				cKey = uinnt32_from_serial3();
			}

			// now the mod
			time = millis();
			wait_on_serial3(4,1);
			if (  (millis() - time) >= 1000){
				state = listen;
			}
			else {
				cMod = uinnt32_from_serial3();
			}
			// if we haven't timed out, move on
			if (state == keyWait){
				state = ackWait;

			}

			if (keySent == false){
				uinnt32_to_serial3('A');
				uinnt32_to_serial3(sKey);
				uinnt32_to_serial3(sMod);
				keySent = true;
				Serial.println("Keys sent!");
			}
		}

		if (state == ackWait){
			Serial.println("Waiting for ack...");
			time = millis();
			wait_on_serial3(1,1);
			if (  (millis() - time) >= 1000){
				state = listen;
			}
			else if (Serial3.read() == 65){
				Serial.println("Ack found!");
				state = ready;

			}
			else if (Serial3.read() == 67){
				Serial.println("CR received, waiting for keys");
				state = keyWait;
			}
			else{
				Serial.println("Different char received restarting...");
				state = listen;
			}

		}

	}

}






int main(){

}