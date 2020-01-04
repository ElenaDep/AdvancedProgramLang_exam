/*
 * Implement the Sieve of Eratosthenes algorithm. Write a code that prints on screen the first prime numbers up to `N` **included**, where `N` is read from stdin. The first prime number that should be printed is `2`
*
* To find all the prime numbers less than or equal to a given integer n by Eratosthenes' method:
-Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
-Initially, let p equal 2, the smallest prime number.
-Enumerate the multiples of p by counting in increments of p from 2p to n, and mark them in the list (these will be 2p, 3p, 4p, ...; the p itself should not be marked).
-Find the first number greater than p in the list that is not marked. If there was no such number, stop. Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3.
-When the algorithm terminates, the numbers remaining not marked in the list are all the primes below n.
The main idea here is that every value given to p will be prime, because if it were composite it would be marked as a multiple of some other, smaller prime. Note that some of the numbers may be marked more than once (e.g., 15 will be marked both for 3 and 5).
As a refinement, it is sufficient to mark the numbers in step 3 starting from p2, as all the smaller multiples of p will have already been marked at that point. This means that the algorithm is allowed to terminate in step 4 when p2 is greater than n.[1]
*
*
*THIS IMPLEMENTATION IS MADE USING VECTOR STRUCTURE
*
*
*/

#include <iostream>
#include <vector>
#include <cmath>

#include <chrono>
using namespace std::chrono;

int main(){

	int N{};

	std::cout << "This program implement the Eratosten seive to look for prime nurmber."<<" ";
	std::cout<< " Inser the the N of the interval [0,N] in which you want to look for prime numbers"<<std::endl;

	std::cin >> N;

	// Initialize to false an array of n-1 bool;
	// its index (form 0 to n-2) will correspond to numbers from 2 to n,
	// i.e. we have a shift by 2 between numbers and index

	std::vector<bool> seive(N,false); //false==prime

	unsigned int p{2};
	auto start = high_resolution_clock::now();
	
	while(p <= std::sqrt(N)){

		for(int i=2*p; i<=N; i+=p) seive[i-2]=true;
		
		unsigned int nextp=p+1;
		for( ;nextp<N; ++nextp) if(!seive[nextp-2]) break;
		p=nextp;

	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << duration.count() << " microseconds" << std::endl;	

	std::cout<<"Primes smaller or equal to "<< N << std::endl;
	std::cout<< 1 << ' ';

	for(int i=0; i<N-1;++i){
		if(!seive[i]) std::cout<< i+2 <<' ';
		//std::cout<< i+2 << " " << seive[i] << std::endl;

	}
	std::cout<<"\n";

	return 0;
}

