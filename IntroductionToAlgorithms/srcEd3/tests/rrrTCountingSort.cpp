/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
//using std::cout; using std::endl;

#include<vector>
//using std::vector;

#include<algorithm>
//using std::max_element;
#include <random>
#include <iterator>
#include <iostream>
#include <functional>

using namespace std;

template<typename T>
void print(vector<T>&v)
{
  std::copy(v.begin(),v.end(),ostream_iterator<T>(cout, " "));
  cout <<"\n";
}

vector<int> generateRandomVector(unsigned size=10, unsigned max=10)
{
  // First create an instance of an engine.
  random_device rnd_device;
  // Specify the engine and distribution.
  mt19937 mersenne_engine(rnd_device());
  uniform_int_distribution<int> dist(0,max);

  auto gen = std::bind(dist, mersenne_engine);
  vector<int> vec(size);
  generate(begin(vec), end(vec), gen);
  return vec;
}


vector<int> CountingSort(vector<int>& A)
{
  // C will hold cumulative frequency of elements of A.
  // Note: +1 for the 0 number.
  vector<unsigned>C(*max_element(A.begin(),A.end())+1);
  // Note: in c++, vector of unsigned is initialized to 0s.
  cout << "C: ";
  print(C);

  // Count the elements, loop through elements of A, from index 0 to n-1
  for(size_t j=0; j<A.size(); ++j)
  {
    ++C[A[j]];
  }
  // C[i] now contains the number of elements equal to i
  cout << "C: ";
  print(C);

  // Now get the cumulative frequency
  for (size_t i = 1; i < C.size(); ++i)
  {
    C[i]=C[i]+C[i-1];
  }
  // C[i] now contains the number of elements less than or equal to i.
  cout << "C: ";
  print(C);

  // B is the output
  vector<int> B(A.size());
  for(int j=static_cast<int>(A.size()-1); j!=-1; --j)
  {
    // LOOK AT HERE! ATTENTION HERE!!!!!!!!!!
    // the magic is the -1 here.
    B[C[A[j]]-1]=A[j];

    // minus 1 in the case of duplicate elements.
    --C[A[j]];
  }

  return B;
}

int main()
{
  //auto A=generateRandomVector();
  
  vector<int>A={2,5,3,0,2,3,0,3};
  cout << "A: ";
  print(A);
  auto B=CountingSort(A);
  cout << "B: ";
  print(B);

  return 0;
}

