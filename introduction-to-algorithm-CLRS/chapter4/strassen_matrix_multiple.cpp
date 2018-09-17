#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
using std::vector;

//This is an implementation of naive matrix multiple algorithm and stassen
//matrix multiple algorithm. The time comlexity of stassen algorithm was
//O(n^2.81). The time complexity of naive matrix multiple algorithm was O(n^3)
//But the constant factor of stassen algorithm was much larger than the naive
//method. So don't use stassen algrithm when the n was small, just used the
//naive algorithm. The leaf_size can be tuned to adjust the moment when to turn
//to naive algorithm from the stassen algorithm. leaf_size==1 means naive
//algorithm for arbitrary size.

static const int leaf_size=200;
//At which size, stassen algorithm was switch to naive loop algorithm

void naive_matrix_multiple(vector<vector<int> > &A, vector<vector<int> > &B,
    vector<vector<int> > &C);

void sum_matrix(vector<vector<int> > & A, vector<vector<int> > &B, vector<vector<int> > & C);

void subtract_matrix(vector<vector<int> > & A, vector<vector<int> > & B, vector<vector<int> > & C);

void expand(vector<vector<int> > & A,int new_size);

void shrink(vector<vector<int> > & A,int new_size);

void stassen(vector<vector<int> > & A, vector<vector<int> > &B, vector<vector<int> > & C);

void print_matrix(vector<vector<int> > & A);

vector<vector<int> > stassen(vector<vector<int> > & A, vector<vector<int> > & B)
{
  //This is the entry of the stassen algorithm which calculate A*B
  //Args:
  //  A,B: calcualte A*B and return, A and B must be square matrix with same
  //  size, but the size of A and B don't need to be pow of 2.
  //Retrun:
  //  The result of A*B

  int n=A.size();
  int n_backup=n;
  int min_pow_of_2=1;
  int tmp=1;
  while(n>0)
  {
    min_pow_of_2+=tmp;
    tmp=tmp<<1;
    n=n>>1;
  }
  if(min_pow_of_2==n_backup*2) min_pow_of_2=n_backup;

  expand(A,min_pow_of_2);
  expand(B,min_pow_of_2);
  vector<vector<int> > C(min_pow_of_2,vector<int>(min_pow_of_2,0));
  stassen(A,B,C);
  shrink(A,n_backup);
  shrink(B,n_backup);
  shrink(C,n_backup);
  return C; 
}




void stassen(vector<vector<int> > & A, vector<vector<int> > &B, vector<vector<int> > & C)
  //This is a stassen implementation of C=A*B.
  //The A and B must be square matrix and the size of A and B must be pow of 2.
  //The implementation was similar to
  //https://martin-thoma.com/strassen-algorithm-in-python-java-cpp/
  //Args:
  //  A,B:calculate A*B
  //  C:the result
  //
{
  int n=A.size();
  if(n<=leaf_size)
  {
    naive_matrix_multiple(A,B,C);
    return;
  }
  else
  {
    int mid=n>>1;
    vector<int> tmp(mid,0);
    vector<vector<int> > a11(mid,tmp),a12(mid,tmp),a21(mid,tmp),a22(mid,tmp),
      b11(mid,tmp),b12(mid,tmp),b21(mid,tmp),b22(mid,tmp),
      c11(mid,tmp),c12(mid,tmp),c21(mid,tmp),c22(mid,tmp),
      p1(mid,tmp),p2(mid,tmp),p3(mid,tmp),p4(mid,tmp),p5(mid,tmp),p6(mid,tmp),p7(mid,tmp),
      aResult(mid,tmp),bResult(mid,tmp);

    for(int i=0;i<mid;i++)
      for(int j=0;j<mid;j++)
      {
        a11[i][j]=A[i][j];
        a12[i][j]=A[i][j+mid];
        a21[i][j]=A[i+mid][j];
        a22[i][j]=A[i+mid][j+mid];

        b11[i][j]=B[i][j];
        b12[i][j]=B[i][j+mid];
        b21[i][j]=B[i+mid][j];
        b22[i][j]=B[i+mid][j+mid];
      }

    subtract_matrix(b12,b22,bResult);
    stassen(a11,bResult,p1);  //p1=a11*(b12-b22)

    sum_matrix(a11,a12,aResult);
    stassen(aResult,b22,p2); //p2=(a11+a12)*b22

    sum_matrix(a21,a22,aResult);
    stassen(aResult,b11,p3);  // p3=(a21+a22)*b11

    subtract_matrix(b21,b11,bResult);
    stassen(a22,bResult,p4);  //p4=a22*(b21-b11)

    sum_matrix(a11,a22,aResult);
    sum_matrix(b11,b22,bResult);
    stassen(aResult,bResult,p5);  //p5=(a11+a22)*(b11+b22)

    subtract_matrix(a12,a22,aResult);
    sum_matrix(b21,b22,bResult);
    stassen(aResult,bResult,p6);  //p6=(a12-a22)*(b21+b22)

    subtract_matrix(a11,a21,aResult);
    sum_matrix(b11,b12,bResult);
    stassen(aResult,bResult,p7);  //p7=(a11-a21)*(b11+b12)

    //calculate c11,c12,c21 and c22 using p1 p2 ... p7
    sum_matrix(p5,p4,aResult);
    subtract_matrix(p6,p2,bResult);
    sum_matrix(aResult,bResult,c11);

    sum_matrix(p1,p2,c12);

    sum_matrix(p3,p4,c21);

    sum_matrix(p5,p1,aResult);
    sum_matrix(p3,p7,bResult);
    subtract_matrix(aResult,bResult,c22);

    for(int i=0;i<mid;i++)
      for(int j=0;j<mid;j++)
      {
        C[i][j]=c11[i][j];
        C[i][j+mid]=c12[i][j];
        C[i+mid][j]=c21[i][j];
        C[i+mid][j+mid]=c22[i][j];
      }
  }
}

void naive_matrix_multiple(vector<vector<int> > & A,vector<vector<int> > & B,
    vector<vector<int> > &C)
  //The naive implementation of matrix multiple using loop.
  //The time complexity was O(n^3).
  //The args was the same as the stassen function.
{
  int n=A.size();
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      for(int k=0;k<n;k++)
        C[i][j]+=A[i][k]*B[k][j];
}

void sum_matrix(vector<vector<int> > & A, vector<vector<int> > &B, vector<vector<int> > & C)
{
  int n=A.size();
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      C[i][j]=A[i][j]+B[i][j];
}

void subtract_matrix(vector<vector<int> > & A, vector<vector<int> > & B, vector<vector<int> > & C)
{
  int n=A.size();
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      C[i][j]=A[i][j]-B[i][j];
}

void expand(vector<vector<int> > & A,int new_size)
  // expand the square matrix A to the new_size, padding with 0.
  // new_size>=A.size()
  //
  // Args:
  //  A:The matrix to be expanded
  //  new_size:The new size of the matrix
  // Return 
  //
{
  int n=A.size();
  if(n>=new_size) return;
  for(int i=n;i<new_size;i++)
    A.push_back(vector<int>(n,0));
  for(int i=0;i<new_size;i++)
    for(int j=n;j<new_size;j++)
      A[i].push_back(0);
}

void shrink(vector<vector<int> > & A, int new_size)
  //shrink the square matrix A to shrink A[0,n-1][0,n-1] to
  //A[0,new_size-1][0,new_size-1]
  //
  //args:
  //  A: The matrix to be shrinked
  //  new_size: The new size of the matrix
  //Return
  //
{
  int n=A.size();
  if(n<=new_size) return;
  for(int i=n;i>new_size;i--)
    A.pop_back();
  for(int i=0;i<new_size;i++)
    for(int j=n;j>new_size;j--)
      A[i].pop_back();
}


void print_matrix(vector<vector<int> > &A)
{
  int n=A.size();
  int m=A[0].size();

  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
      std::cout<<A[i][j]<<" ";
    std::cout<<std::endl;
  }
}

//test code
int main()
{
  int N;
  std::cout<<"Please give the size of the matrix:__\b\b";
  std::cin>>N;
  vector<vector<int> > A(N,vector<int>(N)),B(N,vector<int>(N));
//  std::srand(std::time(NULL));
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
    {
      A[i][j]=std::rand()%100-50;
      B[i][j]=std::rand()%100-50;
    }

  if(N<=10)
  {
    std::cout<<"The first matrix was:"<<std::endl;
    print_matrix(A);
    std::cout<<"The second matrix was:"<<std::endl;
    print_matrix(B);
  }

  std::clock_t t=std::clock();
  vector<vector<int> > C=stassen(A,B);
  t=std::clock()-t;
  std::cout<<"The running time of stassen algorithm when the matrix size was "<<N<<": "
    <<double(t)/CLOCKS_PER_SEC<<" seconds\n";

  if(N<=10)
  {
    std::cout<<"The multiple result was :"<<std::endl;
    print_matrix(C);
  }

  vector<vector<int> > D(N,vector<int>(N,0));
  t=std::clock();
  naive_matrix_multiple(A,B,D);
  t=std::clock()-t;
  std::cout<<"The running time of naive algorithm when the matrix size was "<<N<<": "
    <<double(t)/CLOCKS_PER_SEC<<" seconds\n";

  if(N<=10)
  {
    std::cout<<"The multiple result was :"<<std::endl;
    print_matrix(D);
  }

  return 0;
}

  




