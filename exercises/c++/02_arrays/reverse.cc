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
