#ifndef bst_tpp
#define bst_tpp

// recursive function to look where insert the new node
template<class key_type , class key_value, class key_comp=std::less<key_type> >
bst::node* bst::node::find(const value_type value){

   // content.second corresponds to the key_value of the node
   if(value == content.second)
      return this;

   if( (left) && (key< content.second) )
      return left->find( key );

   if( (right) && (key > content.second) )
      return right->find( key );

   return nullptr;
}

// function to insert the new node.
//it called find
template<class key_type , class key_value, class key_comp >
bst::node* bst::node::insert( const key_type type, const key_value value, const bool substitution ){

   node* new = nullptr;

   if( substitution && value == content.second ){
   
   // ha senso cambiare il valore di type che e` casuale?
   //content.first = type;

   new = this;

   }
  
   if(value < content.second ){

      if( left ) new=left->insert( type, value, substitute);
      else{
         left.resert( new node{type, value, this } );
         new = left.get();
      }
   }

   if(value > content.second ){

      if( right ) new=right->insert( type, value, substitute);
      else{
         right.reset( new node{type, value, this } );
         new = right.get();
      }
   }

   return new;

}

template<class key_type , class key_value, class key_comp >
bst::node* bst::node::leftmost(){

//?????????????????????????????????????????

}


bst<key_type, key_value, key_comp>::bst ( const bst& c_bst ) {






}
 
bst< k, v, c>::Find (const k & x){
	
}
#endif_tpp
