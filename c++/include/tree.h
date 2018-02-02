#ifndef TREE_H
#define TREE_H
#include<utility>
#include<memory>
#include<iostream>
#include <string>
#include <iostream>


namespace std{
  template < typename K, typename V>
	std::ostream& operator<<(std::ostream& strm, const std::pair< K, V>& pair)
	{
		strm << "(\e[1m" << pair.first << "\e[0m," << pair.second << ")";
		return strm;
	}
}
/**
 * Class for binary trees.
 */
template < typename K, typename V>
class Tree{
private:
  class Node {
  public:
    std::pair<K,V> _pair;   // PBM.PC : K to be replaced by const K ?
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node *_next;
    Node *_prev;

    /**
     * Node Constructor. Takes \p key for the key and \p val for the
     * value. Optionally the children and the godfather (i.e. the first "left" ancestor) can be specified.
     */
  Node(const K & key, const V & val, Node * l = nullptr, Node * r = nullptr, Node * n = nullptr) :
    _pair{key, val}, left{l}, right{r}, _next{n}, _prev{nullptr} {};
    // PBM: What if l or r are already assigned to other unique_ptrs?
    /**
     * Prints the key, value and children's keys of a node.
     */
    void print() const;
    void full_print() const; // PBM: not required.. DEBUG ONLY!

    // PBM: this functions are useful to linearize and balancing the tree
    /**
     * Sets the right pointer to a new value.
     */
    void setr(std::unique_ptr<Node> &newptr){
      right=newptr;
    }
    /**
     * Sets the left pointer to a new value.
     */
    void setl(std::unique_ptr<Node> &newptr){
      left=newptr;
    }
  };
  std::unique_ptr<Node> root;
  size_t _len;
  Node *_first;
  Node *_last;

public:
 Tree() : root{nullptr}, _len{0}, _first{nullptr}, _last{nullptr} {};

  class Iterator;
  class ConstIterator;

  /* PRIVATE OVERLOAD SECTION *********************************************************************************************************************************************************************************/
  // PBM: this private section is ONLY for overloaded function. Luca would not like the user to use the functions with more paremeters then needed, as the tree should use it privately.
 private:
  /**
   * Returns iterator to the begin of the left sub-tree of the node pointed by \p ptr.
   */
  Iterator begin(Node *ptr) const {
    if(ptr->left==nullptr)
      return Iterator{ptr};
    else
      return begin((ptr->left).get());
  }
   /**
   * Returns iterator to the last (non-null) element of the right sub-tree of the node pointed by \p ptr.
   */
  Iterator last(Node *ptr) const {
   if (ptr->right==nullptr)
     return Iterator(ptr);
   else
     return last((ptr->right).get());
  }
    /**
   * Adds iteratively a new node to the tree, defined by the values \p key and \p val. The insertion starts comparing the key from the node pointed by \p ptr and automatically updates the godfather of the new node in the variable \p parent. Returns an iterator (i.e. generalized pointer) to the newly added node.
   */
  Iterator insert(const K & key, const V & val, std::unique_ptr<Node> & ptr, Node *n){
    if (ptr == nullptr ){
      ptr.reset(new Node(key, val,nullptr,nullptr,n));
      ++_len;
      // root case
      if(_len==1){
	       this->_first=ptr.get();
	       this->_last=ptr.get();
      }else{
	      if(n==nullptr){
          ptr->_prev=this->_last;
          (ptr->_prev)->_next=ptr.get();
          this->_last=ptr.get();
	      }else{
      	  ptr->_prev=n->_prev;
      	  n->_prev=ptr.get();
      	  if(ptr->_prev!=nullptr)
      	    (ptr->_prev)->_next=ptr.get();
      	  else
      	    this->_first=ptr.get();
	      }
      }

      return Iterator(ptr);
    }
    if( ptr->_pair.first > key ){
      n=ptr.get();
      return insert(key, val, ptr->left,n);
    }
    if( ptr->_pair.first < key ){
      n=ptr->_next;
      return insert(key, val, ptr->right,n);
    }
    if( ptr->_pair.first == key ){
      ptr->_pair.second = val;  // PBM: up to us
      return Iterator(ptr);
    }

    return Iterator(nullptr);
  }
  /**
   * Prints the nodes of the tree to stdout.
   */
  void naive_print( const std::unique_ptr<Node> & ptr) const;

  /**
   * Prints the tree as a graph.
   */
  void graph_print( const std::unique_ptr<Node> & ptr, std::string & s) const {
    if (ptr->right != nullptr ){
      std::cout.fill('-');
      std::cout.width(8);
    }
    std::cout << std::left << ptr->_pair.first;
    if (ptr->right != nullptr ){
      std::string tmp{s};
      if (ptr->left != nullptr )
        tmp += "\e[31m|\e[0m";
      tmp += "\t";
      graph_print(ptr->right, tmp);
    }
    if (ptr->left != nullptr ){
      std::cout << std::endl << s << "\e[31m|\e[0m";
      std::cout << std::endl << s;
      graph_print(ptr->left, s);
    }
  }
  /**
   * Find the \p unique_ptr<Node> pointing to the node with the desired \p key.
   * If it is not found inside the tree it returns the pointer that would point to it if it would be insered.
   */
  std::unique_ptr<Node> * find_unique_ptr (const K key) {
    std::unique_ptr<Node> * ptr{ &root };
    while( (*ptr)->_pair.first != key && *ptr != nullptr ){
      if( (*ptr) -> _pair.first > key ){
        ptr = &((*ptr)->left);
      }
      else{
        ptr = &((*ptr)->right);
      }
    }
    return ptr;
  }


  Iterator find(const K & key, const std::unique_ptr<Node> & ptr) const {
    if ( ptr == nullptr )
      return Iterator(nullptr);
    if (ptr->_pair.first == key ){
      return Iterator(ptr);
    }
    if( ptr->_pair.first > key ){
      return find(key,ptr->left);
    }
    if( ptr->_pair.first < key ){
      return find(key,ptr->right);
    }
    return Iterator(nullptr); // PBM.PC Exception? it isn't needed, but wo there's a warning
  }
  /**
   * Release all the unique pointers of the sub-tree having \p ptr as root,
   *  loosing permanently the tree strucutre.
   */
  void release_subtree( std::unique_ptr<Node> & ptr ){
    if ( ptr == nullptr )
      return;
    release_subtree( ptr->left );
    release_subtree( ptr->right );
    ptr.release();
  }
  /**
   * Find recursively the middle points of a linked list of length \p N and starting from \p first.
   *
   * To be call only if the tree strucutre has already been released.
   */
  void balance( std::unique_ptr<Node> & ptr, Node * first, int N ){
    if ( N <= 0 )
      return;
    Node * tmp = first;
    for ( int i = 0; i < N/2; ++i ){
      tmp = tmp->_next;
    }
    std::cout << N << ":" << tmp->_pair << " ";
    ptr.reset(tmp);
    balance(tmp->left, first, N/2);
    balance(tmp->right, ptr->_next, N - N/2 - 1);
  }


  /***********************************************************************************************************************************************************************************************************/
 public:
  /**
   * Returns an iterator (i.e. generalized pointer) to the last node of the tree, where the ordered is specified by the key value.
   */
  K& last_key() const{
    return ((this->_last)->_pair).first;
  }
  /**
   * Returns an iterator (i.e. generalized pointer) to the first node of the tree, that is the node with the lowest key value.
   */
  Iterator begin() const{ return Iterator(this->_first); }
  /**
   * Returns an null iterator (i.e. generalized pointer) in order to determine out of bound access to the tree.
   */
  Iterator end() const{
    return Iterator{nullptr};
  }
  /**
   * Returns a constant iterator (i.e. generalized pointer) to the first node of the tree, that is the node with the lowest key value.
   */
  ConstIterator cbegin() const { return ConstIterator{(this->begin()).get()}; }
  /**
   * Returns an null iterator (i.e. generalized pointer) in order to determine out of bound access to the tree.
   */
  ConstIterator cend() const { return ConstIterator{nullptr}; }
  /**
   * Adds iteratively a new node to the tree with value \p val and key \p key
   */
  Iterator insert(const K & key, const V & val){
    return insert(key, val, root, nullptr);
  }

  /**
   * Prints to stdout \p key : \p value of each node starting from the root.
   */
  void naive_print() const { naive_print(root); }
  /**
   * Prints \p key : \p value of each node properly oredered.
   */
  void print() const {
    for (auto& it : *this ) {
      std::cout << it << " ";
    }
    std::cout << std::endl;
   }

  // PBM.PC - working till 8 digits!!
  /**
   * Prints the tree as a graph.
   */
  void graph_print() const {
    std::cout << "\n*\n";
    std::string s;
    graph_print(root, s);
    std::cout << "\n";
  }
  /**
   * Returns the length of the tree.
   */
  size_t len() const { return _len; }
  /**
   * Removes every node in the tree.
   */
  void clean(){ root.reset(nullptr); }
   /**
    * Returns an iterator to the node with key \p key. If the node does not exist return end().
    */
   Iterator find(const K key) const { return find(key,root); }

  V & operator[] ( const K & key ) {
     Iterator it = find(key);
     if ( it.get() == nullptr ){    // PBM.PC exception?
       std::cout << "opss.. New node added!";
       it = insert( key, V{} );
     }
     return (*it).second;
   }

   ////////////////////// PBM.PC: come fa ad essere const se può aggiungere un nodo??
   const V & operator[]( const K & key ) const noexcept {
    Iterator it = find(key);
    if ( it.get() == nullptr ){
      std::cout << "No node with this key";
      return V{};
    }
    return (*this)[ key ];
   }

   /**
    * @brief Left rotation of the tree centered on the node associated to the \p unique_ptr<Node> pointed by \p ptr (in the example: A).
    *
    * @code
    * ptr -> \
    *         A ----- B --- t3...
    *         |       |
    *         t1      t2
    * @endcode
    * 1. \p *ptr is released and its value stored on a temporary pointer to \p Node.
    * 2. The right son of A (->B) is released, thus \p *ptr can be associeted to B.
    * 3. The left son of B (->t2) is released and stored as right son of A.
    * 4. A can be stored as left son of B.
    * 5. \p ptr is updated, it points now to the left son of B (->A).
    *
    * @code
    *     \
    *      B ---- t3
    *      | <- ptr
    *      A ---- t2
    *      |
    *      t1
    * @endcode
    */
  void rotate_left( std::unique_ptr<Node> * & ptr ){
    if ( (*ptr)->right == nullptr )
        return;    // PBM.PC exception?!
    Node * tmp = (*ptr).release(); // 1.
    (*ptr).reset((tmp->right).release()); // 2.
    (tmp -> right).reset( ((*ptr)->left).release() ); // 3.
    ((*ptr)->left).reset(tmp); // 4.
    ptr = &((*ptr)->left);  //5.
  }
  /**
   * Delete the node with key \p key.
   * This function performs left rotations on the tree centered on that node
   * till it has no right son. At this point it can be erased connecting
   * its father with its left son.
   */

  void erase(const K key) noexcept {
    std::unique_ptr<Node> * ptr{ &root };
    ptr = find_unique_ptr( key );
    if ( *ptr == nullptr ){
      std::cout << "There is no node with key "<< key <<".\n";
      return;
    }
    Node * to_be_erased = (*ptr).get() ;
    (to_be_erased->_prev)->_next = to_be_erased->_next;
    (to_be_erased->_next)->_prev = to_be_erased->_prev;
    while( (*ptr)->right != nullptr ){ // Finché quello che voglio eliminare ha qualcosa a dx,
      rotate_left(ptr);
    }
    (*ptr).reset( ((*ptr)->left).release() );
    --_len;
  }

  void balance(){
    release_subtree(root);
    balance( root, _first, _len);
  }
//////////////////////////////////////// HERE PBM.PC WIP before next strategy
  // Node * release_left_sons( Node * ptr ){
  //   while( (*ptr)->left != nullptr ){
  //     ptr = ((*ptr)->left).release();
  //   }
  //   return ptr;
  // }
  // void release_left_subtree( Node * ptr ){
  //   if( (*ptr)->left != nullptr ){
  //     release_left_subtree(release_left_sons(ptr));
  //   }
  //
  //   if( (*ptr)->right != nullptr ){
  //     ((*ptr)->right).reset(release_left_sons((*ptr)->right));
  //     // ((*ptr)->right).reset(release_left_sons(((*ptr)->right).release()));
  //     release_left_subtree((*ptr)->right);
  //   }
  //   if( (*ptr)->godfather != nullptr ){
  //     ((*ptr)->right).reset( (*ptr)->godfather );
  //     release_left_subtree((*ptr)->right);
  //   }
  //   return;
  // }
  //
  // void linked_list(){
  //   release_left_subtree(& root);
  // }
////////////////////////////////////////

};
// PBM: DEBUG ONLY!
template < typename K, typename V>
void Tree<K,V>::Node::full_print() const {
  std::cout << "key: " << _pair.first << "\t value: "
    <<  _pair.second << "\t left son: ";
  if ( left != nullptr )
    std::cout << left->_pair.first;
  else
    std::cout << "NONE";
  std::cout <<  "\t right son: ";
  if ( right != nullptr )
    std::cout << right->_pair.first;
  else
    std::cout << "NONE";
  if(_next==nullptr)
    std::cout << "\t next: nullptr" << std::endl;
  else
    std::cout << "\t next: key " << (*_next)._pair.first << std::endl;
  if(_prev==nullptr)
    std::cout << "\t prev: nullptr" << std::endl;
  else
    std::cout << "\t prev: key " << (*_prev)._pair.first << std::endl;
}

template < typename K, typename V>
void Tree<K,V>::Node::print() const {
  std::cout << _pair;
}

template <typename K, typename V>
  class Tree<K,V>::Iterator {
  using Node = Tree<K,V>::Node;
  Node *current;

 public:
 Iterator(const std::unique_ptr<Node> &n) : current{n.get()} {}
 Iterator( Node *n): current{n} {}
  /**
   * Returns the key associated to node pointed by the current iterator.
   */
  std::pair<K,V>& operator*() const { return current->_pair; }
  /**
   * Returns the value associated to node pointed by the current iterator.
   */
  V val(){ return (current->_pair).second; }

  /**
   * Returns a raw pointer to the node pointed by the current iterator.
   */
  Node *get() const { return current; }

   /**
   * Returns true if the iterator is pointing to the last element of th tree, else returns false.
   */
  bool islast(){
    Node *tmp=this->get();
    if(tmp->right==nullptr&&tmp->godfather==nullptr)
      return true;
    else
      return false;
  }

  /**
   * Pre-increment operator: moves the iterator to the next element in the tree.
   */
  Iterator& operator++() {
    current = current->_next;
    return *this;
  };

  /**
   * Post-increment operator: moves the iterator to the next element in the tree, returns an iterator to the current node.
   */
  Iterator operator++(int) {
    Iterator it{current};
    ++(*this);
    return it;
  }

  /**
   * Returns true if two iterators point to the same node, false else.
   */
  bool operator==(const Iterator& other) {
    return this->current == other.current;
  }
  /**
   * Returns false if two iterators point to the same node, true else.
   */
  bool operator!=(const Iterator& other) { return !(*this == other); }

};

template < typename K, typename V>
class Tree<K,V>::ConstIterator : public Tree<K,V>::Iterator {
  using parent = Tree<K,V>::Iterator;
 public:
  using parent::Iterator; // PBM: ask alberto
  const V& operator*() const { return parent::operator*(); }
};

/* Extra stuff */
template < typename K, typename V>
  void Tree<K,V>::naive_print( const std::unique_ptr<Node> & ptr) const {
  if(ptr==nullptr){
    std::cout << "The tree is empty." << std::endl;
  }else{
    if (ptr->left != nullptr )
      naive_print(ptr->left);
    if (ptr->right != nullptr )
      naive_print(ptr->right);
    ptr->full_print();
  }
}




#endif
