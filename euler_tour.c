/**
 * @file    euler_tour.c
 * @author  Umang Rastogi
 * @brief   Check an Euler tour possible for the given and find the tour if it exists
 */

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
unsigned int max_edge_operations = 0;

// Define a new structure for linked-lists
typedef struct Node 
{
    // Data of the node
    int num;
    // Address of the next node
    struct Node *next;
} Node;

/**
 * @brief: Add a new node to a given linked-list
 * @param: head - pointer to the head of the linked-list
 *         data - data of the new node to be added
 * @return: none
 */
void push_front( Node **head, int data );

/**
 * @brief: Delete a node from a given linked-list
 * @param: head - pointer to the head of the linked-list
 *         data - data of the node to be deleted
 * @return: none
 */
void delete_node( Node **head, int data );

/**
 * @brief: Find an Euler tour, if it exists, from a given graph
 * @param: argc - count no. of inputs
 *         argv - location of input graph in the form of a text file
 * @return: Indicate whether Euler tour found in the given graph
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

    // Create an adjacent list using the input text file
    char line[1024];

    // Initialize source and destination vertices to represent an edge and degree
    unsigned int src_vertex, dst_vertex, degree;

    // Increment operations count for all the above commands
    // excluding the file reading commands
    count_operations +=  num_v + 5;

    // Go through each line of the text file to create the adjacent list
	while ( fgets( line, sizeof line, ifp ) != NULL )
	{
        // Start degree of each vertex with 0
        degree = 0;
        // Initialize finder to search for vertices in the text
		char * pch;
		pch = strtok( line, " \n\r" );
        // Find the source vertex
		sscanf( pch, "%d", &src_vertex );
		pch = strtok( NULL, " \n\r" );

        // Get various vertices forming an edge with the source vertex
		while ( pch != NULL )
		{
            // Find next destination vertex
			sscanf( pch, "%d", &dst_vertex );
            // Add vertex to the adjacent list
            push_front( &adj_list[src_vertex - 1], dst_vertex - 1 );
			pch = strtok( NULL, " \n\r" );
            // Increment the degree of the source vertex
            degree++;
		}

        // Check if graph contains an euler tour
        if ( degree % 2 != 0 ) 
        {
            // Increment operations count by 2 for the next commands
            count_operations += degree + 3 + 2;

            check_eulerian = 0;
            break;
        }

        // Increment operations count for above commands
        // Note that most of the commands in this loop are related reading the input file, hence they have been excluded
        // Only the ones related to degree evaluation of a vertex have been included towards the count of operations
        count_operations += degree + 3;
	}

    // Close the text file since adjacent list has been created
    fclose( ifp );

    // Open the output file and add whether an Euler tour exists for the graph 
    ifp = fopen( EULER_TOUR_FILE, "w+" );
    fprintf( ifp, "%d\n", check_eulerian );

    // Check if an Euler tour exists in the graph
    if ( !check_eulerian )
    {
        // Increment operations count for the 3 print statements
        // Operations related to editing output files are excluded from count
        count_operations += 3;
        printf( "Total operations: %d\n", count_operations );

        // Store total operations in another text file
        FILE *ofp;
        ofp = fopen( OPERATIONS_NUM_FILE, "w+" );
        fprintf( ofp, "Maximum number of operations charged to any single edge is: %d\n", max_edge_operations );
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
    unsigned int prev_cnt, temp;

    // Initialize a linked-list to store the euler tour
    Node *euler_tour = malloc( sizeof( Node ) );
    euler_tour->num = v + 1;
    euler_tour->next = NULL;

    // Increment operations count for the above commands
    count_operations += 5;

    // Go through all the edges to find an euler tour
    while ( adj_list[v] != NULL )
    {
        // For counting commands pertaining to an edge
        prev_cnt = count_operations;

        // Get the other vertex corresponding to the edge v and head of linked-list associated with v
        w = adj_list[v]->num;

        // Delete all instances of the edge (v,w) from the adjacent lists
        delete_node( &adj_list[v], w );
        delete_node( &adj_list[w], v );

        // Now that we have traveled (v,w), look for next edge to travel from w
        v = w;

        // Add this edge to the Euler tour
        push_front( &euler_tour, v + 1 );

        // Get the maximum no. of operations on any edge
        temp = count_operations - prev_cnt;
        if (temp > max_edge_operations) max_edge_operations = temp;

        // Increment operations count for the above commands
        // except delete node as it is being counted internally
        count_operations += 6;
    }

    // Store the Euler tour in output file
    while ( euler_tour != NULL ) 
    {
        fprintf( ifp, "%d ", euler_tour->num );
        euler_tour = euler_tour->next;
    }

    // Close the output text file that stores the Euler tour if it exists
    fclose( ifp );

    // Increment operations count for the 2 print statements below and store it in an output text file
    count_operations += 2;
    // Print total no. of operations
    printf( "Total operations: %d\n", count_operations );

    // Write the total no. of operations to the output file
    ifp = fopen( OPERATIONS_NUM_FILE, "w+" );
    fprintf( ifp, "Maximum number of operations charged to any single edge is: %d\n", max_edge_operations );
    fprintf( ifp, "Total number of operations is: %d", count_operations );
    fclose( ifp );

    // Print overall time taken in seconds
    printf( "Time taken = %lf\n", ((double)clock()-begin)/CLOCKS_PER_SEC );

    // Indicate successful execution for finding an euler tour in the input graph
    return 1;
}

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
