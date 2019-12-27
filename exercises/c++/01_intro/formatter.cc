#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

int main()
{
    for(std::string line; std::getline(std::cin, line);)
    {
        if(line.size() <= 40)//size returns the num of bytes. 1char=1bytes
        {
	    //std::cout<<"linesize: "<< line.size()<< "\n";	
            std::cout << line << std::endl;
        }
        else
        {
            while(line.size() > 40)
            {
                int out{40};
                std::string sub{line.substr(0,out+1)};//substr prende fino a pos non incluso. 
						      //fino a out+1 per considerare il caso in cui l'ultimo sia uno spazio 
                
		out = sub.find_last_of(" ");// per non andare a capo tagliando le parole
                sub = sub.substr(0,out);// qui fino a out cosi non  stampa lo spazio finale
                
	    	//std::cout<<"sub.size: "<< sub.size()<< "\n";	
		std::cout << sub << std::endl;
                
		line = line.erase(0,out+1);
            }
	    std::cout<<"linesize: "<< line.size()<< "\n";	
            std::cout << line << std::endl;
        }
    }

    return 0;
}
