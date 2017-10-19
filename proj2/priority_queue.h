// This file defines and implements indexed PriorityQueue ADT
//
// The queue contains an array of elements of generic type Key.
// We assume Key has implemented =, ==, <, <=, >, >= operators
// that make sense for priority queue operations. 
//
// This class is not thread-safe.
// 
// Author: Thanh Doan
//

#include <stdexcept>
#include <cassert>

using namespace std;

template<class Key>
class MinPq
{
 public:

  // construct empty queue with max capacity.
  MinPq(int capacity) : maxN(capacity), n(0)
  {
    keys = new Key[maxN+1];
    pq = new int[maxN+1];
    qp = new int[maxN+1];
    for (int i = 0; i <= maxN; i++)
      {
	qp[i] = -1;
      }
  }
  

  // Class destructor to deallocate memory
  // that was allocated by the constructor.
  ~MinPq()
  {
    delete [] pq;
    delete [] qp;
    delete [] keys;
  }

  bool IsEmpty()
  {
    return n == 0;
  }

  int  Size()
  {
    return n;
  }

  Key Min()
  {
    if (n < 1) throw runtime_error("MinPq is empty");
    return keys[pq[1]];
  }

  Key MinIndex()
  {
    if (n < 1) throw runtime_error("MinPq is empty");
    return pq[1];
  }

  bool Contains(int i)
  {
    if (i < 0 || i >= maxN) throw runtime_error("Illegal index argument");
    return qp[i] != -1;
  }  
  

  // add new element x and index i to the queue
  void Insert(int i, Key x)
  {
    if (i < 0 || i >= maxN) throw runtime_error("Illegal index argument");
    if (Contains(i)) throw runtime_error("bad argument. index already in the queue");
    n++;
    qp[i] = n;
    pq[n] = i;
    
    keys[i] = x;
    
    fix_up(n);
  }

  // remove the minimum (the top) element
  int RemoveMin()
  {
    if (n < 1) throw runtime_error("MinPq is empty");

    int min = pq[1];
    swap(1, n--);    
    fix_down(1);

    assert(min == pq[n+1]);

    qp[min] = -1;
    pq[n+1] = -1;
    
    return min;
  }

  // Return key coresponding to index i
  Key KeyOf(int i)
  {
    if (i < 0 || i >= maxN) throw runtime_error("Illegal index argument");
    if (!Contains(i))
	throw runtime_error("bad argument. index not in the queue");
    else
      return keys[i];    
  }

  // Change key coresponding to index i
  void ChangeKey(int i, Key key)
  {
    if (i < 0 || i >= maxN) throw runtime_error("Illegal index argument");
    if (!Contains(i)) throw runtime_error("bad argument. index not in the queue");

    keys[i] = key;
    fix_up(qp[i]);
    fix_down(qp[i]);    
  }

  // Decrease the key associated with index i
  void DecreaseKey(int i, Key key)
  {
    if (i < 0 || i >= maxN) throw runtime_error("Illegal index argument");
    if (!Contains(i)) throw runtime_error("bad argument. index not in the queue");
    
    if (keys[i] <= key)
      throw runtime_error("Calling DecreaseKey() with given argument not strictly decrease the key");

    keys[i] = key;
    fix_up(qp[i]);
  }


  // Increase the key associated with index i
  void IncreaseKey(int i, Key key)
  {
    if (i < 0 || i >= maxN) throw runtime_error("Illegal index argument");
    if (!Contains(i)) throw runtime_error("bad argument. index not in the queue");
    
    if (keys[i] >= key)
      throw runtime_error("Calling IncreaseKey() with given argument not strictly increase the key");

    keys[i] = key;
    fix_down(qp[i]);
  }

  // Delete key associated with index i
  void Remove(int i)
  {
    if (i < 0 || i >= maxN) throw runtime_error("Illegal index argument");
    if (!Contains(i)) throw runtime_error("bad argument. index not in the queue");
    
    int index = qp[i];
    swap(index, n--);

    fix_up(index);
    fix_down(index);
    qp[i] = -1;
  }
  
  
 private:

  // point to an array of elements
  Key* keys;

  // max capacity of the queue
  int maxN;
  
  // number of queue elements
  int n;

  // binary heap with 1-based indexing
  int* pq;

  // inverse of pq. qp[pq[i]] = pq[qp[i]] = i
  int* qp;

  // swap pq[i], pq[j]
  void swap(int i, int j)
  {
    auto temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;

    qp[pq[i]] = i;
    qp[pq[j]] = j;    
  }

  bool greater(int i, int j)
  {
    return keys[pq[i]] > keys[pq[j]];
  }

  // swim to fix binary heap from element k up to root
  // to ensure binary heap invariant
  void fix_up(int k)
  {
    while (k > 1 && greater(k/2, k))
      {
	swap(k, k/2);
	k = k/2;
      }  
  }

  // fix down binary heap from element k
  void fix_down(int k)
  {
    while (2*k <= n)
      {
	int j = 2*k;
	if (j < n && greater(j, j+1)) j++;
	if (!greater(k, j)) break;
	swap(k, j);
	k = j;
      }
  }  
};
  
