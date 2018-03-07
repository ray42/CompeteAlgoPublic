/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include "./../catch.hpp"

//https://leetcode.com/problems/symmetric-tree
#include<iostream>
using std::cout; using std::endl;
#include<queue>

// This is used as my own debug output. I need to set RAYDEBUG=false/true
#define rcout if(RAYDEBUG) cout 
static bool RAYDEBUG=false;

#include "./../leetcodeutility.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution
{
public:
  bool isSymmetric(TreeNode* root)
  {
    return root==nullptr || isMirrorImage(root->left,root->right);
  }

  bool isSymmetricIter(TeeeNode* root)
  {
    std::queue<TreeNode*> node_queue;
    node_queue.push_back(root);
    node_queue.push_back(root);

    while()
    {}
    return true;

  }

private:
  bool isMirrorImage(TreeNode* node1, TreeNode* node2)
  {
    // Both of them are null
    if(node1==nullptr && node2==nullptr)
      return true;
    // Only one of them is null
    else if(node1==nullptr || node2==nullptr)
      return false;
    // Both are not null
    else
    {
      // Compare the value of the two nodes, then 
      // node1's left has to be compared with node2's right.
      // node1's right has to be compared with node2's left.
      return (node1->val == node2->val) 
        && isMirrorImage(node1->left,node2->right)
        && isMirrorImage(node1->right,node2->left);
    }
  }
};

TEST_CASE("Testing isSymmetric", "[isSymmetric]" )
{
  Solution s;
  
  SECTION("Sec Testing isSymmetric")
  {
    TreeNode A1{1};
    TreeNode A2{2};
    TreeNode A3{2};
    TreeNode A4{3};
    TreeNode A5{4};
    TreeNode A6{4};
    TreeNode A7{3};
    A1.left  = &A2;
    A1.right = &A3;
    A2.left  = &A4;
    A2.right = &A5;
    A3.left  = &A6;
    A3.right = &A7;

    TreeNode B1{1};
    TreeNode B2{2};
    TreeNode B3{2};
    TreeNode B4{3};
    TreeNode B5{4};
    TreeNode B6{4};
    TreeNode B7{3};
    B1.left  = &B2;
    B1.right = &B3;
    //B2.left  = &B4;
    B2.right = &B5;
    //B3.left  = &B6;
    B3.right = &B7;

    TreeNode C1{1};
    TreeNode C2{2};
    TreeNode C3{3};
    TreeNode C4{3};
    TreeNode C5{4};
    TreeNode C6{4};
    TreeNode C7{3};
    C1.left  = &C2;
    C1.right = &C3;
    //C2.left  = &C4;
    C2.right = &C5;
    //C3.left  = &C6;
    C3.right = &C7;

//    REQUIRE(s.isSymmetric(&A1)==true);
//    REQUIRE(s.isSymmetric(&B1)==false);
//    REQUIRE(s.isSymmetric(&C1)==false);
    
    REQUIRE(s.isSymmetricIter(&A1)==true);
  }
}

//auto main()->int
//{
//  return 0;
//}















