/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// https://www.geeksforgeeks.org/?p=27455
/*
We have discussed Kruskal's algorithm for Minimum Spanning Tree. Like 
Kruskal's algorithm, Prim's algorithm is also a Greedy algorithm. It starts
with an empty spanning tree. The idea is to maintain two sets of vertices.
The first set contains the vertices already included in the MST, the other
set contains the vertices not yet included. At every step, it considers all
the edges that connect the two sets, and picks the minimum weight edge from
these edges. After picking the edge, it moves the other endpoint of the edge
to the set containing MST.

A group of edges that connects two set of vertices in a graph is called cut
in graph theory. So, at every step of Prim's algorithm, we find a cut (of
two sets, one contains the vertices already included in MST and other
contains rest of the verices), pick the minimum weight edge from the cut and
include this vertex to MST Set (the set that contains already included
vertices).

How does Prim's Algorithm Work? The idea behind Prim's algorithm is simple,
a spanning tree means all vertices must be connected. So the two disjoint
subsets (discussed above) of vertices must be connected to make a Spanning
Tree. And they must be connected with the minimum weight edge to make it a
Minimum Spanning Tree.

Algorithm
1) Create a set mstSet that keeps track of vertices already included in MST.
2) Assign a key value to all vertices in the input graph. Initialize all key
   values as INFINITE. Assign key value as 0 for the first vertex so that it
   is picked first.
3) While mstSet doesn't include all vertices
  a) Pick a vertex u which is not there in mstSet and has minimum key value.
  b) Include u to mstSet.
  c) Update key value of all adjacent vertices of u. To update the key 
     values, iterate through all adjacent vertices. For every adjacent
     vertex v, if weight of edge u-v is less than the previous key value of
     v, update the key value as weight of u-v

The idea of using key values is to pick the minimum weight edge from cut.The
key values are used only for vertices which are not yet included in MST, the
key value for these vertices indicate the minimum weight edges connecting
them to the set of vertices included in MST.

Let us understand with the following example:

*Look at the example, it's pretty good*
*/

// NOTE: To update the key value of v, if the weight of u-v is LESS THAN THE
// PREVIOUS KEY VALUE OF v (it is initially INF, or it may have been 
// updated already) then update the key value of v.
//
// How to implement the above algo?
//
// We use a boolean array mstSet[V] to represent the set of vertices 
// included in the MST. If 


#include<iostream>
using std::cout; using std::endl;
int main()
{
  return 0;
}

