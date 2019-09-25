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

//logic for the bruteoforce approach
int bruteAlgo(int W,int *weights,int *profits,int n)
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
        maxProfit = max(profits[n - 1]+bruteAlgo(W - weights[n - 1], weights, profits, n- 1), bruteAlgo(W, weights, profits, n - 1));  //getting the max from one of them
        //decide if item is to be included
        if(maxProfit == profits[n - 1]+bruteAlgo(W - weights[n - 1], weights, profits, n- 1))
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
        maxProfit = bruteAlgo(W, weights, profits, n - 1);
          if(itemsIncluded[n-2] == 0)
          {
            itemsIncludedCount++;
          }
          itemsIncluded[n-2] = 1; // the previous item is included
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

  fgets(line, 100, fpMpL);


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



  fgets(line, 100, fpMpL);
  fgets(line, 100, fpMpL);




  int n = 0;


//tokenizing the weights and profits
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

//call to brute force algo
maxProfit = bruteAlgo(totalWeight, weights,profits, noOfItems);

//getting the total weights of the items included
for(int i = 0; i < noOfItems; i++)
{
  if(itemsIncluded[i] == 1)
  {
    maxWeight = maxWeight + weights[i];
  }
}

//output printing as per the given format
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
