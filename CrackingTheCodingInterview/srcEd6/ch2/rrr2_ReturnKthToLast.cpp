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
ListNode* getKthToLastKnownSize(ListNode* head)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Impl 2: Recursive (approach B in CTCI, C++)
ListNode* getKthToLastRecur(ListNode* head)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Impl 3: Iterative using two pointers
// This is one pass: https://leetcode.com/articles/remove-nth-node-end-list
ListNode* getKthToLastIter(ListNode* head)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    // Null 
    { // 1
      ListNode* n = nullptr;
      ListNode* r = return
      REQUIRE(n==nullptr);
    }
    { // 2
      ListNode* n0 = buildSinglyLinkedList({0});
      std::vector<int> sol0{0};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // More edge cases, duplicates at the (3) beginning and at the (4) end
    { // 3
      ListNode* n0 = buildSinglyLinkedList({1,1,1,2,3,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    { // 4
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,4,4,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - no deletion
    { // 5
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,5,6,7});
      std::vector<int> sol0{1,2,3,4,5,6,7};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - delete every other element.
    { // 6
      ListNode* n0 = buildSinglyLinkedList({1,1,2,2,3,3,4,4,5,5,6,6});
      std::vector<int> sol0{1,2,3,4,5,6};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // in-place two-pointer algo test:
  //////////////////////////////////////////////////////////////////////////
  SECTION("Sec Testing ")
  {
    // First check edge cases: (1) empty linked list and (2) one element:
    { // 1
      ListNode* n0 = buildSinglyLinkedList({});
      std::vector<int> sol0{};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    { // 2
      ListNode* n0 = buildSinglyLinkedList({0});
      std::vector<int> sol0{0};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // More edge cases, duplicates at the (3) beginning and at the (4) end
    { // 3
      ListNode* n0 = buildSinglyLinkedList({1,1,1,2,3,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    { // 4
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,4,4,4});
      std::vector<int> sol0{1,2,3,4};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - no deletion
    { // 5
      ListNode* n0 = buildSinglyLinkedList({1,2,3,4,5,6,7});
      std::vector<int> sol0{1,2,3,4,5,6,7};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    // General case - delete every other element.
    { // 6
      ListNode* n0 = buildSinglyLinkedList({1,1,2,2,3,3,4,4,5,5,6,6});
      std::vector<int> sol0{1,2,3,4,5,6};
      ListNode* res0 = deleteDupsInplace(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

