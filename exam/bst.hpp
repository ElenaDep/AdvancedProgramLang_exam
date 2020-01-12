#ifndef __BST__HPP__
#define __BST__HPP__

#include <iostream>
#include <utility>
#include <functional>
#include <memory>
#include <cmath>
#include <vector>


// binary search tree class:
template <typename K, typename V, typename C=std::less<K>>
class bst {

   // come uso questo comparatore?
   //C cmp;
   
   // struct node
   struct node{
	
	// content of the node: the key and the value
	std::pair< const K, V> content;
	
	// raw pointer to parent node
	node* parent = nullptr;

	// pointer to left node
	std::unique_ptr<node> left = nullptr;
	
	// pointer to right node
	std::unique_ptr<node> right = nullptr;

	// default constructor
	node() : content{ std::pair< const K, V>{} }, parent{nullptr} {}

	// custom constructor	
	node( std::pair<const K, V>&& p, node* par = nullptr)
	   : content{ std::move(p) }, parent{par} {}
	
        node( const std::pair<const K, V>& p, node* par = nullptr)
	   : content{p}, parent{par} {}

	// default destructor
	~node() = default;

	//node.key() returns the key
	const K& key() const { return content.first; }
	// questa no perche` K e` costante
	// K& key() { return content.first; }
	
	//node.value() returns the value
	const V& value() const { return content.second; }
   	V& value() {return content.second; }
   
	// node find function
        node * find(const K key);

	// recursive function to insert a new node
	std::pair< node*, bool> insert( std::pair<const K, const V> p, const bool sub = false );
   	
	// recursive function to find the leftmost node in the bst
	node* leftmost(){
	
	if(left)
	   return left->leftmost();
	else
	   return this;
	
	}
	
	// clear node in the bst
	void clear(){

	   left.reset();
	   right.reset();
	}

   
   };
   
   // the root of the BSK
   std::unique_ptr<node> root = nullptr;

   // the tail of the BSK
   node * tail = nullptr;

   // in-place balance of a section of the bst
   // it receive as params the iterator to current position,
   // node vector of raw pointers to nodes
   void in_place_balance( typename bst<K, V, C>::iterator pos, const std::vector<node*>& nodes);

   public:
   
   //    
   
   bool cmp( K& k1, K& k2) { 
	C c= C();
	return c( k1, k2); 
   }
   bool cmp( const K& k1, K& k2) { 
       C c = C();
       return c( k1, k2); 
   }
   
   // class iterator
   // it builds the new node
   class iterator{

	node* current;

      public:

	// default constructor
	iterator() noexcept = default;

	// custom constructor
	explicit iterator(node* x) : current{ x } {}

	// de-reference operator overload:
	// returns a reference to the de-referenced object of type node contained
	// in the iterator
	node& operator*() { return *current; }

	// member-access operator overload:
	// returns the raw pointer to the object of type node contained
	// in the iterator
	node* operator->() const { return current; }

	// logical-equality operator overload:
	// returns bool variable, true only if iterators contained 
	// the same pointer
	bool operator==(const iterator& other) { return current == other.current; }
   
   	// logical-inequality operator overload
	bool operator!=(const iterator& other) { return !( *this==other );}
   
   	// pre-increment operator overload
	// returns a pointer to the net element of the bst hierarchy
	iterator& operator++(){
	   if ( current ){
	      if( current->right )
	         current = current->right->leftmost();
	      else
	         current = current->parent;
	   }
	      return *this;
	}

	// post-increment operator overload
	iterator operator++( int){
	
		iterator it{ *this};
		++( *this);
		return it;

	}
   };

   // class const_iterator
   // it inherits from class iterator 
   class const_iterator : public iterator {

      public:
 	
	// 'Iterator' keyword definition
	using Iterator = iterator;
	using Iterator::iterator; 

	// de-reference operator overload
	const node& operator*() const { return Iterator::operator*(); };
	
	// member-access operator overload
	const node* operator->() const { return Iterator::operator->(); };

	//logical-equality operator overload
	using Iterator::operator==;

	//logical-inequality operator overload
	using Iterator::operator!=;
   };

   
   // default constructor
   bst () noexcept = default;


   // COPY & MOVE
   // copy-constructor build by deep-copying
   bst ( const bst& c_bst );

   // copy-assignement operator overload
   bst& operator=( const bst& c_bst ){

      this->clear();
      auto tmp = c_bst;
      (*this) = std::move( tmp );

      return *this;
   }

   // move constructor
   bst ( bst&& c_bst ) : root{std::move( c_bst.root )}, 
		         tail{std::move( c_bst.tail )} {}

   // move-assignement operator
   bst& operator= ( bst&& c_bst ){
	   root = std::move( c_bst.root );
	   tail = std::move( c_bst.tail );
   
   	   return *this;
   }

   // default destructor
   ~bst() noexcept = default;
 
   
   // INSERT FUNCTION
   // bool is true if the new node is allocated
   // iterator to the new node
   std::pair<iterator, bool> insert(const std::pair<K,V>& x);
   //iterator insert(const std::pair<K,V>& x, const bool substitute = false );


   // ITERATOR BEGIN
   // return iterator to the tail of the bst
   iterator begin() { return iterator{tail}; }
   const_iterator begin() const { return iterator{tail}; }
   const_iterator cbegin() const { return const_iterator{tail}; }

   // Iterator to the root
   iterator top() { return iterator{ root.get() }; }

   // ConstIterator to the root 
   const_iterator ctop() const { return const_iterator{ root.get() }; }

   // ITERATOR END
   iterator end() { return iterator{nullptr}; }
   const_iterator end() const { return iterator{nullptr}; }
   const_iterator cend() const { return const_iterator{nullptr}; }


   // FIND FUNCTION
   // returns an iterator to the proper node or ends()
   iterator find(const K& k) { return iterator{ root->find(k) }; }
   const_iterator find(const K& k) const { return const_iterator{ root->find(k) }; }


   
   // BALANCE
   void balance();


   // PUT-TO OPERATOR
   // operator << overload
   template <class oK, class oV >
      friend std::ostream& operator<< ( std::ostream& , bst< oK, oV >& );


   // CLEAR
   // remove all the nodes from the bst
   void clear(){
	
	root.reset();
   }

   // ARRAY SUBSCRIPT OVERLOAD
   V& operator[]( const K& key ) {

   iterator n = find( key );
    
   if ( n == end() ) {
      
      n = insert( {key, 1. } ).first;
      
   }
    
   return n->value();
    
   }

   // CONST ARRAY SUBSCRIPT OVERLOAD
   const K& operator[]( const K key ) const {
    
      const_iterator n = find( key );
    
   if ( n == cend() ) {
      throw key_not_found{ "\n I can't do that\n(key " +  std::to_string(key) + " is not present.)"};
   }
   
   return n->value();
    
   }

   // KEY NOT FOUND
   struct key_not_found {
    
   std::string message;
   key_not_found( const std::string &s ) : message{s} {}
    
   };



   // EMPLACE FUNCTION
   // container constructed in-place
   template< class... Types >
   std::pair<iterator,bool> emplace(Types&&... args);


};

#include "bst.tpp"
#endif
