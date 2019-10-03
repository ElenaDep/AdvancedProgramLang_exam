#include<iostream>
#include<string>
#include<fstream>

int main(){

std::string s1;
int i {1};

std::ifstream myfile;
myfile.open("testo.txt");

std::getline(myfile,s1);

std::string line;
while(std::getline(myfile,line))
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

std::cout<<"\t"<<i<<s1<<"\n";

myfile.close();
return 0;

}




