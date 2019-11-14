#include <iostream>

using namespace std;




int mulmod(uint32_t a, uint32_t b, uint32_t m){
	uint32_t sum = 0;
	for (int i = 0; i<31; i++){
		if ( (a & 1<<i)!=0 ){
			sum = ( ( ( (1 << i) * b ) % m) + sum ) % m;
		}
	}
	return sum;
}



int main(){

	uint32_t sPub = 7;
	uint32_t sPriv = 27103;
	uint32_t sm = 95477;
	uint32_t cPub = 11;
	uint32_t cPriv = 38291;
	uint32_t cm = 84823;
	



	uint32_t pow = 'a';

	uint32_t ans = 1;


	
	for (uint32_t i = 0; i < 32; i++){
		if ((cPub & 1 << i) != 0){
			ans = mulmod(ans, pow, cm);
		}
		pow = mulmod(pow,pow,cm);
	}
	cout << ans << endl;


	uint32_t pow2 = 69287;
	uint32_t ans2 = 1;
	for (uint32_t i = 0; i < 32; i++){
		if ((cPriv & 1 << i) != 0){
			ans2 = mulmod(ans2, pow2, cm);
		}
		pow2 = mulmod(pow2,pow2,cm);
	}
	cout << ans2 << endl;





	return 0;



}
