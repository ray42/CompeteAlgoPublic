/*
 * =========================================================================
 * Copyright (c) 2018, Raymon White - All Rights Reserved
 * Author:  Raymon White (ray), rayaxiom42 AT gmail DOT com
 * =========================================================================
 */

// NOTE: I need to properly understand find and union algorithms first.
// After that, Kruskal's algorithm is easy.
//https://www.geeksforgeeks.org/?p=26604
/* 
What is Minimum Spanning Tree?
Given a connected and undirected graph, a spanning tree of that graph is a 
*subgraph* that is a *tree* and *connects all the vertices together*. 
A single graph can have many different spanning trees. A minimum spanning 
tree (MST) or minimum weight spanning tree for a weighted, connected and 
undirected graph is a spanning tree with weight less than or equal to the 
weight of every other spanning tree. The weight of a spanning tree is the 
sum of weights given to each edge of the spanning tree.

How many edges does a minimum spanning tree has?
A minimum spanning tree has (V – 1) edges where V is the number of vertices 
in the given graph.

What are the applications of Minimum Spanning Tree?
See this for applications of MST.

Below are the steps for finding MST using Kruskal's algorithm

1. Sort all the edges in non-decreasing order of their weight.
2. Pick the smallest edge. Check if it forms a cycle with the spanning tree
   formed so far. If cycle is not formed, include this edge. Else, discard 
   it.
3. Repeat step#2 until there are (V-1) edges in the spanning tree.
*/



#include<iostream>
using std::cout; using std::endl;


int main()
{
  return 0;
}

