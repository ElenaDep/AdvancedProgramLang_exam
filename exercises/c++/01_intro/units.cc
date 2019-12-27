#include<iostream>
#include<string>


int main()
{    
    double num{};
    std::string unit{};
    bool test{false};//per controllare se le unita di misura inserite sono giuste
   
    while(!test){
    std::cout << "Please insert a number and an unit measure (e.g. 25 feet)" << std::endl;
    std::cout << "(choose between: inches, feet, miles, yards, ounces, pounds):" << std::endl;
    
    std::cin >> num >> unit;
    
    std::string units_eng[]{"inches", "feet", "miles", "yards", "ounces", "pounds"};
    
    double conv_values[]{0.0254, 0.3048, 1609.35, 0.9144, 0.0283495, 0.453592};
    
    std::string units_si[]{"meters", "meters", "meters", "meters", "kg", "kg"};
    
    // sizeof() returns the byte-size of the array
    for (int i = 0; i < sizeof(conv_values) / sizeof(double); ++i)
    {
        if(unit == units_eng[i])
        {
            std::cout << num << " " << unit << " are " << num*conv_values[i] << " " << units_si[i] << std::endl;
            test = true;
            break;//break statement: the loop is immediately terminated
        }
    }
    if(test==false)
    {
        std::cout << "You inserted a wrong input!" << std::endl;
   	unit.clear();
    }
    }
    return 0;
}

