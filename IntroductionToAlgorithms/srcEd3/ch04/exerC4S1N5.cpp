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

#include<tuple>
using std::tuple;

#include<cstddef>
using std::size_t;

#include<numeric>
using std::accumulate;

#include<iterator>
using std::reverse_iterator;
using std::distance;
using std::advance;
using std::prev;
using std::next;

#include<limits>
using std::numeric_limits;

#include<random>
using std::uniform_real_distribution;
using std::mt19937;
using std::random_device;

#include<algorithm>
using std::generate;
using std::all_of;
using std::max;

#include<chrono>
using namespace std::chrono;

#include<sstream>
using std::istringstream;

// Brute force maximum subarray problem
template<typename InputIt>
auto maximum_subarray_bruteforce(InputIt first, InputIt last)
  ->tuple<InputIt,InputIt,typename InputIt::value_type>
{
  InputIt left;
  InputIt right;

  using T=typename InputIt::value_type;

  T maxSum{};
  T maxSumPerRow{};

  for(InputIt i = first; i != last; ++i)
  {
    maxSumPerRow = T{};
    for(InputIt j = i; j != last; ++j)
    {
      maxSumPerRow+= *j;
      if(maxSumPerRow > maxSum)
      {
        maxSum = maxSumPerRow;
        left = i;
        right= j+1;
      }
    }
  }
  return {left,right,maxSum};
}

template<typename InputIt>
auto find_max_crossing_subarray(InputIt low, InputIt mid, 
                                InputIt high)
  ->tuple<InputIt,InputIt,typename InputIt::value_type>
{

  using RIter = reverse_iterator<InputIt>;
  RIter rmid{mid};
  RIter rlow{low};

  auto leftSum = 
    numeric_limits<typename InputIt::value_type>::lowest();

  InputIt leftIndex;

  auto sum = typename InputIt::value_type{};
  for(;rmid != rlow; ++rmid)
  {
    sum+=*rmid;
    if(sum > leftSum)
    {
      leftSum = sum;
      leftIndex = prev(rmid.base());
    }
  }

  sum = typename InputIt::value_type{};
  auto rightSum = 
    numeric_limits<typename InputIt::value_type>::lowest();
  InputIt rightIndex;
  for(InputIt it = mid; it != high; ++it)
  {
    sum+=*it;
    if(sum > rightSum)
    {
      rightSum = sum;
      rightIndex = next(it);
    }
  }
  return {leftIndex,rightIndex,leftSum+rightSum};
}

template<typename InputIt>
auto find_maximum_subarray(InputIt lowIt, InputIt highIt)
  -> tuple<InputIt,InputIt,typename InputIt::value_type>
{
  if(highIt==lowIt)
  {
    cout << "highIt==lowIt" << endl;
    exit(0);
  }
  else if(distance(lowIt,highIt) == 1)
  {
    return {lowIt, highIt,*lowIt};
  }
  else
  {
    auto midIt = lowIt;
    advance(midIt,distance(lowIt,highIt)/2);

    auto[leftLowIt,leftHighIt,leftSum]=
      find_maximum_subarray(lowIt,midIt);
    auto[rightLowIt,rightHighIt,rightSum]=
      find_maximum_subarray(midIt,highIt);
    auto[crossLowIt,crossHighIt,crossSum]=
      find_max_crossing_subarray(lowIt,midIt,highIt);

    if(leftSum >= rightSum && leftSum >= crossSum)
    {
      return {leftLowIt,leftHighIt,leftSum};
    }
    else if(rightSum >= leftSum && rightSum >= crossSum)
    {
      return {rightLowIt, rightHighIt, rightSum};
    }
    else
    {
      return {crossLowIt,crossHighIt,crossSum};
    }
  }
}

  template<typename InputIt>
auto find_maximum_subarray2(InputIt lowIt, InputIt highIt)
  -> tuple<InputIt,InputIt,typename InputIt::value_type>
{
  if(highIt==lowIt)
  {
    cout << "highIt==lowIt" << endl;
    exit(0);
  }
  else if(distance(lowIt,highIt) <= 128)
  {
    return maximum_subarray_bruteforce(lowIt,highIt);
  }
  else
  {
    auto midIt = lowIt;
    advance(midIt,distance(lowIt,highIt)/2);

    auto[leftLowIt,leftHighIt,leftSum]=
      find_maximum_subarray2(lowIt,midIt);
    auto[rightLowIt,rightHighIt,rightSum]=
      find_maximum_subarray2(midIt,highIt);
    auto[crossLowIt,crossHighIt,crossSum]=
      find_max_crossing_subarray(lowIt,midIt,highIt);

    if(leftSum >= rightSum && leftSum >= crossSum)
    {
      return {leftLowIt,leftHighIt,leftSum};
    }
    else if(rightSum >= leftSum && rightSum >= crossSum)
    {
      return {rightLowIt, rightHighIt, rightSum};
    }
    else
    {
      return {crossLowIt,crossHighIt,crossSum};
    }
  }
}



template<typename InputIt>
auto maximum_subarray_linear(InputIt lowIt, InputIt highIt)
  ->tuple<InputIt, InputIt, typename InputIt::value_type>
{
  // max value found
  typename InputIt::value_type max_val = 
    numeric_limits<typename InputIt::value_type>::lowest();
  // max value found per i
  typename InputIt::value_type max_val_i = 
    numeric_limits<typename InputIt::value_type>::lowest();

  // range to return.
  InputIt lowItMax = lowIt;
  InputIt highItMax = next(lowIt);

  for(InputIt it = lowIt; it != highIt; ++it)
  {
    //max_val_i = max(*it,max_val_i + *it);
    // Need to split up max into if-else to update the lowItMax,
    // This part determines the LHS iterator
    if(*it > (max_val_i+ *it))
    {
      max_val_i = *it;
      lowItMax = it;
    }
    else
    {
      max_val_i += *it;
    }

    // max_val = max(max_val,max_val_i);
    // Similar to the above, but it determines the RHS iterator, highItMax.
    if(max_val_i > max_val)
    {
      max_val = max_val_i;
      highItMax = next(it);
    }
    else
    {
      max_val = max_val;
    }
  }

  cout << "Hello from maximum_sub"<<endl;

  return {lowItMax,highItMax,max_val};
}

auto main(int , char* argv[])->int
{
//  //              begin       mid       end
//  //                0  1 2  3  4 5 6  7  8
//  vector<double> v{-2,-3,4,-1,-2,1,5,-3,-4};

  // Will be used to obtain a seed for the random number engine
//  random_device rd; 

  // Standard mersenne_twister_engine seeded with rd{}
//  std::mt19937 gen{rd()};
  std::mt19937 gen{};
  std::uniform_real_distribution<> dis(-30, 30);

  auto iss = istringstream{argv[1]};
  auto vsize=size_t{};
  iss >> vsize;
  auto v = vector<double>(vsize);
  do{
    generate(v.begin(),v.end(),[&]()
                               {
                                 return dis(gen);
                               });
  }while(all_of(v.begin(),v.end(),[](auto i){return i < 0;}) ||
         all_of(v.begin(),v.end(),[](auto i){return i > 0;}));

  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////

//  {
//    auto starttime1 = steady_clock::now();
//
//    auto[low1,high1,sum1] = 
//      maximum_subarray_bruteforce(v.cbegin(),v.cend());
//    auto endtime1 = steady_clock::now();
//    auto diff1 = endtime1 - starttime1;
//    cout << "Brute force: " 
//         << duration<double, std::milli> (diff1).count() << " ms" << endl;
////    cout << "i = " << distance(v.cbegin(),low1) << ", "
////         << "j = " << distance(v.cbegin(),high1) << ", "
////         << "sum: " << sum1 << endl;
//  }
//  {
//    auto starttime1 = steady_clock::now();
//    auto[low1,high1,sum1] = 
//      find_maximum_subarray(v.cbegin(),v.cend());
//    auto endtime1 = steady_clock::now();
//    auto diff1 = endtime1 - starttime1;
//    cout << "Divide: " 
//         << duration<double, std::milli> (diff1).count() << " ms" << endl;
////    cout << "i = " << distance(v.cbegin(),low1) << ", "
////         << "j = " << distance(v.cbegin(),high1) << ", "
////         << "sum: " << sum1 << endl;
//  }
//
  {
    auto starttime1 = steady_clock::now();
    auto[low1,high1,sum1] = 
      find_maximum_subarray2(v.cbegin(),v.cend());
    auto endtime1 = steady_clock::now();
    auto diff1 = endtime1 - starttime1;
    cout << "Divide2: " 
         << duration<double, std::milli> (diff1).count() << " ms" << endl;
    cout << "i = " << distance(v.cbegin(),low1) << ", "
         << "j = " << distance(v.cbegin(),high1) << ", "
         << "sum: " << sum1 << endl;
  }

  {
    auto starttime1 = steady_clock::now();
    auto[low1,high1,sum1] = 
      maximum_subarray_linear(v.cbegin(),v.cend());
    auto endtime1 = steady_clock::now();
    auto diff1 = endtime1 - starttime1;
    cout << "linear: " 
         << duration<double, std::milli> (diff1).count() << " ms" << endl;
    cout << "i = " << distance(v.cbegin(),low1) << ", "
         << "j = " << distance(v.cbegin(),high1) << ", "
         << "sum: " << sum1 << endl;
  }



  return 0;
}
