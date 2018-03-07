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
#include<algorithm>
using std::nth_element;

// https://leetcode.com/problems/median-of-two-sorted-arrays/description/
// There are two sorted arrays nums1 and nums2 of size m and n respectively.
//
// Find the median of the two sorted arrays. The overall run time complexity
// should be O(log (m+n)).
//
// Example 1:
// nums1 = [1, 3]
// nums2 = [2]
// 
// The median is 2.0
// Example 2:
// nums1 = [1, 2]
// nums2 = [3, 4]
//
// The median is (2 + 3)/2 = 2.5


// odd:  0,1,2,3,4, middle = 2 = size/2
// even: 0,1,2,3,   middle = 1 =, 

class Solution {
public:
  double findMedianSortedArrays(vector<int> nums1, vector<int> nums2)
  {
    nums1.insert(nums1.end(), nums2.begin(), nums2.end());
    auto nums1size = nums1.size();
    if(nums1size % 2 == 0)
    {
      nth_element(nums1.begin(),nums1.begin()+nums1size/2-1,nums1.end());
      auto i = nums1[nums1size/2-1];

      nth_element(nums1.begin(),nums1.begin()+nums1size/2,nums1.end());
      auto j = nums1[nums1size/2];
      return (i + j)/2.0;
    }
    else
    {
      nth_element(nums1.begin(),nums1.begin()+nums1size/2,nums1.end());
      return nums1[nums1size/2];
    }
  }
};

int main()
{
  cout << Solution{}.findMedianSortedArrays({1,3},{2})<<'\n';
  cout << Solution{}.findMedianSortedArrays({1,2},{3,4})<<'\n';
  cout << Solution{}.findMedianSortedArrays({1,2,3},{1,2,2})<<'\n';

  return 0;
}

