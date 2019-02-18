#include <climits>
#include <vector>
#include "graph_abc.h"
using std::vector;

template <typename Tv>
struct Vertex
{
  Tv data;
  int inDegree,outDegree;
  VStatus status;
  int dTime,fTime;
  int parent;
  int priority;
  Vertex(const Tv & d=(Tv) 0):data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
  dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){};
};

template <typename Te>
struct Edge
{
  Te data;
  int weight;
  EStatus status;
  Edge(const Te &d,int w):data(d),weight(w),status(UNDETERMINED){};
};

template <typename Tv, typename Te>
class GraphMatrix:public Graph<Tv,Te>
{
  private:
    vector<Vertex<Tv> > V;
    vector<vector<Edge<Te> *> > E;
  public:
    GraphMatrix(){this->n=this->e=0;};
    ~GraphMatrix();
    virtual Tv & vertex(int i) {return V[i].data;};
    virtual int inDegree(int i) {return V[i].inDegree;};
    virtual int outDegree(int i) {return V[i].outDegree;};
    virtual int firstNbr(int i) {return nextNbr(i,this->n);};
    virtual int nextNbr(int i,int j) {while((j>=0) && (!exists(i,--j))) return j;};
    virtual VStatus & status(int i) {return V[i].status;};
    virtual int & dTime(int i) {return V[i].dTime;};
    virtual int & fTime(int i) {return V[i].fTime;};
    virtual int & parent(int i) {return V[i].parent;};
    virtual int & priority(int i) {return V[i].priority;};
    virtual int insert(const Tv & vertex);
    virtual Tv remove(int i);
    virtual bool exists(int i,int j);
    virtual EStatus & status(int i,int j){return E[i][j]->status;};
    virtual Te & edge(int i,int j) {return E[i][j]->data;};
    virtual int & weight(int i,int j) {return E[i][j]->weight;};
    virtual void insert(const Te & edge,int w,int i,int j);
    virtual Te remove(int i,int j);
};

template<typename Tv, typename Te>
GraphMatrix<Tv,Te>::~GraphMatrix()
{
  for(int i=0;i<this->n;i++)
    for(int j=0;j<this->n;j++)
      delete E[i][j];
}

template<typename Tv,typename Te>
int GraphMatrix<Tv,Te>::insert(const Tv & vertex)
{
  for(int i=0;i<this->n;i++) E[i].push_back(NULL);
  this->n++;
  E.push_back(vector<Edge<Te> *>(this->n,(Edge<Te> *)NULL));
  V.push_back(Vertex<Tv>(vertex));
  return this->n;
}

template<typename Tv,typename Te>
Tv GraphMatrix<Tv,Te>::remove(int i)
{
  for(int j=0;j<this->n;i++)
    if(exists(i,j)) {delete E[i][j];V[j].inDegree--;}
  E.erase(E.begin()+i); 
  this->n--;
  for(int j=0;j<this->n;j++)
    if(exists(j,i)) {Edge<Te> * tmp=E[j][i]; E[j].erase(E[j].begin()+i);delete tmp; V[j].outDegree--;};
  Tv vv=vertex(i);
  V.erase(V.begin()+i);
  return vv;
}

template<typename Tv, typename Te>
bool GraphMatrix<Tv,Te>::exists(int i,int j)
{
  return (0<=i)&&(i<=this->n)&&(0<=j)&&(j<=this->n)&&(E[i][j]!=NULL);
}

template<typename Tv,typename Te>
void GraphMatrix<Tv,Te>::insert(const Te & edge,int w,int i,int j)
{
  if(exists(i,j)) return;
  E[i][j]=new Edge<Te>(edge,w);
  this->e++;
  V[i].outDegree++;
  V[j].inDegree++;
}

template<typename Tv,typename Te>
Te GraphMatrix<Tv,Te>::remove(int i,int j)
{
  Te ee=edge(i,j);
  delete E[i][j];
  E[i][j]=NULL;
  this->e--;
  V[i].outDegree--;
  V[j].inDegree--;
  return ee;
}

