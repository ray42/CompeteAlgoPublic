/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;

// https://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/
// https://www.geeksforgeeks.org/iterative-depth-first-traversal/

#include<vector>
using std::vector;
#include<stack>
using std::stack;

// Graph class represents a directed graph using adjacency list 
// representation
class Graph
{
  int V; // number of nodes
  vector<vector<int>> adj; // adjacency list
public:
  Graph(int v):V{v}, adj{v,vector<int>{}}
  {}

  void addEdge(const int v, const int w)
  {
    adj[v].push_back(w);
  }

  void DFSRecur(const int s);

  void DFSRecurUtil(const int s, vector<bool>& visited);

  void DFSIter(const int s);

  void DFSIterAll();


};

////////////////////////////////////////////////////////////////////////////
void Graph::DFSRecur(const int s)
{
  vector<bool> visited(V,false);
  DFSRecurUtil(s,visited);
}

void Graph::DFSRecurUtil(const int s, vector<bool>& visited)
{
  // Mark the current node as visited
  visited[s] = true;
  cout << s << ' ';

  // Recur for all the vertices adjacent to this vertex
  for(const int i:adj[s])
    if(!visited[i])
      DFSRecurUtil(i,visited);

}
////////////////////////////////////////////////////////////////////////////

// Do iterative approach.
void Graph::DFSIter(int s)
{
  vector<bool> visited(V,false);
  stack<int> sStack;

  // push in the current source node
  sStack.push(s);
  while(!sStack.empty())
  {
    s = sStack.top();
    sStack.pop();

    // Stack may contain same vertex twice. So we need to print the popped
    // item only if it is not visited
    if(!visited[s])
    {
      cout << s << ' ';
      visited[s]=true;
    }

    // Get all adjacent vertices of the popped vertex s. If a adjacent has
    // not been visited, then push it to the stack.
    for(const auto i:adj[s])
    {
      if(!visited[i])
      {
        sStack.push(i);
      }
    }
  }

}

int main()
{
  Graph g{4};
  g.addEdge(0,1);
  g.addEdge(0,2);
  g.addEdge(1,2);
  g.addEdge(2,0);
  g.addEdge(2,3);
  g.addEdge(3,3);
  cout << "DFS Recur is:\n";
  g.DFSRecur(2);
  cout << '\n';

  return 0;
}

