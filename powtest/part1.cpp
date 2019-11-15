
#include <iostream>

using namespace std;




int mulmod(uint32_t a, uint32_t b, uint32_t m){
	uint32_t sum = 0;
	a = a%m;
	b = b%m;
	for (int i = 0; i<31; i++){
		if ( (a & 1<<i) != 0 ){
			sum = ( ( ( (1 << i) % m * b ) % m) + sum ) % m;
		}
	}
	return sum % m;
}



int main(){

	uint32_t sPub = 7;
	uint32_t sPriv = 27103;
	uint32_t sm = 95477;
	uint32_t cPub = 11;
	uint32_t cPriv = 38291;
	uint32_t cm = 84823;
	



	uint32_t c = 97;

	uint32_t e = 11;

	uint32_t m = 84823;

	uint32_t x = 1;

	uint32_t pow = c;

	while (e != 0){
		if (e & 1 != 0){
			x = mulmod(x,pow,m);
		}
		pow = mulmod(pow,pow,m);
		e = e/2;
	}

	cout << x <<endl;
	uint32_t n = 84823;

	uint32_t d = 38291 % n;
	uint32_t y = 1 % n;
	uint32_t pow2 = x % n ;

	while (d != 0){
		if (d & 1 != 0){
			y = mulmod(y, pow2, n) % n;
		}
		pow2 = mulmod(pow2,pow2,n) % n;
		d=d/2 % n;
	}
	cout << y % n  <<endl;






	return 0;



}
