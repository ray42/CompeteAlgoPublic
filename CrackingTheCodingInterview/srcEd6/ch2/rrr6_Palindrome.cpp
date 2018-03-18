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
  ListNode* rev_list = reverse_copy(l);
  return is_equal(l,rev_list);
}

ListNode* reverse_copy(ListNode* l)
{
  // check for null
  if(l==nullptr) return l;

  // Recall in rrr5_SumLists.cpp that to reverse a linked list, we need to
  // point curr to prev, then iterate through the linked list by 
  // curr = curr->next, but since we've changed curr->next, we must cache 
  // curr->next.
  // 
  // However, in this case we don't need to cache curr->next, since 
  // curr->next is never modified. We create a copy of curr!
  ListNode* prev_copy = nullptr;
  ListNode* curr = l;
  while(curr!=nullptr)
  {
    // create a copy of the current node, then point it to the previous copy
    // node.
    ListNode* curr_copy = new ListNode{curr->data};
    
    // Do the reverse using the copy.
    curr_copy->next = prev_copy;

    // move along the input list, and set the copy curr to the previous copy
    curr = curr->next;
    prev_copy = curr_copy;
  }

  // when loop ends, prev_copy points to the last element added to the 
  // (copied) reversed list, and curr is nullptr.
  return prev_copy;
}

// Return if two linked lists are equal
bool is_equal(ListNode* l1, ListNode* l2)
{
  // At least one of these is not nullptr. Let's assume that both are not 
  // nullptr, then we simply loop until one of them is nullptr
  while(l1 != nullptr && l2 != nullptr)
  {
    if(l1->data != l2->data)
      return false;

    // advance heads
    l1 = l1->next;
    l2 = l2->next;
  }

  // If we get here, then either l1 is nullptr, l2 is nullptr, or both.
  // If both are nullptr, then the two lists are equal.
  return l1==nullptr && l2==nullptr;
}

//////////////////////////////////////////////////////////////////////////////
//// optimized version, only compare half the linked list

// Reverse and copy the given linked list, and return the size.
ListNode* reverse_copy(ListNode*, int&); // not unit tested, cba.

bool is_xnums_equal(ListNode*, ListNode*, int); // not unit tested, cba.

bool is_palindrome_reverse_opt(ListNode* l)
{
  int lsize = 0;
  ListNode* rev_list = reverse_copy(l,lsize);

  return is_xnums_equal(l, rev_list, lsize/2);
}

ListNode* reverse_copy(ListNode* l, int& x)
{
  // Initially, the size is zero
  x = 0;
  if(l == nullptr) return l;

  ListNode* prev_copy = nullptr;
  ListNode* curr = l;
  while(curr)
  {
    // copy
    ListNode* curr_copy = new ListNode{curr->data};

    // link
    curr_copy->next = prev_copy;
    ++x;
    
    // advance through both lists.
    prev_copy = curr_copy;
    curr = curr->next;
  }
  return prev_copy;
}

bool is_xnums_equal(ListNode* l1, ListNode* l2, int x)
{
  // NOTE: Since we are only comparing half the list, there is an additional
  // edge case which we did not consider in the first attempt. If x = 0, it 
  // means there is only 1 element in the list, since 1/2 = 0 (in ints).
  // Thus, we check for this and return if the two data is equal.
  if(x==0 && l1!= nullptr && l2!=nullptr)
  {
    return l1->data == l2->data;
  }

  while(l1 != nullptr && l2 != nullptr && x > 0)
  {
    --x;
    if(l1->data != l2->data)
      return false;

    // advance pointers
    l1 = l1->next;
    l2 = l2->next;
  }

  // This part also changed. Since we've compared only x number of elements,
  // where l1 or l2 could have finished before x reaches zero then we have 
  // the following scenario:
  //
  // if x==0, then we have compared x numbers of nodes from l1 and l2, they
  // are equal:
  if(x==0) 
  {
    return true;
  }

  // Otherwise, if x != 0, it then either l1 or l2 finished before the
  // other, so they are not equal.
  return false;
}

////////////////////////////////////////////////////////////////////////////
//// We use a stack, insert half way, then compare the popped out value with
//// the rest of the list. For this version, we pre-compute the size.
int get_size(ListNode* l);

bool is_palindrome_stack_known_size(ListNode* l)
{
  // get the size
  int lsize = get_size(l);

  // edge case: check for size 0 (nullptr) and size 1, both should return
  // true.
  if(lsize == 0 || lsize ==1) 
    return true;

  // We're going to put half of the elements in a stack, then pop it out
  // whilst comparing with the second half. Thus we need half the size.
  // Note that if lsize is odd, then this is rounded down, i.e. it does not
  // take into account the middle element, thus we will need to remember to 
  // skip over the middle element if it is odd.
  int halflsize = lsize/2;

  // working pointer to iterate through the list.
  ListNode* curr = l;
  // we don't need to test for curr, but it's just good practice. We don't
  // need to test for curr because it's guaranteed that halflsize <= lsize.
  // so halflsize will get to 0 before curr gets to nullptr.
  std::stack<decltype(curr->data)> left_half_stack;
  while(curr && halflsize > 0)
  {
    // insert into back of stack
    left_half_stack.push(curr->data);

    // advance pointer and decrement the count.
    curr = curr->next;
    --halflsize;
  }

  // If there is an odd number of nodes, we skip the middle.
//  if(lsize & 1) // if it's off. This works since we're AND-ing with 1! :)
//    curr = curr->next;
  // More fancy way:
  curr = (lsize&1)? curr->next : curr;

  // Now iterate through the rest of the nodes, comparing with what's popped
  while(!left_half_stack.empty() && curr != nullptr)
  {
    // get the value and pop
    auto left_data = left_half_stack.top();
    left_half_stack.pop();

    // Now  compare the datas
    if(left_data != curr->data)
      return false;

    // advance the curr pointer.
    curr = curr->next;
  }

  // if we get here, everything is okay!
  return true;
}

int get_size(ListNode* l)
{
  int lsize = 0;
  while(l)
  {
    ++lsize;
    l = l->next;
  }
  return lsize;
}

////////////////////////////////////////////////////////////////////////////
// This version also uses a stack, but we do not pre-calculate the size.
// Instead we use a slow pointer and a fast pointer. This is the runner 
// technique.
bool is_palindrome_stack_two_point(ListNode* l)
{
  // Check for nullptr or one node (if there is only one node, then l->next)
  // is nullptr
  if(l==nullptr || l->next == nullptr)
    return true;

  // Now there are at least two nodes. I'll illustrate the runner technique:
  // we have two pointers, slow (S) and fast (F). The fast moves two times 
  // as fast as the slow one:
  // F
  // S
  // 1->2->3->4->5->null
  //
  //       F
  //    S
  // 1->2->3->4->5->null
  //
  //             F
  //       S
  // 1->2->3->4->5->null
  //
  // To make F move twice as fast S, for each S = S->next, we do 
  // F = F->next->next, thus we must check that F and F-next is not null, 
  // but F->next->next *can* be null.
  //
  // At this point, we have added 1 and 2 to the stack, and we need to skip
  // 3 without adding it to the queue, and then compare 4 and 5 with the 
  // popped stack values.
  //
  // Let's see how it works with an even number of nodes:
  // F
  // S
  // 1->2->3->4->5->6->null
  // 
  //       F
  //    S
  // 1->2->3->4->5->6->null
  //
  //             F
  //       S
  // 1->2->3->4->5->6->null
  //
  //                   F
  //          S
  // 1->2->3->4->5->6->null
  //
  // So again, we have pushed the left half into the stack, but we do NOT 
  // skip over the element S is pointing to. But how do we know if do we 
  // need to skip or not? Looking at:
  //
  // odd:
  //             F
  //       S
  // 1->2->3->4->5->null - stack has odd number of elements
  //
  // even:
  //                   F
  //          S
  // 1->2->3->4->5->6->null - stack has even number of elements
  //
  // So we can either check the size of the stack, or, notice that since F
  // starts at 1, and keeps advancing by 2, it will always land on an odd 
  // numbered node. Thus, if there is an EVEN number of element, F must be
  // null. If there is an odd number of elements, F will point to the last
  // element. Thus, if F!=nullptr, we know that there is an odd number of 
  // elements (since it's pointing to the last odd numbered element, the 
  // nullptr would be where the next even element is.)

  ListNode* slow = l;
  ListNode* fast = l;

  // Now loop through, remember that for us to be able to do 
  // fast = fast->next->next, we need both fast and fast->next to be not
  // null.
  std::stack<decltype(l->data)> left_half_stack;
  while(fast && fast->next)
  {
    left_half_stack.push(slow->data);

    cout << "pushing to q: " << slow->data << '\n';

    slow = slow->next;
    fast = fast->next->next;
  }

  // If there is an odd number of nodes, we skip the middle node.
  // If there is an odd number of nodes, then fast would be pointing to the 
  // last odd node, i.e. it is not nullptr
  if(fast != nullptr)
  {
    cout << "odd nnode, advancing slow pointer\n";
    slow = slow->next;
  }

  // Now iterate through the rest of the list and compare
  while(slow)
  {
    auto data = left_half_stack.top();
    left_half_stack.pop();
    if(slow->data != data)
      return false;

    // advance pointer
    slow = slow->next;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////
// recursive - I'll read the solution.
bool is_palindrome_recur(ListNode* l)
{

}

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

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
SECTION("Sec Testing is_palindrome_recur")
{
  // 1 - nullptr, true
  ListNode* l1 = nullptr;
  REQUIRE(is_palindrome_recur(l1)==true);

  // 2 - 1 node, true
  ListNode* l2 = vec_to_slist({3});
  REQUIRE(is_palindrome_recur(l2)==true);

  // 3.1 - 2 node, false
  ListNode* l31 = vec_to_slist({3,42});
  REQUIRE(is_palindrome_recur(l31)==false);

  // 3.2 - 2 node, true
  ListNode* l32 = vec_to_slist({3,3});
  REQUIRE(is_palindrome_recur(l32)==true);

  // 4.1 - 3 node, false
  ListNode* l41 = vec_to_slist({1,2,3});
  REQUIRE(is_palindrome_recur(l41)==false);

  // 4.2 - 3 node, true
  ListNode* l42 = vec_to_slist({1,2,1});
  REQUIRE(is_palindrome_recur(l42)==true);

  // 5.1 - 4 node, false
  ListNode* l51 = vec_to_slist({1,2,3,1});
  REQUIRE(is_palindrome_recur(l51)==false);

  // 5.2 - 4 node, true
  ListNode* l52 = vec_to_slist({1,2,2,1});
  REQUIRE(is_palindrome_recur(l52)==true);

  // 6.1 - 5 node, false
  ListNode* l61 = vec_to_slist({1,2,3,1,1});
  REQUIRE(is_palindrome_recur(l61)==false);

  // 6.2 - 5 node, true
  ListNode* l62 = vec_to_slist({1,2,3,2,1});
  REQUIRE(is_palindrome_recur(l62)==true);
}



} // end testcase

//auto main(int argc, char * argv[])->int
//{
//  return 0;
//}

