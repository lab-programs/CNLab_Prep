# CNLab_Prep

## Program-01 : TCP Server and Client

#### Header files to include for both client.c and server.c
```c
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>
#include<netstat/in.h>
#include<arpa/inet.h>
```

#### Main Function
```c
int main(int argc, char** argv) {
```
#### Common
```c
    int connectionSocket;
    int bufferSize = 1024;
    char* buffer = malloc(bufferSize);
    char filename[255];
    
    struct sockaddr_in socketAddress;
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(15000);
```
#### Server
```c
    socketAddress.sin_addr.s_addr = INADDR_ANY;
```
#### Common
```c
    connectionSocket = socket(AF_INET, SOCK_STREAM, 0);
```

#### Client
```c
    inet_pton(AF_INET, argv[1], &socketAddress.sin_addr);
    connect(connectionSocket, (struct sockaddr_in*) &socketAddress, sizeof(socketAddress));
```
#### Server
```c
    bind(connectionSocket, (struct socketaddr_in*) &socketAddress, sizeof(socketAddress));
    listen(connectionSocket, 3);
```
#### Client
```c
    printf("Enter the filename: ");
    scanf("%s", &filename);

    send(connectionSocket, filename, 255, 0);
```    
#### Server
```c
    int communicationSocket = accept(connectionSocket, (struct sockaddr_in*)NULL, NULL);
    recv(communicationSocket, filename, 255, 0);
    
    int file = open(filename, R_ONLY);
    int n = read(file, buffer, bufferSize);
    
    send(communicationSocket, buffer, n, 0);
``` 
#### Client
```c
    while((recv(connectionSocket, buffer, bufferSize, 0)) > 0) {
		    printf("%s", buffer);
	  }
    print("\nEOF\n\n");
```
#### Server
```c
    close(communicationSocket);
```
#### Common
```c
    return close(connectionSocket);
}
```

## Program-03 : Bellman Ford

#### Headers and Definitions
```c
#include<stdio.h>
#include<stdlib.h>
#define INF 999
```
#### Structure to define an Edge
```c
struct Edge {
    int from;
    int to;
    int wt;
};
```

#### Structure to define a Graph
```c
struct Graph {
    int nV, nE;
    struct Edge* edges;
};
```

#### Function to create a graph
```c
struct Graph* createGraph(int nV, int nE) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->nV = nV;
    graph->nE = nE;
    graph->edges = (struct Edge*) malloc(nE*sizeof(struct Edge));
    return graph;
}
```

#### To print the answer after the algorithm is performed
```c
void printDistances(int dist[], int n) {
    printf("Vertex       Distance from Source\n");
    for(int i=0; i<n; i++) {
        printf("\t%d\t\t%d\n", i, dist[i]);
    }
}
```

#### The bellman ford algorithm
```c
void bellmanFord(struct Graph* graph, int src) {
```
#### Get the variables nV and nE from graph. Define the dist array
```c
    int nV = graph->nV;
    int nE = graph->nE;
    int dist[nV];
```
#### Set all the distances from src to infinity
```c
    for(int i=0; i<nV; i++) {
        dist[i] = INF;
    }
```
#### Distance from src to src is set to 0
```c
    dist[src] = 0;
```

#### Relax edges nV-1 times
```c
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
```

#### Check for negatice weight cycles
```c
    for(int e=0; e<nE; e++) {
        int from = graph->edges[e].from;
        int to = graph->edges[e].to;
        int wt = graph->edges[e].wt;
        
        if(dist[from] != INF && dist[from] + wt < dist[to]) {
            printf("The graph contains negative weight cycle");
            return;
        }
    }
```
#### Print the distances from the source node
```c
    printDistances(dist, nV);    
    return;
}
```
#### Main function to get the graph from the user and call bellmanFord
```c
int main() {
    int nV, nE, src;
    
    // Take input from user
    printf("Enter the no of vertices: ");
    scanf("%d", &nV);
    
    printf("Enter the no of edges: ");
    scanf("%d", &nE);
    
    // Create a graph
    struct Graph* graph = createGraph(nV, nE);
    
    for(int e=0; e<nE; e++) {
        
        printf("Enter from vertex for edge %d: ", e);
        scanf("%d", &graph->edges[e].from);
        
        printf("Enter to vertex for edge %d: ", e);
        scanf("%d", &graph->edges[e].to);
        
        printf("Enter weight for edge %d: ", e);
        scanf("%d", &graph->edges[e].wt);
        
    }
    
    // Get the source node from user
    printf("Enter source node: ");
    scanf("%d", &src);
    
    bellmanFord(graph, src);
    
    return 0;
}
```

## Program-04 : Dijkstra's algorithm

```c
#include<stdio.h>
#define INF 999
```
#### Dijkstra's algorithm
```c
void dijkstra(int n, int cost[20][20], int src, int dist[]) {
    int isVisited[20], iNode, min;
```
#### Set isVisited to 0 and assign the row of cost matrix to the dist arr
```c
    for(int i=1; i<=n; i++) {
        isVisited[i] = 0;
        dist[i] = cost[src][i];
    }
```
#### Repeat the code for n-1 times
```c
    for(int c=1; c<n; c++) {
```
#### Set min to INF
```c
        min=INF;
```
#### Find the edge with the minimum distance
```c
        for(int j=1; j<=n; j++) {
            if(dist[j] < min && !isVisited[j]) {
                iNode = j;
                min = dist[j];
            }
        }
```
#### Visit the node with the minimum edge
```c
        isVisited[iNode] = 1;
```
#### For every node, check the sum of distances through intemediate nodes with every non-visited nodes. If it is shorted, assign it to dist arr
```c
        for(int j=1; j<=n; j++) {
            if(dist[iNode] + cost[iNode][j] < dist[j] && !isVisited[j]) {
                dist[j] = dist[iNode]+cost[iNode][j];
            }
        }
    }
}
```
#### Main Function
```c
int main() {
    int n, cost[20][20], src, dist[20];
    
    printf("Enter the no of nodes: ");
    scanf("%d", &n);
    
    printf("Enter the cost matrix:\n");
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            scanf("%d", &cost[i][j]);
            if(cost[i][j] == 0) {
                cost[i][j] = INF;
            }
        }
    }
    
    printf("Enter the source node: ");
    scanf("%d", &src);
    
    dijkstra(n, cost, src, dist);
    
    for(int i=1; i<=n; i++) {
        if(i != src) {
            printf("%d -> %d, cost = %d\n", src, i, dist[i]);
        }
    }
}
```
