/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<limits>
using std::numeric_limits;
#include<vector>
using std::vector;

//       0, 1, 2, 3, 4
// p = [40,20,30,10,30]
// Start with i=1, j=p.size()-1=4
auto matChainMult(vector<int>& p, int i, int j)->int
{
  // If there is only one matrix, return 0 (no flops)
  if(i==j) return 0;

  int minOps = std::numeric_limits<int>::max();

  // separate between 1 and less than j because the last k will be:
  //       0, 1, 2, 3, 4
  // p = [40,20,30,10,30]
  //                k k+1
  for(int k = i; k < j; ++k)
  {
    int flops = p[i-1]*p[k]*p[j] + matChainMult(p,i,k)
                                 + matChainMult(p,k+1,j);
    if(flops<minOps) minOps = flops;
  }
  return minOps;
}

void printParen(vector<vector<int>>&s, int i, int j)
{
  if(i==j)
  {
    cout << "A" << i;
  }
  else
  {
    cout << "(";
    printParen(s,i,s[i][j]);
    printParen(s,s[i][j]+1,j);
    cout << ")";
  }
}

// Matrix Ai has dimension p[i-1]xp[i] for i=1..n
//
//        0  1  2  3  4
//p[] = [40,20,30,10,30] -> A1,A2,A3,A4
//
//Table m:
//j 0|1|2|3|4
//i ---------
//0| | | | | |
//1| |1|2|3|4|
//2| | |1|2|3|
//3| | | |1|2|
//4| | | | |1|
//
//Table m's entries in the above represent the length, it depicts how the
//below algorithm fills in m, i.e. m[i,j] = i implies that i==j and we're 
//dealing with a matrix mult. of length 1, i.e. one matrix. These are NOT 
//the actual values of m. The actual values of m is the min. flops required
//to perform the mult. of chain length j-i+1.
void matChainMultDP(vector<int>& p)
{
  // length of p, so n-1 is the number of matrices to multiply.
  auto n = static_cast<int>(p.size());

  // Base case: i==j, chain of length 1, so there is no multiplication. We
  // would fill the diagonal entries with 0, but this is already done as 
  // part of the initialization.
  vector<vector<int>>m(n,vector<int>(n,0));
  
  // Used to record the split
  vector<vector<int>>s(n,vector<int>(n,0));

  // Loop from length of 2 to n-1
  for(int l=2; l<n; ++l)
  {
    // Loop down the matrix m.
    for(int i = 1; i < n-l+1; ++i)
    {
      // Calculate the j entries such that j-i+1=l.
      int j = l+i-1;

      // Set number of flops in m to max(), then we can minimize it.
      m[i][j] = std::numeric_limits<int>::max();

      // Loop through all possible splits.
      for(int k=i; k < j; ++k)
      {
        int q = p[i-1]*p[k]*p[j] // Top level mult.
                +m[i][k]         // min flops of left section
                +m[k+1][j];      // min flops of right section

        // Does this give a smaller flop count then a previous split?
        if(q<m[i][j])
        {
          m[i][j] = q;
          s[i][j] = k;
        }
      }
    }
  }
  
  cout << "Optimal flops: " << m[1][n-1] << '\n'
       << "With parens: ";
  printParen(s,1,n-1);
  cout << '\n';
}

auto main(int, char* [])->int
{

  vector<int> p{40,20,30,10,30};
  //       0, 1, 2, 3, 4
  // p = [40,20,30,10,30]
  // Start with i=1, j=p.size()-1=4
  cout << matChainMult(p,1,p.size()-1) << '\n';

  matChainMultDP(p);

  return 0;
}

