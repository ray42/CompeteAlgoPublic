/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// https://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm
/*
Given a graph and a source vertex in graph, find shortest paths from source 
to all vertices in the given graph.

Dijkstra's algorithm is very similar to Prim's algorithm for minimum 
spanning tree. Like Prim's MST, we generate a SPT (shortest path tree) with
given source as root. We maintain two sets, one set contains vertices 
included in shortest path tree, other set includes vertices not yet included
in shortest path tree. At every step of the algorithm, we find a vertex 
which is in the other set (set of not yet included) and has minimum distance
from source.

Below are the detailed steps used in Dijkstra's algorithm to find the 
shortest path from a single source vertex to all other vertices in the given
graph.
Algorithm
1) Create a set sptSet (shortest path tree set) that keeps track of vertices
   included in shortest path tree, i.e., whose minimum distance from source
   is calculated and finalized. Initially, this set is empty.
2) Assign a distance value to all vertices in the input graph. Initialize
   all distance values as INFINITE. Assign distance value as 0 for the 
   source vertex so that it is picked first.
3) While sptSet doesn't include all vertices
  a) Pick a vertex u which is not there in sptSetand has minimum distance 
  value.
  b) Include u to sptSet.
  c) Update distance value of all adjacent vertices of u. To update the 
     distance values, iterate through all adjacent vertices. For every 
     adjacent vertex v, if sum of distance value of u (from source) and 
     weight of edge u-v, is less than the distance value of v, then update
     the distance value of v.

Let us understand with the following example:

*/

#include<iostream>
using std::cout; using std::endl;
#include<vector>
using std::vector;
#include<limits>
#include<cstddef> // size_t
#include<climits> // INT_MAX

// How to implement the above algorithm?
// We use a bool array sptSet[V] to represent the set of vertices included
// in SPT. If a value sptSet[v] is true, then vertex v is included in the 
// SPT, otherwise not. Array dist[V] is used to store the shortest distance
// of all vertices.


// A C++ program for Dijkstra's single source shortest path algorithm. The
// program is for adjacency matrix representation of the graph. (This gives
// O(V^2), binary heap gives O(ElogV), fib heap gives O(E+VlogV)).

// number of vertices in the graph.
#define V 9

// A utility function to find the vertex with minimum distance value from
// the set of vertices not yet included in shortest path tree.
int minDistance(const vector<int>& dist, const vector<bool>& sptSet)
{
  int min = std::numeric_limits<int>::max();
  int min_index{};
  for(size_t i = 0; i < dist.size(); ++i)
  {
    if(sptSet[i]==false && dist[i] < min)
    {
      min = dist[i];
      min_index = i;
    }
  }
  return min_index;
}

// A utility function to print the constructed distance array
void printSolution(const vector<int>& dist)
{
  cout << "Vertex Distance from Source\n";
  for(size_t i = 0; i < dist.size(); ++i)
  {
    cout << i << ", " << dist[i] << '\n';
  }
}

template<typename T>
using Graph = vector<vector<T>>;
// Function that implements Dijkstra's single source shortest path algo
// for a graph represented using adjacency matrix representation
void dijkstra(const Graph<int>& graph, int src)
{
  // the output array. dist[i] will hold the shortest distance from src to i
  vector<int> dist(V,std::numeric_limits<int>::max());
  // sptSet[i] is true if vertex i is included in the shortest path tree or
  // shortest distance from src to i is finalized (if it's not finalized,
  // dist[i] may still be updated, since it cannot be in the SPT yet, since
  // it may get smaller!)
  vector<bool> sptSet(V,false);

  // Start off the iteration, distance of source vertex from itself is 
  // always 0.
  dist[src] = 0;

  // find the shortest path for all vertices
  for(size_t v = 0; v < V; ++v)
  {
    // Pick the minimum distance vertex from the set of vertices not yet
    // processed. u is always equal to src in first iteration.
    int u = minDistance(dist,sptSet);

    // Mark the picked vertex as processed
    sptSet[u] = true;

    // Update dist value of adjacent vertices of the picked vertex.
    // We loop through all nodes and determine if
    // it is not in sptSet: !sptSet[v]
    // there is an edge from u to v: graph[u][v]>0,
    // and the total weight of path from src to v through u is smaller than
    // current value of dist[v]
    if(!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                 && dist[u]+graph[u][v]<dist[v])
    {
      dist[v] = dist[u]+graph[u][v];
    }
  }
  
  // print the constructed distance array
  printSolution(dist);
}

int main()
{
  Graph<int> graph = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 14, 10, 0, 2, 0, 0},
                      {0, 0, 0, 0, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}};

  dijkstra(graph,0);
  return 0;
}

