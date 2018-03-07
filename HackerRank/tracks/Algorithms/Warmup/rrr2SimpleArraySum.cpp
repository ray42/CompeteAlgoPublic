#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<iterator> // for iterator adaptors
#include<numeric> // for accumulate
using namespace std;


int main(int argc, char* argv[]) 
{  
  int foo(0);
  cin >> foo;
  int sum= std::accumulate(std::istream_iterator<int>(cin),
                           std::istream_iterator<int>(),
                           0);
  cout << sum << endl;
  return 0;
}

