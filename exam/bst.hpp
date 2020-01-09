#ifndef bst
#define bst

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <cmath>

// binary search tree class:
template <typename key_type, typename key_value, typename C=std::less<key_type>>
class bst(){

   // struct node
   struct node{
	
	// content of the node: the key and the value
	std::pair<key_type, key_value> content;
	
	// raw pointer to parent node
	node * parent = nullptr;

	// pointer to left node
	std::unique_ptr<node> left = nullptr;
	
	// pointer to right node
	std::unique_ptr<node> right = nullptr;

	// default constructor
	node() : content{std::pair<key_type, key_value>{}}, parent{nullptr} {}

	// custom constructor	
	node( key_type t, key_value v, node * par = nullptr)
	   : content{ std::pair<key_type, key_value>(t,v) }, parent{par} {}
	
	// default destructor
	~node() = default;

	//node.type() returns the type
	const key_type& type() const { return content.first; }
	key_type& type() { return content.first; }
	
	//node.value() returns the value
	const key_value& value() const { return content.second; }
   	key_value& value() {return content.second; }
   
   };
  
   // class iterator
   class iterator{

	node* current;

      pubblic:

	// default constructor
	iterator() noexcept = default;

	// custom constructor
	iterator(Node * n) {return *current; }

	// de-reference operator overload:
	// returns a reference to the de-referenced object of type node contained
	// in the iterator
	node& operator*() { return *current; }

	// member-access operator overload:
	// returns the raw pointer to the object of type node contained
	// in the iterator
	node* operator->() { return current; }

	// logical-equality operator overload:
	// returns bool variable, true only if iterators contained 
	// the same pointer
	bool operator==() { return current == other.current; }
   
   	// logigal-inequality operator overload
	bool operator!=() { return !( *this==other );}
   
   	// pre-increment operator overload
	// returns a pointer to the net element of the bst hierarchy
	iterator& operator++(){
	   if ( current ){
	      if(current->right)
	         current= current->right->leftmost();
	      else
	         current = current->parent;
	   }
	}
   };

   // class const_iterator
   // it inherits from class iterator 
   class const_iterator : public iterator<key_type, key_value>{

      public:
 	
	// 'Iterator' keyword definition
	using Iterator = iterator<key_type, value_type>;
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

   
   // the root of the BST
   std::unique_ptr<node> root = nullptr;

   // the tail of the BST
   node * tail = nullptr;

   public:
   
   // default constructor
   bst () noexcept = default;

   // copy-constructor build by deep-copying
   bst ( const bst& c_bst );

   // copy-assignement operator overload
   bst ( const bst & c_bst ){

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

   //node* find(const value_type); 
   
   
   // INSERT FUNCTION
   // bool is true if the new node is allocated
   // iterator to the new node
   //
   std::pair<iterator, bool> insert(const node& x);
   std::pair<iterator, bool> insert(pair_type&& x);

   // ITERATOR BEGIN
   // return iterator to the tail of the bst
   iterator begin() { return iterator{tail}; }
   const_iterator begin() const;
   const_iterator cbegin() const;

   // ITERATOR END
   iterator end() { return iterator{nullptr}; }
   const_iterator end() const;
   const_iterator cend() const;

   // FIND FUNCTION
   // returns an iterator to the proper node or ends()
   iterator find(const key_type& x);
   const_iterator find(const key_type& x) const;

   // BALANCE
   void balance();

   // PUT-TO OPERATOR
   friend
   std::ostream& operator<<(std::ostream& os, const bst& x);

   // COPY & MOVE

	
   void clear(){
	left.rest();
	right.reset();
   }

}


// EMPLACE FUNCTION
// container constucted in-place
template< class... Types >
std::pair<iterator,bool> emplace(Types&&... args);

#include "bst.tpp"
#endif
