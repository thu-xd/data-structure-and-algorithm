#include "../list/List.h"
template <typename T>
class Queue:public List<T>
{
  public:
    void enqueue(T const & e){this->insertAsLast(e);}; // the new data was added to the tail of the queue.
    T dequeue(){return this->remove(this->first());};
    T & front(){return this->first()->data;};
};

