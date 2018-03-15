#ifndef GFGUTILITY_H
#define GFGUTILITY_H

#include<vector>
#include<string>
#include<stack>
#include<iostream>

#define SENTINEL -999

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Utility for list problems.
// Definition for singly-linked list.
struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

// Convert to vector for testing
std::vector<int> listToVec(ListNode* l)
{
  std::vector<int> ret;
  while(l != nullptr)
  {
    ret.push_back(l->val);
    l = l->next;
  }
  return ret;
}

// Generate a singly linked list based on vector nums
template<typename T>
ListNode* genList(const std::vector<T>& nums)
{
  ListNode* dummy=new ListNode{0};
  ListNode* tmp = dummy;
  for(const auto& i:nums)
  {
    tmp->next = new ListNode{i};
    tmp = tmp->next;
  }
  return dummy->next;
}

// print vector
template<typename T>
void printVec(const std::vector<T>& v, const std::string& str="")
{
  if(!str.empty())
  {
    cout << str;
  }
  for(const auto& vi : v)
  {
    cout << vi << ' ';
  }
  cout << '\n';
}

// print container
template<typename T>
void printCont(const T& v, const std::string& str="")
{
  if(!str.empty())
  {
    cout << str;
  }
  for(const auto& vi : v)
  {
    cout << vi << ' ';
  }
  cout << '\n';
}

// print linked list
void printList(ListNode* l, const std::string& str="")
{
  printVec(listToVec(l),str);
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// utility for binary trees

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// iterative solution to inorder traversal since we need to put the values
// in a vector and return it.
std::vector<int> treeInorderToVec(TreeNode* root)
{
  std::vector<int> ret{};
  std::stack<TreeNode*>  stack{};

  TreeNode* curr = root;
  while(curr != nullptr || !stack.empty())
  {
    // Keep pushing the left child into the stack
    while(curr != nullptr)
    {
      stack.push(curr);
      curr = curr->left;
    }

    curr = stack.top();
    stack.pop();
    ret.push_back(curr->val);
    curr = curr->right;
  }
  return ret;
}

#endif


