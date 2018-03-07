/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
# include <limits.h>

#include<cstddef> // for size_t
#include<limits> // for numeric_limits<T>::max()
#include<algorithm> // for std::min and std::max
#include<vector>
using std::vector;
#include<string>
using std::string;

template<typename T>
void print_2dvec(vector<vector<T>>& v, 
                 const string& str1="",
                 const string& str2="")
{
  if(!str1.empty())
    cout << str1;

  for(const auto& vi:v)
  {
    for(const auto& j:vi)
    {
      cout << j << ' ';
    }
    cout << '\n';
  }

  if(!str2.empty())
    cout << str2;
}

// n - number of eggs
// h - number of floors to be tested
int eggDropRecur(int n, int h)
{
  // Base cases:
  // If there is one egg (n=1) and some floors (h>0), then we always need
  // to test every floor
  if(n==1 && h>0) return h;

  // If there are no floors to be tested (h=0), no drops are required.
  if(h==0) return 0;

  // If there is one floor to be tested, we need 1 drop.
  if(h==1) return 1;

  // Now, we test all floors from x=[1..h].
  // Each drop will give two subproblems:
  //   one for the lower half (if egg breaks)-> x-1 floors to test
  //   one for the upper half (if egg doesn't break)-> h-x floors to test
  // we take the max of the result of the two subproblems 
  // (to get the worst case answer)
  // However, we take the min over all droppings, since we do want the 
  // minimum dropping over the worst case.
  int minimum = std::numeric_limits<int>::max();
  for(int x = 1; x<=h; ++x)
  {
    minimum = std::min(minimum,
                       (1+std::max(eggDropRecur(n-1,x-1), // egg broke
                                   eggDropRecur(n  ,h-x)) // egg no break
                       )
                      );
  }
  return minimum;
}

// n - number of eggs
// k - number of floors in the building.
int eggDropDP(const int n, const int k)
{
  // table to store results
  // rows = num eggs
  // column = num floors to be tested.
  vector<vector<int>> dp(n+1,vector<int>(k+1,0));
//  print_2dvec(dp,"initial dp:\n","\n");

  // base cases:
  // 1) If there is one egg (n=1), the required number of drops is the same
  // as the number of floors to be tested W(n=1,k)=k, i.e.:
  //   0 1 2 3 4
  //   ---------
  // 0|
  // 1|0 1 2 3 4
  // 2|
  // 3|
  // 4|
  for(int j=0; j <= k; ++j)
  {
    dp[1][j]=j;
  }
//  print_2dvec(dp,"n=1 dp:\n","\n");

  // Base case 2) If there are no floors (k=0), num drops=0
  //              If there is one floor (k=1), num drops=1
  // So we have
  //   0 1 2 3 4
  //   ---------
  // 0|0 1
  // 1|0 1 2 3 4
  // 2|0 1
  // 3|0 1
  // 4|0 1
  for(int i=0; i<=n; ++i)
  {
    dp[i][0]=0;
    dp[i][1]=1;
  }
//  print_2dvec(dp,"k=0 or 1 dp:\n","\n");


	// Fill rest of the entries in table using optimal substructure
	// property
  for (int i = 2; i <= n; i++)
  {
    for (int j = 2; j <= k; j++)
    {
      dp[i][j] = INT_MAX;
			for (int x = 1; x <= j; x++)
			{
				int res = 1 + std::max(dp[i-1][x-1], dp[i][j-x]);
				if (res < dp[i][j])
					dp[i][j] = res;
			}
		}
	}

  // Now loop through the rows (num of eggs)
  for(int i=2; i <= n; ++i)
  {
    // Now loop through the number of floors.
    for(int j=2; j<= k; ++j)
    {
      // Now we drop the egg from each floor from x=[1..j]
      dp[i][j] = std::numeric_limits<int>::max();
      for(int x=1; x<=j; ++x)
      {
        dp[i][j] = std::min(dp[i][j],(1+std::max(dp[i-1][x-1],
                                                 dp[i][j-x])
                                     )
                           );
      }
    }
  }

//  print_2dvec(dp,"dp:\n","\n");
  return dp[n][k];
}

int main()
{
  int n = 2, k=10;
  cout << "\nMin. num. of trials in worst case with " << n << " eggs  and "
       << k << " floors is " << eggDropRecur(n,k) << '\n';

  cout << "DP solution: " << eggDropDP(2,10)<<'\n';

  return 0;
}

