/*
 * =========================================================================
 * Copyright (c) 2017, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;
#include<string>
using std::string;

#include<vector>
using std::vector;


template<typename T>
using Grid2d = vector<vector<T>>;

// function to output a vector
template<typename T>
void printVec(vector<T>& v, const string& str="")
{
  if(!str.empty()) cout << str;
  for(const auto& val:v)
    cout << val << " ";
  cout << '\n';
}

// a color m_index is legal for nodei is no other node in graph[nodei] has
// the same color
bool isLegal(const int nodei, const int m_index, 
             const Grid2d<int>& graph, const vector<int>& color)
{
  // Loop through the nodes, if they are adjacent to node i, check if
  // it has been assigned a color the same as color[m_index]
  for(size_t i = 0; i < graph.size(); ++i)
    if(graph[nodei][i] && (m_index==color[i]))
      return false;
  
  return true;
}

bool solveMColor(const Grid2d<int>& graph, const int m, const int nodei, 
                  vector<int>& color)
{
  // base case is when we have coloured all the nodes, i.e.
  // when nodei = color.size()
  if(nodei == color.size())
    return true;

  // For this node, loop through the colors, backtrack is necessary 
  // (breadth-first).
  // Recursively call solveMColor for node+1 (depth-first)
  for(int m_index = 1; m_index <= m; m_index++)
  {
    if(isLegal(nodei, m_index, graph, color))
    {
      color[nodei] = m_index;
      if(solveMColor(graph, m, nodei+1, color))
        return true;

      // backtrack
      color[nodei] = 0;
    }
  }

  return false;
}

void runSolveMColor()
{
  Grid2d<int> grid{{0,1,1,1},
                   {1,0,1,0},
                   {1,1,0,1},
                   {1,0,1,0}};

  int m = 3;
  vector<int> color(grid.size(),0);

  if(solveMColor(grid, m, 0, color))
    printVec(color,"Solution is:\n");
  else
    cout << "No sol" << '\n';
}

int main()
{
  runSolveMColor();
  return 0;
}

