// This file defines and implement weighted undirected graph ADT
// This class is not thread-safe.
// Author: Thanh Doan

#include <vector>
#include <iostream>

using namespace std;

// Struct to hold weighted edge, namely distance. 
class Edge
{
 public:
  int v;
  int w;
  double distance;

  Edge() : v(-1), w(-1), distance(0) {}
  Edge(int v, int w, int weight) : v(v), w(w), distance(weight) {}
  Edge& operator=(const Edge& other)
  {
    v = other.v;
    w = other.w;
    distance = other.distance;
    return *this;
  }
};

bool operator> (const Edge& e1, const Edge& e2)
{
  return e1.distance > e2.distance;
}

bool operator>= (const Edge& e1, const Edge& e2)
{
  return e1.distance >= e2.distance;
}

bool operator< (const Edge& e1, const Edge& e2)
{
  return e1.distance < e2.distance;  
}

bool operator<= (const Edge& e1, const Edge& e2)
{
  return e1.distance <= e2.distance;
}

// implement the output operator for Edge.
ostream& operator<<(ostream& os, const Edge& edge)
{
  os << " ( " << edge.v << ":" << edge.w << ", " << edge.distance << " ) ";
  return os;
}

// Graph class represents weighted direrected graph
// data type. 
class Graph
{
 public:

  // Graph constructor
  // For each node v store a vector of edges from that vertix v.
  Graph(int vertices) : vertices(vertices), edges(0)
    {
      adj = new vector<Edge>[vertices];
      for (int v = 0; v < vertices;  ++v)
	{
	  adj[v] = vector<Edge>();
	}
    }

  // Deallocate heap memory pointed by adj
  ~Graph()
    {
      delete [] adj;
    }


  // return number of vertices
  int V() const 
  {
    return vertices;
  }

  // return number of the vertices
  int E() const
  {
    return edges;
  }

  // add an edge from vertex edge.v to edge.w
  // for undirected graph edge.w to edge.v is also added
  void addEdge(Edge edge)
  {
    // Constructor make sure
    //    adj !=null
    //    and adj[e.v] is alreay initialized
    //    end adj[e.w] is alreay initialized
    adj[edge.v].push_back(edge);
    adj[edge.w].push_back(edge);
    ++edges;
  }

  // return all edges linking vertex v with other vertex 
  const vector<Edge>& AdjList(int v) const
  {
    return adj[v];
  }
    
 private:
  const int vertices;
  int edges;
  vector<Edge>* adj;
};

// implement the output operator for Graph ADT. 
ostream& operator<<(ostream& os, const Graph& g)
{
  // for each vertex x
  for (int x = 0; x < g.V(); x++)
    {
      os << x << ": ";
      for (const Edge& edge : g.AdjList(x))
	{
	  os << edge;
	}
      os << endl;
    }
  return os;
}
