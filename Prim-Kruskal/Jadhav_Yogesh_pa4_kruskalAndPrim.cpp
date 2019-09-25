#include<iostream>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

int n = 0;
//Class for edge
class Edge
{
  public:
    int nodeU;
    int nodeV;
    int weight;

    Edge()
    {

    }

    Edge(int nodeU, int nodeV, int weight)
    {
      this->nodeU = nodeU;
      this->nodeV = nodeV;
      this->weight = weight;
    }
};

//class for find and Union
class FindAndUnion
{
  public:
    int size;

    int sz[100];

    int id[100];

    int numComponents;

    FindAndUnion(int size)
    {

    this->size = numComponents = size;

    for(int i = 0; i < size; i++) {
      id[i] = i;
      sz[i] = 1;
    }

   }

  int find(int p) {

    int root = p;
    while( root != id[root] )
      root = id[root];

    while(p != root) {
      int next = id[p];
      id[p] = root;
      p = next;
    }

    return root;

  }

  bool Isconnected(int p, int q) {
    return find(p) == find(q);
  }

  int componentSize(int p) {
    return sz[find(p)];
  }

  int components() {
    return numComponents;
  }

  void union3(int p, int q) {

    int root1 = find(p);
    int root2 = find(q);

    if (root1 == root2) return;

    if (sz[root1] < sz[root2]) {
      sz[root2] += sz[root1];
      id[root1] = root2;
    } else {
      sz[root1] += sz[root2];
      id[root2] = root1;
    }

    numComponents--;

  }

};

//Utility Functions
int findMinEdge(int key[], bool mstSet[], int n)
{
// Initialize min value
int min = 99 ;
int min_index;

for (int v = 0; v < n; v++)
	if (mstSet[v] == false && key[v] < min)
		min = key[v], min_index = v;

return min_index;
}

int intialisePrims(int key[], bool mstSet[], int parent[], int n){
	// Initialize all keys as INFINITE
	for (int i = 0; i < n; i++) {
		key[i] = 99 ;
		mstSet[i] = false;
	}

	key[0] = 0;
	parent[0] = -1;
}

int displayPrims(int parent[], int n, int **A)
{
cout << "The Spanned edges are" << '\n';
for (int i = 1; i < n; i++) {
	std::cout << "(" << parent[i] << ", " << i << ")" << "  " ;
  cout << " \n";
 }
}


void Sort(Edge *edges, int size)
{
    int i, j;
    Edge *key = new Edge();
    for (i = 1; i < size; i++) {
        key->weight = edges[i].weight;
        key->nodeU = edges[i].nodeU;
        key->nodeV = edges[i].nodeV;
        j = i - 1;

        while (j >= 0 && edges[j].weight > key->weight) {
            edges[j + 1].weight = edges[j].weight;
            edges[j + 1].nodeU = edges[j].nodeU;
            edges[j + 1].nodeV = edges[j].nodeV;
            j = j - 1;
        }
        edges[j + 1].weight = key->weight;
        edges[j + 1].nodeU = key->nodeU;
        edges[j + 1].nodeV = key->nodeV;
    }
}


// Kruskal's Logic
void kruskal(int **a, Edge *edges, int size)
{
  int i, j, k;
  FindAndUnion fnU = FindAndUnion(n);
  Edge *spannedEdges = new Edge[size];
  Edge e = Edge(-1, -1, -1);

  k=0;
  j=0;
  while(k != (n - 1))
  {
    e = edges[j];
    j++;
    if(!fnU.Isconnected(e.nodeU, e.nodeV))
    {
      spannedEdges[k] = Edge(e.nodeU, e.nodeV, e.weight);
      k++;
      fnU.union3(e.nodeU, e.nodeV);
    }
  }
  cout << "The Spanned edges are" << '\n';
  while(k >0)
  {
    e = spannedEdges[--k];
    cout << "("<< e.nodeU << ", " << e.nodeV << ")"<< "  " << '\n';
  }

}



//Prim's Logic
void prims(int **A, int n)
{
    int parent[n];
	int key[n];
	bool mstSet[n];

	intialisePrims(key, mstSet, parent, n);
	for (int count = 0; count < n-1; count++)
	{
		int u = findMinEdge(key, mstSet, n);

		mstSet[u] = true;

		for (int v = 0; v < n; v++) {
		if (A[u][v] && mstSet[v] == false && A[u][v] < key[v])
			parent[v] = u, key[v] = A[u][v];
		}
	}

	displayPrims(parent, n, A);
}

int main()
{
  srand(time(NULL));
  n = rand() % 6 + 5;
  cout << "N has the value " << n << '\n';
  int i, j, choice;
  int **A;
  A = new int*[n];
  for(i = 0; i < n; ++i)
     A[i] = new int[n];

   int k, maxSize;
   maxSize = (n*n - n)/2;
   Edge *edges = new Edge[maxSize];
   k = 0;


   for(i = 0; i < n; i++)
   {
     for(j = 0; j < n; j++)
     {
       if(i == j)
       {
         A[i][j] = 0;
       }
       else if(i < j)
       {
         A[j][i] = A[i][j] = rand() % 10 + 1;
         edges[k] = Edge(i, j, A[i][j]);
         k++;
       }
     }
   }
   cout << "\n" ;
   for(i = 0; i < n; i++)
   {
     for(j = 0; j < n; j++)
     {
         cout << A[i][j] << "  ";
     }
     std::cout << '\n';
   }

 do
 {
   std::cout << "\nPlease Enter:" << "\n\n" << "1 for Kruskal's" << "\n" << "2 for Prim's" << "\n";
   cin >> choice;


  if(choice == 1)
 {
   cout << "\nYou have Chosen Kruskal's algorithm" << "\n\n";
   Sort(edges,k);
   kruskal(A, edges, k);
 }
 else if(choice == 2)
 {
   cout << "\nYou have Chosen Prim's algorithm" << "\n\n";
   prims(A, n);
 }
 else
 {
   cout << " Exiting....." << '\n';
 }

  cout << "\n";

 }
 while(choice == 1 || choice == 2);

  return 0;
}
