/* 
- Write a program that reads from stdin the length of an array and
  then store in it the numbers given from stdin. The program should
  then prints the numbers in **reverse order**. Remember to properly
  free the used memory. You should divide the problem in two parts:

  1. Write one **template** function that allocates on the *heap* one
     array of a given size, initialize its elements and returns the
       pointer to the first element.

  2. Write a **template** function that prints the elements of an
     array in the reverse order.

- Test with integers and doubles.

- Use `std::size_t`.
*/

#include<iostream>
#include<cstring>

template <typename T>
T* init(std::size_t n);

//template <typename T>	prova per fare un array di tutti i tipi
//T* initiauto(std::size_t n);

template <typename T>
void print_a(const T* a, std::size_t n);

int main () {

  std::cout << "Please insert array lenght: ";
  std::size_t n;
  std::cin >> n;
   
  //int* const a{init<int>(n)};

  auto a = init<int>(n);
  //auto b = init<double>(n);


  std::cout << "Please fill the array of leght "<< n <<", insering "<< n <<" numbers."<< std::endl;
  for(std::size_t i{0}; i<n; i++){
    std::cin>>*(a+i);
   }

  print_a<int>(a,n);  

  delete[] a;
return 0;
}

template <typename T>
T* init(std::size_t n){			//con auto* const a sarebbe T* solo init(std::size_t n)
   return new T[n];  // allocated on the HEAP 
   
   //auto * const a=new T[n];  prova per fare un array di tutti i tipi, ma non funziona
   //for(std::size_t i{0}; i<n; i++){std::cin>>*(a+i);}
   //return a;

}

template <typename T>
void print_a(const T* a, std::size_t n){
  for(std::size_t i{0}; i<n; i++){
    std::cout << "a[" << i << "] = " << a[n-i-1] << "\n";
}
}
