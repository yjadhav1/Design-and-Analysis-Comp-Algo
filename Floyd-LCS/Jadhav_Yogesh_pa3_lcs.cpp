#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
char X[100], Y[100];
char **lcsPath;
void print(char **lcsPath, int Xlen, int Ylen);

int main(int argc, char *argv[])
{
 int Xlen, Ylen;
 int i,j, maxLen;
 strcpy(X, argv[1]);
 strcpy(Y, argv[2]);

 Xlen = strlen(X);
 Ylen = strlen(Y);

 int lcsMatrix[Xlen + 1][Ylen + 1];
 lcsPath = new char*[Xlen];
 for(i = 0; i < Xlen; ++i)
    lcsPath[i] = new char[Ylen];


 for(i = 1; i <= Xlen; i++)
  lcsMatrix[i][0] = 0;
 for(j = 1; j <= Ylen; j++)
  lcsMatrix[0][j] = 0;


maxLen = 0;
for(i = 1; i <= Xlen; i++)
 {
   for(j = 1; j <= Ylen; j++)
   {
     if(X[i-1] == Y[j-1])
     {
       lcsMatrix[i][j] = lcsMatrix[i-1][j-1] + 1;
       lcsPath[i-1][j-1] = 'D';
     }
     else if(lcsMatrix[i-1][j] >= lcsMatrix[i][j-1])
     {
       lcsMatrix[i][j] = lcsMatrix[i-1][j];
       lcsPath[i-1][j-1] = 'U';
     }
     else
     {
       lcsMatrix[i][j] = lcsMatrix[i][j-1];
       lcsPath[i-1][j-1] = 'L';
     }
     if(maxLen < lcsMatrix[i][j])
      maxLen = lcsMatrix[i][j];
   }
 }
cout<< "\n";
 for(i = 0; i < Xlen; i++)
  {
    for(j = 0; j < Ylen; j++)
    {
      cout << lcsPath[i][j] << "\t";
    }
    cout<< "\n";
  }

  cout<< "The LCS length is " << maxLen <<" and the string is ";
print(lcsPath,Xlen - 1,Ylen - 1);
cout<< "\n";
  for(i = 0; i < Xlen; ++i)
    free(lcsPath[i]);

  free(lcsPath);
  return 0;
}



void print(char **lcsPath, int Xlen, int Ylen)
{
  if(Xlen < 0 || Ylen < 0)
   return;
  if(lcsPath[Xlen][Ylen] == 'D')
  {
    print(lcsPath, Xlen - 1 , Ylen - 1);
    cout << X[Xlen];
  }
  else if(lcsPath[Xlen][Ylen] == 'U')
  {
    print(lcsPath, Xlen - 1 , Ylen);
  }
  else if(lcsPath[Xlen][Ylen] == 'L')
  {
    print(lcsPath, Xlen , Ylen - 1);
  }
}
