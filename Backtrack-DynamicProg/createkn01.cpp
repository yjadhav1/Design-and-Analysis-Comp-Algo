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
using namespace std;


int main(int argc, char* argv[])
{
 srand(time(NULL));
 FILE *fpOut;
 int noOfItems, *profit;
 float *weight, W = 0.0;
 char* weightInString;

 weightInString = (char *) malloc(100);
 noOfItems = rand() % 5 + 4;     //random number of items
 weight = new float[noOfItems];
 profit = new int[noOfItems];
 for(int i = 0; i < noOfItems; i++)
 {
   profit[i] = rand() % 21 + 10;   // random profit value
   weight[i] = rand() % 16 + 5;    // random weights value
   W = W + weight[i];
 }

 W = floor(0.6 * W);       //total max Weight

 sprintf(weightInString, "%d", (int)W);

 char* output;
 output = (char *) malloc(1000);
 fpOut = fopen(argv[2],"w");

//concatenating the string for 1st line of text file
 sprintf(weightInString, "%d", noOfItems);
 strcat(output, weightInString);
 strcat(output, "\t");
 sprintf(weightInString, "%d", (int)W);
 strcat(output, weightInString);
 strcat(output, "\n\n");

//concatenating the string with all item values
 for(int i = 0; i < noOfItems; i++)
 {
   strcat(output, "Item");
   sprintf(weightInString, "%d", i + 1);
   strcat(output, weightInString);
   strcat(output, "\t");
   sprintf(weightInString, "%d", profit[i]);
   strcat(output, weightInString);
   strcat(output, "\t");
   sprintf(weightInString, "%d", (int)weight[i]);
   strcat(output, weightInString);
   strcat(output, "\n");
 }
cout << output;
 fputs(output, fpOut); //wrting to the file
fclose(fpOut);
return 0;
}
