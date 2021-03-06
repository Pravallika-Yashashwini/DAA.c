HUFFMAN:
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 100

struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};
struct MinHeapNode* newNode(char data, unsigned freq)
{
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(
        sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHeapNode**)malloc(
        minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size
        && minHeap->array[left]->freq
               < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size
        && minHeap->array[right]->freq
               < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i
           && minHeapNode->freq
                  < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}
int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(char data[],int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}
struct MinHeapNode* buildHuffmanTree(char data[],
                                     int freq[], int size)

{
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap= createAndBuildMinHeap(data, freq, size);
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
void printCodes(struct MinHeapNode* root, int arr[],
                int top)

{
    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {

        printf("%c: ", root->data);
        printArr(arr, top);
    }
}
void HuffmanCodes(char data[], int freq[], int size)

{
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);

    int arr[MAX_TREE_HT], top = 0;

    printCodes(root, arr, top);
}
int main()
{
    int n,i;
    printf("Enter the number of characters you wanted to encode <27");
    scanf("%d",&n);
    char arr[26];
    char c;
    int freq[26];
    printf("Enter the characters and their frequency\n");
    for(i=0;i<n;i++)
    {
        scanf("\n%c %d",&c,&freq[i]);
        arr[i]=c;
    }
    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, n);

    return 0;
}
-----------------------------------------------------------------------
0/1 KNAPSACK:

#include <stdio.h>

int max(int a, int b) { return (a > b) ? a : b; }

int knapSack(int W, int wt[], int val[], int n)
{
	if (n == 0 || W == 0)
		return 0;

		if (wt[n - 1] > W)
		return knapSack(W, wt, val, n - 1);

	else
		return max(
			val[n - 1]
				+ knapSack(W - wt[n - 1],
						wt, val, n - 1),
			knapSack(W, wt, val, n - 1));
}

int main()
{
	int val[] = { 60, 100, 120 };
	int wt[] = { 10, 20, 30 };
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);
	printf("%d", knapSack(W, wt, val, n));
	return 0;
}

----------------------------------------------------------------------------
TSP PROBLEM:
#include<stdio.h>
 
int ary[10][10],completed[10],n,cost=0;
 
void takeInput()
{
	int i,j;
 
	printf("Enter the number of villages: ");
	scanf("%d",&n);
 
	printf("\nEnter the Cost Matrix\n");
 
	for(i=0;i < n;i++)
	{
		printf("\nEnter Elements of Row: %d\n",i+1);
 
		for( j=0;j < n;j++)
			scanf("%d",&ary[i][j]);
 
		completed[i]=0;
	}
 
	printf("\n\nThe cost list is:");
 
	for( i=0;i < n;i++)
	{
		printf("\n");
 
		for(j=0;j < n;j++)
			printf("\t%d",ary[i][j]);
	}
}
 
void mincost(int city)
{
	int i,ncity;
 
	completed[city]=1;
 
	printf("%d--->",city+1);
	ncity=least(city);
 
	if(ncity==999)
	{
		ncity=0;
		printf("%d",ncity+1);
		cost+=ary[city][ncity];
 
		return;
	}
 
	mincost(ncity);
}
 
int least(int c)
{
	int i,nc=999;
	int min=999,kmin;
 
	for(i=0;i < n;i++)
	{
		if((ary[c][i]!=0)&&(completed[i]==0))
			if(ary[c][i]+ary[i][c] < min)
			{
				min=ary[i][0]+ary[c][i];
				kmin=ary[c][i];
				nc=i;
			}
	}
 
	if(min!=999)
		cost+=kmin;
 
	return nc;
}
 
int main()
{
	takeInput();
 
	printf("\n\nThe Path is:\n");
	mincost(0); //passing 0 because starting vertex
 
	printf("\n\nMinimum cost is %d\n ",cost);
 
	return 0;
}
-------------------------------------------------------------------------------
JOB SEQUENCE:
#include<stdio.h>
#include<string.h>

struct Job{
    char no[100];
    int deadline,profit;
};

int main()
{
    struct Job Default;
    Default.no[0]='N';
    Default.no[1]='U';
    Default.no[2]='L';
    Default.no[3]='L';
    Default.deadline=0;
    Default.profit=0;
    struct Job job[1000],te,order[1000];
    int n,i,j,dmax,maxprofit=0,curr_dead;
    scanf("%d",&n);
    dmax=-1;
    for(i=0;i<n;i++)
    {
        printf("Enter job name");
        scanf("%s",job[i].no);
        printf("Enter deadline");
        scanf("%d",&job[i].deadline);
        if(dmax<job[i].deadline)
        {
            dmax=job[i].deadline;
        }
        printf("Enter profit");
        scanf("%d",&job[i].profit);
    }
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(job[i].profit<job[j].profit)
            {
                te=job[i];
                job[i]=job[j];
                job[j]=te;
            }
        }
    }
    for(i=0;i<=dmax;i++)
    {
        order[i]=Default;
    }
    for(i=0;i<n;i++)
    {
        curr_dead=job[i].deadline;
        while(strcmp(order[curr_dead].no,Default.no)!=0 && order[curr_dead].deadline!=Default.deadline && order[curr_dead].profit!=Default.profit)
        {
            curr_dead-=1;
        }
        if(curr_dead!=0)
        order[curr_dead]=job[i];
    }
    for(i=1;i<=dmax;i++)
    {
        printf("%s is Job name, %d is Job deadline, %d is Job profit\n",order[i].no,order[i].deadline,order[i].profit);
          maxprofit+=order[i].profit;
    }
    printf("%d is the maximum profit achievable", maxprofit);
    return 0;
}
---------------------------------------------------------------------------
PRIMS:

#include<stdio.h>
#include<stdio.h>
#include<conio.h>
int a,b,u,v,n,i,j,ne=1;
int visited[10]={0},min,mincost=0, cost[10][10];
void main()
{
    
    printf("enter the number of nodes");
    scanf("%d",&n);
    printf("enter the adjacency matrix");
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    {
        scanf("%d",&cost[i][j]);
        if(cost[i][j]==0)
        cost[i][j]=999;
    }
    visited[1]=1;
    printf("\n");
    while(ne<n)
    {
        for(i=1,min=999;i<=n;i++)
        for(j=1;j<=min;j++)
        if(cost[i][j]<min)
        if(visited[i]!=0)
        {
            min=cost[i][j];
            a=u=i;
            b=v=j;
            if(visited[u]==0||visited[v]==0)
            {
                printf("\n edge %d:(%d %d)cost:%d",ne++,a,b,min);
                mincost += min;
                visited[b]=1;
            }
            cost[a][b]=cost[b][a]=999;
        }
        printf("\n minimum cost=%d",mincost);
        getch();
    }
}
--------------------------------------------------------------------------------------
KRUSKAL'S:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Edge {
	int src, dest, weight;
};
struct Graph {
	int V, E;
	struct Edge* edge;
};
struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = (struct Graph*)(malloc(sizeof(struct Graph)));
	graph->V = V;
	graph->E = E;

	graph->edge = (struct Edge*)malloc(sizeof( struct Edge)*E);

	return graph;
}
struct subset {
	int parent;
	int rank;
};
int find(struct subset subsets[], int i)
{
	if (subsets[i].parent != i)
		subsets[i].parent
			= find(subsets, subsets[i].parent);

	return subsets[i].parent;
}
void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}
int myComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight > b1->weight;
}
void KruskalMST(struct Graph* graph)
{
	int V = graph->V;
	struct Edge
	result[V]; 
	int e = 0; 
	int i = 0; 
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]),
		myComp);
	struct subset* subsets
		= (struct subset*)malloc(V * sizeof(struct subset));
	for (int v = 0; v < V; ++v) {
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}
	while (e < V - 1 && i < graph->E) {
		struct Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);
		if (x != y) {
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
	}
	printf(
		"Following are the edges in the constructed MST\n");
	int minimumCost = 0;
	for (i = 0; i < e; ++i)
	{
		printf("%d -- %d == %d\n", result[i].src,
			result[i].dest, result[i].weight);
		minimumCost += result[i].weight;
	}
	printf("Minimum Cost Spanning tree : %d",minimumCost);
	return;
}
int main()
{
	int V = 4; 
	int E = 5; 
	struct Graph* graph = createGraph(V, E);
	
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;
	graph->edge[0].weight = 10;

	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 6;
	
	graph->edge[2].src = 0;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 5;

	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 15;

	graph->edge[4].src = 2;
	graph->edge[4].dest = 3;
	graph->edge[4].weight = 4;

	KruskalMST(graph);

	return 0;
}

--------------------------------------------------------------------------------------
DIJKSTRA'S:
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#define V 9
int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
void dijkstra(int graph[V][V], int src)
{
    int dist[V];  
    bool sptSet[V];  
    for (int i = 0; i < V; i++)
    dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0; 
    for (int count = 0; count < V - 1; count++) {
         int u = minDistance(dist, sptSet);
         sptSet[u] = true;
 
         for (int v = 0; v < V; v++)
	 if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    
    printSolution(dist);
}

 int main()
{
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
 
    dijkstra(graph, 0);
 
    return 0;
}
-------------------------------------------------------------------------------------------------------------------

MATRIX CHAIN ORDER:

#include <limits.h>
#include <stdio.h>

int MatrixChainOrder(int p[], int i, int j)
{
	if (i == j)
		return 0;
	int k;
	int min = INT_MAX;
	int count;

	
	for (k = i; k < j; k++) {
		count = MatrixChainOrder(p, i, k) +
				MatrixChainOrder(p, k + 1, j) +
				p[i - 1] * p[k] * p[j];

		if (count < min)
			min = count;
	}

	return min;
}


int main()
{
	int arr[] = { 1, 2, 3, 4, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Minimum number of multiplications is %d ",
		MatrixChainOrder(arr, 1, n - 1));

	getchar();
	return 0;
}
-------------------------------------------------------------
OPTIMAL BINARY SEARCH TREE:

#include <stdio.h>
#include <limits.h>
 

int sum(int freq[], int i, int j);

int optCost(int freq[], int i, int j)
{
   
   if (j < i)      
     return 0;
   if (j == i)     
     return freq[i];
 
   
   int fsum = sum(freq, i, j);
 
   
   int min = INT_MAX;
 
   
   for (int r = i; r <= j; ++r)
   {
       int cost = optCost(freq, i, r-1) +
                  optCost(freq, r+1, j);
       if (cost < min)
          min = cost;
   }
 
  
   return min + fsum;
}
 

int optimalSearchTree(int keys[], int freq[], int n)
{
     return optCost(freq, 0, n-1);
}

int sum(int freq[], int i, int j)
{
    int s = 0;
    for (int k = i; k <=j; k++)
       s += freq[k];
    return s;
}
 

int main()
{
    int keys[] = {10, 12, 20};
    int freq[] = {34, 8, 50};
    int n = sizeof(keys)/sizeof(keys[0]);
    printf("Cost of Optimal BST is %d ",
               optimalSearchTree(keys, freq, n));
    return 0;
}
--------------------------------------------------------
N-OUEEN:
#include<stdio.h>
#include<math.h>
int board[20],count;
int main()
{
int n,i,j;
void queen(int row,int n);
printf("Enter number of Queens:");
scanf("%d",&n);
queen(1,n);
return 0;
}
void print(int n)
{
int i,j;
printf("\nSolution %d:",++count);

for(i=1;i<=n;++i)
for(i=1;i<=n;++i)
{
  printf("\n\n");
  for(j=1;j<=n;++j)
  {
   if(board[i]==j)
    printf("\tQ");
   else
    printf("\t*");
  }
}
}
int place(int row,int column)
{
int i;
for(i=1;i<=row-1;++i)
{
  if(board[i]==column)
   return 0;
  else
   if(abs(board[i]-column)==abs(i-row))
    return 0;
}

return 1;
}
void queen(int row,int n)
{
int column;
for(column=1;column<=n;++column)
{
  if(place(row,column))
  {
   board[row]=column;
   if(row==n)
    print(n);
   else
    queen(row+1,n);
  }
}
}
--------------------------------------------------------------------
FLYOD'S WARSHALL
#include<stdio.h>

#define V 4

#define INF 99999

void printSolution(int dist[][V]);
 

void floydWarshall (int graph[][V])
{
    
    int dist[V][V], i, j, k;
 
    
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
 
    
    for (k = 0; k < V; k++)
    {
        
        for (i = 0; i < V; i++)
        {
            
            for (j = 0; j < V; j++)
            {
               
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
 
    
    printSolution(dist);
}
 

void printSolution(int dist[][V])
{
    printf ("The following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}
 

int main()
{
               int graph[V][V] = { {0,   5,  INF, 10},
                        {INF, 0,   3, INF},
                        {INF, INF, 0,   1},
                        {INF, INF, INF, 0}
                      };
 
    
    floydWarshall(graph);
    return 0;
}
----------------------------------------------------------------------------------------
SUM OF SUBSETS:
#include <stdio.h>
#include <stdlib.h>
static int total_nodes;
void printValues(int A[], int size){
   for (int i = 0; i < size; i++) {
      printf("%*d", 5, A[i]);
   }
   printf("\n");
}
void subset_sum(int s[], int t[], int s_size, int t_size, int sum, int ite, int const target_sum){
   total_nodes++;
   if (target_sum == sum) {
      printValues(t, t_size);
      subset_sum(s, t, s_size, t_size - 1, sum - s[ite], ite + 1, target_sum);
      return;
   }
   else {
      for (int i = ite; i < s_size; i++) {
         t[t_size] = s[i];
         subset_sum(s, t, s_size, t_size + 1, sum + s[i], i + 1, target_sum);
      }
   }
}
void generateSubsets(int s[], int size, int target_sum){
   int* tuplet_vector = (int*)malloc(size * sizeof(int));
   subset_sum(s, tuplet_vector, size, 0, 0, 0, target_sum);
   free(tuplet_vector);
}
int main(){
   int set[] = { 5, 6, 12 , 54, 2 , 20 , 15 };
   int size = sizeof(set) / sizeof(set[0]);
   printf("The set is ");
   printValues(set , size);
   generateSubsets(set, size, 25);
   printf("Total Nodes generated %d\n", total_nodes);
   return 0;
}
