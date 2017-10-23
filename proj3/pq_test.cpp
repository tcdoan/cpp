#include "graph.h"
#include "pq.h"
#include <iostream>

using namespace std;

int main()
{  
  Edge sam_red(0, 1, 15);
  Edge bel_red(1, 2, 10);
  Edge bel_sea(2, 3, 15);
  Edge red_sea(1, 3, 20);
  Edge sam_iss(0, 4, 15);
  Edge iss_sea(4, 3, 20);
  
  MinPq<Edge> q;

  cout << "Adding sam_red: " << endl;  
  q.Insert(sam_red);
  
  Edge e = q.Min();
  cout << "extecting sam_red: " << e << endl;

  cout << "Remove sam_red: " << endl;  
  q.RemoveMin();  

  cout << "Adding red_rea, sam_iss, iss_sea: " << endl;
  q.Insert(red_sea);
  q.Insert(sam_iss);
  q.Insert(iss_sea);

  e = q.RemoveMin();
  cout << "expecting (0, 4, 15) " << e << endl;

  e = q.RemoveMin();
  cout << "expecting (x, y, 20) " << e << endl;

 e = q.RemoveMin();
 cout << "expecting (x, y, 20) " << e << endl;
}
