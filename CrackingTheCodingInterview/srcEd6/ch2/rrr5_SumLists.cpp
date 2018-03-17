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
  int res = 0;
  int pow_ten = 1; // power of ten, starts with 10^0 = 1
  while(l)
  {
    // Add to res
    res+=l->data * pow_ten;
    
    l = l->next;  // advance l
    pow_ten *= 10;// next power of 10
  }
  return res;
}

// Convert an int to singly linked list, in reverse order, that is, input 
// 524 returns 4->2->5
// NOTE: 0 will be converted to a node with data 0, NOT a nullptr
ListNode* int_to_list(int x)
{
  // The below algorithm will return a nullptr if x is 0, so let's handle
  // this edge case.
  if(x==0)
    return new ListNode{0};

  // Because the following algorithm repeatedly gets the lowest part (the 
  // least significant part) of the number x, we extract the units first,
  // then tens, then hundreds, etc...
  //
  // So we need to repeatedly add to the END of the linked list, so that 
  // the units appear first. i.e. for 524, after two iterations, we have
  // 4->2, and we need to be positioned at 2, to be able to attach 5 at the 
  // end.
  //
  // This has the problem that we've lost the head, and we need this to
  // return the ListNode*. Thus, we use a dummy head.
  std::unique_ptr<ListNode> dummy_head = std::make_unique<ListNode>(0);
  
  // This is used to advance through the linked list
  ListNode* node = dummy_head.get();

  while(x)
  {
    // Get the least significant digit
    int node_data = x%10;

    // Create the new node and attach.
    node->next = new ListNode{node_data};

    // Advance node and move x one place to the right (divide by 10) to get
    // rid of the least significant digit
    node = node->next;
    x /= 10;
  }

  // Now return from dummy pointer
  return dummy_head->next;
}

////////////////////////////////////////////////////////////////////////////
// Adds two linked lists (which are in reverse order) by first converting to
// int, adding, then converting back to linked list. E.g.:
//  7->1->6    617
// +5->9->2   +295
// =2->1->9   =912
ListNode* sum_convert_int(ListNode* l1, ListNode* l2)
{
  // First check if they're both nullptr, if so, just return nullptr
  if(l1==nullptr && l2==nullptr) return nullptr;

  // At least one is not nullptr. Convert both to integers.
  int n1 = list_to_int(l1);
  int n2 = list_to_int(l2);

  // Add the numbers
  int res = n1+n2;

  return int_to_list(res);
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
  // Edge case, if both l1 and l2 are nullptr, we simply return a nullptr
  if(l1==nullptr && l2==nullptr) return nullptr;
  
  // I have decided to create a new linked list. I *could* use one of the
  // inputs as the output, but I cba.
  // Again, here we need a dummy_head, so we can return dummy_head->next, 
  // this is because when we're attaching a linked list, we go along it, 
  // losing track of the head.
  std::unique_ptr<ListNode> dummy = std::make_unique<ListNode>(0);
  // we use this to go along the linked list
  ListNode* node = dummy.get();

  // The carry-over
  int carry = 0; // initially there is no carry.

  while(l1 && l2)
  {
    // calculate the sum
    int sum = l1->data + l2->data + carry;

    // sum may be double digits, the maximum would be 9+9+1 (1 being the 
    // carry), which is 19. First we extract the 9 and put it in this place
    // value:

    // The modulo 10 of the sum to get the digit in the current place value.
    node->next = new ListNode{sum%10};

    // Now we calculate the next carry, if sum is over or equal to 10, it's
    // 1, otherwise it's 0. We can do this:
    carry = sum/10;

    // Now we move l1, l2 and node
    l1 = l1->next;
    l2 = l2->next;
    node = node->next;
  }

  // When we get out here, it means either one or both of l1 and l2 are 
  // nullptr. We find out which one and store it in l1.
  l1 = (l1==nullptr) ? l2:l1;

  // Carry may still be 1, and if the value (data) in l1 is 9, we'll have a 
  // sum of 10, and thus we'll have a carry of 1 again, thus we need to keep
  // the carry.
  while(l1)
  {
    int sum = l1->data + carry;

    node->next = new ListNode{sum%10};
    carry = sum/10;

    l1 = l1->next;
    node = node->next;
  }

  // if we still have a carry left over, we put it on at the end.
  if(carry)
  {
    node->next = new ListNode{carry};
  }
  
  return dummy->next;
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
  // Check if both are null
  if(l1==nullptr && l2==nullptr) return nullptr;

  // Now, at least one is not null, we call the recursive function with a
  // carry of 0.
  return sum_recur_helper(l1,l2,0);
}

ListNode* sum_recur_helper(ListNode* l1, ListNode* l2, int carry)
{
  // Base case: check if both l1 and l2 are nullptr
  if(l1==nullptr && l2==nullptr)
  {
    // if the carry is 0, return a nullptr, otherwise, return a new node
    // with value (data) of carry (which will be 1)
    if(carry)
    {
      return new ListNode{carry};
    }
    else
    {
      return nullptr;
    }
  }

  // Now, at least one of l1 or l2 (or both) is not null,
  if(l1 != nullptr && l2 != nullptr)
  {
    // Calculate the sum and carry of this value place.
    int sum = l1->data + l2->data + carry;
    
    // new carry is sum/10 (since we want the next value place up)
    int new_carry = sum/10;

    ListNode* next_node = sum_recur_helper(l1->next, l2->next,new_carry);

    // Create new node for this place value.
    ListNode* node = new ListNode{sum%10};
    node->next = next_node;

    return node;
  }
  // Otherwise, only one of them is null, so we call the one list function.
  else
  {
    // find out which one is not null.
    l1 = (l1==nullptr) ? l2:l1;

    // Work out the sum and new carry.
    int sum = l1->data + carry;
    int new_carry = sum/10;

    ListNode* next_node = sum_recur_helper(l1->next, new_carry);

    // Create node for this value place
    ListNode* node = new ListNode{sum%10};
    node->next = next_node;

    return node;
  }

  // Should not get here.
  return nullptr;
}

// helper for a single list
ListNode* sum_recur_helper(ListNode* l, int carry)
{
  // Base case: l == nullptr
  if(l==nullptr)
  {
    // If there a carry to add on at the end?
    if(carry)
    {
      return new ListNode{carry};
    }
    else
    {
      return nullptr;
    }
  }

  // l is not null, so we recurse:
  int sum = l->data + carry;
  int new_carry = sum/10;

  ListNode* next_node = sum_recur_helper(l->next,new_carry);

  // Create node for this value place, set the data and next node.
  ListNode* node = new ListNode{sum%10};
  node->next = next_node;

  return node;
}

////////////////////////////////////////////////////////////////////////////
//
ListNode* reverse(ListNode* l)
{
  return nullptr;
}

////////////////////////////////////////////////////////////////////////////
// This works with the mode significant digits on the left, so that
// adding two linked lists means:
//  6->1->7    617
// +2->9->5   +295
// =9->1->2   =912
ListNode* sum_reverse(ListNode* l1, ListNode* l2)
{
  return nullptr;
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
}

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}






















































