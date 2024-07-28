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
    int i;
    for ( i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Check if an edge already exists
bool edgeExists(Node* head, int id) {
    Node* current = head;
    while (current != NULL) {
        if (current->id == id)
            return true;
        current = current->next;
    }
    return false;
}

// Add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest if it doesn't already exist
    if (!edgeExists(graph->array[src].head, dest)) {
        Node* newNode = createNode(dest);
        newNode->next = graph->array[src].head;
        graph->array[src].head = newNode;
    }

    // Since it's an undirected graph, add an edge from dest to src if it doesn't already exist
    if (!edgeExists(graph->array[dest].head, src)) {
        Node* newNode = createNode(src);
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
}

// Load the graph from a file
Graph* loadGraph(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    int n, e;
    fscanf(file, "%d %d", &n, &e);

    Graph* graph = createGraph(n);

    int src, dest;
    int i;
    for (i = 0; i < e; i++) {
        fscanf(file, "%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    fclose(file);
    return graph;
}

//=====================================================//

// Function to display the friend list of a given ID
void displayFriendList(Graph* graph) {

    int i, personID, nFriends = 0;
    int Friends[MAX_FRIENDS];

    printf("Enter ID of person: ");
    scanf("%d", &personID);


    while (personID >= graph->numVertices || personID < 0) {
        printf("ID does not exist. Please try again.\n");
        printf("Enter ID of person: ");
        scanf("%d", &personID);
    }

    Node* pCrawl = graph->array[personID].head;
    nFriends = 0;
    while (pCrawl && nFriends < MAX_FRIENDS) {
        Friends[nFriends] = pCrawl->id;
        pCrawl = pCrawl->next;
        nFriends++;
    }

    printf("\nPerson %d has %d friends!\n", personID, nFriends);
    printf("List of friends: ");
    
    for(i = 0; i < nFriends; i++) {
        printf("%d ", Friends[i]);
    }
    printf("\n");
}

// checks if ID is within the data set
bool isValidID(Graph* graph, int id) {
    if (id < 0 || id >= graph->numVertices) {
        return false;
    }
    return graph->array[id].head != NULL;
}

// Function to check if there is a connection between two IDs using BFS
// Function to check if there is a connection between two IDs using BFS
bool isConnectedUtil(Graph* graph, int src, int dest, int* path, int* pathIndex) {
    if (src == dest) {
        path[(*pathIndex)++] = src;
        return true;
    }

    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    int i;
    for ( i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    visited[src] = true;
    queue[rear++] = src;
    int* previous = (int*)malloc(graph->numVertices * sizeof(int));
    for ( i = 0; i < graph->numVertices; i++) {
        previous[i] = -1;
    }

    while (front != rear) {
        int current = queue[front++];

        Node* adjList = graph->array[current].head;
        while (adjList != NULL) {
            int adjVertex = adjList->id;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                previous[adjVertex] = current;
                queue[rear++] = adjVertex;

                if (adjVertex == dest) {
                    // Build path from src to dest
                    int crawl = dest;
                    while (crawl != -1) {
                        path[(*pathIndex)++] = crawl;
                        crawl = previous[crawl];
                    }

                    // Reverse path to get from src to dest
                    for ( i = 0; i < (*pathIndex) / 2; i++) {
                        int temp = path[i];
                        path[i] = path[(*pathIndex) - i - 1];
                        path[(*pathIndex) - i - 1] = temp;
                    }

                    free(queue);
                    free(visited);
                    free(previous);
                    return true;
                }
            }
            adjList = adjList->next;
        }
    }

    free(queue);
    free(visited);
    free(previous);
    return false;
}
void displayConnection(Graph* graph, int a, int b) {
    if (!isValidID(graph, a) || !isValidID(graph, b)) {
        printf("One or both IDs do not exist in the dataset.\n");
        return;
    }

    int* path = (int*)malloc(graph->numVertices * sizeof(int));
    int pathIndex = 0;
    int i;

    if (isConnectedUtil(graph, a, b, path, &pathIndex)) {
        printf("There is a connection from %d to %d!  \n", a, b);
        for ( i = 0; i < pathIndex; i++) {
            if (i > 0) {
                printf("%d is friends with %d", path[i - 1], path[i]);
                if (i < pathIndex - 1) {
                    printf(" \n ");
                }
            }
        }
        printf("\n");
    } else {
        printf("cannot find a connection between %d and %d. \n", a, b);
    }

    free(path);
}
//=====================================================//

int main() {
    char filename[100];
    printf("Input file path: ");
    scanf("%s", filename);

    Graph* graph = loadGraph(filename);

    if (graph == NULL) {
        printf("Failed to load the graph.\n");
        return 1;
    }
    else
        printf("Graph loaded!");


    int choice;
	int a, b;
    
     do {
	        printf("\nMAIN MENU\n");
	        printf("[1] Get friend list\n");
	        printf("[2] Get connection\n");
	        printf("[3] Exit\n");
	        printf("\nEnter your choice: ");
	        scanf("%d", &choice);
	
	        switch (choice) {
			case 1: 
		        displayFriendList(graph);
				break;
	   		case 2:
	            	printf("Enter ID of first person: ");
	            	scanf("%d" , &a );
	            	printf("Enter ID of second person: ");
	            	scanf("%d" , &b );
	            	if(a == b)
	            	{
	            		printf("Cannot be the same ID.");
	            		break;
			}
			else if (!isValidID(graph, a) || !isValidID(graph, b)) {
				printf("One or both IDs do not exist in the dataset.\n");
	  			break;
	    		}
			else
	            		displayConnection(graph, a, b);
		      	break;
	        }
    } while (choice != 3);

    // Free memory
    int i;
    for ( i = 0; i < graph->numVertices; ++i) {
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
