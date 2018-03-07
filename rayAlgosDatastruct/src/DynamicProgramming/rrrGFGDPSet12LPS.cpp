/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// http://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence

#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;
#include<algorithm>
using std::max;
#include<vector>
using std::vector;


int LPS(string& X, int i, int j)
{
  // We do the base cases from decreasing length, since, size 2 is more 
  // likely to happen before size 1 or size 0.
  
  if( ((j-i)==1) && X[i]==X[j]) // size 2
    return 2;
  if(j==i)
    return 1;
  if(j<i)
    return 0;

  // recursive case
  if(X[i]==X[j])
  {
    // plus two since we took two off.
    return LPS(X,i+1,j-1) + 2;
  }
  else
  {
    // No palindrome contributions found.
    return std::max(LPS(X,i+1,j),LPS(X,i,j-1));
  }
  return 0;
}
void runLPS(string& str)
{
  cout << "LPS: " << LPS(str,0,str.size())<<'\n';
}

////////////////////////////////////////////////////////////////////////////
int LPSDP(string& X)
{
  int n = X.size();

  vector<vector<int>> dp(n+1,vector<int>(n+1,0));

  // First we fill in the base case for j==i
  for(int i=1; i<=n; ++i) dp[i][i]=1;

  // Loop through the lengths l=2..n (we have already done l=1)
  for(int l=2; l<=n; ++l)
  {
    // Loop through the i
    for(int i=1; i <= (n-l+1); ++i)
    {
      int j = l+i-1;

      // Base case of length 2
      if((l==2) && X[j]==X[i])
        dp[i][j]=2;
      else if(X[i]==X[j]) // ends are the same
      {
        dp[i][j] = 2+dp[i+1][j-1];
      }
      else // ends not the same
      {
        dp[i][j] = std::max(dp[i+1][j],dp[i][j-1]);
      }
    }
  }
  return dp[1][n];
}
void runLPSDP(string& str)
{
  cout << "LPSDP: " << LPSDP(str)<<'\n';
}

int main()
{
  string str="GEEKSFORGEEKS";
  runLPS(str);
  runLPSDP(str);

  return 0;
}

