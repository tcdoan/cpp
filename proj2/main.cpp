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
#include <limits>
#include <list>

using namespace std;

// Compute average path length for
// (s..1), (s..2),... (s..V-1) paths
double average_path_len(Graph *g, int s) {

  // compute shortest paths from source s to other vertices
  ShortestPath sp(g, s);
  double dist_sum = 0.0;

  // Number of vertices v such that exists path
  int n = 0;
  for (int v = 0; v < g->V(); v++) {
    if (s != v && sp.DistanceTo(v) < numeric_limits<double>::infinity()) {
      dist_sum += sp.DistanceTo(v);
      n++;
    }
  }
  return dist_sum / n;
}

int main(void) {
  // Construct graph g1 with 50 vertices, density 0.2
  // and random distance in range [1.0, 10.0)
  //
  Graph g1(50, 0.2, 1.0, 10.0);

  cout << "Graph 1 " << endl;
  cout << "  Nodes: " << g1.V() << endl;
  cout << "  Density: 0.2" << endl;
  cout << "  Edge distance: random between 1.0 to 10.0" << endl;
  cout << "  One run average path length: " << average_path_len(&g1, 0) << endl;

  // Since the Average path length of graph g1 is a bit random on each run
  // I'm going to run it 1000 times then compute the average of the averages
  // to the find out the converged average number.
  double sumOfAverage1 = 0.0;
  for (int i = 0; i < 1000; i++) {
    // graph i initialized with 50 vertices, 0.2 density
    // and randon distance in [1.0, 10.0] range.
    //
    Graph gi(50, 0.2, 1.0, 10.0);

    // shortest path average from source vertex 0 to ther vertices
    sumOfAverage1 += average_path_len(&gi, 0);
  }
  cout << "  1000-run average path length: " << sumOfAverage1/1000 << endl;
  
  cout << endl;

  // graph2 has 50 vertices is a random graph
  // with density 0.4 and distance range [1.0, 10.0)
  Graph g2(50, 0.4, 1.0, 10.0);
  cout << "Graph 2 " << endl;
  cout << "  Nodes: " << g2.V() << endl;
  cout << "  Density: 0.4" << endl;
  cout << "  Edge distance: random between 1.0 to 10.0" << endl;
  cout << "  One run average path length: " << average_path_len(&g2, 0) << endl;

  // Run 1000 times to compute the average of the averages
  double sumOfAverage2 = 0.0;
  for (int i = 0; i < 1000; i++) {
    // graph i initialized with 50 vertices, 0.4 density
    // and randon distance in [1.0, 10.0] range.
    //
    Graph gi(50, 0.4, 1.0, 10.0);
    sumOfAverage2 += average_path_len(&gi, 0);
  }
  cout << "  1000-run average path length: " << sumOfAverage2/1000 << endl;
}
