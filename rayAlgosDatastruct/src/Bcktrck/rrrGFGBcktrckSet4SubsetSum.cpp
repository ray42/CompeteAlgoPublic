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
//#include<cstddef>

void printSubset(vector<int>& A, const int size)
{
  for(int i=0; i < size; ++i)
    cout << A[i] << ' ';
  cout << '\n';
}

// Keep track of how many nodes are generated.
// This is just used for the output at the end, it doesn't seem to do much
// for the algorithm.
static int total_nodes=0;

void subset_sum(const vector<int>& s, vector<int>& t,
                int t_size,
                int sum, int ite,
                const int target_sum)
{
  // If this function is entered, a new node is created.
  ++total_nodes;

  // base case, sum == target sum
  if(target_sum == sum)
  {
    // We found a subset
    printSubset(t,t_size);

    // Exclude the previously added item and consider the next candidate
    subset_sum(s,t,
               t_size-1,sum-s[ite],  // exclude this item
               ite+1, // start at the next candidate
               target_sum);
  }
  else
  {
    // Generate nodes along the breadth
    for(int i = ite; i < s.size(); ++i)
    {
      // use this branch/item. At the next iteration of this loop, another
      // branch is taken.
      t[t_size] = s[i];

      // consider next level node (along depth)
      subset_sum(s,t,
                 t_size+1,
                 sum+s[i],i+1,
                 target_sum);
    }
  }
}

void runSubsetSum()
{
  const vector<int> s{10,7,5,18,12,20,15};
  vector<int>t(s.size(),0);
  const int target_sum=35;
  subset_sum(s,t,0,0,0,target_sum);
}


int main()
{
  runSubsetSum();
  return 0;
}

