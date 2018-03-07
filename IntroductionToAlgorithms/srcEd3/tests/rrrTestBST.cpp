/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl; using std::ostream;

#include<memory>
using std::unique_ptr;
using std::make_unique;

template<typename T> class BinNode;

template<typename T>
void printBinNode(const BinNode<T>&node)
{
  cout << "key: " << node.key();

  if(node.parent()){ cout << ", P: " << node.parent(); }
  else { cout << ", P: 0"; }

  if(node.left()){ cout << ", L: " << node.left().get(); }
  else { cout << ", L: 0";}

  if(node.right()){ cout << ", R: " << node.right().get(); }
  else { cout << ", R: 0";}

  cout << endl;
}

template<typename T>
class BinNode
{
public:
  using value_type=T;

  // Default constructor, and using key.
  BinNode(T t=T{}): Key_(t),
    Parent_(nullptr),Left_(nullptr),Right_(nullptr)
  {}
  
  //////////////////////////////////////////////////////////////////////////
  // Rule of 5, since we have pointers.
  // copy constructor, copy assignment operator
  // move constructor, move assignment operator
  // Destructor
  BinNode(BinNode& other)=delete;
  BinNode& operator=(const BinNode&)=delete;
  BinNode(BinNode&& other):BinNode{}
  {
    if((other.Left_==nullptr)&&(other.Right_==nullptr))
    {
      Key_=std::move(other.Key_);
    }
  }
  BinNode& operator=(BinNode&& other)
  {
    if((other.Left_==nullptr) && (other.Right_==nullptr))
    {
      Key_=std::move(other.Key_);
    }
    return *this;
  }

  virtual ~BinNode()=default;

  //////////////////////////////////////////////////////////////////////////
  // Accessors to key, parent, left and right
  T& key(){return Key_;}
  const T& key()const {return Key_;}

  BinNode*& parent(){ return Parent_; }
  const BinNode* parent() const { return Parent_; }
  
  unique_ptr<BinNode>& left(){return Left_;}
  const unique_ptr<BinNode>& left()const {return Left_;}

  unique_ptr<BinNode>& right(){return Right_;}
  const unique_ptr<BinNode>& right()const {return Right_;}

private:

  T                   Key_;
  // https://stackoverflow.com/questions/46804703/
  // smart-pointers-for-binary-tree/
  BinNode*            Parent_;
  unique_ptr<BinNode> Left_;
  unique_ptr<BinNode> Right_;
};


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BinarySearchTree
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
template<typename T>
class BinarySearchTree
{
public:
  BinarySearchTree()=default;

  void insert_iter(const BinNode<T>&);
  void insert_iter(const T&);
  void insert_recur(const T&);

  void transplant(BinNode<T>*u,BinNode<T>*v);
  void deletenode(BinNode<T>* z);

  // Do CLRS 12.3.5
  // Do CLRS 12.3.6

  void inorder_recur(const BinNode<T>*);
  void inorder_iter_stack(const BinNode<T>*);
  void inorder_iter_nostack(const BinNode<T>*);
  void preorder_recur(const BinNode<T>*);
  void preorder_iter_stack(const BinNode<T>*);
  void preorder_iter_nostack(const BinNode<T>*);
  void postorder_recur(const BinNode<T>*);
  void postorder_iter(const BinNode<T>*);
  void postorder_iter_nostack(const BinNode<T>*);

  BinNode<T>* search_recur(const BinNode<T>*, const T&);
  BinNode<T>* search_iter(const BinNode<T>*, const T&);

  BinNode<T>* minimum_recur(const BinNode<T>*);
  BinNode<T>* minimum_iter(const BinNode<T>*);
  BinNode<T>* maximum_recur(const BinNode<T>*);
  BinNode<T>* maximum_iter(const BinNode<T>*);

  BinNode<T>* successor(const BinNode<T>*);
  BinNode<T>* predecessor(const BinNode<T>*);



private:
  unique_ptr<BinNode<T>> Root_=nullptr;
};

////////////////////////////////////////////////////////////////////////////
//Insert
////////////////////////////////////////////////////////////////////////////
template<typename T>
void BinarySearchTree<T>::insert_iter(const BinNode<T>& z)
{
  insert_iter(z.key());
}

template<typename T>
void BinarySearchTree<T>::insert_iter(const T& key)
{
  // Observer pointers.
  // trailing pointer to keep tract of parent.
  BinNode<T>* y_pt = nullptr;
  // Checks where we find the first null.
  decltype(y_pt) x_pt = Root_.get();

  // walk down the tree from the root.
  while(x_pt!=nullptr)
  {
    y_pt=x_pt;
    if(key<x_pt->key())
    {
      x_pt=x_pt->left().get();
    }
    else
    {
      x_pt=x_pt->right().get();
    }
  }

  // At this point, x_pt is null, which has `parent' y.
  // So we need to figure out where to put x in y.
  if(y_pt==nullptr)
  {
    Root_=make_unique<BinNode<T>>(key);
    Root_->parent()=nullptr;
  }
  else if(key < y_pt->key())
  {
    y_pt->left()=make_unique<BinNode<T>>(key);
    y_pt->left()->parent()=y_pt;

  }
  else
  {
    y_pt->right()=make_unique<BinNode<T>>(key);
    y_pt->right()->parent()=y_pt;
  }
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// main
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int main()
{
  // testing constructors and destructors.
  BinNode<double> dnode1;
  decltype(dnode1) dnode2{42.42};
  printBinNode(dnode1);
  printBinNode(dnode2);
  decltype(dnode1) dnode3{std::move(dnode2)};
  printBinNode(dnode3);
  decltype(dnode1) dnode4;
  dnode4=std::move(dnode2);
  printBinNode(dnode4);

  BinarySearchTree<decltype(dnode1)::value_type> bst;
  bst.insert_iter(std::move(dnode1));





  return 0;
}















