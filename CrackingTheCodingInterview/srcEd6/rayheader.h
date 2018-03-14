#ifndef RAYHEADER_H
#define RAYHEADER_H

#include<iostream>
#include<iterator>
#include<vector>
#include<deque>
#include<string>
#include<cstddef> // size_t
#include<stdexcept>

// Generic stuff
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
template<typename Cont>
void printCont(Cont c, const std::string& str = "")
{
  if(!str.empty())
  {
    std::cout << str;
  }
  for(const auto& val:c)
  {
    std::cout << val << ' ';
  }
  std::cout << '\n';
}


// Linked list stuff.
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
struct ListNode{
  int data;
  ListNode* next;
  ListNode* prev;

  ListNode(int d):data(d), next(nullptr), prev(nullptr)
  {}
};

ListNode* buildSinglyLinkedList(const std::vector<int>& v)
{
  ListNode dummy = ListNode{0};
  ListNode* head = &dummy;
  for(const auto& val:v)
  {
    head->next = new ListNode{val};
    head = head->next;
  }
  return dummy.next;
}

std::vector<int> convertSinglyLinkedListToVec(ListNode* n)
{
  std::vector<int> ret{};

  if(n == nullptr)
    return ret;

  while(n)
  {
    ret.push_back(n->data);
    n = n->next;
  }
  return ret;
}

void printListNode(ListNode* n, const std::string& str="")
{
  if(!str.empty())
  {
    std::cout << str;
  }
  while(n)
  {
    std::cout << n->data << ' ';
    n = n->next;
  }
  std::cout << '\n';
}

// Stack and Queues
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

template<typename T, 
         typename Container = std::deque<T> >class MyStack;


// Stack helpers
////////////////////////////////////////////////////////////////////////////
template<typename T>
void printStack(const T& s, const std::string& str="")
{
  if(!str.empty())
  {
    std::cout << str;
  }
  std::cout << "sz: " << s.size()
            << ", empty: " << s.isEmpty()
            << ", data: ";
  for(int i=0; i < s.size(); ++i)
  {
    std::cout << s.data_.at(i) << ' ';
  }
  std::cout << '\n';
}



// MyStack class
// /////////////////////////////////////////////////////////////////////////
template<typename T, 
         typename Container
>class MyStack{

// Friend functions
template<typename U> friend void printStack(const U&, const std::string&);

public:
  // Remove the top item from the stack.
  void pop()
  {
    if(isEmpty())
    {
      throw std::runtime_error("pop on empty stack");
    }
    --size_;
  }

  // Add an item to the top of the stack
  void push(const T& item)
  {
    if(size() == static_cast<int>(data_.size()))
    {
      data_.push_back(item);
    }
    else
    {
      data_.at(size_) = item;
    }
    ++size_;
  }

  // Return the top of the stack
  T peek() const
  {
    if(isEmpty())
    {
      throw std::runtime_error("peek on empty stack");
    }
    return data_.at(size_-1);
  }

  // Return true if and only if the stack is empty
  bool isEmpty() const
  {
    return size()==0;
  }

  // Return the number of items in the stack.
  int size() const
  {
    return size_;
  }

  T data(int i) const
  {
    return data_.at(i);
  }

private:
  int       size_=0;
  Container data_=Container{};
};

MyStack<int> buildStack(const std::vector<int>& v)
{
  MyStack<int> mystack{};
  for(const auto& val:v)
  {
    mystack.push(val);
  }
  return mystack;
}
std::vector<int> convertStackToVec(const MyStack<int>& mystack)
{
  std::vector<int> ret;
  for(int i = 0; i < mystack.size(); ++i)
  {
    ret.push_back(mystack.data(i));
  }
  return ret;
}


// Nodes, Trees and Graphs
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// A general node.
template<typename T>
class GenNode{
public:
  GenNode(T d=T{}, int nchild=0, const std::string& s=""):
    data_{d},children_{std::vector<GenNode*>(nchild,nullptr)},name_{s}
  {
  }

  virtual ~GenNode(){};

  T& data(){return data_;}
  const T& data()const {return data_;}

  std::string name(){return name_;}
  const std::string name()const {return name_;}

  void set_num_children(int n){ children_.resize(n); }

  GenNode* child(int i){ return children_.at(i); }
  const GenNode* child(int i) const { return children_.at(i); }

  virtual void printStat(const std::string& s = "")
  {
    if(!s.empty())
    {
      std::cout << s;
    }

    if(!name_.empty())
    {
      std::cout << "s: " << name_ << ", ";
    }
    cout << "d: " << data_ << ", nchilds: " << children_.size() << '\n';
  }

private:
  T data_;
  std::vector<GenNode*> children_;
  std::string name_;
};


template<typename T>
class BinNode: public GenNode<T>
{
public:
  BinNode(T d=T{}, const std::string& s=""):GenNode<T>{d,2,s}
  {}

  BinNode* left() { return this->child(0); }
  const BinNode* left()const { return this->child(0); }

  BinNode* right() { return this->child(0); }
  const BinNode* right()const { return this->child(0); }

};






#endif
