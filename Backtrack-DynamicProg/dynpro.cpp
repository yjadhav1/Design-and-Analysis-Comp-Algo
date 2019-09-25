#include<iostream>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<string>
#include<stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

int totalWeight;
int noOfItems;
int  *profits, *weights, *itemsIncluded, itemsIncludedCount, maxWeight;


//dynamic algo for the refinement method
int getRefinementMatrix(int **B, int n, int w)
{

  if(w == 0)
  {

    B[n][w] = 0;
  }
  else if(n == 1)
  {
    B[n][w] = profits[n-1];
  }
  else
  {
    if(weights[n-1] <= w)
    {
      B[n][w] = std :: max(getRefinementMatrix(B, n-1, w), profits[n-1] + getRefinementMatrix(B, n-1, w-weights[n-1]) ); //conditional calls as per the algo, getting the max
      if(B[n][w] == (profits[n-1] + B[n-1][w-weights[n-1]]))                                                             //condition to include the item in knapsack
      {
        if(itemsIncluded[n-1] == 0)
        {
          itemsIncludedCount++;
        }
        itemsIncluded[n-1] = 1;
      }
    }
    else if(weights[n-1] > w)
    {
      B[n][w] = getRefinementMatrix(B, n-1, w);
      if(itemsIncluded[n-2] == 0)
      {
        itemsIncludedCount++;
      }
      itemsIncluded[n-2] = 1;                                                                                             //including the previous item
    }
  }
  return B[n][w];
}



int main(int argc, char* argv[])
{
  FILE *fpPL, *fpMpL,*fpOut;
  char line[100], *value;
  char *token;
  char *errstr;
  int k = 0;
  int **B;

  fpMpL = fopen(argv[2], "r");            //opening the given text file in the arguments
  token = new char[100];
  value = new char[100];


  fgets(line, 100, fpMpL);
  //fclose(fpMpL);

  token = strtok(line, "\t");
  noOfItems = (int)strtol(token, &errstr, 10);

  token = strtok(NULL, "\t");

  totalWeight = (int)strtol(token, &errstr, 10);

//initializing the arrays(pointers)
  maxWeight = 0;
  itemsIncludedCount = 0;
  profits = new int[noOfItems];
  weights = new int[noOfItems];
  itemsIncluded = new int[noOfItems];
  B = new int*[noOfItems + 1];

  for(int i = 0; i <= noOfItems; i++)
  {
    B[i] = new int[totalWeight + 1];
  }

  for(int i = noOfItems; i > 0; i--)
  {
    for(int j = totalWeight; j > 0; j--)
    {
      B[i][j] = 0;
    }
  }


  fgets(line, 100, fpMpL);
  fgets(line, 100, fpMpL);




  int n = 0;

  do {

    token = strtok(line, "\t");
    while(token != NULL)
    {
      if(n == 1)
      {
        profits[k] = (int)strtol(token, &errstr, 10);
      }
      else if(n == 2)
      {
        weights[k] = (int)strtol(token, &errstr, 10);
      }
      token = strtok(NULL, "\t");
      n++;
    }

    itemsIncluded[k] = 0;
    fgets(line, 100, fpMpL);
    k++;
    n = 0;
  } while(k < noOfItems);

//assigning the profit to the last element as it is supposed to be
B[noOfItems][totalWeight] = getRefinementMatrix(B, noOfItems, totalWeight);   //passing B as a pointer which updates all the values in B matrix


//printing the entries in given project format
cout << "\nEntries :\n";

for(int i = 1; i <= noOfItems; i++)
{
  cout << "row" << i << "\t";
  for(int j = 0; j <=totalWeight; j++)
  {
    if(B[i][j] > 0)
    {
      cout << B[i][j] << "  ";
    }

  }

  cout << "\n";
}

//calculating the total weight of all included elements
for(int i = 0; i < noOfItems; i++)
{
  if(itemsIncluded[i] == 1)
  {
    maxWeight = maxWeight + weights[i];
  }

}


// printing the output as in the given project format.
cout << "\n\nOutPut : \n" << itemsIncludedCount << "\t" << B[noOfItems][totalWeight] << "\t" << maxWeight << "\n";
for(int i = 0; i < noOfItems; i++)
{
  if(itemsIncluded[i] == 1)
  {
    cout << "Item" << i+1 << "   " << profits[i] << "\t" << weights[i] << "\n";
  }
}

fclose(fpMpL);            //closing the file
return 0;


}
