#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"

// Create a new node
Node* createNode(int id) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->next = NULL;
    return newNode;
}

// Create a graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));
    for (int i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since it's an undirected graph, add an edge from dest to src also
    newNode = createNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Load the graph from a file
Graph* loadGraphFromFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    int n, e;
    fscanf(file, "%d %d", &n, &e);
    
    Graph* graph = createGraph(n);

    int src, dest;
    for (int i = 0; i < e; i++) {
        fscanf(file, "%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    fclose(file);
    return graph;
}

// Print the graph
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; ++v) {
        Node* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl) {
            printf("-> %d", pCrawl->id);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

//=====================================================//

/*

// Function to display the friend list of a given ID
void displayFriendList(Graph* graph, int id) {
    if (id >= graph->numVertices || id < 0) {
        printf("ID does not exist.\n");
        return;
    }

    printf("Friends of %d: ", id);
    int count = 0;
    Node* pCrawl = graph->array[id].head;
    while (pCrawl) {
        printf("%d ", pCrawl->id);
        pCrawl = pCrawl->next;
        count++;
    }
    printf("\nTotal friends: %d\n", count);
}

// Function to check if there is a connection between two IDs using BFS
bool isConnected(Graph* graph, int a, int b) {
    if (a >= graph->numVertices || b >= graph->numVertices || a < 0 || b < 0) {
        printf("One or both IDs do not exist.\n");
        return false;
    }

    bool* visited = (bool*)calloc(graph->numVertices, sizeof(bool));
    int queue[graph->numVertices], front = 0, rear = 0;

    visited[a] = true;
    queue[rear++] = a;

    while (front < rear) {
        int current = queue[front++];
        if (current == b) {
            free(visited);
            return true;
        }

        Node* pCrawl = graph->array[current].head;
        while (pCrawl) {
            int adj = pCrawl->id;
            if (!visited[adj]) {
                visited[adj] = true;
                queue[rear++] = adj;
            }
            pCrawl = pCrawl->next;
        }
    }

    free(visited);
    return false;
}

// Function to display the connection between two IDs
void displayConnection(Graph* graph, int a, int b) {
    if (isConnected(graph, a, b)) {
        printf("There is a connection between %d and %d.\n", a, b);
    } else {
        printf("No connection found between %d and %d.\n", a, b);
    }
}
*/

//=====================================================//


int main() {
    char filename[100];
    printf("Enter the filename of the dataset: ");
    scanf("%s", filename);

    Graph* graph = loadGraphFromFile(filename);

    if (graph == NULL) {
        printf("Failed to load the graph.\n");
        return 1;
    }

    // Print the entire graph (for debugging or initial verification)
    printGraph(graph);

/*
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Display Friend List\n");
        printf("2. Display Connection\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int id;
            printf("Enter the ID: ");
            scanf("%d", &id);
            displayFriendList(graph, id);
        } else if (choice == 2) {
            int a, b;
            printf("Enter the two IDs: ");
            scanf("%d %d", &a, &b);
            displayConnection(graph, a, b);
        }
    } while (choice != 3);
*/
    // Free memory
    for (int i = 0; i < graph->numVertices; ++i) {
        Node* pCrawl = graph->array[i].head;
        while (pCrawl) {
            Node* temp = pCrawl;
            pCrawl = pCrawl->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);

    return 0;
}



/*
int main ()
{
    char filename[100];
    
    printf("Enter filename: ");
    scanf("%s", &filename);

    Graph* graph = loadGraphFromFile(filename);
    
    if (graph != NULL) {
        printGraph(graph);
    }
    else
    	printf("awmen");
    
    return 0;
}
*/	
	
	
	
	
	
	
	
	
