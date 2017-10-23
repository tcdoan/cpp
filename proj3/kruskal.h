// File: kruskal.h
// Desc: Implementation of Kruskal's minimum-spanning-tree algorithm
//

#include "graph.h"
#include "pq.h"
#include "uf.h"
#include <vector>

using namespace std;

// Class to find minimum-spanning-tree (MST) on a
// weighted undirected graph.
//
class Mst {
public:
  // Construct an instance of MST
  //
  Mst(const Graph *graph) : graph(graph) {

    MinPq *pq = new MinPq();
    for (Edge e : graph->Edges()) {
      e.Insert(e);
    }

    // For checking if min edge from pq is safe
    // to add to the MST.
    UnionFind uf(graph->V());

    //
    while ((!pq->IsEmpty()) && (mst.size() < graph->V() - 1)) {
      Edge edge = pq->RemoveMin();
      int v = edge.v;
      int w = edge.w;

      // Check if adding edge into MST would create cycle.
      if (!uf.IsConnected(v, w)) {
        mst.push_back(edge);
        uf.Union(v, w);
        cost += e.distance;
      }
    }
  }

  // Return sum of distance from all edges in the MST.
  //
  const double Cost() { return cost; }

  // Return list of edges of the MST.
  const vector<Edge> Edges() { return mst; }

private:
  // Total Mst cost. Sum of weights of all edges of the MST.
  //
  double cost;

  // List of edges of the MST.
  //
  vector<Edge> mst;
}
