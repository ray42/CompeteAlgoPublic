/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Question here.
// 2.2: Return Kth to Last: Implement an algorithm to find the kth to last 
//      element of a singly linked list.
//
// Hints:
//
// #8: What if you knew the linked list size? What is the difference between
//     finding the Kth-to-last element and finding the Xth element?
// #25: If you don't know the linked list size, can you compute it? How does
//      this impact the runtime?
// #41: Try implementing it recursively. If you could find the (K-1)th to 
//      last element, can you find the Kth element?
// #67: You might find it useful to return multiple values. Some languages 
//      don't directly support this, but there are workarounds in 
//      essentially any language. What are some of those workarounds?
// #126: Can you do it iteratively? Imagine if you had two pointers pointing
//       to adjacent nodes and they were moving at the same speed through 
//       the linked list. When one hits the end of the linked list, where 
//       will the other be?

// Note: In this question, we have to ask a few clarifying questions and
// make some assumption. 
//
// Firstly, we have to decide on the valid input:
// Does the input start form k=0 or k=1?
//
// If we use some foresight, we will see that it's better to use k=1, since
// if we have:
//
// 4->3->2->1
//
// And we want to get the k=1 to last element, which is 1, we can have two
// pointers which is k-apart:
// p1 p2
// 4->3->2->1
// Then we simply move them both until p2 reaches null:
//          p1 p2
// 4->3->2->1
// Now we can simply return the node pointed to by p1.
//
// HOWEVER, note that if we need to remove the node, then we would need k+1
// element apart between p1 and p2, since then p1 points to the ONE BEFORE
// the node we need to delete, which is what we want.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include "./../rayheader.h"
#include<memory>

// Def of ListNode: (make sure to write this for practice, then comment it 
// out)
//struct ListNode{
//  int data;
//  ListNode* prev;
//  ListNode* next;
//
//  ListNode(int d):data(d), prev(nullptr), next(nullptr)
//  {}
//};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Impl 1: Linked list size is known (or work out the size)
// This is two pass: https://leetcode.com/articles/remove-nth-node-end-list
ListNode* getKthToLastKnownSize(ListNode* head, int k)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Impl 2: Recursive (approach B in CTCI, C++)

ListNode* getKthToLastRecurHelper(ListNode* head, int k, int& i);

ListNode* getKthToLastRecur(ListNode* head, int k)
{
}

ListNode* getKthToLastRecurHelper(ListNode* head, int k, int& i)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Impl 3: Iterative using two pointers
// This is one pass: https://leetcode.com/articles/remove-nth-node-end-list
ListNode* getKthToLastIter(ListNode* head, int k)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    { // 1 Edge case: null input
      ListNode* input = buildSinglyLinkedList({}); //  this returns null
      ListNode* res = getKthToLastKnownSize(input,1);
      ListNode* ans = nullptr;

      // For impossible inputs, the function should return nullptr. We can
      // only compare this with nullptr.
      REQUIRE(res==ans);
    }
    { // 2 Edge case: return nonexistence: node 10 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastKnownSize(input,10);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 3 Edge case: return nonexistence node: node -1 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastKnownSize(input,-1);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 4 Edge case: return nonexistence node: node 0 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastKnownSize(input,0);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 5 Get the first 1st to last node (i.e the last node)
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastKnownSize(input,1);
      ListNode* ans = new ListNode{1};
      REQUIRE(res->data == ans->data);
    }
    { // 6 Get the nth to last node (i.e. the first element)
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastKnownSize(input,4);
      ListNode* ans = new ListNode{4};
      REQUIRE(res->data == ans->data);
    }
    { // 7 get every kth to last element from k=1..n
      ListNode* input = buildSinglyLinkedList({6,5,4,3,2,1});
      for(int k = 1; k <= 6; ++k)
      {
        ListNode* res = getKthToLastKnownSize(input,k);
        ListNode* ans = new ListNode{k};
        REQUIRE(res->data == ans->data);
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Recursive 
  //////////////////////////////////////////////////////////////////////////
  SECTION("Sec Testing ")
  {
    { // 1 Edge case: null input
      ListNode* input = buildSinglyLinkedList({}); //  this returns null
      ListNode* res = getKthToLastRecur(input,1);
      ListNode* ans = nullptr;

      // For impossible inputs, the function should return nullptr. We can
      // only compare this with nullptr.
      REQUIRE(res==ans);
    }
    { // 2 Edge case: return nonexistence: node 10 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastRecur(input,10);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 3 Edge case: return nonexistence node: node -1 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastRecur(input,-1);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 4 Edge case: return nonexistence node: node 0 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastRecur(input,0);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 5 Get the first 1st to last node (i.e the last node)
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastRecur(input,1);
      ListNode* ans = new ListNode{1};
      REQUIRE(res->data == ans->data);
    }
    { // 6 Get the nth to last node (i.e. the first element)
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastRecur(input,4);
      ListNode* ans = new ListNode{4};
      REQUIRE(res->data == ans->data);
    }
    { // 7 get every kth to last element from k=1..n
      ListNode* input = buildSinglyLinkedList({6,5,4,3,2,1});
      for(int k = 1; k <= 6; ++k)
      {
        ListNode* res = getKthToLastRecur(input,k);
        ListNode* ans = new ListNode{k};
        REQUIRE(res->data == ans->data);
      }
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Iterative - two pass 
  //////////////////////////////////////////////////////////////////////////
  SECTION("Sec Testing ")
  {
    { // 1 Edge case: null input
      ListNode* input = buildSinglyLinkedList({}); //  this returns null
      ListNode* res = getKthToLastIter(input,1);
      ListNode* ans = nullptr;

      // For impossible inputs, the function should return nullptr. We can
      // only compare this with nullptr.
      REQUIRE(res==ans);
    }
    { // 2 Edge case: return nonexistence: node 10 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastIter(input,10);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 3 Edge case: return nonexistence node: node -1 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastIter(input,-1);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 4 Edge case: return nonexistence node: node 0 in a list of 4 ele
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastIter(input,0);
      ListNode* ans = nullptr;
      REQUIRE(res==ans);
    }
    { // 5 Get the first 1st to last node (i.e the last node)
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastIter(input,1);
      ListNode* ans = new ListNode{1};
      REQUIRE(res->data == ans->data);
    }
    { // 6 Get the nth to last node (i.e. the first element)
      ListNode* input = buildSinglyLinkedList({4,3,2,1});
      ListNode* res = getKthToLastIter(input,4);
      ListNode* ans = new ListNode{4};
      REQUIRE(res->data == ans->data);
    }
    { // 7 get every kth to last element from k=1..n
      ListNode* input = buildSinglyLinkedList({6,5,4,3,2,1});
      for(int k = 1; k <= 6; ++k)
      {
        ListNode* res = getKthToLastIter(input,k);
        ListNode* ans = new ListNode{k};
        REQUIRE(res->data == ans->data);
      }
    }
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

