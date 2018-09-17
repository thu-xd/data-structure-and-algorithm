#ifndef GRAPH_ABC_H_
#define GRAPH_ABC_H_
#include "../stack/stack.h"
#include "../queue/queue.cpp"
#include <climits>

enum VStatus {UNDISCOVERED,DISCOVERED,VISITED};
enum EStatus {UNDETERMINED,TREE,CROSS,FORWARD,BACKWARD};

template<typename Tv, typename Te>
class Graph
{
  private:
    void reset();
    void BFS(int,int &);
    void DFS(int,int &);
    void BCC(int,int &,Stack<int> &);
    bool TSort(int,int &,Stack<Tv> *);
    template <typename PU> void PFS(int,PU);
  public:
    int n;
    virtual int insert(Tv const &)=0;
    virtual Tv remove(int)=0;
    virtual Tv & vertex(int)=0;
    virtual int inDegree(int)=0;
    virtual int outDegree(int)=0;
    virtual int firstNbr(int)=0;
    virtual int nextNbr(int,int)=0;
    virtual VStatus & status(int)=0;
    virtual int & dTime(int)=0;
    virtual int & fTime(int)=0;
    virtual int & parent(int)=0;
    virtual int & priority(int)=0;

    int e;
    virtual bool exists(int,int)=0;
    virtual void insert(Te const &,int,int,int)=0;
    virtual Te remove(int,int)=0;
    virtual EStatus & status(int,int)=0;
    virtual Te & edge(int ,int)=0;
    virtual int & weight(int,int)=0;

    void bfs(int);
    void dfs(int);
    void bcc(int);
    Stack<Tv> * tSort(int);
    void prim(int);
    void dijkstra(int);
    template <typename PU> void pfs(int,PU);
};

template <typename Tv,typename Te>
void Graph<Tv,Te>::reset()
{
  for(int i=0;i<n;i++)
  {
    status(i)=UNDISCOVERED;
    dTime(i)=fTime(i)=-1;
    parent(i)=-1;
    priority(i)=INT_MAX;
    for(int j=0;j<n;j++)
      if(exists(i,j)) status(i,j)=UNDETERMINED;
  }
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::bfs(int s)
{
  reset();
  int clock=0;
  int v=s;
  do
    if(UNDISCOVERED==status(v))
      BFS(v,clock);
  while(s!=(v=(++v)%n));
}

template <typename Tv,typename Te>
void Graph<Tv,Te>::BFS(int v,int & clock)
{
  Queue<int> Q;
  status(v)=DISCOVERED;Q.enqueue(v);
  while(!Q.empty())
  {
    int v=Q.dequeue(); dTime(v)=++clock;
    for(int u=firstNbr(v);u>=0;u=nextNbr(v,u))
    {
      if(UNDISCOVERED==status(u))
      {
        status(u)=DISCOVERED;Q.enqueue(u);
        status(v,u)=TREE;parent(u)=v;
      }
      else status(v,u)=CROSS;
    }

    status(v)=VISITED;
  }
}
      
template<typename Tv,typename Te>
void Graph<Tv,Te>::dfs(int s)
{
  reset();
  int clock=0,v=s;
  do
    if(UNDISCOVERED==status(v))
      DFS(v,clock);
  while(s!=(v=++v)%n);
}

template<typename Tv,typename Te>
void Graph<Tv,Te>::DFS(int v,int & clock)
{
  dTime(v)=++clock;status(v)=DISCOVERED;
  for(int u=firstNbr(v);u>=0;u=nextNbr(v,u))
    switch(status(u))
    {
      case UNDISCOVERED:
        status(v,u)=TREE;parent(u)=v;DFS(u,clock);break;
      case DISCOVERED:
        status(v,u)=BACKWARD;break;
      default:
        status(v,u)=(dTime(v)<dTime(u))?FORWARD:CROSS;break;
    }
  status(v)=VISITED;
  fTime(v)=++clock;
}

#endif
