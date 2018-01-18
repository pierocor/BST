#ifndef TREE_H
#define TREE_H
#include<utility>
#include<memory>
#include<iostream>
#include <string>
#include <iostream>
/**
 * Class for binary trees.
 */
template < typename K, typename V>
class Tree{
private:
  class Node {
  public:
    std::pair<K,V> _pair;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node *godfather;
    
    /**
     * Node Constructor. Takes \p key for the key and \p val for the
     * value. Optionally the children and the godfather (i.e. the first "left" ancestor) can be specified.
     */
  Node(const K & key, const V & val, Node * l = nullptr, Node * r = nullptr, Node * g = nullptr) :
    _pair{key, val}, left{l}, right{r}, godfather{g} {};
    // PBM: What if l or r are already assigned to other unique_ptrs?
    /**
     * Prints the key, value and children's keys of a node.
     */
    void print();

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

public:
 Tree() : root{nullptr}, _len{0} {};

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
  Iterator insert(const K & key, const V & val, std::unique_ptr<Node> & ptr, Node *parent){

    if (ptr == nullptr ){
      ptr.reset(new Node(key, val,nullptr,nullptr,parent));
      ++_len;
      return Iterator(ptr);
    }
    if( ptr->_pair.first > key ){
      parent=ptr.get();
      return insert(key, val, ptr->left,parent);
    }
    if( ptr->_pair.first < key ){
      parent=ptr->godfather;
      return insert(key, val, ptr->right,parent);
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
  void naive_print(std::unique_ptr<Node> & ptr);

  /**
   * Prints the tree as a graph.
   */
  void graph_print(std::unique_ptr<Node> & ptr, std::string & s) {
    if (ptr->right != nullptr ){
      std::cout.fill('-');
      std::cout.width(8);
    }
    std::cout << std::left << ptr->_pair.first;
    if (ptr->right != nullptr ){
      std::string tmp{s};
      if (ptr->left != nullptr )
        tmp += "|";
      tmp += "\t";
      graph_print(ptr->right, tmp);
    }
    if (ptr->left != nullptr ){
      std::cout << std::endl << s << "|";
      std::cout << std::endl << s;
      graph_print(ptr->left, s);
    }
  }

  
  /***********************************************************************************************************************************************************************************************************/
 public:
  /**
   * Returns an iterator (i.e. generalized pointer) to the last node of the tree, where the ordered is specified by the key value.
   */
  Iterator last() const{
    return last(root.get());
  }
  /**
   * Returns an iterator (i.e. generalized pointer) to the first node of the tree, that is the node with the lowest key value.
   */
  Iterator begin() const{
    return begin(root.get());
  }
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
   * Prints the nodes of the tree to stdout.
   */
  void naive_print(){ naive_print(root); }

  // PBM.PC - working till 8 digits!!
  /**
   * Prints the tree as a graph.
   */
  void graph_print(){
    std::cout << "\n*\n";
    std::string s;
    graph_print(root, s);
    std::cout << "\n";
  }
  /**
   * Returns the length of the tree.
   */
  size_t len() const { return _len; }
  
};

template < typename K, typename V>
void Tree<K,V>::Node::print(){
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
  if(godfather==nullptr)
    std::cout << "\t GP: nullptr" << std::endl;
  else
    std::cout << "\t GP: key " << (*godfather)._pair.first << std::endl;

}

// Iterator definitions
template <typename K, typename V>
  class Tree<K,V>::Iterator {
  using Node = Tree<K,V>::Node;
  Node *current;

 public:
 Iterator(std::unique_ptr<Node> &n) : current{n.get()} {}
 Iterator(Node *n): current{n} {}
  /**
   * Returns the value associated to node pointed by the current iterator.
   */
  K& operator*() const { return (current->_pair).first; }

  /**
   * Returns a raw pointer to the node pointed by the current iterator.
   */
  Node *get() const { return current; }

   /**
   * Returns an iterator pointing to the \p godfather of the node associated to the current iterator.
   */
  Iterator get_godfather() const { return Iterator(current->godfather); }

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
    if(current->right != nullptr){
      current = (current->right).get();
      while ( (current->left).get() != nullptr )
        current = (current->left).get();
	    return *this;
    }else{
	    current=(this->get_godfather()).get();
	    return *this;
    }
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
  using parent::Iterator;
  const V& operator*() const { return parent::operator*(); }
};

/* Extra stuff */
template < typename K, typename V>
  void Tree<K,V>::naive_print(std::unique_ptr<Node> & ptr){
  if (ptr->left != nullptr )
    naive_print(ptr->left);
  if (ptr->right != nullptr )
    naive_print(ptr->right);
  (*ptr).print();
}

#endif
