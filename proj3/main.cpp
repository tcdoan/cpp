#include "graph.h"
#include "pq.h"
#include <iostream>

using namespace std;

int main() {
  Graph graph("tinyEWG.txt");
  cout << "Graph : " << endl;
  cout << graph << endl;
}
