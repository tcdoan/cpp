
#include "graph.h"
#include "priority_queue.h"
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


  MinPq<Edge> q;

  cout << "inserting into queue " << endl;
  q.Insert(sam_red);
  q.Insert(bel_red);  
  q.Insert(iss_sea);

  Edge top = q.Top();
  cout << "min = " << top << endl;

  q.RemoveTop();
  top = q.Top();
  cout << "next min = " << top << endl;  
}
