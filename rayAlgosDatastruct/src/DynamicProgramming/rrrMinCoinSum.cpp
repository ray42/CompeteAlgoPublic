/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl; using std::cin;
#include<vector>
using std::vector;

#include<numeric>
using std::iota;
#include<iterator>
//using std::begin; using std::end;

#include<limits>
using std::numeric_limits;



template<typename T>
vector<T> mincoins(const vector<T>& V, const T sum)
{
  // The solutions for {0,..,sum}
  vector<T>mins(sum+1,numeric_limits<T>::max());

  // 0 coins for sum 0:
  mins[0] = 0;

  // Loop through the sums
  for(T i = 1; i != (sum+1); ++i)
  {
    cout << "===================" << endl;
    cout << "i: " << i << endl;
    // Loop through the coin types
    for(const auto im:mins)
    {
      cout << im << " ";
    }
    cout << '\n';

    for(decltype(V.size()) j = 0; j != V.size(); ++j)
    {
      if((V[j] <= i) && (mins[i-V[j]]+1 < mins[i]))
      {
        mins[i] = mins[i-V[j]]+1;
      }
    }
//    cout << "===================" << endl;

//    std::cout << "Press ENTER to continue...";
//    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

  }

  return mins;
}

int main()
{
  auto mins = mincoins<int>({1,3,5},11);
  for(const auto i : mins)
  {
    cout << i << endl;
  }
  return 0;
}
