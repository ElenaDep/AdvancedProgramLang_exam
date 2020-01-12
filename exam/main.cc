#include <memory> //unique_ptr
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>

#include "bst.hpp"

//library for time measures
typedef std::chrono::high_resolution_clock Clock;


void compare() {
   // allocate an object of class Tree
   bst<int,int> tree{};

   // allocate an object of class Tree
   std::map<int,int> map{};

   std::srand(std::time(nullptr));

   int trial{100000};
   int ks{100};

   for(int i=0; i<trial; ++i){
		int j = std::rand();
		tree.emplace(j,j);
		map.emplace(j,j);
   }

std::cout<< " Num of trials: " << trial << "\n" << "Num of keys tp find: " << ks << std::endl;

   auto t0 = std::chrono::high_resolution_clock::now();
   for(int i=0; i<ks; ++i){
	tree.find(i);
   }
   auto t1 = std::chrono::high_resolution_clock::now();
   auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
   std::cout<< "****** Unbalanced Tree ******" << std::endl;
   std::cout << "Elapsed time: " << elapsed.count() << " [nanoseconds]" << std::endl;

   tree.balance();

   std::cout << std::endl << std::endl;

   t0 = std::chrono::high_resolution_clock::now();
   for(int i=0; i<ks; ++i){
	map.find(i);
   }
   t1 = std::chrono::high_resolution_clock::now();
   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
   std::cout<< "******** Map ********" << std::endl;
   std::cout << "Elapsed time: " << elapsed.count() << " [nanoseconds]" << std::endl;	

   std::cout << std::endl << std::endl;

   t0 = std::chrono::high_resolution_clock::now();
   for(int i=0; i<ks; ++i){
	tree.find(i);
	}
   t1 = std::chrono::high_resolution_clock::now();
   elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0);
   std::cout<< "****** Balanced Tree ******" << std::endl;
   std::cout << "Elapsed time: " << elapsed.count() << " [nanoseconds]" << std::endl;

   tree.clear();

}


int main(){

try{   

   std::cout << "Albero " << std::endl;
		
   bst<int, double> Tree{};
   
   //fill_me( Tree);

   std::pair<int, double> p(1,10.);
   Tree.insert( p );
   Tree.insert( {2, 4.2} );
   Tree.insert( {8,1.6} );   
   Tree.insert( {5,3.9} );   
   Tree.insert( {4,1.5} );   
   Tree.insert( {3,11.4} );
   Tree.insert( {2, 120.} );
   Tree.insert( {2, 3.7} );
   Tree.insert( {10, 1.9} );
   Tree.insert( {10, 1.2} );
   Tree.emplace(12, 1.2);

   std::cout<< "Printing all the tree: " << std::endl;
   std::cout<< Tree ;
   std::cout<< "******* finish to print Tree *******" << std::endl;
 
   // cmp non funzione dice che:
   // error: cannot call member function ‘bool bst<K, V, C>::cmp(const K&, K&) [with K = int; V = double; C = std::less<int>]’ without object
   // bool a = bst<int, double, std::less<int>>::cmp(2, 3);
   
   bst< int, double >::iterator it = Tree.top();
   std::cout << "\n!! ---- Check if they correspond ---- !!\n" << std::endl;
   std::cout << "Checking position in Tree:\n\t should be 5:\t" << it->right->right->left->key()<< "\n";//right->left->key() << std::endl;
   std::cout << "Checking Tree.find(2):\n\t should be 3.7 :\t" << Tree.find( 2 )->value() << std::endl;
   std::cout << "Checking Tree[2]:\n\t should be 3.7 :\t" << Tree[2] << std::endl;
   Tree[2] = 1.1;
   std::cout << "Checking assignment Tree[2]=1.1:\n\t should be 1.1:\t" << Tree[2] << std::endl;
   std::cout << "Checking Tree[6]:\n\t should be default value:\t" << Tree[16] << std::endl;
   std::cout << "Checking assignment Tree[7] (with const Tree):\n\t should not be there and throw exception.\t";

   const auto Tree2 = Tree;
   try{
      std::cout << Tree2[17] << std::endl;
   } catch (const bst<int,double>::key_not_found& s) {
      std::cerr << s.message << std::endl;
   } catch (...) {
      std::cerr << "Unknown exception. Aborting.\n";
     return 1;
   }
  
   auto t_start = Clock::now();
   Tree.balance();
   auto t_end = Clock::now();
   double ttime = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start).count();
   std::cout<< "Elapsed Time of balance() function : " << ttime << " nanoseconds" << std::endl ;
   

   Tree.clear();
   if ( ! Tree.top().operator->() )
   std::cout << "\n ********** Clear all *********\n" << std::endl;

   compare();
   

   } catch (std::exception& bo) {
		std::cerr << bo.what() << std::endl;
   } catch (...) {
		std::cerr << "Unknown exception" << std::endl;
   }

   return 0;

}
