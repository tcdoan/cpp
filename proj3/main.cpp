// File: main.cpp
// Desc: Implements main driver of the program
//
// Author: Thanh Doan

#include "kruskal.h"
// #include "graph.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

  // Read input data file from command line
  // and create an instance of the weighted graph.
  //
  string data_file = argv[1];
  Graph graph(data_file);

  // cout << "Input Graph:" << endl << graph << endl;

  // Create an instance of Mst
  // using the address of the graph object created above
  Mst mst(&graph);

  // Print out the MST and its cost.
  cout << mst;
}
