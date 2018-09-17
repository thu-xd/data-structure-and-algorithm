#include <iostream>
#include <vector>
#include "stack.h"
#include <string>
using std::vector;
using std::string;
/* This is implementation of finding path in the maze. The implementation was
 * mainly using stack to track the path. The code was already tested for
 * correct. But there  still need some improvements. The code should keep track
 * of point from which we can't reach the final point. Then at the next
 * iterator we don't need to traversal these points. But we don't know how
 * could I track these points. 
 *
 * Author xd */

enum Direction {UP,DOWN,LEFT,RIGHT,NO_WAY};  // The direction which point can go.

struct Point
{
  int x,y;
  bool go_up,go_down,go_left,go_right; //indicated where can go up,down,left,right in this cell
                                       //if you have go one direction once ,you
                                      //can't do it again in a single path.
  bool on_the_path; //indicated whether the point is already on the path, you can't pass a point twice.
 
  Point(int xx=0,int yy=0) {x=xx,y=yy,go_up=go_down=go_left=go_right=true,on_the_path=false;};
  bool dead(){return !(go_up || go_down || go_left || go_right);}; // a point is dead if it
                                                                   // has no
                                                                   // way to go
  bool operator==(const Point & p)const {return x==p.x && y==p.y;};
  bool operator!=(const Point & p)const {return !(*this==p);};

  Direction new_direction()    // new direction of a point.
  {
    if(go_up) return UP;
    if(go_right) return RIGHT;
    if(go_down) return DOWN;
    if(go_left) return LEFT; 
    return NO_WAY;
  }
  
};

class Maze
{
  private:
    int N;
    vector<vector<Point> > points;
    vector<Point> obstacles; 
    vector<Stack<Point> > paths;
  public:
    Maze(int _N,vector<Point> & _obstacles);
    void find_path();
    friend std::ostream & operator<<(std::ostream & os, const Maze & M);

};

Maze::Maze(int _N,vector<Point> & _obstacles):N(_N),obstacles(_obstacles)
{
  for(int i=0;i<N;i++)
  {
    points.push_back(vector<Point>());
    for(int j=0;j<N;j++)
    {
      Point p(i,j);
      p.go_down=(j==0)?false:true;
      p.go_up=(j==N-1)?false:true;
      p.go_left=(i==0)?false:true;
      p.go_right=(i==N-1)?false:true;
      points[i].push_back(p);
    }

  }
  for(int i=0;i<int(obstacles.size());i++)
  {
    int x=obstacles[i].x;
    int y=obstacles[i].y;
    if(x>0) points[x-1][y].go_right=false;
    if(x<N-1) points[x+1][y].go_left=false;
    if(y>0) points[x][y-1].go_up=false;
    if(y<N-1) points[x][y+1].go_down=false;
  }
}

void Maze::find_path()
{
  Stack<Point> S;
  Point p=points[0][0];
  while(p!=Point(0,0) || (!p.dead()))
  {
    S.push(p),points[p.x][p.y].on_the_path=true;  //if a point is added to the stack,the on_the_path 
                                                 //should be true;
    if(S.top().x==N-1 && S.top().y==N-1)  // if reach the final point,store the stack in the paths.
    {
      paths.push_back(S);
      p=S.pop(),points[p.x][p.y].on_the_path=false;// if reach the final point,pop the final point and 
                                                   // begin new try.
    }
    p=S.pop(),points[p.x][p.y].on_the_path=false;

    Direction dir=p.new_direction();
    switch(dir)
    {
      case UP:
        p.go_up=false;
        S.push(p),points[p.x][p.y].on_the_path=true;
        p=points[p.x][p.y+1];
        if(points[p.x][p.y].on_the_path==true)  // if the new point is already on the path,pop the previous.
        {
          p=S.pop(),points[p.x][p.y].on_the_path=false;
          break;
        }
        p.go_down=false;  // you can't go back to the previous point.
        break;
      case DOWN:
        p.go_down=false;
        S.push(p),points[p.x][p.y].on_the_path=true;
        p=points[p.x][p.y-1];
        if(points[p.x][p.y].on_the_path==true)
        {
          p=S.pop(),points[p.x][p.y].on_the_path=false;
          break;
        }
        p.go_up=false;
        break;
      case LEFT:
        p.go_left=false;
        S.push(p),points[p.x][p.y].on_the_path=true;
        p=points[p.x-1][p.y];
        if(points[p.x][p.y].on_the_path==true)
        {
          p=S.pop(),points[p.x][p.y].on_the_path=false;
          break;
        }
        p.go_right=false;
        break;
      case RIGHT:
        p.go_right=false;
        S.push(p),points[p.x][p.y].on_the_path=true;
        p=points[p.x+1][p.y];
        if(points[p.x][p.y].on_the_path==true)
        {
          p=S.pop(),points[p.x][p.y].on_the_path=false;
          break;
        }
        p.go_left=false;
        break;
      case NO_WAY:
        p=S.pop(),points[p.x][p.y].on_the_path=false;
    }
  }
}

std::ostream & operator<<(std::ostream & os, const Maze & M)
{
  vector<string> str;
  for(int i=0;i<M.N;i++)
    str.push_back(string(M.N,'*'));
  for(int i=0;i<int(M.obstacles.size());i++)
  {
    int x=M.obstacles[i].x;
    int y=M.obstacles[i].y;
    str[y][x]='W';
  }


  for(int i=M.N-1;i>=0;i--)
    std::cout<<str[i]<<std::endl;
  std::cout<<std::endl;

  for(int i=0;i<int(M.paths.size());i++)
  {
    vector<string> tmp=str;
    Stack<Point> path=M.paths[i];
    while(!path.empty())
    {
      Point p=path.pop();
      tmp[p.y][p.x]='x';
    }
    for(int i=M.N-1;i>=0;i--)
      std::cout<<tmp[i]<<std::endl;
    std::cout<<std::endl;
  }

  return os;
}

int main()
{
  vector<Point> obstacles;
  int x,y;
  int N;

  std::cout<<"Please enter the size of the maze: "<<std::endl;
  std::cin>>N;
  std::cout<<"Please enter the obstacles of the maze,"
    "one obstacles per line, including x and y ,q to exit"<<std::endl;
  while(std::cin>>x>>y)
    obstacles.push_back(Point(x,y));
  Maze M(N,obstacles);
  M.find_path();
  std::cout<<M<<std::endl;
  return 0;
}





