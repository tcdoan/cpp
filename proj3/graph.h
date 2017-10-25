// File: graph.qh
// Desc: Defines and implement weighted undirected graph ADT
//       Here we use the adjacency list to represent the
//       graph data structure internally.
//
// Author: Thanh Doan
//

#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using namespace std;

// Class to implement undirected weighted edge.
class Edge {
public:
  int v;
  int w;
  double distance;

  // Construct an edge with vertices and weight.
  // Default constructor creates "empty" edge denoted with
  // sentinel (-1, -1, -1) values.
  //
  Edge(int v = -1, int w = -1, double weight = -1.0)
      : v(v), w(w), distance(weight) {}

  // Copy constructor
  Edge operator=(Edge other) {
    v = other.v;
    w = other.w;
    distance = other.distance;
    return *this;
  }
};

// In undirected graph, edge(v, w) is edge(w, v)
bool operator==(const Edge &e1, const Edge &e2) {
  return (e1.v == e2.v && e1.w == e2.w) || (e1.v == e2.w && e1.w == e2.v);
}

bool operator>(const Edge &e1, const Edge &e2) {
  return e1.distance > e2.distance;
}

bool operator<(const Edge &e1, const Edge &e2) {
  return e1.distance < e2.distance;
}

// Implement the output operator for Edge class
ostream &operator<<(ostream &os, const Edge &edge) {
  os << " ( " << edge.v << ":" << edge.w << ", " << edge.distance << " ) ";
  return os;
}

// Graph class represents weighted undirected graph data type.
// Here we use edge lists, aka adjacency lists, to represent the
// graph data structure internally.
class Graph {
public:
  // Construct a graph with number of vertices as parameter.
  //
  Graph(int vertices) : vertices(vertices), edges(0) { Init(); }

  // Construct a Graph from a file given its filename.
  // Format for file:
  //  1. First line : the number of vertices
  //  2. Each line after the first is a triplet
  //     (v, w, d) are ertices (v, w) of an edge
  //     and d is the edge distance.
  //
  Graph(string file_name) {

    ifstream data_file(file_name);
    istream_iterator<double> start(data_file), eos;
    vector<double> input(start, eos);

    vertices = static_cast<int>(input[0]);

    Init();

    // Read tiplet (v, w, dist) from input vector, starting from input[0]
    for (unsigned int i = 1; i < input.size() - 2; i += 3) {
      int v = static_cast<int>(input[i]);
      int w = static_cast<int>(input[i + 1]);
      Edge edge(v, w, input[i + 2]);
      AddEdge(edge);
    }
  }

  // Deallocate heap memory pointed by adj
  //
  ~Graph() {}

  // return number of vertices
  int V() const { return vertices; }

  // return number of the vertices
  int E() const { return edges; }

  // Add an edge from vertex v to w
  void AddEdge(Edge edge) {
    // We assume positive cost
    if (edge.distance <= 0)
      throw runtime_error("Edge distance must be positive");

    if (IsEdgeExisted(edge.v, edge.w) == false) {
      adj[edge.v].push_back(edge);

      // undirected graph, so edge(w, v) = edge(v, w)
      Edge wv(edge.w, edge.v, edge.distance);
      adj[edge.w].push_back(wv);
      ++edges;
    }
  }

  // Return all edges adj to vertex v.
  //
  vector<Edge> AdjList(int v) { return adj[v]; }

  // Return all edges of the graph
  //
  vector<Edge> Edges() {    
    vector<Edge> list;
    for (auto v : adj) {
      for (Edge e : v) {
        list.push_back(e);
      }
    }
    return list;
  }

private:
  // Number of vertices
  int vertices;

  // Number of edges;
  int edges;

  // Graph adjacency list;
  vector<vector<Edge>> adj;

  // Initialize the adj list.
  void Init() {
    adj = vector<vector<Edge>>(vertices);
    // For each node v store a vector of edges from that vertex
    for (int v = 0; v < vertices; ++v) {
      adj[v] = vector<Edge>();
    }
  }

  // Return true if exists edge from v to w
  bool IsEdgeExisted(int v, int w) {
    for (const Edge &e : adj[v]) {
      if (e.w == w) {
        return true;
      }
    }
    return false;
  }
};

// Implement the output operator for Graph ADT.
//
ostream &operator<<(ostream &os, Graph &g) {
  for (int x = 0; x < g.V(); x++) {
    os << x << ": ";
    for (auto& edge : g.AdjList(x)) {
      os << edge;
    }
    os << endl;
  }
  return os;
}
