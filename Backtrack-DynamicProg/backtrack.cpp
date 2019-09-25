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


class Node
{
  public:
    int profit;
    int weight;
    int upperbound;
};



int totalWeight;
int noOfItems;
int  *profits, *weights, *itemsIncluded, itemsIncludedCount, maxWeight;

//the knapsack function for given entries
int Knapsack(int W,int *weights,int *profits,int n)
{
    int maxProfit = 0;

      if (n == 0 || W == 0)
      {
        return maxProfit;
      }
      else if(n == 1)
      {
        maxProfit = profits[n-1];
        return maxProfit;
      }

      if (weights[n - 1] <= W)
      {
        maxProfit = max(profits[n - 1]+Knapsack(W - weights[n - 1], weights, profits, n- 1), Knapsack(W, weights, profits, n - 1));
        if(maxProfit == profits[n - 1]+Knapsack(W - weights[n - 1], weights, profits, n- 1))
        {
          if(itemsIncluded[n-1] == 0)
          {
            itemsIncludedCount++;
          }
          itemsIncluded[n-1] = 1;
        }
        return maxProfit;
      }
      else
      {
        maxProfit = Knapsack(W, weights, profits, n - 1);
          if(itemsIncluded[n-2] == 0)
          {
            itemsIncludedCount++;
          }
          itemsIncluded[n-2] = 1;
        return maxProfit;
      }

}


int main(int argc, char* argv[])
{
  FILE *fpPL, *fpMpL,*fpOut;
  char line[100], *value;
  char *token;
  char *errstr;
  int k = 0;
  int maxProfit = 0;

  fpMpL = fopen(argv[2], "r");
  token = new char[100];
  value = new char[100];

  //reading the file
  fgets(line, 100, fpMpL);

  token = strtok(line, "\t");
  noOfItems = (int)strtol(token, &errstr, 10);

  token = strtok(NULL, "\t");

  totalWeight = (int)strtol(token, &errstr, 10);

  maxWeight = 0;
  itemsIncludedCount = 0;
  profits = new int[noOfItems];
  weights = new int[noOfItems];
  itemsIncluded = new int[noOfItems];



  fgets(line, 100, fpMpL);
  fgets(line, 100, fpMpL);



// token = strtok(line, "\t");
//   cout << token << "\n";
//   while(token != NULL)
//   {
//     cout << token;
//     token = strtok(NULL, "\t");
//
//   }
  int n = 0;
//tokenizing for weights and profits
  do {
    /* code */
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

//calling for the optimal node
maxProfit = Knapsack(totalWeight, weights,profits, noOfItems);

//getting the total weights of the items included
for(int i = 0; i < noOfItems; i++)
{
  if(itemsIncluded[i] == 1)
  {
    maxWeight = maxWeight + weights[i];
  }
}

//printing the output of the items included in the given format as project description
cout << "\n\nOutPut : \n" << itemsIncludedCount << "\t" << maxProfit << "\t" << maxWeight << "\n";
for(int i = 0; i < noOfItems; i++)
{
  if(itemsIncluded[i] == 1)
  {
    cout << "Item" << i+1 << "   " << profits[i] << "\t" << weights[i] << "\n";
  }
}

  fclose(fpMpL);
return 0;



}
