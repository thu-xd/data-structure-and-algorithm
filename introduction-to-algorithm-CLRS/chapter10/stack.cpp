#include <vector>
using std::vector;


//This is a naive implementation of LIFO stack using std::vector
template<typename T>
class stack
{
  private:
    vector<T> data;
  public:
    stack():data(vector<T>()){};
    bool empty(){return data.empty();};
    int size(){return data.size();};
    T & top(){return data.back();};
    void push(T & e){data.push_back(e);};
    void pop(){data.pop_back();};
};
