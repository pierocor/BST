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
    std::pair<K,T> _pair;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

  public:
    /**
     * Node Constructor. Takes \p key for the key and \p val for the
     * value. Optionally the sons can be specified.
     */
    Node(const K & key, const T & val, Node * l = nullptr, Node * r = nullptr) :
      _pair{key, val}, left{l}, right{r} {};
///////////////////////////// EXCEPTIONS IN THE CONSTRUCTOR ?  ////////////////////////
// What if l or r are already assigned to other pointers?
    /**
     * Print the key and the value of a node.
     */
    void print(){
      std::cout << "key: " << _pair.first << "\t value: " <<  _pair.second << std::endl;
    }
  };
  std::unique_ptr<Node> root;

public:
  Tree() : root{nullptr} {};
  void insert(const K & key, const T & val){
    root.reset(new Node(key, val));
  }
  void naive_print(){
    (*root).print();
  }
};

#endif
