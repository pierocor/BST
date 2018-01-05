# Binary search tree
## A collaborative project by Luca Ciuffreda and Piero Coronica


## Notes:

In this exam you are required to implement a **template** binary search tree (BST). A BST, is a hierarchical (ordered) data structure where each **node** can have at most two children, namely, **left** and **right** child. Each node stores a **pair** of a **key** and the associated **value**. The binary tree is ordered according to the keys. Given a node `N`, all the nodes having keys **smaller** than the key of the node `N` can be found going **left**. While all the nodes with a key **greater** than the key of the node `N` can be reached going **right**.


From the implementation point of view, you node has two pointers `left` and `right` pointing to the left and right child respectively. The pointers points to `nullptr` if they have no children.

It is useful to add an additional pointer (head, root, whatever you like) pointing to the first node, called **root node**.

### Tree traversal

The tree must be traversed in order, i.e., if I "print" the tree in the picture, I expect to see on the screen the sequence
```
1 3 4 6 7 8 10 13 14
```
node `1` is the first node, and node `14` is the last one.

### Assignments
You have to solve the following tasks in C++11 (C++14 and 17 are welcomed as well).

  - implement a **template** binary search tree
    - it must be templated on the type of the key and the type of the value associated with it.
    - **optional** you can add a third template on the operation used to compare two different keys.
    - implement proper iterators for your tree (i.e., `iterator` and `const_iterator`)
    - the tree must have at least the following public member function
      1. `insert`, used to insert a new pair key-value.
      2. `print`,  used to print `key: value` of each node. Note that the output should be in order with respect to the keys.
      3. `clear()`, clear the content of the tree.
      4. `begin()`, return an `iterator` to the first node (which likely will not be the root node)
      5. `end()`, return a proper `iterator`
      6. `cbegin()`, return a `const_iterator` to the first node
      7. `cend()`, return a proper `const_iterator`
      8. `balance()`, balance the tree.
      9. `find`, find a given key and return an iterator to that node. If the key is not found returns `end()`;
      9. **optional** `erase`, delete the node with the given key.
      10. **optional** implement the `value_type& operator[](const key_type& k)` function int the `const` and `non-const` versions). This functions, should return a reference to the value associated to the key `k`. If the key is not present, a new node with key `k` is allocated having the value `value_type{}`.

    - implement copy and move semantics for the tree.

- test the performance of the lookup (using the function `find`) before and after the tree is re-balanced. Use proper numbers (and types) of nodes and look-ups. Does lookup behaves as `O(log N)`?
- **optional** document the code with `Doxygen`
- write a short report
- test everything

### Hints
- you can use `std::pair<key_type,value_type>` found in the header `utility`
- use recursive functions
- **Big hint** start coding and using the iterators ASAP.
