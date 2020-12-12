// Add necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define names of output files
#define EULER_TOUR_FILE "A.txt"
#define OPERATIONS_NUM_FILE "C.txt"

// Define global variable to count operations
unsigned int count_operations = 0;

// Define a new structure for linked-lists
typedef struct Node 
{
    // Data of the node
    int num;
    // Address of the next node
    struct Node *next;
} Node;

/*
@brief: Add a new node to a linked-list
@param: head - pointer to the head of the linked-list
        data - data of the new node to be added
@return: none
*/
void push_front( Node **head, int data );

/*
@brief: Delete a node from a linked-list
@param: head - pointer to the head of the linked-list
        data - data of the node to be deleted
@return: none
*/
void delete_node( Node **head, int data );

/*
@brief: Find an Euler tour, if it exists, from a given graph
@param: argc - count no. of inputs
        argv - location of input graph in the form of a text file
@return: Indicate whether Euler tour found in the given graph
*/
int main( int argc, char *argv[] )
{
    // Check if graph has been provided by the user as an input
	if ( argc < 2 )
	{
		printf( "Graph input file not provided!\n" );
		return 0;
	}

    // Start timer
    clock_t begin = clock();

    // Open input text file for reading
    FILE *ifp;
	ifp = fopen( argv[1], "r" );

    // Count the number of vertices in the graph
    int num_v = 0;
	char l[256];
	while ( fgets( l, sizeof l, ifp ) != NULL ) num_v++;
    // Revert the pointer back to the start of the text file
	rewind( ifp );

    // Create an array of empty linked list to store the adjaccency list of the graph
    Node * adj_list[num_v];
    for ( int i=0; i < num_v; i++ ) adj_list[i] = NULL;

    // Define variable to check if euler tour exists in the given graph
    int check_eulerian = 1;

    // Create an adjacency list using the input text file
    char line[1024];
    unsigned int counter = 0;

    // Increment operations count for all the above commands
    count_operations += ( 2 * num_v ) + 10;

    // Go through each line of the text file to create the adjacency list
	while ( fgets( line, sizeof line, ifp ) != NULL )
	{
        // Initialize source and destination vertices to represent an edge
        unsigned int src_vertex, dst_vertex;
        // Initialize degree of each vertex as 0
        unsigned int degree = 0;
        // Initialize finder to search for vertices in the text
		char * pch;
		pch = strtok( line, " \n\r" );
        // Find the source vertex
        // Not storing the source vertex in the adjacency since the index of array will provide us the source veretx
		sscanf( pch, "%d", &src_vertex );
		pch = strtok( NULL, " \n\r" );

        // Get various vertices forming an edge with the source vertex
		while ( pch != NULL )
		{
            // Find next destination vertex
			sscanf( pch, "%d", &dst_vertex );
            // Add vertex to the adjacency list
            push_front( &adj_list[counter], dst_vertex-1 );
			pch = strtok( NULL, " \n\r" );
            // Increment the degree of the source vertex
            degree++;
            // Increment operations count for the above commands
            count_operations += 5;
		}

        // Check if graph contains an euler tour
        if ( degree % 2 != 0 ) 
        {
            // Increment operations count by 2 for the next commands
            count_operations += 2;
            check_eulerian = 0;
            break;
        }

        // Increment counter to enter vertices in the next linked list
        counter++;
        // Increment operations count for the above commands
        count_operations += 8;
	}

    // Close the text file since adjacency list has been created
    fclose( ifp );

    // Open the output file and add whether an Euler tour exists for the graph 
    ifp = fopen( EULER_TOUR_FILE, "w+" );
    fprintf( ifp, "%d\n", check_eulerian );

    // Increment operations count for the above commands (outside of the while loop)
    count_operations += 3;

    // Check if an Euler tour exists in the graph
    if ( !check_eulerian )
    {
        // Increment operations count for the next commands and print it on the terminal
        count_operations += 6;
        printf( "Total operations: %d\n", count_operations );

        // Store total operations in another text file
        FILE *ofp;
        ofp = fopen( OPERATIONS_NUM_FILE, "w+" );
        fprintf( ofp, "Total number of operations is: %d", count_operations );
        fclose( ofp );

        // Close the output text file that stores the Euler tour if it exists
        fclose( ifp );

        printf( "The given graph does not contain an Euler tour!\n" );
        // Print overall time taken in seconds
        printf( "Time taken = %lf\n", ((double)clock()-begin)/CLOCKS_PER_SEC );
        return 0;
    }

    // Use the first vertex as the starting point
    unsigned int v = 0;
    unsigned int w = 0;

    // Initialize a linked-list to store the euler tour
    Node *euler_tour = malloc( sizeof( Node ) );
    euler_tour->num = v + 1;
    euler_tour->next = NULL;

    // Increment operations count for the above commands
    count_operations += 5;

    // Go through all the edges to find an euler tour
    while ( adj_list[v] != NULL )
    {
        // Get the other vertex corresponding to the edge v and head of linked-list associated with v
        w = adj_list[v]->num;

        // Delete all instances of the edge (v,w) from the adjacency lists
        delete_node( &adj_list[v], w );
        delete_node( &adj_list[w], v );

        // Now that we have traveled (v,w), look for next edge to travel from w
        v = w;

        // Add this edge to the Euler tour
        push_front( &euler_tour, v + 1 );

        // Increment operations count for the above commands
        // except delete node as it is being counted internally
        count_operations += 6;
    }

    // Store the Euler tour as output in a text file
    while ( euler_tour != NULL ) 
    {
        fprintf( ifp, "%d ", euler_tour->num );
        euler_tour = euler_tour->next;

        // Increment operations count for the above commands
        count_operations += 2;
    }

    // Close the output text file that stores the Euler tour if it exists
    fclose( ifp );

    // Increment operations count for the next commands, store it in an output text file, and print it on the terminal
    count_operations += 5;
    ifp = fopen( OPERATIONS_NUM_FILE, "w+" );
    fprintf( ifp, "Total number of operations is: %d", count_operations );
    fclose( ifp );
    printf( "Total operations: %d\n", count_operations );

    // Print overall time taken in seconds
    printf( "Time taken = %lf\n", ((double)clock()-begin)/CLOCKS_PER_SEC );

    // Indicate successful execution for finding an euler tour in the input graph
    return 1;
}

// Implementation of the function to add a new node to a given linked-list
void push_front( Node **head, int data )
{
    Node *new_node = malloc( sizeof( Node ) );
    // Add data to the new node
    new_node->num = data;
    // Point next of the node to the original linked-list
    new_node->next = *head;
    // Assign head to new node
    *head = new_node;
}

// Implementation of the function to delete a node to a given linked-list
void delete_node( struct Node **head, int data ) 
{
    // Increment operations count for the above commands
    // except the while loop as it is already accounted for 
    count_operations += 6;

    // Store head node
    struct Node* temp = *head, *prev;

    // If head node itself holds the data to be deleted
    if ( temp != NULL && temp->num == data )
    {
        // Change head
        *head = temp->next;
        // Free old head
        free( temp );
        return;
    }
  
    // Search for the data to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while ( temp != NULL && temp->num != data )
    {
        prev = temp;
        temp = temp->next;

        // Increment operations count
        count_operations += 2;
    }

    // If data was not present in linked list
    if ( temp == NULL ) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    // Free memory
    free( temp );
}
