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
#include<cstddef> // for size_t


unsigned BinomCoeff(unsigned n, unsigned k)
{
  if(k==n || k == 0) return 1;

  if(k>n || k<0) return 0;

  return BinomCoeff(n-1,k)+BinomCoeff(n-1,k-1);
}
void runBinomCoeff(unsigned n, unsigned k)
{
  cout << "C"<<n<<","<<k<<")="<<BinomCoeff(n,k) <<'\n';
}

template<typename T>
void print2Dvec(const vector<vector<T>>& v)
{
  for(const auto& row : v)
  {
    for(const auto& col:row)
    {
      cout << col << " ";
    }
    cout << '\n';
  }
  cout << '\n';
  cout << '\n';
}

//////////////////////////////////////////////////////////
unsigned BinomCoeffDP(unsigned n, unsigned k)
{
  // Make (n+1)x(k+1) table of 0's
  // we need +1 to account for the zero entry for when we do choose 0 out
  // of n, i.e. C(n,0) = 1.
  auto nrow = n+1;
  auto ncol = k+1;

  vector<vector<unsigned>> dp(nrow,vector<unsigned>(ncol,0));

  // Base case, set C(n,0) = 1, i.e. set the first column to 1's
  for(size_t i = 0; i < nrow; ++i)
  {
    dp[i][0]=1;
  }

  // base case: set C(n,n) to 1, i.e. set the diagonal entries to 1
  for(size_t j = 0; j < ncol; ++j)
  {
    dp[j][j]=1;
  }

  // Calculate binom coeff according to the recursive formula
  // dp[i,j] = dp[i-1,j-1]+dp[i-1,j]
  // See my notes for why I start i = 2 and j=1. It follows from a sketch of
  // dp with the boundary conditions filled only.
  for(size_t i = 2; i <= n; ++i)
  {
    for(size_t j = 1; j <= k; ++j)
    {
      dp[i][j] = dp[i-1][j-1]+dp[i-1][j];
    }
  }

  return dp[n][k];
}

int main()
{
  runBinomCoeff(0,0);
  cout << BinomCoeffDP(4,3) << '\n';
  return 0;
}
