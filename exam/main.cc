#include <memory> //unique_ptr
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <chrono>
#include <functional>

#include "bst.hpp"

typedef std::chrono::high_resolution_clock Clock;

void fill_me ( bst< int, double>& Tree) {

  std::pair<int, double> p(1,10.);
  Tree.insert( p );
  Tree.insert( {2, 1.2} );

  return;
  
}

/*
void balance_tree () {

  // allocate an object of class Tree
  bst< int, double > myT;

  // insert elements into the two allocated objects
  // (pairs 'key-value' are read from stdin)
  int key;
  double value;
  while ( std::cin >> key >> value )
    myT.insert( {key, value} );
  
  auto myT_time_start = Clock::now();
  myT.balance();
  auto myT_time_end = Clock::now();
  double myT_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myT_time_end - myT_time_start).count();
  std::cout << myT_time << std::endl;

  myT.clear();
  
  return;
  
}*/


int main(){

   std::cout << "Albero coi frutti" << std::endl;
		
   bst<int, double> Tree{};
   
   //fill_me( Tree);

   std::pair<int, double> p(1,10.);
   Tree.insert( p );
   Tree.insert( {2, 1.2} );
   Tree.insert( {8,1.6} );   
   Tree.insert( {5,1.9} );   
   Tree.insert( {4,1.5} );   
   Tree.insert( {3,1.4} );
   Tree.insert( {2, 120.} );
   Tree.insert( {2, 45.} );
   Tree.insert( {10, 1.9} );
   Tree.insert( {10, 1.2} );

   // cmp non funzione dice che:
   // error: cannot call member function ‘bool bst<K, V, C>::cmp(const K&, K&) [with K = int; V = double; C = std::less<int>]’ without object
   // bool a = bst<int, double, std::less<int>>::cmp(2, 3);
   
   bst< int, double >::iterator it = Tree.top();
   std::cout << "\n!! ---- Check if they correspond ---- !!\n" << std::endl;
   std::cout << "Checking position in Tree:\n\t should be 5:\t" << it->right->right->left->key()<< "\n";//right->left->key() << std::endl;
   std::cout << "Checking Tree.find(2):\n\t should be 45.0 :\t" << Tree.find( 2 )->value() << std::endl;
   std::cout << "Checking Tree[2]:\n\t should be 45.0 :\t" << Tree[2] << std::endl;
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
  
   //Tree2.clear();
   
   auto t_start = Clock::now();
   Tree.balance();
   auto t_end = Clock::now();
   double ttime = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start).count();
   std::cout<< "Time to balance the tree: " << ttime << " nanoseconds" << std::endl ;
   

   Tree.clear();
   if ( ! Tree.top().operator->() )
   std::cout << "\n!! --------- Done all clear --------- !!\n" << std::endl;

   return 0;
}
