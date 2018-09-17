#include <list>
#include <iostream>
using std::list;

//This is a naive implementation of queue using std::list
template<typename T>
class queue
{
  private:
    list<T> data;
  public:
    queue():data(list<T>()){};
    bool empty(){return data.empty();};
    int size(){return data.size();};
    T & front() {return data.front();};
    T & back() {return data.back();};
    void push(const T & e){data.push_back(e);};
    void pop(){data.pop_front();};
};

int main()
{
  queue<int> Q;
  Q.push(3);
  Q.push(2);
  Q.push(1);
  std::cout<<"The front was: "<<Q.front()<<std::endl;
  std::cout<<"The back was: "<<Q.back()<<std::endl;
  std::cout<<"The size of the queue was: "<<Q.size()<<std::endl;
  Q.pop();
  std::cout<<"The front after pop was: "<<Q.front()<<std::endl;
  return 0;
}
