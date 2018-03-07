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
#include "./../leetcodeutility.h"
#define RDEBUG(x) cout << '>' << #x << ':' << x << '\n';


#include<vector>
using std::vector;
#include<stack>
using std::stack;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root)
  {
    vector<int> ret{};
    stack<TreeNode*> node_stack{};
    TreeNode* curr = root;
    while(curr != nullptr || !node_stack.empty())
    {
      // insert all left until null.
      while(curr != nullptr)
      {
        node_stack.push(curr);
        curr = curr->left;
      }

      // Now we pop the most recently added one, print it's value, and
      // set curr to it's right child, and let the above while loop
      // insert all it's left (if possible)
      curr = node_stack.top();
      ret.push_back(curr->val);
      node_stack.pop();
      curr = curr->right;
    }
        
    return ret;
  }
};


TEST_CASE("Testing ", "[]" )
{
  TreeNode n1{1};
  TreeNode n2{2};
  TreeNode n3{3};
  n1.right = &n2;
  n2.left = &n3;

  printCont(treeInorderToVec(&n1));


  Solution s;
  
  SECTION("Sec Testing ")
  {
    REQUIRE(s.FOO()==);
  }
}

//auto main()->int
//{
//  return 0;
//}















