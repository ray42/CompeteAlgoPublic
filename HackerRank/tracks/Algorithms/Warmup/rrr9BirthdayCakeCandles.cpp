/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
//https://www.hackerrank.com/challenges/birthday-cake-candles/problem

#include<iostream>
using std::cin;using std::endl;using std::cout;
#include<iterator>
using std::istream_iterator;
#include<vector>
using std::vector;
#include<algorithm>
using std::for_each;

auto main(int argc, char* argv[])->int
{
  using lu=long unsigned;
  auto i=lu{};

  cin >> i;// throw away first one.
  vector<lu>v{istream_iterator<lu>{cin},
              istream_iterator<lu>{}};

  auto max=lu{};
  auto count=lu{};
  for_each(v.begin(),v.end(),
      [&max,&count](const auto&i){
        if(i>max)
        {
          max=i;
          count=1;
        }else if(i==max)
        {
          ++count;
        }
      });
  cout << count << endl;

  return 0;
}
