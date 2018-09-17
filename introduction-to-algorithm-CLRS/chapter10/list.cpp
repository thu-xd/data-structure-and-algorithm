#include <iostream>
//This is an simple implementation of double-linked list.
//
template<typename T>
struct Node
{
  T val;
  Node * prev;
  Node * next;
  Node(T _val=T(),Node * _prev=nullptr, Node * _next=nullptr)
    :val(_val),prev(_prev),next(_next){};
};

template <typename T>
class list
{
  private:
    Node<T> * header, * tailer;  //This was two sentinel node in the list.
    int _size;
    void init();
  public:
    list();
    list(int n, const T & e=T());
    template<typename InputIterator>  list(InputIterator first,InputIterator last);
    list(const list<T> & l);
    ~list();
    Node<T> * begin() const {return header->next;};
    Node<T> * end()const {return tailer;};
    Node<T> * insert(Node<T> * pos, const T & e);
    Node<T> * erase(Node<T> * pos);
    void push_front(const T & e);
    void pop_front();
    void push_back(const T & e);
    void pop_back();
    void clear();
    void operator=(const list<T> & l);
    bool empty()const {return !_size;};
    int size() const{return _size;};
    T & front(){return begin()->val;};
    T & back(){return end()->val;};
};

template<typename T>
void list<T>::init()
{
  header=new Node<T>;
  tailer=new Node<T>;
  header->next=tailer;
  tailer->prev=header;
  _size=0;
}

template<typename T>
list<T>::list()
{
  init();
}

template<typename T>
list<T>::list(int n,const T & e)
{
  init();
  while(n--)
    push_back(e);
}

template<typename T>
template<typename InputIterator>
list<T>::list(InputIterator first,InputIterator last)
{
  init();
  while(first!=last)
  {
    push_back(*first);
    first++;
  }
}

template<typename T>
list<T>::list(const list<T> & l)
{
  init();
  for(Node<T> * p=l.begin();p!=l.end();p=p->next)
    push_back(p->val);
}

template<typename T>
list<T>::~list()
{
  Node<T> * cursor=header;
  while(cursor)
  {
    Node<T> * tmp=cursor->next;
    delete cursor;
    cursor=tmp;
  }
}


template<typename T>
Node<T> * list<T>::insert(Node<T> * pos, const T & e)
{
  Node<T> * tmp=pos->prev;
  Node<T> * new_node=new Node<T>(e,tmp,pos);
  tmp->next=new_node;
  pos->prev=new_node;
  _size++;
  return new_node;
}

template<typename T>
void list<T>::push_front(const T & e)
{
  insert(header->next,e);
}

template<typename T>
void  list<T>::push_back(const T & e)
{
  insert(tailer,e);
}

template<typename T>
Node<T> * list<T>::erase(Node<T> * pos)
{
  Node<T> * prev=pos->prev, * next=pos->next;
  prev->next=next;
  next->prev=prev;
  delete pos;
  _size--;
  return next;
}

template<typename T>
void list<T>::pop_front()
{
  erase(header->next);
}

template<typename T>
void list<T>::pop_back()
{
  erase(tailer->prev);
}

template<typename T>
void list<T>::clear()
{
  while(!empty())
    pop_back();
}

template<typename T>
void list<T>::operator=(const list<T> & l)
{
  clear();
  Node<T> * cursor=l.begin();
  while(cursor!=l.end())
  {
    push_back(cursor->val);
    cursor=cursor->next;
  }
}

template<typename T>
std::ostream & operator<<(std::ostream & os,const list<T> & l)
{
  for(Node<T> * it=l.begin();it!=l.end();it=it->next)
    os<<it->val<<" ";
  os<<std::endl;
  return os;
}

int main ()
{
  // constructors used in the same order as described above:
  list<int> first;                                // empty list of ints
  std::cout<<"The first list: "<<first;
  first.push_back(1);
  first.push_front(2);
  std::cout<<"The first list after push_back and push_front: "<<first;
  list<int> second (4,100);                       // four ints with value 100
  std::cout<<"The second list:" <<second;
  second.pop_back();
  second.pop_front();
  std::cout<<"The second list after pop_back and pop_front: "<<second;
  list<int> third(second);
  std::cout<<"The third list: "<<third;
  third.insert(third.begin()->next,1);
  std::cout<<"The third list after insert: "<<third;
  std::cout<<"The size of the list: "<<third.size()<<std::endl;
  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  list<int> fouth (myints, myints + sizeof(myints) / sizeof(int) );
  std::cout<<fouth;
  return 0;
}
