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
// 2.3: Delete Middle Node: Implement an algorithm to delete a node in the 
//      middle (i.e., any node but the first and last node, not necessarily 
//      the exact middle) of a singly linked list, given only access to that
//      node.
//
// EXAMPLE:
// Input: the node c from the linked list a->b->c->d->e->f.
// Result: nothing is returned, but the new linked list looks like
//         a->b->d->e->f
//
// Hints:
//
// #72: Picture the list 1->5->9->12. Removing 9 would make it look like 
//      1->5->12. You only have access to the 9 node. Can you make it look 
//      like the correct answer?

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
//  int data;
//  ListNode* next;
//  ListNode* prev;
//
//  ListNode(int d):data(d), next(nullptr), prev(nullptr)
//  {}
//};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here
// The return value is if we can delete it or not.
bool deleteNode(ListNode* mid)
{
  if(mid == nullptr)
  {
    return false; // failure
  }

  // We also need the next node to be valid to copy over the value. If it's
  // not available, we cannot set this to null, since we need access to the
  // previous node.
  if(mid->next == nullptr)
  {
    return false;
  }

  // get the next node in a tmp variable (so we can delete it)
  ListNode* tmp = mid->next;

  // Copy over the value
  mid->data = tmp->data;

  // relink
  mid->next = tmp->next;

  // delete tmp
  delete tmp; tmp = nullptr;

  // success
  return true;
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
      ListNode* input = buildSinglyLinkedList({});
      bool ans = deleteNode(input);

      REQUIRE(ans==false);
    }
    { // 2
      ListNode* input = buildSinglyLinkedList({1,5,9,12});
      ListNode* thrdNode = input->next->next;
      deleteNode(thrdNode);

      std::vector<int> sol{1,5,12};
      REQUIRE(convertSinglyLinkedListToVec(input)==sol);
    }
  }
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

