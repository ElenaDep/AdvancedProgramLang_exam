#include<iostream>
#include<cstring>

template <typename T>
T* init(std::size_t n, T* a);

template <typename T>
void print_a(const T* a, std::size_t n);

int main () {

  std::cout << "Please insert array lenght: ";
  std::size_t n;
  std::cin >> n;
  
  int* const a{init<int>(n, a)};

  for(std::size_t i{0}; i<n; i++){
    std::cin>>*(a+i);
  }

  print_a<int>(a,n);  

  delete[] a;
return 0;
}

template <typename T>
T* init(std::size_t n, T* a){
  return new T[n];  // allocated on the HEAP 
}

template <typename T>
void print_a(const T* a, std::size_t n){
  for(std::size_t i{0}; i<n; i++){
    std::cout << "a[" << i << "] = " << a[n-i-1] << "\n";
}
}
