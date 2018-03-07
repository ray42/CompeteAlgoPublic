/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<limits>
#include<iostream>
using std::cout; using std::endl; using std::cin;

auto main(int argc, char* argv[])->int
{
  // Number of test cases
  unsigned T;//1 <= T <= 50
  cin >> T;

  // N people per test
  long int N{};   // 1<=N<=10^6
  long int n;     // 1<=N<=10^6
  long int R{};   // 1<=Ai<=10^9

  long int hi{};  // 1<=Ai<=10^9
  long int low{}; // 1<=Ai<=10^9
  long int temp{};// 1<=Ai<=10^9
  for(decltype(T) t=0; t!=T; ++t)
  {
    cin >> N >> R;
    // Reset low and high
    low=0;
    hi=1000000001;
    
    n=0;
    while(n!=N)
    {
      ++n;
      cin >> temp;
      if((temp < hi) && (temp>low))
      {
        if(R<temp)
        {
          hi=temp;
        }
        else
        {
          low=temp;
        }
      }
      else
        break;
    } // while
    if(n==N)
    {
      cout << "YES" << "\n";
    }
    else
    {
      cout << "NO" <<"\n";
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
