#include<iostream>
#include<iomanip>
#include <string>


int main(){

  double i{}, c{0.};

    std::cout<< "Please insert an double value"<< "\n";

    while(!(std::cin>>i) || ( i-(int)i == c)) {  	//it returns true if std::cin is a double and it fails if it's a double

	std::cout<< "Error! The input value is not an double, please insert it again."<< "\n";
	std::cin.clear();
	std::cin.ignore(100,'\n');

    }

	std::cin.ignore(100,'\n');

	/*c= int(i) - i;
	std::cout<< c << "\n";*/

    std::cout<<"The insert value "<< i <<" is a correct double"<<std::endl;
    return 0;
	
}
