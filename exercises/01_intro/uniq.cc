#include<iostream>
#include<string>

int main(){

std::string s1;
int i {1};

std::getline(std::cin,s1);

std::string line;
while(std::getline(std::cin,line))
{

	if(line == s1){
	i++;
	}
	if(line != s1){	
	std::cout<<"\t"<<i<<s1<<"\n";
	i=1;
	}
	s1=line;
}

return 0;

}




