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

#include<algorithm> // std::find
using std::find;

#include<string>
using std::string;

template<typename T>
using Grid2d = vector<vector<T>>;


void printVec(const vector<int>& vec, const string& str="")
{
  if(!str.empty()) cout << str;
  for(const auto& i:vec) cout << i << " ";
  cout << '\n';
}

bool isLegal(int j, Grid2d<int>& grid, vector<int>&path, int nodei)
{
  // Check there is a path from the previous node to this node.
  // If there isn't, we cannot recur on this node, so return false.
  if(grid[path[nodei-1]][j]==0)
    return false;

  // Now see if this node j have already been included in path
  return find(path.begin(),path.end(),j) == path.end();
}

bool solHam(Grid2d<int>& grid, int nodei, vector<int>& path)
{
  // we have placed the last node. But we have to check if the last node
  // can form a path to the first node.
  if(nodei == grid.size())
  {
    // If there is a path from the last vertex to the first vertex,
    // return true
    if(grid[path[nodei-1]][path[0]]==1)
      return true;
    else
      return false;
  }

  // loop through the adjacency list of the given node
  // we can begin at j=1, since j-0 has already been included in path
  for(size_t j = 0; j < grid.size(); ++j)
  {
    if(isLegal(j,grid,path,nodei))
    {
      path[nodei] = j;
      // try go depth
      if(solHam(grid,nodei+1,path))
        return true;

      // if we can't, then backtrack and try the next node in the adjacency
      // list
      path[nodei] = -1;
    }
  }
  return false;
}

void runSolHam()
{
  int V = 5;
  /* Let us create the following graph
      (0)--(1)--(2)
       |   / \   |
       |  /   \  |
       | /     \ |
      (3)-------(4)    */
//   Grid2d<int> graph1 = {{0, 1, 0, 1, 0},
//                         {1, 0, 1, 1, 1},
//                         {0, 1, 0, 0, 1},
//                         {1, 1, 0, 0, 1},
//                         {0, 1, 1, 1, 0},
//                        };
 
   /* Let us create the following graph
      (0)--(1)--(2)
       |   / \   |
       |  /   \  |
       | /     \ |
      (3)       (4)    */
    Grid2d<int> graph1= {{0, 1, 0, 1, 0},
                      {1, 0, 1, 1, 1},
                      {0, 1, 0, 0, 1},
                      {1, 1, 0, 0, 0},
                      {0, 1, 1, 0, 0},
                     };

   vector<int>path1(V,-1);
   //path1[0]=0;
   // Print the solution
   if(solHam(graph1,0,path1))
   {
     cout << "Sol pos\n";
     printVec(path1);
   }
   else
   {
     cout << "No sol\n";
     printVec(path1);
   }
}


int main()
{
  runSolHam();
  return 0;
}

