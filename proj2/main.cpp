
#include "graph.h"
#include "priority_queue.h"
#include "shortest_path.h"
#include <list>
#include <iostream> 

using namespace std;

int main(void)
{
  Graph g(5);
  Edge sam_red(0, 1, 15);
  Edge bel_red(1, 2, 10);
  Edge bel_sea(2, 3, 15);
  Edge red_sea(1, 3, 20);
  Edge sam_iss(0, 4, 15);
  Edge iss_sea(4, 3, 20);
  g.addEdge(sam_red);
  g.addEdge(bel_red);
  g.addEdge(bel_sea);
  g.addEdge(red_sea);
  g.addEdge(sam_iss);
  g.addEdge(iss_sea);
  
  cout << "East seatle graph" << endl << g;


  MinPq<Edge> q(100);

  cout << "testing index priority queue... " << endl;
  vector<Edge> edges = {sam_red, bel_red, iss_sea};
  for (int i = 0; i < 3; i++) q.Insert(i, edges[i]);

  int min = q.RemoveMin();
  cout << "min = " << edges[min] << endl;

  min = q.RemoveMin();
  cout << "next min = " << edges[min] << endl;

  cout << "testing shorest path from sammamish to seattle... " << endl;

  ShortestPath sp(&g, 0);
  double shortestDist = sp.DistanceTo(3);
  list<Edge> path = sp.PathTo(3);
  cout << "shorst path ditance is " << shortestDist << endl;

  for (Edge e: path)
    {
      cout << e;
    }
  cout << endl;  
  
}
