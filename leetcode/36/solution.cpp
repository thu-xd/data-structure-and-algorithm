#include <vector>
using std::vector;

class Solution
{
    public:
        bool isValidSudoku(vector<vector<char> > & board)
        {
            vector<bool> visited_backup(9,false),visited(visited_backup),visited1(visited_backup),
                visited2(visited_backup);
            for(int i=0;i<9;i++)
            {
                visited=visited_backup;
                visited1=visited_backup;
                visited2=visited_backup;
                for(int j=0;j<9;j++)
                {
                    if(board[i][j]>='1' && board[i][j]<='9')
                    {
                        if(visited[board[i][j]-'1'])
                            return false;
                        else
                            visited[board[i][j]-'1']=true;
                    }

                    if(board[j][i]>='1' && board[j][i]<='9')
                    {
                        if(visited1[board[j][i]-'1'])
                            return false;
                        else
                            visited1[board[j][i]-'1']=true;
                    }

                    int row=(i/3)*3+j/3;
                    int column=(i%3)*3+j%3;
                    if(board[row][column]>='1' && board[row][column]<='9')
                    {
                        if(visited2[board[row][column]-'1'])
                            return false;
                        else
                            visited2[board[row][column]-'1']=true;
                    }
                }
            }
            return true;
        }
};

            


