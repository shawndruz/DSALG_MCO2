#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the adjacency list
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Define the structure for the adjacency list
typedef struct AdjList {
    Node* head;
} AdjList;

// Define the structure for the graph
typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;