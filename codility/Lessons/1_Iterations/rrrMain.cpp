/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
// https://leetcode.com/problems/two-sum/description/

#include<unordered_map>
using std::unordered_map;
#include<vector>
using std::vector;
#include<type_traits>
using std::remove_reference;
#include<iostream>
using std::cout; using std::endl;
#include<algorithm>
using std::for_each;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target)
  {
    // Hash map to store the numbers in nums along with the index
    unordered_map
      <typename remove_reference<decltype(nums)>::type::value_type,
       decltype(target)> m;

    // We loop through the numbers in nums and calculate the complement
    // target-nums[i]. If this is in the map, we have found the values, and
    // the indices is the one in the map and i. If not, we add the pair
    // nums[i] and i to the map, and move on.
    for(decltype(nums.size()) i=0; i!=nums.size();++i)
    {
      auto complement=target-nums[i];
      auto it=m.find(complement);
      if(it!=m.end())
      {
        return 
          vector<typename remove_reference<decltype(nums)>::type::value_type>
            {it->second,static_cast<int>(i)};
      }
      else
      {
        m.emplace(nums[i],i);
      }
    }
    return vector<int>{};
  }// end twofum
};

auto main(int, char* [])->int
{
  Solution s;

  vector<int>nums{2,7,11,15};
  decltype(nums)::value_type target=9;

  auto v=s.twoSum(nums,target);

  for_each(v.begin(),v.end(),[](const auto& c){
      cout << c << " ";
      });
  cout << endl;
}
