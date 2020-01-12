//template <class K , class V, class C > using iterator_t = typename bst<K, V, C >::iterator ;
//template <class K , class V, class C > using node_s = typename bst<K, V, C >::node ;

//****************** INSIDE BST::STRUCT NODE *******************************

// recursive function to look
template <typename K , typename V, typename C=std::less<K>>
typename bst< K, V, C>::node* bst<K, V, C>::node::find( const K key ){

   // content.first corresponds to the key_value of the node
   if(key == content.first)
      return this;

   if( (left) &&  ( key < content.first )  )
      return left->find( key );

   if( (right) && ( content.first < key ) )
      return right->find( key );

   return nullptr;
}


// function to inser the new node.
template <class K , class V, class C >
std::pair< typename bst< K, V, C>::node* , bool> bst<K, V, C>::node::insert( std::pair< const K, const V> p, const bool sub ){

   node* n = nullptr;

   if( sub && p.first == content.first ){
   
      // ha senso cambiare il valore di value che e` casuale?
      content.second = p.second;
      n = this;
      //sub = false;
   }
  
   if( (p.first < content.first) ){
      if( left ) 
         n = left->insert(p, sub).first;
      else{
         left.reset ( new node{ { p.first, p.second}, this } );
         n = left.get();
      }
      //sub = true;
   }

   if( ( content.first <  p.first ) ){

      if( right ) 
         n = right->insert( p, sub).first;
      else{
         right.reset( new node{ { p.first, p.second}, parent } );
         n = right.get();
      }
      //sub = true;
   }

   return {n,sub};

}


//********************* INSIDE CLASS BST ****************************

// ===================== COPY CONSTRUCTOR FUNCTION ====================
//copy-constructor build by deep-copying
template < class K, class V, class C >
bst<K, V, C >::bst ( const bst& c_bst ) {

   std::function< void ( const_iterator ) > deep_copy =
   [this, &deep_copy] ( const_iterator it){

      insert( {it -> key(), it-> value()});

      if( it->left )
         deep_copy( const_iterator { it->left.get()} );

      if( it->right )
         deep_copy( const_iterator {it->right.get()} );

   return;

   };

   deep_copy( const_iterator{ c_bst.root.get() });
}

//=============== INSERT FUNCTION ===================================
// bool is true if the new node i allocated
// iterator to the new node
template < class K, class V, class C >
std::pair< typename bst< K, V, C>::iterator, bool> bst< K, V , C>::insert(const std::pair<K,V>& x){

   bool sub = true;

   if( root ){//se root esiste
      
      //la funzione ricorsiva e` dentro il nodo
      std::pair<iterator,bool> it{ root->insert( { x.first, x.second}, sub) };
      
      // devo ricordarmi dispostare la coda
      if( (x.first < tail->key()) ) tail = tail->left.get();
      return it;

   }
   else{ //se root non esiste
      root.reset( new node{ {x.first, x.second} } );
      tail = root.get();
      return {iterator{ root.get() }, sub};
   }

}

//================ OUTPUT STREAM FUNCTION ===========================
template < class oK, class oV >
std::ostream& operator<< ( std::ostream& os, bst< oK, oV >& x){

   typename bst< oK, oV>::iterator it = x.begin(); //x.begin()==tail;

   if( it.operator->() ){
      typename bst< oK, oV>::iterator stop = x.end(); //x.end() == stop;
      while ( it != stop )	{
         os << "key" << ":\t" << it->key() << "\n"; 
         ++it;
      }
   }else{
	os<< "EMPTY TREE!";
   }
   
   return os;
}

//================== BALANCE FUNCTIONS =============================


// function to balance the bst
template < class K, class V, class C >
void bst<K, V, C>::balance() {

// allocate the nodes in vector sorted by key

   std::vector<node*> nodes;

   iterator it = begin();

   for( ; it!=end() ; ++it )
      nodes.push_back( new node { {it->key(), it->value()} } );

   clear();

   if ( nodes.size() > 0 ){

      root.reset( nodes[ 0.5 * nodes.size() ] );
      in_place_balance( iterator{ root.get() }, nodes );
      tail = nodes[ 0 ];
   }
   else{
      tail = root.get();
   }

}


//in-place balance of a section of the bst
//it receives as params the iterator to current position,
//node vector of raw pointers to nodes
template < class K, class V, class C>
void bst< K, V, C>::in_place_balance ( bst< K, V, C>::iterator pos, const std::vector<node*>& nodes){

   auto begin = nodes.begin();
   auto mid = nodes.begin() + 0.5 * nodes.size();
   auto last = nodes.end();

   std::vector< node *> leftmid {begin, mid};

   if( leftmid.size() > 0 ){
      pos->left.reset( leftmid[ 0.5 * leftmid.size() ] );
      pos->left->parent = pos.operator->();
      in_place_balance(iterator{ pos->left.get()}, leftmid);
   }
   
   std::vector< node *> rightmid { ++mid, last};

   if( rightmid.size() > 0 ){
      pos->right.reset( rightmid[ 0.5 * rightmid.size() ] );
      pos->right->parent = pos->parent ;
      in_place_balance(iterator{ pos->right.get()}, rightmid);
   }
   return;
}


template <typename K, typename V, typename C>
template <typename... Types>
std::pair<typename bst<K, V, C>::iterator,bool> bst<K, V, C>::emplace(Types&&... args){
	return insert(std::pair<const K, V>{std::forward<Types>(args)...});
}
