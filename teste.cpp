#include "bibs/evo.h"

class numero : private individuo<double>{
public:
	numero(double x=0){
		genes.push_back(x);
	}
};

int main(){
	printf("hello world\n");
	return 0;
}
