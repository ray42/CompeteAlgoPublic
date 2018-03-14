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
// 2.1: Remove Dups: Write code to remove duplicates from an unsorted
//      linked list.
//
//FOLLOW UP
//
//How would you solve this problem if a temporary buffer is not allowed?
//
// I would loop through the linked list and place each entry in a hash set. 
// If I cannot insert it into the linked list, then I would delete it.
//
// I don't know what to do if a temporary buffer is not allowed. (See the
// solution below. My mind was trying to do it in O(N), but they sacrifice 
// time for space, so it becomes O(N^2).)
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Hints:
//
// #9: Have you tried a hash table? You should be able to do this in a
//     single pass of the linked list.
// #40: Without extra space, you'll need O(N^2) time. Try using two 
//      pointers, where the second one searches ahead of the first one.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include "./../rayheader.h"
#include<unordered_set>
#include<memory>

// Def of ListNode: (make sure to write this for practice, then comment it 
// out)
//struct ListNode{
//};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here
ListNode* deleteDups(ListNode* head)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// This implementation is in-place, but uses two pointers and is O(N^2) time 
// instead of O(N).
ListNode* deleteDupsInplace(ListNode* head)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    // First check edge cases: (1) empty linked list and (2) one element:
    { // 1
      ListNode* n0 = buildSinglyLinkedList({});
      std::vector<int> sol0{};
      ListNode* res0 = deleteDups(n0);
      REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
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

