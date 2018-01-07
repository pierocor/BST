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

    /**
     * Node Constructor. Takes \p key for the key and \p val for the
     * value. Optionally the sons can be specified.
     */
    Node(const K & key, const T & val, Node * l = nullptr, Node * r = nullptr) :
      _pair{key, val}, left{l}, right{r} {};
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
  //Node * parent(const K & key){
    // PBM: to be implemented


public:
 Tree() : root{nullptr} {};

  void insert(const K & key, const T & val, std::unique_ptr<Node> & ptr){
    if ( ptr == nullptr ){
      std::cout << key << " IN!\n";
      ptr.reset(new Node(key, val));
      return;
    }
    if( ptr->_pair.first > key ){
      std::cout << key << " less than " << ptr->_pair.first << "\n";
      insert(key, val, ptr->left);
    }
    if( ptr->_pair.first < key ){
      std::cout << key << " greather than "<< ptr->_pair.first << "\n";
      insert(key, val, ptr->right);
    }
    if( ptr->_pair.first == key )
      ptr->_pair.second = val;  // PBM: up to us!
  }

  void insert(const K & key, const T & val){
    insert(key, val, root);
  }

  void naive_print(std::unique_ptr<Node> & ptr){
    if (ptr->left != nullptr )
      naive_print(ptr->left);
    if (ptr->right != nullptr )
      naive_print(ptr->right);
    (*ptr).print();
  }

  void naive_print(){
    // (*root).print();
    naive_print(root);
  }

  // Find minimum in path from root to a given node  

  // Iterator declarations
  class Iterator;
  Iterator begin(std::unique_ptr<Node> &ptr){    
   if (ptr->left==nullptr)
     return Iterator(ptr);
   else
     begin(ptr->left);
  }

  Iterator end(std::unique_ptr<Node> &ptr){    
   if (ptr->right==nullptr)
     return Iterator(ptr);
   else
     end(ptr->right);
  }

  
  Iterator begin(){    
    return begin(root);
  }
  
  Iterator end(){    
    return end(root);
  }

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
  std::cout << std::endl;
}

// Iterator definitions
template <typename K, typename V>
  class Tree<K,V>::Iterator {
  using Node = Tree<K,V>::Node;
  std::unique_ptr<Node> &current;

 public:
 Iterator(std::unique_ptr<Node> &n) : current{n} {}
  std::pair<K,V>& operator*() const { return current->_pair; }

  // WORK HERE
  // ++it
  /*
  Iterator& operator++() {
    std::pair<K,V> target{current->_pair};
    std::unique_ptr<Node> &tmp{current};
    
    K target_k{target.first};
    
    if(current->right!=nullptr){
      //tmp{current->right};
      //current=Tree<K,V>::begin(&current->right);
      //return current;
    }
    
    return *this;
  };
  */
  
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




#endif
