// This file implements main client program main.cpp
//
// The main function creates 2 random graphs.
//
// graph1 has 50 vertices is a random graph
// with density 0.2 and distance range [1.0, 10.0)
//
// graph2 has 50 vertices is a random graph
// with density 0.4 and distance range [1.0, 10.0)
//
// Author: Thanh Doan

#include "graph.h"
#include "priority_queue.h"
#include "shortest_path.h"
#include <iostream>
#include <list>

using namespace std;

// Compute average path length for
// 0 -> 1, 0 -> 2,..., 0 -> V-1 paths
double average_path_len(Graph *g) {
  ShortestPath sp(g, 0);
  double dist_sum = 0.0;
  for (int v = 1; v < g->V(); v++) {
    dist_sum += sp.DistanceTo(v);
  }
  return dist_sum / (g->V() - 1);
}

int main(void) {
  // graph1 has 50 vertices is a random graph
  // with density 0.2 and distance range [1.0, 10.0)
  Graph g1(50, 0.2, 1.0, 10.0);

  cout<< "Graph 1 " << endl;
  cout<< "  Nodes: " << g1.V() << endl;
  cout<< "  Density: 0.2" << endl;
  cout<< "  Edge distance: random between 1.0 to 10.0" << endl;
  cout<< "  Average path length: " << average_path_len(&g1) << endl;
  
  cout<< endl;
  
  // graph2 has 50 vertices is a random graph
  // with density 0.4 and distance range [1.0, 10.0)
  Graph g2(50, 0.4, 1.0, 10.0);
  cout<< "Graph 2 " << endl;
  cout<< "  Nodes: " << g2.V() << endl;
  cout<< "  Density: 0.4" << endl;
  cout<< "  Edge distance: random between 1.0 to 10.0" << endl;
  cout<< "  Average path length: " << average_path_len(&g2) << endl;
}
