/*- Populate an array named `primes` containing the first prime numbers
  smaller than 100. Consider 2 as the first prime (i.e. `primes[0] == 2`).

  - you are free to choose the design and the implementation.

  - please comment and motivate your choices (e.g., allocate one big
    array or every time I find a new prime number I increase the size of
    the previous `primes` array, etc.)

*Hints*:

- The remainder of a division between two integers can be computed as
  follows:

```c++
unsigned int remainder = 6%3;
```

- Inside a for loop, you can use `continue` to immediately go to the
  next iteration, `break` to exit the loop. Note that if you have two
  or more nested loops, the statements affect only the innermost loop.
*
*
*HERE I CREATE ONE BIG ARRAY
*
*/

#include <iostream>

bool prime_check(int num){

	bool check{true};

	for(int i=2; i<num; i++){
	  if(!(num%i)){
		check=false;
		break;
	  }
	}
	return check;
}

void print(int * a, size_t lenght){

	for(int i=0; i<lenght; i++)
		std::cout<< *(a+i) << "\n";

}

int main(){

	int n{100};
	//int primes[n];
	int* primes{new int[n]};
	size_t lenght{0};

	primes[0]=1;
	++lenght;

	for(int i=2; i<n; i++){
	
	if(prime_check(i)){
		primes[lenght]=i;
		++lenght;
	}
	}	
	
	std::cout<<"Prime numbers small than 100:"<<std::endl;
	print(primes,lenght);

	// Free heap memory --gsanitize for checking
	delete[] primes;

	return 0;


}

