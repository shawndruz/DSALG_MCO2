#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the adjacency list
typedef struct Node {
    int id;
    struct Node* next;
} Node;

// Structure to represent an adjacency list
typedef struct AdjList {
    Node* head;
} AdjList;

// Structure to represent a graph
typedef struct Graph {
    int numVertices;
    AdjList* array;
} Graph;

// Function prototypes
Node* createNode(int id);
Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int src, int dest);
Graph* loadGraphFromFile(char* filename);
void printGraph(Graph* graph);

#endif // STRUCTS_H
