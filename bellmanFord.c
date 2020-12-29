#include<stdio.h>
#include<stdlib.h>
#define INF 999

// Structure to define an Edge
struct Edge {
    // From vertex
    int from;
    // To vertex
    int to;
    // Weight of the edge
    int wt;
};

// Structure to define a Graph
struct Graph {
    // nV -> No of Vertices
    // nE -> No of Edges
    int nV, nE;
    
    // Array of edges
    struct Edge* edges;
};

// Function to create a graph
struct Graph* createGraph(int nV, int nE) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->nV = nV;
    graph->nE = nE;
    graph->edges = (struct Edge*) malloc(nE*sizeof(struct Edge));
    return graph;
}

// To print the answer after the algorithm is performed
void printDistances(int dist[], int n) {
    printf("Vertex       Distance from Source\n");
    for(int i=0; i<n; i++) {
        printf("\t%d\t\t%d\n", i, dist[i]);
    }
}

// The bellman ford algorithm
void bellmanFord(struct Graph* graph, int src) {
    
    int nV = graph->nV;
    int nE = graph->nE;
    int dist[nV];
    
    // Set all the distances from src to infinity
    for(int i=0; i<nV; i++) {
        dist[i] = INF;
    }
    
    // Distance from src to src is set to 0
    dist[src] = 0;
    
    // Relax edges nV-1 times
    for(int i=0; i<nV-1; i++) {
        // For every edge e
        for(int e=0; e<nE; e++) {
            int from = graph->edges[e].from;
            int to = graph->edges[e].to;
            int wt = graph->edges[e].wt;
            if(dist[from] != INF && dist[from] + wt < dist[to]) {
                dist[to] = dist[from] + wt;
            }
        }
    }
    
    // Check for negatice weight cycles
    for(int e=0; e<nE; e++) {
        int from = graph->edges[e].from;
        int to = graph->edges[e].to;
        int wt = graph->edges[e].wt;
        
        if(dist[from] != INF && dist[from] + wt < dist[to]) {
            printf("The graph contains negative weight cycle");
            return;
        }
    }
    
    printDistances(dist, nV);
    
    return;
}

int main() {
    int nV, nE, src;
    
    printf("Enter the no of vertices: ");
    scanf("%d", &nV);
    
    printf("Enter the no of edges: ");
    scanf("%d", &nE);
    
    struct Graph* graph = createGraph(nV, nE);
    
    for(int e=0; e<nE; e++) {
        
        printf("Enter from vertex for edge %d: ", e);
        scanf("%d", &graph->edges[e].from);
        
        printf("Enter to vertex for edge %d: ", e);
        scanf("%d", &graph->edges[e].to);
        
        printf("Enter weight for edge %d: ", e);
        scanf("%d", &graph->edges[e].wt);
        
    }
    
    printf("Enter source node: ");
    scanf("%d", &src);
    
    bellmanFord(graph, src);
    
    return 0;
}
