#ifndef bst
#define bst

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <cmath>

// binary search tree class:
template <typename key_type, typename key_value, typename key_comp=std::less<key_type>>
class bst(){

   // compe uso questo comparatore?
   key_comp C;

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
   
	// node find function
        node* find(const value_type value);

	// recursive function to insert a new node
	node* insert(const key_type k, const key_value value, const bool substitution);
   	
	// recursive function to find the leftmost node in the bst
	node *leftmost(){
	
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

	// post-increment operator overload
	iterator operator++( int){
	
		iterator it{ *this};
		++( *this);
		return it;

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

   // in-place balance of a section of the bst
   // it receive as params the iterator to current position,
   // node vector of raw pointers to nodes

   void in_place_balance(iterator position, const std::vector<>& nodes);

   public:
   
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
   std::pair<iterator, bool> insert(const node& x);
   std::pair<iterator, bool> insert(node&& x);


   // ITERATOR BEGIN
   // return iterator to the tail of the bst
   iterator begin() { return iterator{tail}; }
   const_iterator begin() consti { return iterator{tail}; }
   const_iterator cbegin() const { return const_iterator{tail}; }


   // ITERATOR END
   iterator end() { return iterator{nullptr}; }
   const_iterator end() const { return iterator{nullptr}; }
   const_iterator cend() const { return const_iterator{nullptr}; }


   // FIND FUNCTION
   // returns an iterator to the proper node or ends()
   iterator find(const key_value& x) { return iterator{ root->find(x) }; }
   const_iterator find(const key_value& x) const { return const_iterator{ root->find(x) }; }

   
   // BALANCE
   void balance();


   // PUT-TO OPERATOR
   // operator << overload
   template <class okey_type, class o_keyvalue>
   friend std::ostream& operator<<(std::ostream& os, const bst& x);


   // CLEAR
   // remove all the nodes from the bst
   void clear(){
	
	root.reset();
   }


   // EMPLACE FUNCTION
   // container constructed in-place
   template< class... Types >
   std::pair<iterator,bool> emplace(Types&&... args);
}

#include "bst.tpp"
#endif
