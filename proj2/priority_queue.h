// Header defining and implement PriorityQueue ADT
// This class is not thread-safe.
// Author: Thanh Doan

// Generic class represents min priority queue with
// meta element type T and assuming T has implemented
// operator>
#include <stdexcept>

template<class T>
class MinPq
{
 public:

  // Construct an empty priority queue 
  MinPq() : capacity(1), n(0)
  {
    pq = new T[capacity];
  }

  // construct empty queue with initial capacity.
  MinPq(int capacity) : capacity(capacity), n(0)
  {
    pq = new T[capacity];
  }


  // Class destructor to deallocate memory
  // that was allocated by the constructor.
  ~MinPq()
  {
    delete [] pq;
  }

  bool IsEmpty()
  {
    return n == 0;
  }

  int  Size()
  {
    return n;
  }

  T Top()
  {
    return pq[1];  
  }

  // add new element to the queue
  void Insert(T x)
  {
    if (this->Size() == this->capacity-1)
    {
      resize(2 * this->capacity);
    }

    pq[++n] = x;
    fix_up(n);   
  }

  // remove the minimum (the top) element
  T RemoveTop()
  {
    if (this->IsEmpty())
    {
      throw std::runtime_error("MinPq is empty"); 
    }

    T min = pq[1];
    swap(1, n--);
    fix_down(1);

    if ( (n > 0) && (n == (capacity -1) / 4) )
    {
      resize(capacity / 2);
    }
    return min;
  }
    
 private:

  // point to an array of elements
  T* pq;

  // capacity of the queue
  int capacity;
  
  // size of the array 
  int n;

  // swap pq[i], pq[j]
  void swap(int i, int j)
  {
    auto temp = pq[i];
    pq[i] = pq[j];
    pq[j] = temp;
  }

  // swim to fix binary heap from element k up to root
  // to ensure binary heap invariant
  void fix_up(int k)
  {
    while (k > 1 && pq[k/2] > pq[k])
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
	if (j < n && pq[j] > pq[j+1]) j++;
	if (pq[k] <= pq[j]) break;
	swap(k, j);
	k = j;
      }
  }

  void resize(int capacity)
  {
    this->capacity = capacity;
    T* temp = new T[capacity];
    for (int i = 1; i <=n; i++)
    {
	temp[i] = pq[i];      
    }
    pq = temp;
  }
};
  
