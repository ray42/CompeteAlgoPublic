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

ListNode* sum(ListNode* l1, ListNode* l2)
{
  if(l1==nullptr && l2==nullptr)
  {
    return nullptr;
  }

  ListNode* dummy = new ListNode{0};
  ListNode* head = dummy;
  int carry = 0;

  while(l1 && l2)
  {
    int sum = l1->data + l2->data + carry;
    head->next = new ListNode{sum%10};
    carry =sum/10;
    l1 = l1->next;
    l2 = l2->next;
    head = head->next;
  }
  // Find out which list we have left to deal with.
  l1 = (l1==nullptr) ? l2:l1;
  // Carry on adding
  while(l1)
  {
    int sum = l1->data + carry;
    head->next = new ListNode{sum%10};
    carry = sum/10;
    l1 = l1->next;
    head = head->next;
  }
  // Check if array is 1 for the last entry
  if(carry>0)
    head->next = new ListNode{1};

  return dummy->next;
}

ListNode* reverse(ListNode* l1)
{
  if(l1==nullptr)
    return l1;

  ListNode* prev = nullptr;
  ListNode* curr = l1;
  while(curr)
  {
    // Store the next node so we can set it as curr.
    ListNode* next = curr->next;
    curr->next = prev;
    // Update prev and curr.
    prev = curr;
    curr = next;
  }
  return prev;
}

ListNode* sum_reverse(ListNode* l1, ListNode* l2)
{
  return reverse(sum(reverse(l1),reverse(l2)));
}

TEST_CASE("Testing ", "[]" )
{
  SECTION("Sec Testing ")
  {
    // test1
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({7,1,6});
    ListNode* l2 = buildSinglyLinkedList({5,9,2});
    // Solution
    vector<int> sol{2,1,9};
    // Output
    ListNode* out = sum(l1,l2);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test2 - reverse of test1
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({7,1,6});
    ListNode* l2 = buildSinglyLinkedList({5,9,2});
    // Solution
    vector<int> sol{2,1,9};
    // Output
    ListNode* out = sum(l2,l1);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }

    // test3 - with remainder.
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({9,7,8});
    ListNode* l2 = buildSinglyLinkedList({6,8,5});
    // Solution
    vector<int> sol{5,6,4,1};
    // Output
    ListNode* out = sum(l1,l2);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test4 - reverse of test3
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({9,7,8});
    ListNode* l2 = buildSinglyLinkedList({6,8,5});
    // Solution
    vector<int> sol{5,6,4,1};
    // Output
    ListNode* out = sum(l2,l1);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test5 - unequal lengths
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({9,7,8,8,8,9});
    ListNode* l2 = buildSinglyLinkedList({6,8,5});
    // Solution
    vector<int> sol{5,6,4,9,8,9};
    // Output
    ListNode* out = sum(l1,l2);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test6 - reversed
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({9,7,8,8,8,9});
    ListNode* l2 = buildSinglyLinkedList({6,8,5});
    // Solution
    vector<int> sol{5,6,4,9,8,9};
    // Output
    ListNode* out = sum(l2,l1);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
  }
  SECTION("Sec Testing Reverse")
  {
    // test1
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({0,1,2});
    // Solution
    vector<int> sol{2,1,0};
    // Output
    ListNode* out = reverse(l1);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
  }
  SECTION("Sec Testing ")
  {
    // test1
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({6,1,7});
    ListNode* l2 = buildSinglyLinkedList({2,9,5});
    // Solution
    vector<int> sol{9,1,2};
    // Output
    ListNode* out = sum_reverse(l1,l2);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test2 - reverse of test1
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({6,1,7});
    ListNode* l2 = buildSinglyLinkedList({2,9,5});
    // Solution
    vector<int> sol{9,1,2};
    // Output
    ListNode* out = sum_reverse(l2,l1);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }

    // test3 - with remainder.
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({8,7,9});
    ListNode* l2 = buildSinglyLinkedList({5,8,6});
    // Solution
    vector<int> sol{1,4,6,5};
    // Output
    ListNode* out = sum_reverse(l1,l2);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test4 - reverse of test3
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({8,7,9});
    ListNode* l2 = buildSinglyLinkedList({5,8,6});
    // Solution
    vector<int> sol{1,4,6,5};
    // Output
    ListNode* out = sum_reverse(l2,l1);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test5 - unequal lengths
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({9,8,8,8,7,9});
    ListNode* l2 = buildSinglyLinkedList({5,8,6});
    // Solution
    vector<int> sol{9,8,9,4,6,5};
    // Output
    ListNode* out = sum_reverse(l1,l2);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
    // test6 - reversed
    {
    // Input
    ListNode* l1 = buildSinglyLinkedList({9,8,8,8,7,9});
    ListNode* l2 = buildSinglyLinkedList({5,8,6});
    // Solution
    vector<int> sol{9,8,9,4,6,5};
    // Output
    ListNode* out = sum_reverse(l2,l1);
    // Test
    REQUIRE(convertSinglyLinkedListToVec(out)==sol);
    }
  }

}

//auto main(int argc, char* argv[])->int
//{
//  return 0;
//}















