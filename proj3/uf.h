// File: uf.h
// Desc: Implements weighted union-find data structure.
//       The data structure will be used in Kruskal algorithm
//       to check adding a new edge into the MST would create cycle.
//
// Author: Thanh Doan
//
class UnionFind {
public:
  // Construct initial UnionFind with n connected components.
  //
  UnionFind(int n) : components(n) {

    parent = new int[n];
    weight = new int[n];

    // Initially parent and component id of node x is x.
    // Each component has weight of 1.
    //
    for (int x = 0; x < n; x++) {
      parent[x] = x;
      weight[x] = 1;
    }
  }

  ~UnionFind() {
    delete[] parent;
    delete[] weight;
  }

  // Find the id of the connected component containing node x.
  //
  int Find(int x) {
    while (x != parent[x])
      x = parent[x];
    return x;
  }

  // Union the component containing x with component containing y.
  //
  void Union(int x, int y) {
    int rootX = Find(x);
    int rootY = Find(y);

    if (rootX == rootY) {
      return;
    }

    if (weight[rootX] < weight[rootY]) {
      parent[rootX] = rootY;
      weight[rootY] += weight[rootX];
    } else {
      parent[rootY] = rootX;
      weight[rootX] += weight[rootY];
    }
    components--;
  }

  // Check if x and y belong to the same connected component.
  //
  bool IsConnected(int x, int y) { return Find(x) == Find(y); }

private:
  // Number of elements in the data structure.
  //
  int components;

  // parent[x] = id of the parent of node x.
  //
  int *parent;

  // weight[x] is the size of the connected component containing x.
  //
  int *weight;
}
