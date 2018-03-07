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
#include<iterator>
using std::begin;
using std::end;
#include<numeric>
using std::iota;

#include<limits>
using std::numeric_limits;

#include<algorithm>
using std::max;

// if p=[1,5,8,9,10,17,17,20,24,30], n=10 then
//
// p[0]+CutRod(10,9),
// p[1]+CutRod(10,8),
// p[n-1]+CutRod(10,0)
// So we need to do n-i-1, starting the index at zero puts everything a bit 
// off
int CutRod(const vector<int>& p, int n)
{
  if(n<=0)
    return 0;

  int q=-1*numeric_limits<unsigned>::infinity();
  for(int i=0; i!=n; ++i)
  {
    q=max(q,p[i]+CutRod(p,n-i-1));
  }
  return q;
}

auto main(int, char *[])->int
{
//  const int n=40;
//  vector<int>p(n);
//  iota(begin(p),end(p),1);
  vector<int>p{1,5,8,9,10,17,17,20,24,30};
  cout << "r: " << CutRod(p, p.size()) << endl;;

  return 0;
}

