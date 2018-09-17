#include <vector>
#include <list>
#include <functional>
#include <fstream>
#include <iostream>
using std::vector;
using std::list;

//This is a toy implementation of hash map using chaining to solve collision
//and using divide hash function.
//
template<typename K,typename E>
struct  Pair
{
  K key;
  E elem;
  Pair(const K _key, const E _elem):key(_key),elem(_elem){};
};

template<typename K,typename E>
class hash_map
{
  private:
    int bucket_size;  //must be a prime number.
    int _size;       // the elements in the map
    vector<list<Pair<K,E> > > data;
    double max_load_factor;
    void re_hash();
  public:
    hash_map():bucket_size(17),_size(0),max_load_factor(1.0),data(vector<list<Pair<K,E> > >(bucket_size)){};
    int size(){return _size;};
    bool empty(){return !_size;};
    void  insert(const Pair<K,E> & p);
    Pair<K,E> *  find(const K key);
    void erase(const K key);
};

template<typename K,typename E>
void hash_map<K,E>::re_hash()
{
  vector<list<Pair<K,E> > > data_backup=data;
  std::ifstream f("primes.txt");
  int prime;
  while(f>>prime)
  {
    if(prime>=bucket_size*2)
      break;
  }
  bucket_size=prime;
  data=vector<list<Pair<K,E> > >(bucket_size);
  _size=0;
  for(auto v:data_backup)
    for(auto p:v)
      insert(p);
}

template<typename K,typename E>
void  hash_map<K,E>::insert(const Pair<K,E> & p)
{
  if(double(_size)/ bucket_size>=max_load_factor)
    re_hash();
  int hash_value=std::hash<K>()(p.key)%bucket_size;
  if(!find(p.key))
  {
    data[hash_value].push_back(p);
    _size++;
  }
}

template<typename K, typename E>
Pair<K,E> * hash_map<K,E>::find(const K key)
{
  int hash_value=std::hash<K>()(key)%bucket_size;
  for(auto & p:data[hash_value])
    if(p.key==key)
      return &p;
  return nullptr;
}

template<typename K,typename E>
void hash_map<K,E>::erase(const K key)
{
  int hash_value=std::hash<K>()(key)%bucket_size;
  for(auto it=data[hash_value].begin();it!=data[hash_value].end();it++)
    if(it->key==key)
    {
      data[hash_value].erase(it);
      _size--;
      break;
    }
}


int main()
{
  hash_map<int,int> map;
  for(int i=0;i<30;i++)
    map.insert(Pair<int,int>(i,i+1));
  std::cout<<map.size()<<"\n";
  std::cout<<map.find(2)->elem<<std::endl;
  map.erase(15);
  std::cout<<map.size()<<std::endl;
}


  

