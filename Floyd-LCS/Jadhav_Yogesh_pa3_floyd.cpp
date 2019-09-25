#include<iostream>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

void printPath(int i, int j, int **P)
{
  if(P[i][j] != 0)
  {
    printPath(i, P[i][j], P);
    cout << "V" << P[i][j] + 1 << "\t";
    printPath(P[i][j], j, P);
    return;
  }
  else
   return;
}

int main()
{
  srand(time(NULL));
  int n = 0;
  n = rand() % 6 + 5;
  cout << "N has the value " << n << '\n';
  int A[n][n], D[n][n], i, j, k;
  int **P;
  P = new int*[n];
  for(i = 0; i < n; ++i)
     P[i] = new int[n];


  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      if(i == j)
      {
        A[i][j] = 0;
        D[i][j] = 0;
        P[i][j] = 0;
      }
      else if(i < j)
      {
        D[j][i] = D[i][j] = A[j][i] = A[i][j] = rand() % 10 + 1;
        P[i][j] = P[j][i] = 0;
      }
    }
  }


  for(k = 0; k < n; k++)
  {
    for(i = 0; i < n; i++)
    {
      for(j = 0; j < n; j++)
      {
        if(D[i][j] > (D[i][k] + D[k][j]))
        {
          D[i][j] = D[i][k] + D[k][j];
          P[i][j] = k;
        }
      }
    }
  }


  cout << "The shortest distance between following vertices are: \n\n";
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
        if((i != 0 || j != 0) && (i>j))
        {
          cout << "V" << i + 1 << " and V" << j + 1 <<" is " << D[i][j] << " and the path has ";
          printPath(i, j, P);
          cout << "\n";
        }
    }
  }
  return 0;
}
