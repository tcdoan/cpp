// This file implements dijkstra algorithm
// to compute the shortest paths
// from source vertex to all oher vertices
// on a undirected graph and allow its client to read off
// the shorest path from s to any other vertex.
//
// The class uses Graph class implemented in graph.h
// and priority queue implemented priority_queue.h
//
// This class is not thread-safe.
//
// Author: Thanh Doan

#include <cassert>
#include <iostream>
#include <limits>
#include <list>
#include <stdexcept>

using namespace std;

class ShortestPath {
public:
  // Construct shortest path given graph g and source vertex s
  ShortestPath(Graph *g, int s) : g(g), s(s) {
    dist_to = new double[g->V()];
    edge_to = new Edge[g->V()];

    // initially set distance for all pairs (s,v) = infinity
    for (int v = 0; v < g->V(); v++) {
      dist_to[v] = numeric_limits<double>::infinity();
    }
    dist_to[0] = 0.0;

    // recompute distance to vertex v
    // by relaxing vertices in order of
    // distance from s to v
    pq = new MinPq<double>(g->V());
    pq->Insert(s, dist_to[s]);

    while (!pq->IsEmpty()) {
      int v = pq->RemoveMin();
      for (Edge e : g->AdjList(v)) {
        relax(e, v);
      }
    }
  }

  ~ShortestPath() {
    delete[] dist_to;
    delete[] edge_to;
    delete pq;
  }

  // Returns a shortest distance from s to v
  // if such shorest path exists.
  // Returns numeric_limits<double>::infinity()
  // if no path exists
  double DistanceTo(int v) { return dist_to[v]; }

  // Returns a shortest path from source vertex s to vertex v
  list<Edge> PathTo(int v) {
    if (!HasPathTo(v)) {
      return list<Edge>();
    }
    list<Edge> path;
    int x = v;

    Edge empty;
    for (Edge e = edge_to[v]; !(e == empty); e = edge_to[x]) {
      path.push_front(e);
      x = e.Other(x);
    }
    return path;
  }

  // Returns true if a path from source vertex s to v exists
  bool HasPathTo(int v) {
    return dist_to[v] < numeric_limits<double>::infinity();
  }

private:
  // The given weighted undirected graph g
  Graph *g;

  // The source vertex s
  int s;

  // dist_to[v] is distance of shorest path from s to v
  double *dist_to;

  // edge[v] is last edge on shortest path from s to v
  Edge *edge_to;

  // priority queue of paths from s to each vertex v
  MinPq<double> *pq;

  // Relax edge e and update pq
  void relax(Edge e, int v) {
    int w = e.Other(v);
    if (dist_to[w] > dist_to[v] + e.distance) {
      dist_to[w] = dist_to[v] + e.distance;
      edge_to[w] = e;

      if (pq->Contains(w))
        pq->DecreaseKey(w, dist_to[w]);
      else
        pq->Insert(w, dist_to[w]);
    }
  }
};
