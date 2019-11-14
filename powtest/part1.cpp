#include <iostream>

using namespace std;




int mulmod(uint32_t a, uint32_t b, uint32_t m){
	uint32_t sum = 0;
	for (int i; i< 31 ; i++){
		if ( (a & 1<<i) != 0) {
			sum = ((((1 << i) * b) % m) + sum) % m;
			cout << sum << endl;
		}
	}

	return  sum;

}



int main(){
	uint32_t d = 1234;
	uint32_t e = 2141;
	uint32_t m = 413;
	uint32_t a = mulmod(d,e,m);

	cout << a << endl;

	return 0;
}