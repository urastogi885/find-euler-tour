#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a new structure for singly-linked lists
typedef struct Node 
{
    // Data of the node
    int num;
    // Address of the next node
    struct Node *next;
} Node;

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

void delete_node(struct Node **head, int data) 
{ 
    // Store head node 
    struct Node* temp = *head, *prev; 
  
    // If head node itself holds the data to be deleted 
    if (temp != NULL && temp->num == data) 
    { 
        *head = temp->next;   // Changed head 
        free(temp);               // free old head 
        return; 
    } 
  
    // Search for the data to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && temp->num != data) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If data was not present in linked list 
    if (temp == NULL) return; 
  
    // Unlink the node from linked list 
    prev->next = temp->next; 

    // Free memory 
    free(temp);
}

const char * get_output_filename(char *input_filename)
{
    // Define variable to store name of the output file
    const char *filename;

    if ( strstr(input_filename, "in1.txt") != NULL )  filename = "A1.txt";
    else if ( strstr(input_filename, "in2.txt") != NULL )  filename = "A2.txt";
    else if ( strstr(input_filename, "in3.txt") != NULL )  filename = "A3.txt";
    else if ( strstr(input_filename, "in4.txt") != NULL )  filename = "A4.txt";
    else if ( strstr(input_filename, "in5.txt") != NULL )  filename = "A5.txt";
    else    filename = "A.txt";
    return filename;
}

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

    // Read input from file
    FILE *ifp;
    // TODO: May be use a loop to run for all given input files
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
    // Go through each line of the text file
	while (fgets(line, sizeof line, ifp) != NULL)
	{
        unsigned int src_vertex, dst_vertex;
        unsigned int degree = 0;
		char * pch;
		pch = strtok(line, " \n\r");
        // Get source vertex    // TODO: remove the comment below. add it to the report instead 
        // not storing the source vertex since the index of array will provide us the source veretx
		sscanf(pch, "%d", &src_vertex);
		pch = strtok(NULL, " \n\r");

        // Get various vertices forming an edge with the source vertex
		while (pch != NULL)
		{
			sscanf(pch, "%d", &dst_vertex);
            // Add vertex to the adjacency list
            push_front( &adj_list[counter], dst_vertex-1 );
			pch = strtok(NULL, " \n\r");
            degree++;
		}

        // Check if graph contains an euler tour
        if ( degree % 2 != 0 ) 
        {
            check_eulerian = 0;
            break;
        }

        // Increment counter to enter vertices in the next linked list
        counter++;
	}

    // Close the text file since adjacency list has been created
    fclose( ifp );

    // Open the output file and add whether an Euler tour exists for the graph 
    ifp = fopen( get_output_filename(argv[1]), "w+" );
    fprintf( ifp, "%d\n", check_eulerian);

    // Check if an Euler tour exists in the graph
    if ( !check_eulerian )
    {
        printf("The given graph does not contain an Euler tour!\n");
        // Close the output file
        fclose( ifp );
        return 0;
    }

    // Use the first vertex as the starting point
    unsigned int v = 0;
    unsigned int w = 0;

    // Initialize a linked-list to store the euler tour
    Node *euler_tour = malloc( sizeof( Node ) );
    euler_tour->num = v + 1;
    euler_tour->next = NULL;

    // Go through all the edges to find an euler tour
    while ( adj_list[v] != NULL )
    {
        // Get the other vertex corresponding to the edge v and head of linked-list associated with v
        w = adj_list[v]->num;

        // Delete edge (v,w) and (w,v)
        delete_node( &adj_list[v], w );
        delete_node( &adj_list[w], v );

        // Now that we have traveled (v,w), look for next edge to travel from w
        v = w;

        // Add this edge to the Euler tour
        push_front( &euler_tour, v + 1);
    }

    // Print the Euler tour
    // TODO: store this in a text file
    while (euler_tour != NULL) 
    {
        printf( " %d ", euler_tour->num );
        fprintf( ifp, "%d ", euler_tour->num);
        euler_tour = euler_tour->next;
    }
    printf( "\n" );

    fclose( ifp );

    // Print overall time taken in seconds
    printf("Time taken = %lf\n", ((double)clock()-begin)/CLOCKS_PER_SEC);

    // Indicate successful execution for finding an euler tour in the input graph
    return 1;
}