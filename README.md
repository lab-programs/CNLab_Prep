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
# Program-06 : Checksum

#### Header files
```c
#include<stdio.h>
#include<string.h>
```

#### Checksum function
```c
int checksum(int flag) {
    char inputString[100];
    int buffer[25];
    int sum=0, hL, temp;
```
#### Request for the input one-word string
```c
    printf("Enter string: ");
    scanf("%s", inputString);
```
#### Calculate half length of input string
```c
    int len = strlen(inputString);
    if(len%2 == 0) {
        hL = len/2;
    }
    else {
        hL = (len+1)/2;
    }
```
#### Calculate the 256 shifted sum
```c
    for(int i=0; i<hL; i++) {
        int temp=inputString[i*2];
        temp=(temp*256)+inputString[1+(i*2)];
        sum += temp;
    }
```
#### If decode, add the checksum value to the sum
```c
    if(flag == 1) {
        printf("Enter checksum value: ");
        scanf("%d", &temp);
        sum += temp;
    }
```
#### Bring the value in the range of 0 to 65535
```c
    if(sum%65536 != 0) {
        sum = sum/65536 + sum%65536;
    }
```
#### Return the inverse of sum (checksum)
```c
    return 65535-sum;
}
```
#### Main function
```c
int main() {
    int ch, sum;
    
    printf("1. Encode    2. Decode   3. Exit\n");
    do {
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                sum=checksum(0);
                printf("Checksum value = %d\n", sum);
                break;
            case 2:
                sum=checksum(1);
                if(sum == 0) {
                    printf("The checksum is valid\n");
                }
                else {
                    printf("The data has been tampered with or checksum is invalid\n");
                }
                break;
            case 3:
                printf("Terminated...\n");
                return 0;
            default:
                printf("Invalid Choice\n");
        }
    } while(ch != 3);
}
```

# Program-07 : Leaky Bucket Algorithm

#### Header files and min function
```c
#include<stdio.h>
#define MIN(x, y) (x>y)? y: x
```
#### Main function
```c 
int main() {
    int bucketSize, outputRate, noOfSeconds, choice, droppedPackets=0;
    int packetsPerSecond[20]={0}, extraPackets=0, excess, second=1;
```
#### Take user input
```c
    printf("Enter bucket size: ");
    scanf("%d", &bucketSize);
    
    printf("Enter output rate: ");
    scanf("%d", &outputRate);
```
#### Take the packetsPerSecond as input
```c
    do {
        printf("Enter the packet at second %d: ", second);
        scanf("%d", &packetsPerSecond[second]);
        
        printf("Enter 1 to continue, 0 to quit... ");
        scanf("%d", &choice);
        
        second += 1;
    } while(choice == 1);
```
#### Assign noOfSeconds and a Table
```c
    noOfSeconds = second;
    
    printf(" Second \tReceived\t  Sent  \t Dropped\tRemained\n");
```
#### Only if extraPackets != 0 or do it n times
```c
    for(int i=1; i<=noOfSeconds || extraPackets; i++) {
        printf("%d\t\t%d\t\t%d\t\t", i, packetsPerSecond[i], 
	MIN(packetsPerSecond[i]+extraPackets, outputRate));
```
#### If there is any excess packets
```c
        if((excess = packetsPerSecond[i]+extraPackets-outputRate) > 0) {
            // Overflow
	    if(excess > bucketSize) {
                extraPackets = bucketSize;
                droppedPackets = excess-bucketSize;
            }
	    // Bucket size is enough
            else {
                extraPackets = excess;
                droppedPackets = 0;
            }
        }
```
#### No excess packets
```c
        else {
            extraPackets = 0;
            droppedPackets = 0;
        }
        
        printf("%d\t\t%d\n", droppedPackets, extraPackets);
    }
}

```

# Program-08 : Priority Queue

#### Headers and definitions
```c
#include<stdio.h>
#define MAX 5
```
#### Define the Priority Queue, front and back pointers.\
```c
int pq[MAX], f=-1, r=-1;
```
#### Insert an element into the queue
```c
void enqueue() {
    if(r>=MAX-1) {
        printf("Overflow\n");
    }
    else {
        int item;
        printf("Enter the item: ");
        scanf("%d", &item);
        printf("%d inserted\n", item);
        if(f == -1) {
            f = 0;
        }
        r++;
        for(int i=f; i<r; i++) {
            if(pq[i] > item) {
                for(int j=r-1; j>=i; j--) {
                    pq[j+1] = pq[j];
                }
                pq[i]=item;
                return;
            }
        }
        pq[r]=item;
    }
}
```
#### Delete an element from the queue
```c
void dequeue() {
    if(f == -1 || r == -1) {
        f = -1;
        r = -1;
        printf("Underflow\n");
        return;
    }
    printf("%d deleted\n", pq[f]);
    for(int i=f; i<r; i++) {
        pq[i] = pq[i+1];
    }
    r--;
}
```
#### Print the Priority Queue
```c
void printqueue() {
    if(f == -1 || r<0) {
        printf("Underflow\n");
    }
    else {
        printf("Priority Queue: ");
        for(int i=f; i<=r; i++) {
            printf("%d ", pq[i]);
        }
        printf("\n");
    }
}
```
#### Main function for menu based ui
```c
int main() {
    int choice;
    printf("1. Enqueue  2. Dequeue  3. Display  4. Exit\n\n");
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                printqueue();
                break;
            case 4:
                printf("Terminated...\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    } while(choice!=4);
}

```

# Program-09 : Go Back N Sliding window protocol
#### Simple program, no need for any explaination
```c
#include<stdio.h>

int main() {
    int windowSize, noOfFrames, frames[100];
    
    printf("Enter the window size: ");
    scanf("%d", &windowSize);
    
    printf("Enter the no of frames to transmit: ");
    scanf("%d", &noOfFrames);
    
    printf("Enter the frames:\n");
    for(int i=1; i<=noOfFrames; i++) {
        scanf("%d", &frames[i]);
    }
    
    printf("The frames will be sent by the sender to the receiver 
    on the following manner(assuming no corruption occurs):\n\n");
    
    printf("%d frames are sent at each stage and until they 
    are acknowledged by the receiver, no frames are sent\n\n", windowSize);
    
    for(int i=1; i<=noOfFrames; i++) {
        if(i%windowSize == 0) {
            printf("%d\n\n", frames[i]);
            printf("Acknowledgement of the above frame(s) received by the sender\n\n");
        }
        else {
            printf("%d ", frames[i]);
        }
    }
    
    if(noOfFrames%windowSize != 0) {
        printf("\n\nAcknowledgement of the above frame(s) received by the sender\n\n");
    }
}
```
# Program-11 : Secret key
```c
#include<stdio.h>

int computePublicKey(int base, int privateKey, int prime) {
	int publicKey=1;
	
	while(privateKey > 0) {
	
		if(privateKey % 2 == 1) {
			publicKey = (publicKey*base) % prime;
		}
		
		base = base*base % prime;
		
		privateKey /= 2;
	}
	
	return publicKey;
}

int computeSecretKey(int base, int publicKey, int prime) {
	return computePublicKey(base, publicKey, prime);
}

int main() {
	int prime, base, privateKeyA, privateKeyB, publicKeyA, publicKeyB, secretKeyA, secretKeyB;
	
	printf("Enter the prime: ");
	scanf("%d", &prime);
	printf("Enter the base: ");
	scanf("%d", &base);
	printf("Enter A's Private Key: ");
	scanf("%d", &privateKeyA);
	printf("Enter B's Private Key: ");
	scanf("%d", &privateKeyB);
	
	publicKeyA = computePublicKey(base, privateKeyA, prime);
	publicKeyB = computePublicKey(base, privateKeyB, prime);
	
	secretKeyA = computeSecretKey(publicKeyB, privateKeyA, prime);
	secretKeyB = computeSecretKey(publicKeyA, privateKeyB, prime);
	
	printf("Alice Secret key is = %d\nBob's Secret Key is = %d\n", secretKeyA, secretKeyB);
	
	return 0;
}
```
# Program-12 : RSA
```c
#include<stdio.h>
#include<math.h>

int gcd(int a, int b) {
	if(b == 0) {
		return a;
	}
	return gcd(b, a%b);
}

int main() {
	long long prime1, prime2, productOfPrimes, phiOfProductOfPrimes, publicKey, privateKey;
	
	printf("Enter the first prime: ");
	scanf("%lld", &prime1);

	printf("Enter the second prime: ");
	scanf("%lld", &prime2);
	
	productOfPrimes = prime1 * prime2;
	
	// phi(p) = p-1 for a prime - Euler's Phi Function
	phiOfProductOfPrimes = (prime1 - 1) * (prime2 - 1);
	
	publicKey = 2;
	
	while(publicKey < phiOfProductOfPrimes) {
		if(gcd(publicKey, phiOfProductOfPrimes) == 1) {
			break;
		}
		else {
			publicKey++;
		}
	}
	
	for(int i=2; i<=productOfPrimes; i++) {
		long long expression = (publicKey*i-1) % phiOfProductOfPrimes;
		if(expression == 0) {
			privateKey = i;
			break;
		}
	}
	
	
	
	printf("Public Key: %lld\n", publicKey);
	printf("Private Key: %lld\n", privateKey);
	
	long long message;
	printf("Enter message: ");
	scanf("%lld", &message);
	
	long long encryptedMessage = powl(message, publicKey);
	encryptedMessage = encryptedMessage % productOfPrimes;
	
	long long decryptedMessage = powl(encryptedMessage, privateKey);
	decryptedMessage = decryptedMessage % productOfPrimes;
	
	printf("Original Message : %lld\n", message);
	printf("Encrypted Message: %lld\n", encryptedMessage);
	printf("Decrypted Message: %lld\n", decryptedMessage);
	
	
	return 0;
}
```
# Program-05 : CRC

```c
#include<stdio.h>
#include<string.h>
#define N strlen(gen)


char data[28];
char checksum[28];
char gen[] = "10001000000100001";
int dataLength, end;
```
#### XOR Function
```c

void xor()
{
    for(int i = 1; i < N; i++) {
        checksum[i] = ((checksum[i] == gen[i])? '0' : '1');
    }
}
```
#### CRC Function
```c
void crc()
{
    end = 0;
    
    for(int i=0; i<N; i++) {
        checksum[i] = data[i];
        end = i;
    }
    
    end += 1;
    
    do {
        if(checksum[0]=='1')
            xor();
        
        for(int i=0; i<N-1; i++)
            checksum[i]=checksum[i+1];
        
        checksum[N-1]= data[end++];
        
    } while(end <= dataLength + N - 1);
}
```
#### Main function
```c
int main()
{
    printf("\nEnter data : ");
    scanf("%s", data);
    dataLength = strlen(data);
    
    printf("\n----------------------------------------");
    printf("\nGeneratng polynomial : %s", gen);
    
    for(int i=dataLength; i<dataLength+N-1; i++)
        data[i] = '0';
    
    printf("\n----------------------------------------");
    printf("\nPadded data is : %s",data);
    printf("\n----------------------------------------");
    
    crc();
    printf("\nChecksum is : %s",checksum);
    
    for(int i=dataLength; i<dataLength+N-1; i++)
        data[i] = checksum[i-dataLength];
    
    printf("\n----------------------------------------");
    printf("\nFinal codeword is : %s", data);
    printf("\n----------------------------------------");
    
    int ch;
    printf("\nTest error detection 0(yes) 1(no)? : ");
    scanf("%d",&ch);

    if(ch == 0)
    {
        int pos;
        
        do{
            printf("\nEnter the position where error is to be inserted : ");
            scanf("%d",&pos);
        } while(pos == 0 || pos > dataLength + N - 1);
        
        data[pos-1] = (data[pos-1] == '0') ? '1' : '0';
        
        printf("\n----------------------------------------");
        printf("\nErroneous data : %s\n", data);
    }
    
    crc();
    
    int i;
    for(i=0; (i<N-1) && (checksum[i] != '1'); i++);
    
    if(i < N-1)
        printf("\nError detected\n\n");
    else
        printf("\nNo error detected\n\n");
        
    printf("\n----------------------------------------\n");
    return 0;
}
```
