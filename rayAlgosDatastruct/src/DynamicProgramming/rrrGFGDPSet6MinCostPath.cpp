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
#include<algorithm>// min

template<typename T>
auto minCost(vector<vector<T>>&cost, size_t m, size_t n)
{
  if(m==0 && n==0)
    return cost[m][n];
  if(m==0 && n != 0)
    return cost[m][n] + minCost(cost,m,n-1);
  if(m!=0 && n==0)
    return cost[m][n] + minCost(cost,m-1,n);

  return cost[m][n] + std::min({minCost(cost,m,n-1),    // left
                                minCost(cost,m-1,n),    // top
                                minCost(cost,m-1,n-1)});// diag
}

template<typename T>
void runMinCost(vector<vector<T>>&c,size_t m, size_t n)
{
  cout << "Min cost path: " << minCost(c,m,n) << '\n';
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
template<typename T>
auto minCostDP(vector<vector<T>>&cost, size_t m, size_t n)
{
  // table of min costs
  // since m and n are used to index the cost table directly, they are one
  // smaller the cost table's sizes. So we +1 when we declare it and give 
  // the size.
  vector<vector<T>> mc(m+1,vector<T>(n+1,T{}));

  using vecsz_t = decltype(cost.size());

  // Take care of base case and edge cases:
  mc[0][0] = cost[0][0];

  // first column
  // Note that we need less than or equal to, since these m and n are used
  // to index the vectors directly. I.e. they range from 0 to cost.size()-1
  for(vecsz_t i = 1; i <= m; ++i)
    mc[i][0] = cost[i][0] + mc[i-1][0];
  
  // first row
  for(vecsz_t j = 1; j <= n; ++j)
    mc[0][j] = cost[0][j] + mc[0][j-1];

  // Now we work in row major order, from first row, then 2nd row, etc...
  for(vecsz_t i = 1; i <= m; ++i)
  {
    for(vecsz_t j = 1; j <= n; ++j)
    {
      mc[i][j] = cost[i][j] + std::min({mc[i-1][j],    // top
                                        mc[i][j-1],    // left
                                        mc[i-1][j-1]});// diag
    }
  }
  // Recall that m and n are not the sizes, we use it to directly index, so 
  // we do not take one off, i.e. not mc[m-1][n-1]
  return mc[m][n];
}
template<typename T>
void runMinCostDP(vector<vector<T>>&c,size_t m, size_t n)
{
  cout << "Min cost path (DP): " << minCostDP(c,m,n) << '\n';
}


auto main(int,char* [])->int
{
  vector<vector<int>> cost{{1,2,3},
                           {4,8,2},
                           {1,5,3}};
  runMinCost(cost,2,2);
  runMinCostDP(cost,2,2);
  return 0;
}
