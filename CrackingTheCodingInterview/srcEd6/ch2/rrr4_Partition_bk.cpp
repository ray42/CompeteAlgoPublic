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


ListNode* partition(ListNode* n, int x)
{
  if(n == nullptr)
    return n;

  ListNode* left_dummy = new ListNode{0};
  ListNode* right_dummy = new ListNode{0};

  ListNode* left_head = left_dummy;
  ListNode* right_head = right_dummy;

  while(n)
  {
    ListNode* curr_n = n;
    n = n->next;
    if(curr_n->data < x)
    {
      left_head->next = curr_n;
      left_head = left_head->next;
    }
    else
    {
      right_head->next = curr_n;
      right_head = right_head->next;
    }
  }
  left_head->next = nullptr;
  right_head->next = nullptr;

  left_head->next = right_dummy->next;

  return left_dummy->next;
}

TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    {
    ListNode* n0 = buildSinglyLinkedList({3,5,8,5,10,2,1});
    vector<int> sol0{3,2,1,5,8,5,10};
    ListNode* res0 = partition(n0,5);
    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
    }
//    {
//    ListNode* n0 = buildSinglyLinkedList({0,1,1,2,1,3,4,3,3,5,6});
//    vector<int> sol0{0,1,2,3,4,5,6};
//    ListNode* res0 = removeDups(n0);
//    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
//    }
//    {
//    ListNode* n0 = buildSinglyLinkedList({0});
//    vector<int> sol0{0};
//    ListNode* res0 = removeDups(n0);
//    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
//    }
//    {
//    ListNode* n0 = buildSinglyLinkedList({});
//    vector<int> sol0{};
//    ListNode* res0 = removeDups(n0);
//    REQUIRE(convertSinglyLinkedListToVec(res0)==sol0);
//    }
  }
}

//auto main(int argc, char* argv[])->int
//{
//  return 0;
//}















