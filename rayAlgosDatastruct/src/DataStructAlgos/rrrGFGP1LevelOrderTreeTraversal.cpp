/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;

#include<queue> // queue

// https://www.geeksforgeeks.org/?p=2686

// Method 1 (use function to print each level)
// Two functions:
// 1) printGivenLevel: prints all nodes at a given level
// 2) printLevelOrder: print level order traversal.
//
// printLevelOrder(tree)
// for d=1 to height(tree)
//   printGivenLevel(tree,d);
//
// printGivenLevel(tree,level)
// if tree is nullptr then return
// if level is 1, then
//   print (tree->data)
// else if level greater than 1, then
//   printGivenLevel(tree->left, level-1)
//   printGivenLevel(tree->right, level-1)

// So the level number determines when to stop and print the value. Of 
// course, if the node is null, we return immediately without printing 
// anything.

struct BinNode
{
  int val;
  BinNode* left;
  BinNode* right;
  
  BinNode(int n):val(n), left(nullptr), right(nullptr)
  {}
};

// print nodes at a given level
void printGivenLevel(BinNode* node, int level)
{
  if(node==nullptr) return;
  
  if(level==1)
    cout << node->val << ' ';
  else
  {
    // Print both left and right, level-1 to reach the base case.
    printGivenLevel(node->left, level-1);
    printGivenLevel(node->right,level-1);
  }
}

// Compute the height of a bin tree - the number of nodes along the longest
// path from the root node down to the farthest leaf node.
int height(BinNode* node)
{
  // nullptr does not contribute to the height. Also, this is the base case,
  // which we plus 1 to when the recursion unrolls.
  if(node==nullptr)
    return 0;
  else
  {
    // compute the height of each subtree. This just works, logic: if we
    // reach a child, then lheight and rheight is 0, then means this child
    // will be height 1, and this propagates up.
    int lheight = height(node->left);
    int rheight = height(node->right);

    // use larger one
    if(lheight > rheight)
      return (lheight+1);
    else
      return (rheight+1);
  }
}

void printLevelOrder(BinNode* node)
{
  int h = height(node);
  for(int i=1; i <= h; ++i)
    printGivenLevel(node,i);
}

//Time Complexity: O(n^2) in worst case. For a skewed tree, printGivenLevel()
//takes O(n) time where n is the number of nodes in the skewed tree. So time
//complexity of printLevelOrder() is O(n) + O(n-1) + O(n-2) + .. + O(1)  (since
//it has to go down to the height at each level) which is O(n^2).

////////////////////////////////////////////////////////////////////////////
// Method 2 - use a FIFO queue.

void printLevelOrderIter(BinNode* root)
{
  // create an empty FIFO queue
  std::queue<BinNode*> q;
  
  // temp node, start from root, this is what we use to store the q.front
  BinNode* temp_node = root;
  // put the temp_node in first to start off the queue
  q.push(temp_node);
  while(!q.empty())
  {
    temp_node = q.front();
    q.pop();
    cout << temp_node->val << ' ';

    // Now push its children. The children values will only be printed after
    // all nodes at this level is printed, since nodes at this level were
    // pushed in first.
    if(temp_node->left != nullptr)
      q.push(temp_node->left);
    if(temp_node->right != nullptr)
      q.push(temp_node->right);
  }
}

int main()
{
  // Testing method 1
  {
    /*  
             1
           2    3
         4   5
  
     *  */
    BinNode* root = new BinNode{1};
    root->left = new BinNode{2};
    root->right = new BinNode{3};
    root->left->left = new BinNode{4};
    root->left->right = new BinNode{5};
    cout << "Level order traversal of Bin Tree is:\n";
    printLevelOrder(root);
    cout << '\n';
  }

  // Testing method 2 (use queue)
  {
    /*  
             1
           2    3
         4   5
  
     *  */
    BinNode* root = new BinNode{1};
    root->left = new BinNode{2};
    root->right = new BinNode{3};
    root->left->left = new BinNode{4};
    root->left->right = new BinNode{5};
    cout << "Level order traversal of Bin Tree is (ITER VERSION):\n";
    printLevelOrderIter(root);
    cout << '\n';
  }
 
  return 0;
}

