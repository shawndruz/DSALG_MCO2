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
	
	
	
	
	
	
	
	
	
