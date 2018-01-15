#ifndef TREE_H
#define TREE_H
#include<utility>
#include<memory>
#include<iostream>
/**
 * Class for binary trees.
 */
template < typename K, typename T>
class Tree{
private:
  class Node {
  public:
    std::pair<K,T> _pair;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node *godfather;

    /**
     * Node Constructor. Takes \p key for the key and \p val for the
     * value. Optionally the sons can be specified.
     */
  Node(const K & key, const T & val, Node * l = nullptr, Node * r = nullptr, Node * g = nullptr) :
    _pair{key, val}, left{l}, right{r}, godfather{g} {};
    // PBM: What if l or r are already assigned to other unique_ptrs?
    /**
     * Print the key, value and sons' keys of a node.
     */
    void print();

  };
  std::unique_ptr<Node> root;
   /**
   * Return a pointer to the (possible) father of a given key.
   */

public:
 Tree() : root{nullptr} {};

  // Iterator declarations
  class Iterator;
  Iterator begin(Node *ptr){
    if(ptr->left==nullptr)
      return Iterator{ptr};
    else
      begin((ptr->left).get());
  }
  
  Iterator last(Node *ptr){    
   if (ptr->right==nullptr)
     return Iterator(ptr);
   else
     last((ptr->right).get());
  }

  Iterator last(){
    return last(root.get());
  }
  
  Iterator begin(){    
    return begin(root.get());
  }
  
  Iterator end(){
    return Iterator{nullptr};
  }

  Iterator insert(const K & key, const T & val, std::unique_ptr<Node> & ptr, Node *parent){

    if (ptr == nullptr ){
      ptr.reset(new Node(key, val,nullptr,nullptr,parent));
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
    }
    
  }

  Iterator insert(const K & key, const T & val){
    return insert(key, val, root, nullptr);
  }

  // PBM: just for debug. I want to see the properties of the last added node. Cannot acces directly from main, so defin this auxiliary.
  void last_node(Iterator tmp);

  void naive_print(std::unique_ptr<Node> & ptr);
  void naive_print(){ naive_print(root); }   

  /*
  Iterator find(std::unique_ptr<Node> &target){
    
    std::pair<K,V> compare=root->_pair;
    std::unique_ptr<Node> &tmp;
    std::unique_ptr<Node> &next;
    
    if(compare.first==target->_pair.first){
      next=root;
      return next;
    }else if(compare.first>target->_pair.first){
      next=
    }
    
  }
  */
    
  /*
  class ConstIterator;
  ConstIterator begin();
  ConstIterator end();
  */
  
};

template < typename K, typename T>
void Tree<K,T>::Node::print(){
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
  
  std::pair<K,V>& operator*() const { return current->_pair; }
  
  Node *get(){ return current; }
  
  Iterator get_godfather(){ return Iterator(current->godfather); }

  // return minimum on right branch
  Iterator rmin(){
    if(current->right!=nullptr){
      Node *tmp{(current->right).get()};
      if(tmp->left==nullptr){
	return Iterator(tmp);
      }
      else{
	current=(current->left).get();
	return this->rmin();
      }
    }else{
      return Iterator(nullptr);
    }
  }

  // returns true is argument is a node with left/right/godfather all nullptr
  bool islast(){
    Node *tmp=this->get();
    if(tmp->right==nullptr&&tmp->godfather==nullptr)
      return true;
    else
      return false;
  }

  // WORK HERE
  // ++it
  
  Iterator& operator++() {
    /*
    if(this->islast()){
      std::cout << "Out of bounds" << std::endl;
      return Iterator(nullptr); // retrun end()
      }else{*/
      if(current->right!=nullptr){
	current=(this->rmin()).get();
	return *this;
      }else{
	current=(this->get_godfather()).get();
	return *this;
      }
      // }
  };
  
  /*
    if(current->rigth==nullptr){
      // find minimum in path from root
      
    };
  */
    
    /*
    current = current->next.get();
    return *this;
    */
    
  /*
  // it++
  Iterator operator++(int) {
    Iterator it{current};
    ++(*this);
    return it;
  }

  bool operator==(const Iterator& other) {
    return this->current == other.current;
  }
  bool operator!=(const Iterator& other) { return !(*this == other); }*/
};

/* Extra stuff */
template < typename K, typename T>
  void Tree<K,T>::last_node(Tree::Iterator tmp){
  Node *parent;
  std::pair<K,T> tmp_pair{*tmp};
  std::cout << "Last added note properties" << std::endl;
  std::cout << "Key: " << tmp_pair.first << std::endl;
  std::cout << "Value: " << tmp_pair.second << std::endl;
  parent=(tmp.get_godfather()).get();
  if(parent==nullptr)
    std::cout << "Godfather: nullptr" << std::endl;
  else
    std::cout << "Godfather: " << parent->_pair.first << "," << parent->_pair.second << std::endl;  
}

template < typename K, typename T>
  void Tree<K,T>::naive_print(std::unique_ptr<Node> & ptr){
  if (ptr->left != nullptr )
    naive_print(ptr->left);
  if (ptr->right != nullptr )
    naive_print(ptr->right);
  (*ptr).print();
}

#endif
