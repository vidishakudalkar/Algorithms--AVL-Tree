#include <iostream>
using namespace std;  

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

class BST
{
 public:
  /***** Function Members *****/
  BST();
  bool empty() const;
  bool search(const int & item) const; 
  void insert(const int & item);
  void preorder() const;
  void inorder() const;
  void nodeCount() const;
  void delete_node(const int & item);
  
 private:
  /***** Node class *****/
  class BinNode 
  {
   public:
    int data;
    BinNode * left;
    BinNode * right;
	BinNode * head;
	int height;
    int balance;

    // BinNode constructors
    // Default -- data part is default int value; both links are null.
    BinNode()
    : left(0), right(0),head(0),height(0),balance(0)
    {}

    // Explicit Value -- data part contains item; both links are null.
    BinNode(int item)
    : data(item), left(0), right(0),head(0),height(0),balance(0)
    {}
 
  };// end of class BinNode declaration
  
  /***** Data Members *****/
  BinNode * myRoot; 
  
  void preorderRecursion(BinNode* node) const;
  void inorderRecursion(BinNode* node) const;
  void leftrotate(BinNode* node,BinNode* myRoot) const;
  void rightrotate(BinNode* node,BinNode* myRoot) const;
  void left_right_rotate(BinNode* node) const;
  void right_left_rotate(BinNode* node) const;
  int nodeCountRecursion(BinNode* node,int count) const;
  void BalanceBST(BinNode* node) const;
 // int height_balance(BinNode* node) const;
}; // end of class declaration

#endif
