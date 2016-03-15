//#include <cstdio>
#include <cstdlib>


// C++ program for implementation of Ford Fulkerson algorithm
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std;

int V;


/* Returns true if there is a path from source 's' to sink 't' in
  residual graph. Also fills parent[] to store the path */
bool bfs(int **rGraph, int s, int t, int parent[])
{
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}
 
// Returns tne maximum flow from s to t in the given graph
int fordFulkerson(int **graph, int s, int t)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    //int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates 
    int **rGraph = (int**)malloc(sizeof(int**)*V);
    for (int i = 0; i < V; ++i) {
        rGraph[i] = (int*)malloc(sizeof(int*)*V);
    }
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not)  
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];
 
    int parent[V];  // This array is filled by BFS and to store path
 
    int max_flow = 0;  // There is no flow initially
 
    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edhes along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
    // Return the overall flow
    return max_flow;
}
 
/*
// Driver program to test above functions
int main()
{
    // Let us create a graph shown in the above example
    int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
 
    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5);
 
    return 0;
}
*/

int **get_input(int *size);
void print_array(int **matr, int size);

int main() {
    int size;
    int **matr = get_input(&size);
    V = size;
    cout <<  fordFulkerson(matr, 0, size-1) << endl;
    //print_array(matr, size);
    free(matr);
}

/*
void print_array(int **matr, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", matr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
*/


int **get_input(int *out_size) {
    int N,F,D, size;
    //scanf("%d %d %d", &N, &F,&D);
    cin >> N >> F >> D;
    size = 2*N+F+D+2;
    *out_size = size;
    int **matr = (int**)malloc(sizeof(int**)*size);//new int*[size];
    for (int i = 0; i < size; ++i) {
        matr[i] = (int*)calloc(size, sizeof(int*));//new int[size];
    }
    // Let 0 be the source
    // size-1 be the sink
    // 1...F (inclusive) be the foods
    // F+1...F+N be cows_1
    // F+N+1...F+2N be cows_2
    // F+2N+1...size-2 be drinks

    // Foods
    for (int food = 1; food < F+1; ++food) {
        matr[0][food] = 1;
    }

    // Connect cow_1 to cow_2
    for (int i = F+1; i < F+N+1; ++i) {
        matr[i][N+i] = 1;
    }

    // 
    for (int i = 1; i < N+1; ++i) {
        int num_food, num_drink;
        cin >> num_food >> num_drink;
        //scanf("%d %d", &num_food, &num_drink);
        for (int j = 0; j < num_food; ++j) {
            int food;
            //scanf("%d", &food);
            cin >> food;
            matr[food][F+i] = 1;
        }
        for (int j = 0; j < num_drink; ++j) {
            int drink;
            //scanf("%d", &drink);
            cin >> drink;
            matr[F+N+i][F+2*N+1+drink] = 1;
        }
    }
 
    // Drink
    for (int drink = F+2*N+1; drink < size-1; ++drink) {
        matr[drink][size-1] = 1;
    }

   return matr;
}
