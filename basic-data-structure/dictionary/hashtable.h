#include "dictionary.h"
#include <cmath>

static int hashCode(int k) {return k;};

template<typename K,typename V>
struct Entry
{
  K key;
  V value;
  Entry(K k=K(),V v=V()):key(k),value(v){};
  Entry(const Entry<K,V> & e):key(e.key),value(e.value){};
  bool operator==(const Entry<K,V> & e) {return key==e.key;};
  bool operator!=(const Entry<K,V> & e) {return key!=e.key;};
};

template <typename K,typename V>
class HashTable:public Dictionary<K,V>
{
  private:
    Entry<K,V> ** ht;
    int M;
    int N;
    bool * removed;
    bool is_prime(int m);
    int minimum_prime(int c);
  protected:
    int probe4Hit(const K & k);
    int probe4Free(const K & k);
    void rehash();
  public:
    HashTable(int c=5);
    ~HashTable();
    int size() const {return N;};
    bool put(K,V);
    V * get(K);
    bool remove(K);
};

template <typename K,typename V>
bool HashTable<K,V>::is_prime(int m)
{
  int sq=std::sqrt(m);
  for(int i=2;i<=sq;i++)
    if(m%i==0)
      return false;
  return true;
}

template <typename K,typename V>
int HashTable<K,V>::minimum_prime(int c) //this function is time consuming, you can store the prime list
{                                       // in the file and select when needing.
  while(!is_prime(c++));
  return c-1;
}


template <typename K,typename V>
HashTable<K,V>::HashTable(int c)  
{
  M=minimum_prime(2*c+1);   //The load factor should smalled than 50% when using open address.
  N=0;
  ht=new Entry<K,V> *[M];
  removed=new bool[M];
  for(int i=0;i<M;i++)
  {
    ht[i]=nullptr;
    removed[i]=false;
  }
}

template <typename K, typename V>
HashTable<K,V>::~HashTable()
{
  for(int i=0;i<M;i++)
    if(ht[i])
      delete ht[i];
  delete [] removed;
  delete [] ht;
}

template <typename K, typename V>
V * HashTable<K,V>::get(K k)
{
  int r=probe4Hit(k);
  return ht[r]?&(ht[r]->value):nullptr;
}

template <typename K, typename V>
int HashTable<K,V>::probe4Hit(const K & k)
{
  int r=hashCode(k)%M;
  while((ht[r] && (k!=ht[r]->key)) || (!ht[r] && removed[r]))
    r=(r+1)%M;
  return r;
}

template <typename K, typename V>
bool HashTable<K,V>::remove(K k)
{
  int r=probe4Hit(k);
  if(!ht[r]) return false;
  delete ht[r];
  ht[r]=nullptr;
  removed[r]=true;
  N--;
  return true;
}

template <typename K, typename V>
bool HashTable<K,V>::put(K k,V v)
{
  if(ht[probe4Hit(k)]) return false;
  int r=probe4Free(k);
  ht[r]=new Entry<K,V>(k,v);
  N++;
  if(N*2>M) rehash();
  return true;
}

template <typename K, typename V>
int HashTable<K,V>::probe4Free(const K & k)
{
  int r=hashCode(k)%M;
  while(ht[r]) r=(r+1)%M;
  return r;
}

template <typename K, typename V>
void HashTable<K,V>::rehash() // just insert every entry to the new hash table;
{
  int old_capacity=M;
  Entry<K,V> ** old_ht=ht;
  M=minimum_prime(2*M);
  N=0;
  ht=new Entry<K,V> * [M];
  delete [] removed;
  removed=new bool[M];
  for(int i=0;i<M;i++)
  {
    ht[i]=nullptr;
    removed[i]=false;
  }

  for(int i=0;i<old_capacity;i++)
    if(old_ht[i])
    {
      put(old_ht[i]->key,old_ht[i]->value);
      delete old_ht[i];
    }
  delete [] old_ht;
}

