// pq.h implements minimum priority queue of of generic type K
//
// Author: Thanh Doan

#include <cassert>
#include <stdexcept>
#include <vector>

using namespace std;

// Class implements minimum priority queue of of generic type K
//
template <class K> class MinPq {
public:
  // Construct an empty minimum priority queue.
  //
  MinPq() : n(0) {

    // Start storing from keys[1]
    // so filling in keys[0] with sentinel default value.
    //
    K defaultValue;
    keys = vector<K>(1, defaultValue);
  }

  // DTOR to clean up heap memory
  //
  ~MinPq() {}

  // Returns true if queue is empty
  //
  bool IsEmpty() { return n == 0; }

  // Returns size of the queue
  //
  int Size() { return n; }

  // Return the minimum element without removing it.
  //
  K Min() {
    if (n < 1)
      throw runtime_error("MinPq is empty");
    return keys[1];
  }

  // Remove and return the minimum key.
  //
  K RemoveMin() {
    if (n < 1)
      throw runtime_error("MinPq is empty");
    K min = keys[1];
    Swap(1, n--);
    keys.pop_back();

    // Fix the array to keep binary heap invariant.
    HeapifyDown(1);

    return min;
  }

  // Insert key into the queue.
  //
  void Insert(K key) {
    keys.push_back(key);
    ++n;
    HeapifyUp(n);
  }

private:
  // Vector of pointers pointing to objects of type K.
  //
  vector<K> keys;

  // Size of the queue.
  //
  int n;

  // Fix the order of keys so that it is a binary heap.
  //
  void HeapifyUp(int k) {
    while (k > 1 && keys[k / 2] > keys[k]) {
      Swap(k / 2, k);
      k = k / 2;
    }
  }

  // Fix the order of keys so that it is a binary heap.
  //
  void HeapifyDown(int k) {
    while (2 * k <= n) {
      int j = 2 * k;
      if (j < n && keys[j] > keys[j + 1]) {
        j = j + 1;
      }

      if (keys[k] < keys[j])
        return;
      Swap(k, j);
      k = j;
    }
  }

  // Swap keys[i] with keys[j]
  void Swap(int i, int j) {
    if (i == j)
      return;
    auto temp = keys[i];
    keys[i] = keys[j];
    keys[j] = temp;
  }
};
