/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//web
#include<iostream>
using std::cout; using std::endl;

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';

#include<string>
using std::string;
#include<unordered_set>
using std::unordered_set;
#include<vector>
using std::vector;
#include<algorithm> // sort
#include<unordered_set>

#include "./../rayheader.h"

ListNode* removeDups(ListNode* n)
{
  // base case
  if(n==nullptr)
    return n;

  ListNode* dummy = new ListNode{0};
  dummy->next = n;

  std::unordered_set<int> dataset;
  // Insert the first one, and then the loop keeps trying to insert the next
  // one.
  dataset.insert(n->data);

  while(n->next)
  {
    const auto& p = dataset.insert(n->next->data);
    // If it cannot be inserted, then n->next is in the data
    if(!p.second)
    {
      ListNode* tmp = n->next;

      n->next = n->next->next;
      delete tmp; tmp = nullptr;
    }
    else
    {
      n = n->next;
    }
  }
  return dummy->next;
}

ListNode* removeDupTwoPinter(ListNode* n)
{
  if(n == nullptr)
    return n;

  ListNode* dummy = new ListNode{0};
  dummy->next = n;

  // Use two pointers
  ListNode* slow = n;
  ListNode* fast = n;
  while(slow)
  {
    int data = slow->data;
    while(fast->next)
    {
      if(fast->next->data == data)
      {
        ListNode* tmp = fast->next;
        fast->next = fast->next->next;
        delete tmp; tmp = nullptr;
      }
      else
      {
        fast = fast->next;
      }
    }
    slow = slow->next;
    fast = slow;
  }
  return dummy->next;
}


TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    {
    ListNode* n0 = buildSinglyLinkedList({0,1,2,3,4,5,6});
    vector<int> sol0{0,1,2,3,4,5,6};
    ListNode* res0 = removeDups(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    {
    ListNode* n0 = buildSinglyLinkedList({0,1,1,2,1,3,4,3,3,5,6});
    vector<int> sol0{0,1,2,3,4,5,6};
    ListNode* res0 = removeDups(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    {
    ListNode* n0 = buildSinglyLinkedList({0});
    vector<int> sol0{0};
    ListNode* res0 = removeDups(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    {
    ListNode* n0 = buildSinglyLinkedList({});
    vector<int> sol0{};
    ListNode* res0 = removeDups(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
  }
  SECTION("Sec Testing ")
  {
    {
    ListNode* n0 = buildSinglyLinkedList({0,1,2,3,4,5,6});
    vector<int> sol0{0,1,2,3,4,5,6};
    ListNode* res0 = removeDupTwoPinter(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    {
    ListNode* n0 = buildSinglyLinkedList({0,1,1,2,1,3,4,3,3,5,6});
    vector<int> sol0{0,1,2,3,4,5,6};
    ListNode* res0 = removeDupTwoPinter(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    {
    ListNode* n0 = buildSinglyLinkedList({0});
    vector<int> sol0{0};
    ListNode* res0 = removeDupTwoPinter(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
    {
    ListNode* n0 = buildSinglyLinkedList({});
    vector<int> sol0{};
    ListNode* res0 = removeDupTwoPinter(n0);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
  }
}

//auto main(int argc, char* argv[])->int
//{
//  return 0;
//}















