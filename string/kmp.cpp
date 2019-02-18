#include <cstring>
#include <iostream>

void next_table(char * P, int * next) // The length of next was the same as P
  //    for [p0 p1 p2 p3...pj-1]
  //    if next[j]=k then [p0 p1...pk-1]=[pj-k  pj-k+1 ... pj-1]
  //    to solve next[j+1]  so the new substr was [p0 p1 p2 ... pj]
  //    we known that [p0 p1 ... pk-1]=[pj-k pk-j+1 ... pj-1]
  //    So if(pk==pj)  next[j+1]=k+1=next[j]+1;
  //    else assuming that next[j+1]=s+1(s<k)  then [p0 p1 p2... ps]=[pj-s pj-s+1...pj]
  //    so [p0 p1 p2...ps-1]=[pj-s pj-s+1 ... pj-1]  and ps=pj
  //    we known that [p0 p1 ... pk-1]=[pj-k pk-j+1 ... pj-1]
  //    so [pk-s pk-s+1 ... pk-1]=p[j-s pj-s+1 ... pj-1]
  //    so we get [p0 p1 p2 ... ps-1]=[pk-s pk-s+1...pk-1]
  //    this is just the next[k]=s means .
  //    So next[j+1]=s+1 satisfy that next[k]=s and ps=pj
{
  int len=std::strlen(P);
  next[0]=-1;
  next[1]=0;
  int j=2;  // solve next[j] using next[0]...next[j-1].
  int s=0;    // a cursor variable
  while(j<len)
  {
    if(s<0 || (P[s]==P[j-1]&&P[s+1]!=P[j]))
    {
      s=next[j]=s+1;
      j++;
    }
    else
      s=next[s];        
  }
}

int match(char *P, char *T) // kmp algorithm
{
  int len_P=std::strlen(P);
  int * next=new int[len_P];
  next_table(P,next);
  int len_T=std::strlen(T);
  int i=0,j=0;
  while(i<len_T && j<len_P)
  {
    if(j<0 || T[i]==P[j])  // the j<0 was used when the first char was dismatched.Then i++, j=0.
    {
      i++;
      j++;
    }
    else
      j=next[j];
  }
  delete [] next;
  if(j==len_P)
    return i-len_P;
  else return -1;
}

int main()
{
  char T[]="00010000101110010100101010";
  char P[80];
  std::cout<<"The text was :"<<T<<std::endl;
  std::cout<<"Please enter the pattern, empty line to teminate."<<std::endl;
  while(std::cin.getline(P,80) && P[0]!='\0')
    std::cout<<"The position of the pattern was :"<<match(P,T)<<std::endl;
  return 0;
}
