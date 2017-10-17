// This file implements dijkstra algorithm 
// to compute the shortest paths
// from source vertex to all oher vertices
// on a undirected graph and allow its client to read off
// the shorest path and distance from s to any other vertex.
//
// The class uses Graph class implemented in graph.h 
// and priority queue implemented priority_queue.h
//
// This class is not thread-safe.
//
// Author: Thanh Doan

#include <vector>
#include <iostream>

using namespace std;

class ShortestPath
{
 public:

  // Construct shortest path given graph g and source vertex s
  ShortestPath(Graph* g, int s) : g(g), s(s)
  {
    dist_to = new double[g.V()];
    edge_to = new Edge[g.V()];

    // initially set distance for all pairs (s,v) = infinity
    for (int v = 0; v < g.V(); v++)
      {
	dist_to[v] = std::numeric_limits<double>::infinity();
      }
    dist_to[0] = 0.0;

    pq = new MinPq<Edge>(g.V());
    Edge s2s(s, s, 0.0);
    pq.Insert(s2s);

    while (!pq.IsEmpty())
      {
	Edge edge = pq.RemoveTop();
	for (Edge e : g.AdjList(edge.v))
	  {
	    relax(e, v);
	  }		
      }    
  }

  // Relax edge e and update pq
  void relax(Edge e, int v)
  {
    int w = e.w;
    if (dist_to[w] > dist_to[v] + e.distance)
      {
	dist_to[w] = dist_to[v] + e.distance;
	edge_to[w] = e;
	
      }
    
  }
  
  
  // Returns a shortest distance from s to v
  // if such shorest path exists.
  // Returns std::numeric_limits<double>::infinity()
  // if no path exists  
  double DistanceTo(int v);

  // Returns a shortest path from source vertex s to vertex v
  vector<Edge> PathTo(int v);


  // Returns true if a path from source vertex s to v exists
  bool hasPathTo(int v)
  {
    return dist_to[v] < numeric_limits<double>::infinity();
  }

 private:
  // The given weighted undirected graph g
  Graph* g;

  // The source vertex s
  int s;
  
  // dist_to[v] is distance of shorest path from s to v
  double dist_to[];

  // edge[v] is last edge on shortest path from s to v
  Edge edge_to[]; 

  // priority queue of paths from s to each vertex v
  MinPQ<Edge> pq;  
  
}
