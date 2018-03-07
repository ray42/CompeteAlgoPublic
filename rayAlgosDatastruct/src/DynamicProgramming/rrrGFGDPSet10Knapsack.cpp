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


// Returns the maximum value that can be put in a knapsack of capacity W
template<typename T>
auto knapsack(const vector<T>& val, const vector<T>& wt, 
              const T W, const int n)->T
{
  if(W == 0)
    return 0;
  if(n == 0)
    return 0;

  if(wt[n-1]>W)
    return 0;

  return std::max(knapsack(val,wt,W-wt[n-1],n-1)+val[n-1],
                  knapsack(val,wt,W        ,n-1)          );
}

template<typename T>
auto knapsackDP(const vector<T>& val, const vector<T>& wt, int W)-> T
{
  using vecsz_t = decltype(val.size());
  // number of items
  auto n = val.size();

  // table for tabulation, +1 for zero entry
  // Note that this also covers the base cases dp[i,j]=0 for i=0 || j=0
  // ALSO NOTE: that when referring to dp, it is "based 1", i.e. if we have 
  // three items,
  // val[]={60, 100, 120}
  // wt[] ={10, 20,  30}
  // Then to refer to the first item, we do val[0], but to refer to the 
  // first item in dp, we do dp[1][1]... hope this makes sense.
  // Also, treat dp as if you were passing state params to a function. So 
  // in the recursive case, it is base 1, so we do it here also.
  // But when referring to the current val, we need to use val[j-1] instead 
  // of just val[j]. Also note that wt is indexed with j, NOT by i which 
  // loops over all weight values.
  vector<vector<T>> dp(W+1,vector<T>(n+1,T{0}));

  for(vecsz_t i = 0; i <= W; ++i)
  {
    for(vecsz_t j = 0; j <= n; ++j)
    {
      if(wt[j-1]>i)
      {
        dp[i][j] = dp[i][j-1];
      }
      else
      {
        dp[i][j] = std::max(dp[i-wt[j-1]][j-1] + val[j-1],
                            dp[i][j-1]);
      }
    }
  }

  return dp[W][n];
}

int main()
{
  {
    vector<int> val{60,100,120};
    vector<int> wt{10,20,30};
    int W = 50;
    int n = val.size();
    cout << knapsack(val,wt,W,n) << '\n';
    cout << knapsackDP(val,wt,W) << '\n';
  }
  return 0;
}

