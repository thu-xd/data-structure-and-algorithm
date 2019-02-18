#include <iostream>
#include "stack.h"
#include <vector>
#include <string>
using std::string;
using std::vector;

struct Queen
{
  int x,y;
  Queen(int xx=0,int yy=0):x(xx),y(yy) {};
  bool operator==(const Queen & q) const
  {
    return (x==q.x) || (y==q.y) || (x-y)==(q.x-q.y) || (x+y)==(q.x+q.y);
  }

  bool operator!=(const Queen & q) const {return !(*this==q);};
};

class N_queens
{
  private:
    int N;
    vector<Stack<Queen> > solutions;
  public:
    N_queens(int NN=8):N(NN) {};
    void find_solution();
    friend std::ostream & operator<<(std::ostream &os,N_queens & Nq);
};

void N_queens::find_solution()
{
  Stack<Queen> S;
  Queen q(0,0);
  while((q.x>0) || (q.y<N)) // The end point of the try and backtracking method was at x=0 and y=N                                // So it's equal to say while(!(q.x==0 && q.y==N)
  {
    if(S.size()==N)
    {
      solutions.push_back(S);
      q=S.pop();
      q.y++;
    }

    while(S.find(q)!=-1)
      q.y++;
    if(q.y<N) //if find the new queen position, push the queen into the stack and go ahead.
    {
      S.push(q);
      q.x++;
      q.y=0;
    }
    else
    {
      q=S.pop();
      q.y++;
    }
  }
}

std::ostream & operator<<(std::ostream & os, N_queens & Nq)
{
  for(int i=0;i<int(Nq.solutions.size());i++)
  {
    Stack<Queen> solu=Nq.solutions[i];
    Queen q;
    while(!solu.empty())
    {
      q=solu.pop();
      os<<string(q.y,'*')<<'x'<<string(Nq.N-1-q.y,'*')<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
  }
  return os;
}


int main()
{
  int N;
  std::cout<<"Please enter the number of Queens: "<<std::endl;
  std::cin>>N;
  N_queens Nq(N);
  Nq.find_solution();
  std::cout<<Nq<<std::endl;
  return 0;
}
