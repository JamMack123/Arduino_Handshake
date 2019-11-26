#include <Arduino.h>





void setup(){
	init();
	Serial.begin(9600);

}



int customRand(int k){
	bool isPrime = false;
	int ans = 0;


	for (int i = 0; i < k-1; i++){
		int bit = analogRead(A3) & 1;
		ans += (bit << i);
	}

	ans += 1 << k;
	return ans;
}




int main(){
	setup();
	while (true){
	Serial.println(customRand(5));
}
}