// This file defines and implement weighted undirected graph ADT
// Here we use edge lists, aka adjacency lists, to represent the
// graph data structure internally.

// Author: Thanh Doan

#include <iostream>
#include <random>
#include <vector>

using namespace std;

// Class to implement undirected weighted edge.
class Edge {
public:
  int v;
  int w;
  double distance;

  // default constructor creates "empty" edge denoted with
  // sentinel (-1, -1, 0) values.
  Edge() : v(-1), w(-1), distance(0) {}

  Edge(int v, int w, int weight) : v(v), w(w), distance(weight) {}
  Edge &operator=(const Edge &other) {
    v = other.v;
    w = other.w;
    distance = other.distance;
    return *this;
  }

  // return other endpoint of this edge
  // given an enpoint.
  int Other(int x) {
    if (x == v)
      return w;
    else if (x == w)
      return v;
    else
      throw runtime_error("Illegal endpoint of this edge");
  }
};

// Implement ==, >, >=, <, <= operators for Edge class
bool operator==(const Edge &e1, const Edge &e2) {
  return e1.v == e2.v && e1.w == e2.w && e1.distance == e2.distance;
}

bool operator>(const Edge &e1, const Edge &e2) {
  return e1.distance > e2.distance;
}

bool operator>=(const Edge &e1, const Edge &e2) {
  return e1.distance >= e2.distance;
}

bool operator<(const Edge &e1, const Edge &e2) {
  return e1.distance < e2.distance;
}

bool operator<=(const Edge &e1, const Edge &e2) {
  return e1.distance <= e2.distance;
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
  Graph(int vertices) : vertices(vertices), edges(0) {
    adj = new vector<Edge>[vertices];
    // For each node v store a vector of edges from that vertex
    for (int v = 0; v < vertices; ++v) {
      adj[v] = vector<Edge>();
    }
  }

  // Construct a random graph given number of vertices,
  // edge density and distance range.
  Graph(int vertices, double density, double range_low, double range_hi)
      : vertices(vertices) {

    edges = 0;
    adj = new vector<Edge>[vertices];
    // For each node v store a vector of edges from that vertex
    for (int v = 0; v < vertices; ++v) {
      adj[v] = vector<Edge>();
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    // random distibution densi is between 0.0 to 1.0
    std::uniform_real_distribution<> densi(0.0, 1.0);

    // random distibution dist is between range_low to hi
    std::uniform_real_distribution<> dist(range_low, range_hi);

    for (int v = 0; v < vertices; v++) {
      // no self loop so w = v + 1
      for (int w = v + 1; w < vertices; w++) {
        if (densi(gen) < density) {
          // Create an edge with random distance
          double distance = dist(gen);
          Edge edge(v, w, distance);
          addEdge(edge);
        }
      }
    }
  }

  // Deallocate heap memory pointed by adj
  ~Graph() { delete[] adj; }

  // return number of vertices
  int V() const { return vertices; }

  // return number of the vertices
  int E() const { return edges; }

  // Add an edge from vertex v to w
  void addEdge(Edge edge) {
    // We assume positive cost
    if (edge.distance <= 0)
      throw runtime_error("Edge distance must be positive");

    // Constructor make sure
    //    adj !=null
    //    and adj[e.v] is alreay initialized
    //    end adj[e.w] is alreay initialized
    adj[edge.v].push_back(edge);
    adj[edge.w].push_back(edge);
    ++edges;
  }

  // return all edges linking vertex v with other vertex
  const vector<Edge> &AdjList(int v) const { return adj[v]; }

private:
  const int vertices;
  int edges;
  vector<Edge> *adj;
};

// implement the output operator for Graph ADT.
ostream &operator<<(ostream &os, const Graph &g) {
  // for each vertex x
  for (int x = 0; x < g.V(); x++) {
    os << x << ": ";
    for (const Edge &edge : g.AdjList(x)) {
      os << edge;
    }
    os << endl;
  }
  return os;
}
