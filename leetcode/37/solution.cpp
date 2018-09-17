#include <vector>
#include <list>
#include <stack>
#include <utility>
using std::vector;
using std::list;
using std::stack;

class Solution
{
    public:
        void solveSudoku(vector<vector<char> > & board)
            //A backtrack problem
        {
            vector<vector<bool> > row_contained(9,vector<bool>(9,false));
            vector<vector<bool> > column_contained(9,vector<bool>(9,false));
            vector<vector<bool> > square_contained(9,vector<bool>(9,false));
            list<std::pair<int,int> > empty_cells;
            stack<std::pair<list<std::pair<int,int> >::iterator,int> > filled_cells;

            for(int i=0;i<9;i++)
                for(int j=0;j<9;j++)
                {
                    char ch=board[i][j];
                    if(ch!='.')
                    {
                        row_contained[i][ch-'1']=true;
                        column_contained[j][ch-'1']=true;
                        square_contained[(i/3)*3+(j/3)][ch-'1']=true;
                    }
                    else
                        empty_cells.push_back(std::make_pair(i,j));
                }

            auto  current_pos=empty_cells.begin();
            int current_num=0;
            while(true)
            {
                for(;current_num<9;current_num++)
                    if(valid(row_contained,column_contained,square_contained,*current_pos,current_num))
                        break;
                if(current_num<9)
                {
                    row_contained[current_pos->first][current_num]=true;
                    column_contained[current_pos->second][current_num]=true;
                    square_contained[(current_pos->first/3)*3+(current_pos->second/3)][current_num]=true;
                    filled_cells.push(std::make_pair(current_pos,current_num));
                    current_pos++;
                    if(current_pos==empty_cells.end())
                        break;
                    current_num=0;
                }
                
                else
                {
                    current_pos=filled_cells.top().first;
                    current_num=filled_cells.top().second+1;
                    filled_cells.pop();
                    row_contained[current_pos->first][current_num-1]=false;
                    column_contained[current_pos->second][current_num-1]=false;
                    square_contained[(current_pos->first/3)*3+(current_pos->second/3)][current_num-1]=false;
                }
            }

            while(!filled_cells.empty())
            {
                current_pos=filled_cells.top().first;
                current_num=filled_cells.top().second;
                board[current_pos->first][current_pos->second]=current_num+'1';
                filled_cells.pop();
            }

        }

        bool valid(vector<vector<bool> > & row_contained, vector<vector<bool> > & column_contained,
                vector<vector<bool> > & square_contained, std::pair<int, int> & pos, int num)
        {
            return (!row_contained[pos.first][num]) && (!column_contained[pos.second][num])
                    && (!square_contained[(pos.first/3)*3+(pos.second/3)][num]);
        }
};
