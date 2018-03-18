/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), https://ray42.com
 * Contact: rayaxiom42 AT gmail DOT com
 * License: GNU AGPLv3
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
//2.6: Palindrome: Implement a function to check if a linked list is a 
//     palindrome. 
//
// I would reverse it and check if it's the same. But I only have to check 
// half way, so it'll be useful if I keep track of the numbers of nodes 
// whilst reversing.
//
// But if I have the number of nodes (by precomputing it), I can move two
// pointers to the middle, then have one step backwards and the other step
// forward, checking if they are the same---this means I need a doubly 
// linked list, which may not be possible.
//
// Let's check the solution since I'm short on time.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Hints:
//
// #5: A palindrome is something which is the same when written forwards and
//     backwards. What if you reversed the linked list?
//
// #13: Try using a stack.
//
// #29: Assume you have the length of the linked list. Can you implement
//      this recursively?
//
// #61: In the recursive approach (we have the length of the list), the 
//      middle is the base case: iSPermutation(middle) is true. The node x 
//      to the immediate left of the middle: What can that node do to check 
//      if x->middle->y forms a palindrome? Now suppose that checks out. 
//      What about the previous node a? If x->middle->y is a palindrome, how
//      can it check that a->x->middle->y->b is a palindrome?
//
// #101: Go back to the previous hint. Remember: There are ways to return 
//       multiple values. You can do this with a new class.

// Definition of ListNode is:
//struct ListNode
//{
//  int data;
//  ListNode* next;
//  ListNode* prev;
//  
//  ListNode(int d):data(d),next(nullptr),prev(nullptr)
//  {}
//};

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include "./../rayheader.h"
#include<stack>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here

////////////////////////////////////////////////////////////////////////////
// In this approach, we reverse a copy of the linked list, and compare.
// i.e. slist: 1->2->3->4->1
//      rever: 1->4->3->2->1 , false
//
// i.e. slist: 1->2->3->2->1
//      rever: 1->2->3->2->1 , true
//
// to optimize this, we can return the length (when reversing), that way we 
// only need to compare half the list.

// return a reversed copy of the list
ListNode* reverse_copy(ListNode*);

// compare two linked list for equality
bool is_equal(ListNode*, ListNode*);

// uses the two functions above
bool is_palindrome_reverse(ListNode* l)
{
}

ListNode* reverse_copy(ListNode* l)
{
}

// Return if two linked lists are equal
bool is_equal(ListNode* l1, ListNode* l2)
{
}

//////////////////////////////////////////////////////////////////////////////
//// optimized version, only compare half the linked list

// Reverse and copy the given linked list, and return the size.
ListNode* reverse_copy(ListNode*, int&); // not unit tested, cba.

bool is_xnums_equal(ListNode*, ListNode*, int); // not unit tested, cba.

bool is_palindrome_reverse_opt(ListNode* l)
{
}

ListNode* reverse_copy(ListNode* l, int& x)
{
}

bool is_xnums_equal(ListNode* l1, ListNode* l2, int x)
{
}

////////////////////////////////////////////////////////////////////////////
//// We use a stack, insert half way, then compare the popped out value with
//// the rest of the list. For this version, we pre-compute the size.
int get_size(ListNode* l);

bool is_palindrome_stack_known_size(ListNode* l)
{
}

////////////////////////////////////////////////////////////////////////////
// This version also uses a stack, but we do not pre-calculate the size.
// Instead we use a slow pointer and a fast pointer. This is the runner 
// technique.
bool is_palindrome_stack_two_point(ListNode* l)
{
}

////////////////////////////////////////////////////////////////////////////
//// recursive - I'll read the solution - not done, this is very long.
//// Come back to it later. RRR
//bool is_palindrome_recur(ListNode* l)
//{
//
//}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
SECTION("Sec Testing reverse_copy")
{
  // nullptr test:
  ListNode* l1 = nullptr;
  ListNode* a1 = reverse_copy(l1);
  REQUIRE(a1==nullptr);

  // test one node, so the head and tail are the same node.
  ListNode* l2 = vec_to_slist({3});
  ListNode* a2 = reverse_copy(l2);
  std::vector<int> v2{3};
  REQUIRE(slist_to_vec(a2)==v2);

  // test two nodes - head and tail are separate nodes, but no elements
  // in between
  ListNode* l3 = vec_to_slist({2,3});
  ListNode* a3 = reverse_copy(l3);
  std::vector<int> v3{3,2};
  REQUIRE(slist_to_vec(a3)==v3);

  // test three nodes - head and tail are separate nodes, with one element
  // in betwen
  ListNode* l4 = vec_to_slist({2,3,4});
  ListNode* a4 = reverse_copy(l4);
  std::vector<int> v4{4,3,2};
  REQUIRE(slist_to_vec(a4)==v4);

  // test many nodes.
  ListNode* l5 = vec_to_slist({2,3,4,5,6});
  ListNode* a5 = reverse_copy(l5);
  std::vector<int> v5{6,5,4,3,2};
  REQUIRE(slist_to_vec(a5)==v5);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
SECTION("Sec Testing is_equal")
{
  // nullptr test:
  ListNode* l11 = nullptr;
  ListNode* l12 = nullptr;
  REQUIRE(is_equal(l11,l12)==true);

  // one null
  ListNode* l21 = nullptr;
  ListNode* l22 = vec_to_slist({3});
  REQUIRE(is_equal(l21,l22)==false);

  // one null, l1 and l2 swapped
  ListNode* l31 = nullptr;
  ListNode* l32 = vec_to_slist({3});
  REQUIRE(is_equal(l32,l31)==false);

  // one null - compared with 2 node list
  ListNode* l41 = nullptr;
  ListNode* l42 = vec_to_slist({3,2});
  REQUIRE(is_equal(l41,l42)==false);

  // one null, l1 and l2 swapped
  ListNode* l51 = nullptr;
  ListNode* l52 = vec_to_slist({3,2});
  REQUIRE(is_equal(l52,l51)==false);

  // many node equal
  ListNode* l61 = vec_to_slist({1,2,3,4,5});
  ListNode* l62 = vec_to_slist({1,2,3,4,5});
  REQUIRE(is_equal(l61,l62)==true);

  // many node not equal
  ListNode* l71 = vec_to_slist({11,22,33,44,55});
  ListNode* l72 = vec_to_slist({1,2,3,4,5});
  REQUIRE(is_equal(l71,l72)==false);

  // many node not equal, unequal length
  ListNode* l81 = vec_to_slist({1,2,3,4,5});
  ListNode* l82 = vec_to_slist({1,2,3,4,5,6,7,8});
  REQUIRE(is_equal(l81,l82)==false);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
SECTION("Sec Testing is_palindrome_reverse")
{
  // 1 - nullptr, true
  ListNode* l1 = nullptr;
  REQUIRE(is_palindrome_reverse(l1)==true);

  // 2 - 1 node, true
  ListNode* l2 = vec_to_slist({3});
  REQUIRE(is_palindrome_reverse(l2)==true);

  // 3.1 - 2 node, false
  ListNode* l31 = vec_to_slist({3,42});
  REQUIRE(is_palindrome_reverse(l31)==false);

  // 3.2 - 2 node, true
  ListNode* l32 = vec_to_slist({3,3});
  REQUIRE(is_palindrome_reverse(l32)==true);

  // 4.1 - 3 node, false
  ListNode* l41 = vec_to_slist({1,2,3});
  REQUIRE(is_palindrome_reverse(l41)==false);

  // 4.2 - 3 node, true
  ListNode* l42 = vec_to_slist({1,2,1});
  REQUIRE(is_palindrome_reverse(l42)==true);

  // 5.1 - 4 node, false
  ListNode* l51 = vec_to_slist({1,2,3,1});
  REQUIRE(is_palindrome_reverse(l51)==false);

  // 5.2 - 4 node, true
  ListNode* l52 = vec_to_slist({1,2,2,1});
  REQUIRE(is_palindrome_reverse(l52)==true);

  // 6.1 - 5 node, false
  ListNode* l61 = vec_to_slist({1,2,3,1,1});
  REQUIRE(is_palindrome_reverse(l61)==false);

  // 6.2 - 5 node, true
  ListNode* l62 = vec_to_slist({1,2,3,2,1});
  REQUIRE(is_palindrome_reverse(l62)==true);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
SECTION("Sec Testing is_palindrome_reverse_opt")
{
  // 1 - nullptr, true
  ListNode* l1 = nullptr;
  REQUIRE(is_palindrome_reverse_opt(l1)==true);

  // 2 - 1 node, true
  ListNode* l2 = vec_to_slist({3});
  REQUIRE(is_palindrome_reverse_opt(l2)==true);

  // 3.1 - 2 node, false
  ListNode* l31 = vec_to_slist({3,42});
  REQUIRE(is_palindrome_reverse_opt(l31)==false);

  // 3.2 - 2 node, true
  ListNode* l32 = vec_to_slist({3,3});
  REQUIRE(is_palindrome_reverse_opt(l32)==true);

  // 4.1 - 3 node, false
  ListNode* l41 = vec_to_slist({1,2,3});
  REQUIRE(is_palindrome_reverse_opt(l41)==false);

  // 4.2 - 3 node, true
  ListNode* l42 = vec_to_slist({1,2,1});
  REQUIRE(is_palindrome_reverse_opt(l42)==true);

  // 5.1 - 4 node, false
  ListNode* l51 = vec_to_slist({1,2,3,1});
  REQUIRE(is_palindrome_reverse_opt(l51)==false);

  // 5.2 - 4 node, true
  ListNode* l52 = vec_to_slist({1,2,2,1});
  REQUIRE(is_palindrome_reverse_opt(l52)==true);

  // 6.1 - 5 node, false
  ListNode* l61 = vec_to_slist({1,2,3,1,1});
  REQUIRE(is_palindrome_reverse_opt(l61)==false);

  // 6.2 - 5 node, true
  ListNode* l62 = vec_to_slist({1,2,3,2,1});
  REQUIRE(is_palindrome_reverse_opt(l62)==true);
}
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
SECTION("Sec Testing is_palindrome_stack_known_size")
{
  // 1 - nullptr, true
  ListNode* l1 = nullptr;
  REQUIRE(is_palindrome_stack_known_size(l1)==true);

  // 2 - 1 node, true
  ListNode* l2 = vec_to_slist({3});
  REQUIRE(is_palindrome_stack_known_size(l2)==true);

  // 3.1 - 2 node, false
  ListNode* l31 = vec_to_slist({3,42});
  REQUIRE(is_palindrome_stack_known_size(l31)==false);

  // 3.2 - 2 node, true
  ListNode* l32 = vec_to_slist({3,3});
  REQUIRE(is_palindrome_stack_known_size(l32)==true);

  // 4.1 - 3 node, false
  ListNode* l41 = vec_to_slist({1,2,3});
  REQUIRE(is_palindrome_stack_known_size(l41)==false);

  // 4.2 - 3 node, true
  ListNode* l42 = vec_to_slist({1,2,1});
  REQUIRE(is_palindrome_stack_known_size(l42)==true);

  // 5.1 - 4 node, false
  ListNode* l51 = vec_to_slist({1,2,3,1});
  REQUIRE(is_palindrome_stack_known_size(l51)==false);

  // 5.2 - 4 node, true
  ListNode* l52 = vec_to_slist({1,2,2,1});
  REQUIRE(is_palindrome_stack_known_size(l52)==true);

  // 6.1 - 5 node, false
  ListNode* l61 = vec_to_slist({1,2,3,1,1});
  REQUIRE(is_palindrome_stack_known_size(l61)==false);

  // 6.2 - 5 node, true
  ListNode* l62 = vec_to_slist({1,2,3,2,1});
  REQUIRE(is_palindrome_stack_known_size(l62)==true);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
SECTION("Sec Testing is_palindrome_stack_two_point")
{
  // 1 - nullptr, true
  ListNode* l1 = nullptr;
  REQUIRE(is_palindrome_stack_two_point(l1)==true);

  // 2 - 1 node, true
  ListNode* l2 = vec_to_slist({3});
  REQUIRE(is_palindrome_stack_two_point(l2)==true);

  // 3.1 - 2 node, false
  ListNode* l31 = vec_to_slist({3,42});
  REQUIRE(is_palindrome_stack_two_point(l31)==false);

  // 3.2 - 2 node, true
  ListNode* l32 = vec_to_slist({3,3});
  REQUIRE(is_palindrome_stack_two_point(l32)==true);

  // 4.1 - 3 node, false
  ListNode* l41 = vec_to_slist({1,2,3});
  REQUIRE(is_palindrome_stack_two_point(l41)==false);

  // 4.2 - 3 node, true
  ListNode* l42 = vec_to_slist({1,2,1});
  REQUIRE(is_palindrome_stack_two_point(l42)==true);

  // 5.1 - 4 node, false
  ListNode* l51 = vec_to_slist({1,2,3,1});
  REQUIRE(is_palindrome_stack_two_point(l51)==false);

  // 5.2 - 4 node, true
  ListNode* l52 = vec_to_slist({1,2,2,1});
  REQUIRE(is_palindrome_stack_two_point(l52)==true);

  // 6.1 - 5 node, false
  ListNode* l61 = vec_to_slist({1,2,3,1,1});
  REQUIRE(is_palindrome_stack_two_point(l61)==false);

  // 6.2 - 5 node, true
  ListNode* l62 = vec_to_slist({1,2,3,2,1});
  REQUIRE(is_palindrome_stack_two_point(l62)==true);
}

// The below is not done.
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// This is not done.
//SECTION("Sec Testing is_palindrome_recur")
//{
//  // 1 - nullptr, true
//  ListNode* l1 = nullptr;
//  REQUIRE(is_palindrome_recur(l1)==true);
//
//  // 2 - 1 node, true
//  ListNode* l2 = vec_to_slist({3});
//  REQUIRE(is_palindrome_recur(l2)==true);
//
//  // 3.1 - 2 node, false
//  ListNode* l31 = vec_to_slist({3,42});
//  REQUIRE(is_palindrome_recur(l31)==false);
//
//  // 3.2 - 2 node, true
//  ListNode* l32 = vec_to_slist({3,3});
//  REQUIRE(is_palindrome_recur(l32)==true);
//
//  // 4.1 - 3 node, false
//  ListNode* l41 = vec_to_slist({1,2,3});
//  REQUIRE(is_palindrome_recur(l41)==false);
//
//  // 4.2 - 3 node, true
//  ListNode* l42 = vec_to_slist({1,2,1});
//  REQUIRE(is_palindrome_recur(l42)==true);
//
//  // 5.1 - 4 node, false
//  ListNode* l51 = vec_to_slist({1,2,3,1});
//  REQUIRE(is_palindrome_recur(l51)==false);
//
//  // 5.2 - 4 node, true
//  ListNode* l52 = vec_to_slist({1,2,2,1});
//  REQUIRE(is_palindrome_recur(l52)==true);
//
//  // 6.1 - 5 node, false
//  ListNode* l61 = vec_to_slist({1,2,3,1,1});
//  REQUIRE(is_palindrome_recur(l61)==false);
//
//  // 6.2 - 5 node, true
//  ListNode* l62 = vec_to_slist({1,2,3,2,1});
//  REQUIRE(is_palindrome_recur(l62)==true);
//}



} // end testcase

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

