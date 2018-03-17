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
// 2.5: Sum Lists: You have two numbers represented by a linked list, where
//      each node contains a single digit. The digits are stored in reverse
//      order, such that the $1$'s digit is at the head of the list. Write a
//      function that adds the two numbers and returns the sum as a linked 
//      list.
//
// EXAMPLE
// Input: (7->1->6) + (5->9->2). That is, 617 + 295.
// Output: 2->1->9. That is, 912.
//
// FOLLOW UP
// Suppose the digits are stored in forward order. Repeat the above problem.
//
// EXAMPLE
// Input: (6->1->7) + (2->9->5) . That is, 617 + 295.
// Output: 9->1->2. That is, 912.
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Hints:
//
// #7: Of course, you could convert the linked lists to integers, compute 
//     the sum, and then convert it back to a new linked list. If you did
//     this in an interview, your interviewer would likely accept the 
//     answer, and then see if you could do this without converting it to a
//     number and back.
// #30: Try recursion. Suppose you have two lists, A=1->5->9 (representing 
//      951) and B=2->3->6->7 (representing 7632), and a function that 
//      operates on the remainder of the lists (5->9 and 3->6->7). Could you
//      use this to create the sum method? What is the relationship between 
//      sum(1->5->9, 2->3->6->7) and sum(5->9,3->6->7)?
// #71: Make sure you have considered linked lists that are not the same
//      length.
// #95: Does your algorithm work on linked lists like 9->7->8 and 6->8->5? 
//      Double check that.
// #109: For the follow-up question: The issue is that when the linked lists
//       aren't the same length, the head of one linked list might represent
//       the 1000's place while the other represents the 10's place. What if
//       you made them the same length? Is there a way to modify the linked
//       list to do that, without changing the value it represents?
//
// Okay, did all of these, except recursive approach.

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// #include here
#include "./../rayheader.h"
#include<unordered_set>
#include<memory>
#include<vector>

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Implementation here

////////////////////////////////////////////////////////////////////////////
// We convert to int, then add, then convert back.
//
// Recall that the lists represent numbers in reverse numbers:
// e.g. the number 425 is represented as 5->2->4

// Given a list l which represents the numbers, convert it to an int.
// I.e. if l = 4->2->5, representing 524, then it returns 524.
// NOTE: nullptr will be converted to 0.
int list_to_int(ListNode* l)
{
}

// Convert an int to singly linked list, in reverse order, that is, input 
// 524 returns 4->2->5
// NOTE: 0 will be converted to a node with data 0, NOT a nullptr
ListNode* int_to_list(int x)
{
}

////////////////////////////////////////////////////////////////////////////
// Adds two linked lists (which are in reverse order) by first converting to
// int, adding, then converting back to linked list. E.g.:
//  7->1->6    617
// +5->9->2   +295
// =2->1->9   =912
ListNode* sum_convert_int(ListNode* l1, ListNode* l2)
{
}

////////////////////////////////////////////////////////////////////////////
// Adds two linked lists (which are in reverse order):
//  7->1->6    617
// +5->9->2   +295
// =2->1->9   =912
//
// By iterating through both linked lists.
ListNode* sum_iter(ListNode* l1, ListNode* l2)
{
}

////////////////////////////////////////////////////////////////////////////
// Adds two linked lists (which are in reverse order):
//  7->1->6    617
// +5->9->2   +295
// =2->1->9   =912
//
// By using recursion
ListNode* sum_recur_helper(ListNode* l1, ListNode* l2, int carry);
ListNode* sum_recur_helper(ListNode* l1, int carry);

ListNode* sum_recur(ListNode* l1, ListNode* l2)
{
}

// helper for a single list
ListNode* sum_recur_helper(ListNode* l, int carry)
{
}

////////////////////////////////////////////////////////////////////////////
// Reverse a linked list iteratively.
ListNode* reverse(ListNode* l)
{
}

////////////////////////////////////////////////////////////////////////////
// This works with the mode significant digits on the left, so that
// adding two linked lists means:
//  6->1->7    617
// +2->9->5   +295
// =9->1->2   =912
ListNode* sum_reverse(ListNode* l1, ListNode* l2)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing ", "[]" )
{
  // Recall that the linked lists are in reverse order, i.e.
  //  7->1->6    617
  // +5->9->2   +295
  // =2->1->9   =912
  SECTION("Sec Testing sum_convert_int")
  {
  { // testing list_to_int
    ListNode* l1 = nullptr;
    REQUIRE(list_to_int(l1)==0);

    ListNode* l2 = vec_to_slist({2,4,3,5}); // number 5342
    REQUIRE(list_to_int(l2)==5342);
  }
  { // testing int_to_list
    ListNode* l1 = int_to_list(0);
    std::vector<int> v1{0};
    REQUIRE(v1==slist_to_vec(l1));

    ListNode* l2 = int_to_list(5342);
    std::vector<int> v2{2,4,3,5};
    REQUIRE(v2==slist_to_vec(l2));
  }
  {//1.1 Edge case: two nullptr, should return nullptr
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    
    // not needed for this edge case
    //vector<int> resvec = slist_to_vec(res); 

    // Correct solution
    // vector<int> vecsol // This is not needed for nullptr
    REQUIRE(res==nullptr);
  }
  {//1.2 Edge case: left nullptr, right is unit.
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({3}); // 3

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.3 Edge case: left nullptr, right is has two numbers: 42
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({2,4}); // 42

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,4};
    REQUIRE(resvec==solvec);
  }
  {//1.4 Edge case: left unit, right is nullptr.
    // Inputs
    ListNode* l1 = vec_to_slist({3}); // 3
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.5 Edge case: left has two numbers, 42. Right is nullptr
    // Inputs
    ListNode* l1 = vec_to_slist({2,4}); // 42
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,4};
    REQUIRE(resvec==solvec);
  }
  {//2.1 Normal addition: 617+295=912
    // Inputs
    ListNode* l1 = vec_to_slist({7,1,6}); // 617
    ListNode* l2 = vec_to_slist({5,9,2}); // 295

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,1,9};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//2.2 Normal addition (swap l1 and l2): 295+617=912
    // Inputs
    ListNode* l1 = vec_to_slist({7,1,6}); // 617
    ListNode* l2 = vec_to_slist({5,9,2}); // 295

    // run program
    ListNode* res = sum_convert_int(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,1,9};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//3.1 solution has remainder: 879+586=1465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8}); // 879
    ListNode* l2 = vec_to_slist({6,8,5}); // 586

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,1};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//3.2 Normal addition (swap l1 and l2): 586+879=1465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8}); // 879
    ListNode* l2 = vec_to_slist({6,8,5}); // 586

    // run program
    ListNode* res = sum_convert_int(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,1};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//4.1 Unequal lengths: 988879+586=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8,8,8,9}); // 988879
    ListNode* l2 = vec_to_slist({6,8,5});       // 586

    // run program
    ListNode* res = sum_convert_int(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,9,8,9};                     // 989465
    REQUIRE(resvec==solvec);
  }
  {//4.2 Unequal (swap l1 and l2): 586+988879=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8,8,8,9}); // 988879
    ListNode* l2 = vec_to_slist({6,8,5});       // 586

    // run program
    ListNode* res = sum_convert_int(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,9,8,9};                     // 989465
    REQUIRE(resvec==solvec);
  }
  }
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  SECTION("Sec Testing sum_iter")
  {
  {//1.1 Edge case: two nullptr, should return nullptr
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_iter(l1,l2);
    
    // not needed for this edge case
    //vector<int> resvec = slist_to_vec(res); 

    // Correct solution
    // vector<int> vecsol // This is not needed for nullptr
    REQUIRE(res==nullptr);
  }
  {//1.2 Edge case: left nullptr, right is unit.
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({3}); // 3

    // run program
    ListNode* res = sum_iter(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.3 Edge case: left nullptr, right is has two numbers: 42
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({2,4}); // 42

    // run program
    ListNode* res = sum_iter(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,4};
    REQUIRE(resvec==solvec);
  }
  {//1.4 Edge case: left unit, right is nullptr.
    // Inputs
    ListNode* l1 = vec_to_slist({3}); // 3
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_iter(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.5 Edge case: left has two numbers, 42. Right is nullptr
    // Inputs
    ListNode* l1 = vec_to_slist({2,4}); // 42
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_iter(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,4};
    REQUIRE(resvec==solvec);
  }
  {//2.1 Normal addition: 617+295=912
    // Inputs
    ListNode* l1 = vec_to_slist({7,1,6}); // 617
    ListNode* l2 = vec_to_slist({5,9,2}); // 295

    // run program
    ListNode* res = sum_iter(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,1,9};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//2.2 Normal addition (swap l1 and l2): 295+617=912
    // Inputs
    ListNode* l1 = vec_to_slist({7,1,6}); // 617
    ListNode* l2 = vec_to_slist({5,9,2}); // 295

    // run program
    ListNode* res = sum_iter(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,1,9};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//3.1 solution has remainder: 879+586=1465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8}); // 879
    ListNode* l2 = vec_to_slist({6,8,5}); // 586

    // run program
    ListNode* res = sum_iter(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,1};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//3.2 Normal addition (swap l1 and l2): 586+879=1465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8}); // 879
    ListNode* l2 = vec_to_slist({6,8,5}); // 586

    // run program
    ListNode* res = sum_iter(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,1};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//4.1 Unequal lengths: 988879+586=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8,8,8,9}); // 988879
    ListNode* l2 = vec_to_slist({6,8,5});       // 586

    // run program
    ListNode* res = sum_iter(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,9,8,9};                     // 989465
    REQUIRE(resvec==solvec);
  }
  {//4.2 Unequal (swap l1 and l2): 586+988879=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8,8,8,9}); // 988879
    ListNode* l2 = vec_to_slist({6,8,5});       // 586

    // run program
    ListNode* res = sum_iter(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,9,8,9};                     // 989465
    REQUIRE(resvec==solvec);
  }
  }
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  SECTION("Sec Testing sum_recur")
  {
  {//1.1 Edge case: two nullptr, should return nullptr
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_recur(l1,l2);
    
    // not needed for this edge case
    //vector<int> resvec = slist_to_vec(res); 

    // Correct solution
    // vector<int> vecsol // This is not needed for nullptr
    REQUIRE(res==nullptr);
  }
  {//1.2 Edge case: left nullptr, right is unit.
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({3}); // 3

    // run program
    ListNode* res = sum_recur(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.3 Edge case: left nullptr, right is has two numbers: 42
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({2,4}); // 42

    // run program
    ListNode* res = sum_recur(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,4};
    REQUIRE(resvec==solvec);
  }
  {//1.4 Edge case: left unit, right is nullptr.
    // Inputs
    ListNode* l1 = vec_to_slist({3}); // 3
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_recur(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.5 Edge case: left has two numbers, 42. Right is nullptr
    // Inputs
    ListNode* l1 = vec_to_slist({2,4}); // 42
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_recur(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,4};
    REQUIRE(resvec==solvec);
  }
  {//2.1 Normal addition: 617+295=912
    // Inputs
    ListNode* l1 = vec_to_slist({7,1,6}); // 617
    ListNode* l2 = vec_to_slist({5,9,2}); // 295

    // run program
    ListNode* res = sum_recur(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,1,9};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//2.2 Normal addition (swap l1 and l2): 295+617=912
    // Inputs
    ListNode* l1 = vec_to_slist({7,1,6}); // 617
    ListNode* l2 = vec_to_slist({5,9,2}); // 295

    // run program
    ListNode* res = sum_recur(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{2,1,9};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//3.1 solution has remainder: 879+586=1465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8}); // 879
    ListNode* l2 = vec_to_slist({6,8,5}); // 586

    // run program
    ListNode* res = sum_recur(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,1};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//3.2 Normal addition (swap l1 and l2): 586+879=1465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8}); // 879
    ListNode* l2 = vec_to_slist({6,8,5}); // 586

    // run program
    ListNode* res = sum_recur(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,1};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//4.1 Unequal lengths: 988879+586=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8,8,8,9}); // 988879
    ListNode* l2 = vec_to_slist({6,8,5});       // 586

    // run program
    ListNode* res = sum_recur(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,9,8,9};                     // 989465
    REQUIRE(resvec==solvec);
  }
  {//4.2 Unequal (swap l1 and l2): 586+988879=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,7,8,8,8,9}); // 988879
    ListNode* l2 = vec_to_slist({6,8,5});       // 586

    // run program
    ListNode* res = sum_recur(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{5,6,4,9,8,9};                     // 989465
    REQUIRE(resvec==solvec);
  }
  }

  //////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  SECTION("Sec Testing sum_reverse")
  {
  {// testing reverse helper function. It just reverses a linked list.
    // nullptr test:
    ListNode* l1 = nullptr;
    ListNode* a1 = reverse(l1);
    REQUIRE(a1==nullptr);

    // test one node
    ListNode* l2 = vec_to_slist({3});
    ListNode* a2 = reverse(l2);
    std::vector<int> v2{3};
    REQUIRE(slist_to_vec(a2)==v2);

    // test two nodes
    ListNode* l3 = vec_to_slist({2,3});
    ListNode* a3 = reverse(l3);
    std::vector<int> v3{3,2};
    REQUIRE(slist_to_vec(a3)==v3);

    // test three nodes
    ListNode* l4 = vec_to_slist({2,3,4});
    ListNode* a4 = reverse(l4);
    std::vector<int> v4{4,3,2};
    REQUIRE(slist_to_vec(a4)==v4);

    // test many nodes
    ListNode* l5 = vec_to_slist({2,3,4,5,6});
    ListNode* a5 = reverse(l5);
    std::vector<int> v5{6,5,4,3,2};
    REQUIRE(slist_to_vec(a5)==v5);
  }
  /////////////////////////////////////////////////////////////////////////  
  {//1.1 Edge case: two nullptr, should return nullptr
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_reverse(l1,l2);
    
    // not needed for this edge case
    //vector<int> resvec = slist_to_vec(res); 

    // Correct solution
    // vector<int> vecsol // This is not needed for nullptr
    REQUIRE(res==nullptr);
  }
  {//1.2 Edge case: left nullptr, right is unit.
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({3}); // 3

    // run program
    ListNode* res = sum_reverse(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.3 Edge case: left nullptr, right is has two numbers: 42
    // Inputs
    ListNode* l1 = nullptr;
    ListNode* l2 = vec_to_slist({4,2}); // 42

    // run program
    ListNode* res = sum_reverse(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{4,2};
    REQUIRE(resvec==solvec);
  }
  {//1.4 Edge case: left unit, right is nullptr.
    // Inputs
    ListNode* l1 = vec_to_slist({3}); // 3
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_reverse(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{3};
    REQUIRE(resvec==solvec);
  }
  {//1.5 Edge case: left has two numbers, 42. Right is nullptr
    // Inputs
    ListNode* l1 = vec_to_slist({4,2}); // 42
    ListNode* l2 = nullptr;

    // run program
    ListNode* res = sum_reverse(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{4,2};
    REQUIRE(resvec==solvec);
  }
  {//2.1 Normal addition: 617+295=912
    // Inputs
    ListNode* l1 = vec_to_slist({6,1,7}); // 617
    ListNode* l2 = vec_to_slist({2,9,5}); // 295

    // run program
    ListNode* res = sum_reverse(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{9,1,2};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//2.2 Normal addition (swap l1 and l2): 295+617=912
    // Inputs
    ListNode* l1 = vec_to_slist({6,1,7}); // 617
    ListNode* l2 = vec_to_slist({2,9,5}); // 295

    // run program
    ListNode* res = sum_reverse(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{9,1,2};                     // 912
    REQUIRE(resvec==solvec);
  }
  {//3.1 solution has remainder: 879+586=1465
    // Inputs
    ListNode* l1 = vec_to_slist({8,7,9}); // 879
    ListNode* l2 = vec_to_slist({5,8,6}); // 586

    // run program
    ListNode* res = sum_reverse(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{1,4,6,5};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//3.2 Normal addition (swap l1 and l2): 586+879=1465
    // Inputs
    ListNode* l1 = vec_to_slist({8,7,9}); // 879
    ListNode* l2 = vec_to_slist({5,8,6}); // 586

    // run program
    ListNode* res = sum_reverse(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{1,4,6,5};                   // 1465
    REQUIRE(resvec==solvec);
  }
  {//4.1 Unequal lengths: 988879+586=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,8,8,8,7,9}); // 988879
    ListNode* l2 = vec_to_slist({5,8,6});       // 586

    // run program
    ListNode* res = sum_reverse(l1,l2);
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{9,8,9,4,6,5};                     // 989465
    REQUIRE(resvec==solvec);
  }
  {//4.2 Unequal (swap l1 and l2): 586+988879=989465
    // Inputs
    ListNode* l1 = vec_to_slist({9,8,8,8,7,9}); // 988879
    ListNode* l2 = vec_to_slist({5,8,6});       // 586

    // run program
    ListNode* res = sum_reverse(l2,l1);        // swapped
    std::vector<int> resvec = slist_to_vec(res);//for testing

    // Correct solution
    std::vector<int> solvec{9,8,9,4,6,5};                     // 989465
    REQUIRE(resvec==solvec);
  }
  }

}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}






















































