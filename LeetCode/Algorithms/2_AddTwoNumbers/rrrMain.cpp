/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<vector>
#include<string>

// https://leetcode.com/problems/add-two-numbers/description/

// You are given two non-empty linked lists representing two non-negative 
// integers. The digits are stored in reverse order and each of their nodes 
// contain a single digit. Add the two numbers and return it as a linked 
// list.
//
// You may assume the two numbers do not contain any leading zero, except 
// the number 0 itself.
//
// Example
//
// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
// Explanation: 342 + 465 = 807.

//   Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
  {
    // This is easy. Add two numbers manually, e.g.
    //  3 4 2
    // +4 6 5
    // =8 0 7
    // First we add 2+5=7, no carry over so we're done.
    // If there is a carry, we just add it on in the next sum.
    //
    // Note that they may be different lengths.

    using val_t = decltype(l1->val);

    decltype(l1) sentinel = new ListNode{0};
    auto current = sentinel;
    val_t carry = 0;

    while((l1 != nullptr) || (l2 != nullptr))
    {
      val_t l1_val = (l1 != nullptr) ? l1->val:0;
      val_t l2_val = (l2 != nullptr) ? l2->val:0;
      val_t sum = l1_val + l2_val + carry;
      carry = sum/10;
      current->next = new ListNode{sum%10};
      current = current->next;

      if(l1 != nullptr) l1 = l1->next;
      if(l2 != nullptr) l2 = l2->next;
    }
    if(carry>0) current->next = new ListNode{carry};
    
    return sentinel->next;
  }
};

auto printListNode(ListNode* list_node, std::string str = "") -> void
{
  if(!str.empty()) cout << str << ": ";

  while(list_node != nullptr)
  {
    cout << list_node->val << " ";
    list_node = list_node->next;
  }
  cout << '\n';
}

template<typename T>
auto buildListNode(T& v)
{
  ListNode* list_node = new ListNode{v[0]};
  decltype(list_node) current = list_node;

  for(decltype(v.size()) i = 1; i < v.size(); ++i)
  {
    current->next = new ListNode{v[i]};
    current = current->next;
  }
  return list_node;
}

auto main(int, char* [])->int
{
  std::vector<int> v1{5};
  decltype(v1)     v2{5};
  
  auto l1 = buildListNode(v1);
  auto l2 = buildListNode(v2);
  printListNode(l1, "l1");
  printListNode(l2, "l2");
  cout << "==========================\n";

  auto ans = Solution{}.addTwoNumbers(l1,l2);
  cout << "==========================\n";
  printListNode(ans,"ans");

  return 0;
}
