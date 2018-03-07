/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */
#include<iostream>
using std::cout; using std::endl;

// https://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/

#include<list>
using std::list;

#include<queue>
using std::queue;
#include<vector>
using std::vector;

// program to print BFS traversal from a GIVEN source vertex. BFS(int s) 
// traverses vertices reachable from s.

// This class represents a directed graph using adj list representation
class Graph
{
  int V; // No. of vertices

  // Pointer to an array containing adjacency lists
  // We use a vector of vectors instead.
  vector<vector<int>> adj;

public:
  // constructor
  Graph(int v):V{v}, adj{vector<vector<int>>(v,vector<int>{})}
  {}

  // function to add an edge to graph
  void addEdge(const int v, const int w)
  {
    adj[v].push_back(w); // add w to v's list
  }
  void BFS(int s);
};

void Graph::BFS(int s)
{
  // Mark all vertices as not visited.
  vector<bool> visited(V,false);

  queue<int> q;

  // mark the current node as visited and enqueue it
  visited[s] = true;
  q.push(s);

  while(!q.empty())
  {
    // dequeue, print it,
    s = q.front();
    cout << s << ' ';
    q.pop();

    // Get all adjacent vertices of the dequeued vertex s. If a adjacent has
    // not been visited, then mark it visited and enqueue
    for(const auto& i:adj[s])
    {
      if(!visited[i])
      {
        visited[i] = true;
        q.push(i);
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
  cout << "Following is BFS from vertex 2\n";
  g.BFS(2);
  cout << '\n';
  return 0;
}











