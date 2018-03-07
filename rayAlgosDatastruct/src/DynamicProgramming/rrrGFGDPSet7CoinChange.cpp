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

// Recursively return the count = the number of ways to partition a sum of 
// n using coins in S[0..m-1]. Note that m represents the number of types of
// coins, so the valid inputs are [1..m], but when we index the S array, we
// do S[0..m-1].
int count(vector<int>& S, int m, int n)
{
  // If the sum n is less than 0, then no solution exists.
  if(n<0)
    return 0;

  // If n is greater than 0 and there are no coins left, then there is no
  // solution. m<=0 is correct m describes the coin types, but the array
  // S is indexed by S[0..m-1]
  if(n>0 && m<=0)
    return 0;

  // If n is 0 then there is 1 solution (do not include any coin)
  if(n==0)
    return 1;
  
  // count is the sum of solution (i) including S[m-1] (ii) excluding S[m-1]
  return count(S,m-1,n) + count(S,m,n-S[m-1]);
}

// S is the coin types, n is the sum
int countTabu(vector<int> S, int n)
{
  // number of type of coins. Note that to index the S array, we use
  // j = 0..m-1
  auto m = static_cast<int>(S.size());

  // tab{0..n,0..m-1} of number of ways to partition the sum n. The entry
  // tab(i,j-1) is the number of ways to partition i using j coin types.
  // we need n+1 row as the table is constructed in bottom up manner using
  // the base case 0 (that is, sum n = 0), since we include 0, the indices 
  // actually goes from 0..n, which means the size is n+1.
  vector<vector<int>> tab(n+1,vector<int>(m,0));

  // Recall that the base cases are:
  // n == 0, and we still have coins m>=0, we return 1.
  for(int j = 0; j < m; ++j)
  {
    tab[0][j] = 1;
  }

  // Fill in the rest of the entries in a bottom up manner. Remember the 
  // other two base cases, namely:
  // 1) if sum i < 0, tab is equal to 0
  // 2) if coin types m <= 0, there are no coin types left, so no solution.
  // start i = 1, since the base case i=0 is filled already.
  for(int i = 1; i < n+1; ++i)
  {
    for(int j = 0; j < m; ++j)
    {
      // Count of solutions including S[j]
      int x = 0;
      if(i-S[j]>=0)
        x = tab[i-S[j]][j];
      else
        x=0;

      // Count of solutions excluding S[j]
      int y = 0;
      if(j >= 1)
        y = tab[i][j-1];
      else
        y=0;

      // Total count
      tab[i][j] = x+y;
    }
  }
  return tab[n][m-1];
}


int main()
{
  vector<int> arr{1,2,3};
  auto m = static_cast<int>(arr.size());
  auto n = int{4};

  cout << count(arr,m,n) << '\n';
  cout << countTabu(arr,n) << '\n';
  return 0;
}

