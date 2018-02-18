#ifndef TREE_H
#define TREE_H
#include<utility>
#include<memory>
#include<iostream>
#include <string>
#include <iostream>

/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  STD vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
namespace std{
  /**
   * Overload of \p operator<< for \p std::pair
   */
  template < typename K, typename V>
	std::ostream& operator<< (std::ostream& strm, const std::pair< K, V>& pair){
		strm << "(\e[1m" << pair.first << "\e[0m," << pair.second << ")";
		return strm;
	}
}
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  STD ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv TREE vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
/**
 * Class for binary trees.
 */
template < typename K, typename V, typename OP >
class Tree{
private: // ************************* PRIVATE *************************
  class Node;
  std::unique_ptr<Node> root;
  size_t _len;
  Node *_first;
  Node *_last;
  OP c_op;
public: // ************************* PUBLIC *************************
  /* ______________________________ CTORS ______________________________ */
  /**
   * Tree default constructor.
   */
  Tree() : root{nullptr}, _len{0}, _first{nullptr}, _last{nullptr} {};
  /**
   * Tree copy constructor.
   */
  Tree(const Tree& in){ this->copy((in.root).get()); }
  /**
   * Tree move constructor.
   */
  Tree(Tree&& in) noexcept:
    root{std::move(in.root)},
    _len{std::move(in._len)},
    _first{std::move(in._first)},
    _last{std::move(in._last)}
    {};
  /**
   * Tree copy assignment.
   */
  Tree& operator=(const Tree& in){
    this->copy((in.root).get());
    return *this;
  }
  /**
   * Tree move assignment.
   */
  Tree& operator=(Tree&& in) noexcept {
    root=std::move(in.root);
    _len=std::move(in._len);
    _first=std::move(in._first);
    _last=std::move(in._last);
    return *this;
  }
  /* ______________________________ DEALLOC ______________________________ */
  /**
   * Removes every node in the tree.
   */
  void clean(){ root.reset(nullptr); _len = 0; }
  /**
   * Delete the node with key \p key. This function performs left rotations on
   * the tree centered on the selected node till it has no right son.
   * At this point it can be erased connecting its father with its left son.
   */
  void erase(const K key) noexcept;
  /* ______________________________ GETTERS ______________________________ */
  /**
   * Returns the length of the tree.
   */
  size_t len() const { return _len; }
  /* ______________________________ PRINT ______________________________ */
  /**
   * Prints \p key:value of each node oredered by key via a recursive function.
   */
  void print() const;
  /**
   * Using /p Node::full_print(), it prints all the informations about
   * the nodes of the tree to stdout via a recursive function.
   */
  void naive_print() const;
  /**
   * Prints the tree as a graph. It works fine with keys up to 8 digits.
   */
  void graph_print() const;
  /* ______________________________ ITERATORS ______________________________ */
  class Iterator;
  class ConstIterator;
  /**
   * Returns an iterator (i.e. generalized pointer) to the first node of the
   * tree, that is the node with the lowest key value.
   */
  Iterator begin() const{ return Iterator(this->_first); }
  /**
   * Returns an iterator (i.e. generalized pointer) to the last node of the
   * tree, that is the node with the highest key value.
   */
  Iterator last() const{ return Iterator(this->_last); }
  /**
   * Returns an null iterator (i.e. generalized pointer) in order to determine
   * out of bound access to the tree.
   */
  Iterator end() const{ return Iterator{nullptr}; }
  /**
   * Returns a constant iterator (i.e. generalized pointer) to the first node
   * of the tree, that is the node with the lowest key value.
   */
  ConstIterator cbegin() const { return ConstIterator{(this->begin()).get()}; }
  /**
   * Returns a constant iterator (i.e. generalized pointer) to the last node
   * of the tree, that is the node with the lowest key value.
   */
  ConstIterator clast() const { return ConstIterator{(this->last()).get()}; }
  /**
   * Returns a null iterator (i.e. generalized pointer) in order to determine
   * out of bound access to the tree.
   */
  ConstIterator cend() const { return ConstIterator{nullptr}; }
  /* ______________________________ INSERT ______________________________ */
  /**
   * Adds a new node to the tree with value \p val and key \p key via a
   * recursive function. If the key is already present in the tree it updates
   * the value of the corersponding node.
   */
  Iterator insert(const K & key, const V & val){
     return insert(key, val, root, nullptr);
  }
  /* ______________________________ NAVIGATE ______________________________ */
  /**
   * Returns an iterator to the node with key \p key.
   * If the node does not exist it returns \p nullptr.
   */
  Iterator find(const K key) const { return find(key,root); }
  /**
   * Returns the value of the node with key \p key.
   * If the node does not exist it insert a new node with default value.
   */
  V & operator[] ( const K & key );
  /**
   * \p const version of the above.
   * If the node does not exist it returns the default value.
   */
  const V & operator[]( const K & key ) const noexcept ;
  /* ______________________________ MODIFY ______________________________ */
  /**
   * Left rotation of the tree centered on the node with key \p key (A).
   *
   * @code
   * ptr -> \
   *         A ----- B --- t3...
   *         |       |
   *         t1      t2
   * @endcode
   * 1. release \p *ptr, store its value on a temporary pointer to \p Node.
   * 2. Release the right son of A (->B) and associate \p *ptr to B.
   * 3. Release the left son of B (->t2) and store it as right son of A.
   * 4. Store A as left son of B.
   * 5. Update \p ptr in order to point to the left son of B (->A).
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
  void rotate_left( const K key );
  /**
   * Balance the tree structure.
   */
  void balance();

 private: // ************************* PRIVATE *************************
  /* ______________________________ PRINT ______________________________ */
  /** Recursive function used to implement naive print.*/
  void naive_print( const std::unique_ptr<Node> & ptr) const;

  /** Recursive function used to implement the graph print.*/
  void graph_print( const std::unique_ptr<Node> & ptr, std::string & s) const;
  /* ______________________________ INSERT ______________________________ */
  /** Recursive function used to implement insertion.*/
  Iterator
  insert(const K & key, const V & val, std::unique_ptr<Node> & ptr, Node *n);
  /* ______________________________ FIND ______________________________ */
  /** Find the \p unique_ptr<Node> pointing to the node with the desired \p key.
   * If it is not found inside the tree it returns the pointer that would point
   * to it if it would be insered.*/
  std::unique_ptr<Node> &
  find_uptr (const K key, std::unique_ptr<Node> & ptr) const;
  /** Recursive function used to implement find.*/
  Iterator find(const K & key, const std::unique_ptr<Node> & ptr) const;
  /* ______________________________ MODIFY ______________________________ */
  /** Left rotation.*/
  void rotate_left( std::unique_ptr<Node> * & ptr );
  /** Release all the unique pointers of the sub-tree having \p ptr as root.*/
  void release_subtree( std::unique_ptr<Node> & ptr );
  /** Recursive function used to balance the tree.*/
  void balance( std::unique_ptr<Node> & ptr, Node * first, int N );

  void copy(Node *ptr);
};

/* ______________________________ COPY ______________________________ */
  template < typename K, typename V, typename OP>
  void Tree<K,V,OP>::copy(Node *ptr){
    if(ptr==nullptr){
      return;
    }
    this->insert(ptr->_pair.first,ptr->_pair.second);
    copy(ptr->left.get());
    copy(ptr->right.get());
  }

/* ______________________________ DEALLOC ______________________________ */
template < typename K, typename V, typename OP>
void Tree<K,V,OP>::erase(const K key) noexcept {
  std::unique_ptr<Node> * ptr{ &find_uptr( key, root ) };
  if ( (*ptr) == nullptr ){
   std::cout << "There is no node with key "<< key <<".\n";
   return;
  }
  Node * to_be_erased = (*ptr).get() ;
  (to_be_erased->_prev)->_next = to_be_erased->_next;
  (to_be_erased->_next)->_prev = to_be_erased->_prev;
  while( (*ptr)->right != nullptr ){
   rotate_left(ptr); // rotate till there is no right son
  }
  (*ptr).reset( ((*ptr)->left).release() );
  --_len;
 }
/* ______________________________ PRINT ______________________________ */
template < typename K, typename V, typename OP>
void Tree<K,V,OP>::print() const {
  for (auto& it : *this ) {
    std::cout << it << " ";
  }
  std::cout << std::endl;
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::naive_print() const {
  if( root==nullptr )
    std::cout << "The tree is empty." << std::endl;
  else
    naive_print(root);
 }

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::naive_print( const std::unique_ptr<Node> & ptr) const {
  if( ptr==nullptr )
    return;
  naive_print(ptr->left);
  naive_print(ptr->right);
  ptr->full_print();
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::graph_print() const {
  std::string s;
  std::cout << "\n*\n";
  graph_print(root, s);
  std::cout << "\n";
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::graph_print(
const std::unique_ptr<Node> & ptr, std::string & s) const {
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

/* ______________________________ INSERT ______________________________ */
template < typename K, typename V, typename OP>
typename Tree<K,V,OP>::Iterator Tree<K,V,OP>::insert(
const K & key, const V & val, std::unique_ptr<Node> & ptr, Node * n){
  if (ptr == nullptr ){
    ptr.reset(new Node(key, val, n));
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
  if( c_op(key, ptr->_pair.first) ){
    n=ptr.get();
    return insert(key, val, ptr->left,n);
  }
  if( c_op(ptr->_pair.first, key) ){
    n=ptr->_next;
    return insert(key, val, ptr->right,n);
  }
  if( ptr->_pair.first == key ){
    ptr->_pair.second = val;  // PBM: up to us
    return Iterator(ptr);
  }
  return Iterator(nullptr);
}

/* ______________________________ NAVIGATE ______________________________ */
template < typename K, typename V, typename OP>
std::unique_ptr<typename Tree<K,V,OP>::Node> &
Tree<K,V,OP>::find_uptr(const K key, std::unique_ptr<Node> & ptr) const {
  if ( ptr == nullptr )
    return ptr;
  if (ptr->_pair.first == key )
    return ptr;
  if(  c_op(key, ptr->_pair.first) )
   return find_uptr(key,ptr->left);
  if( c_op( ptr->_pair.first, key) )
    return find_uptr(key,ptr->right);
  return ptr;
}

template < typename K, typename V, typename OP>
typename Tree<K,V,OP>::Iterator
Tree<K,V,OP>::find(const K & key, const std::unique_ptr<Node> & ptr) const {
  if ( ptr == nullptr )
    return Iterator(nullptr);
  if (ptr->_pair.first == key ){
    return Iterator(ptr);
  }
  if(  c_op(key, ptr->_pair.first) ){
   return find(key,ptr->left);
  }
  if( c_op( ptr->_pair.first, key) ){
    return find(key,ptr->right);
  }
  return Iterator(nullptr);
}

template < typename K, typename V, typename OP>
V & Tree<K,V,OP>::operator[] ( const K & key ) {
   Iterator it = find(key);
   if ( it.get() == nullptr ){
     std::cout << "New node added!";
     it = insert( key, V{} );
   }
   return (*it).second;
}

template < typename K, typename V, typename OP>
const V & Tree<K,V,OP>::operator[]( const K & key ) const noexcept {
  Iterator it = find(key);
  if ( it.get() == nullptr ){
    std::cout << "No node with this key";
    return V{};
  }
  return (*this)[ key ];
}

/* ______________________________ MODIFY ______________________________ */
template < typename K, typename V, typename OP>
void Tree<K,V,OP>::balance(){
  release_subtree(root);
  balance( root, _first, _len);
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::balance( std::unique_ptr<Node> & ptr, Node * first, int N ){
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

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::release_subtree( std::unique_ptr<Node> & ptr ){
  if ( ptr == nullptr )
    return;
  release_subtree( ptr->left );
  release_subtree( ptr->right );
  ptr.release();
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::rotate_left( const K key ) {
  std::unique_ptr<Node> * ptr{ &find_uptr( key, root ) };
  if ( ptr != nullptr )
   rotate_left( ptr );
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::rotate_left( std::unique_ptr<Node> * & ptr ){
  if ( (*ptr)->right == nullptr )
    return;
  Node * tmp = (*ptr).release(); // 1.
  (*ptr).reset((tmp->right).release()); // 2.
  (tmp -> right).reset( ((*ptr)->left).release() ); // 3.
  ((*ptr)->left).reset(tmp); // 4.
  ptr = &((*ptr)->left);  //5.
}

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ TREE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv NODE vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
template <typename K, typename V, typename OP>
class Tree<K,V,OP>:: Node {
public:
  std::pair<const K,V> _pair;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;
  Node *_next;
  Node *_prev;
  /**
   * Node Constructor. Takes \p key for the key and \p val for the value.
   * Optionally the next (i.e. the first "left" ancestor) can be specified.
   */
  Node(const K & key, const V & val, Node * n = nullptr) :
    _pair{key, val}, left{nullptr}, right{nullptr}, _next{n}, _prev{nullptr} {};
  /**
   * Prints the key and the value of the node.
   */
  void print() const;
  /**
   * Prints key, value, children's keys, next and prev keys of a node.
   */
  void full_print() const;
private:
  void cond_print (Node * ptr) const;
};

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::Node::print() const {
  std::cout << _pair;
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::Node::full_print() const {
  std::cout << "key: " << _pair.first << "\tvalue: " <<  _pair.second
  << "\tleft son: ";
  cond_print(left.get());
  std::cout <<  "\tright son: ";
  cond_print(right.get());
  std::cout << "\tnext: ";
  cond_print(_next);
  std::cout << "\tprev: ";
  cond_print(_prev);
  std::cout << std::endl;
}

template < typename K, typename V, typename OP>
void Tree<K,V,OP>::Node::cond_print (Node * ptr) const{
  std::cout.width(6);
  std::cout.fill(' ');
  if ( ptr != nullptr )
    std::cout << std::right << ptr->_pair.first;
  else
    std::cout << std::right << "NONE";
}

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ NODE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/* vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv ITERATOR vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv */
template <typename K, typename V, typename OP>
class Tree<K,V,OP>::Iterator {
  using Node = Tree<K,V,OP>::Node;
  Node *current;

public:
  Iterator(const std::unique_ptr<Node> &n) : current{n.get()} {}
  Iterator( Node *n): current{n} {}
  /**
   * Returns the key associated to node pointed by the current iterator.
   */
  std::pair<const K,V>& operator*() const { return current->_pair; }
  /**
   * Returns a raw pointer to the node pointed by the current iterator.
   */
  Node * get() const { return current; }
  /**
   * Pre-increment operator: moves the iterator to the next element.
   */
  Iterator& operator++() {
    current = current->_next;
    return *this;
  };
  /**
   * Post-increment operator: moves the iterator to the next element in the
   * tree, returns an iterator to the current node.
   */
  Iterator operator++(int) {
    Iterator it{current};
    ++(*this);
    return it;
  }
  /**
   * Pre-decrement operator: moves the iterator to the previous element.
   */
  Iterator& operator--() {
    current = current->_prev;
    return *this;
  };
  /**
   * Post-decrement operator: moves the iterator to the previous element in the
   * tree, returns an iterator to the current node.
   */
  Iterator operator--(int) {
    Iterator it{current};
    --(*this);
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
/* ____________________________ CONSTITERATORS ____________________________ */
template < typename K, typename V, typename OP>
class Tree<K,V,OP>::ConstIterator : public Tree<K,V,OP>::Iterator {
  using parent = Tree<K,V,OP>::Iterator;
 public:
  using parent::Iterator;
  const V& operator*() const { return parent::operator*(); }
};
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ITERATOR ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
#endif
