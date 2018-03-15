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
// 2.4: Partition: Write code to partition a linked list around a value x,
//      such that all nodes less than $x$ come before all nodes greater than
//      or equal to $x$. If $x$ is contained within the list, the values of 
//      x only need to be after the elements less than x (see below). The 
//      partition element x can appear anywhere in the ``right partition'';
//      it does not need to appear between the left and right partitions.
//
// EXAMPLE:}
//Input: 3->5->8-> 5 ->10->2->1 [partition = 5]
//Output:3->1->2->10->5 ->5->8

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
ListNode* partition(ListNode* head, int x)
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

