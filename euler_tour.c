#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node 
{
    // data of the node
    int num;
    // address of the next node
    struct Node *next;
} Node;

int push_front( Node **head, int data )
{
    Node *new_node = malloc( sizeof( Node ) );
    int success = new_node != NULL;

    if ( success )
    {
        new_node->num = data;
        new_node->next = *head;
        *head = new_node;
    }

    return success;
}

void output( Node **head )
{
    for( Node *current =*head; current != NULL; current = current->next )
    {
        printf( "%d ", current->num );
    }
    printf( "%s", "NULL" );
}

void display( Node **set, size_t n )
{
    for ( size_t i = 0; i < n; i++ )
    {
        output( set++ );
        putchar( '\n' );
    }
}

int main( int argc, char *argv[] )
{
    FILE *ifp;

	if ( argc < 2 )
	{
		printf( "Graph input file not provided!\n" );
		return 0;
	}
    clock_t begin = clock();

    // read input from file
	ifp = fopen( argv[1], "r" );
    // ifp = fopen( "input/input_example.txt", "r" );

    // count the number of vertices in the graph
    int num_v = 0;
	char l[256];
	while ( fgets( l, sizeof l, ifp ) != NULL ) num_v++;
	rewind( ifp );

    // create an array of empty linked list (adjacency list)
    Node * adj_list[num_v];
    for ( int i=0; i < num_v; i++ ) adj_list[i] = NULL;

    char line[1024];
    unsigned int counter = 0;
	while (fgets(line, sizeof line, ifp) != NULL)
	{
        int src_vertex, dst_vertex;
		char * pch;
		pch = strtok(line, " \n\r");
		sscanf(pch, "%d", &src_vertex);
		pch = strtok(NULL, " \n\r");

		while (pch != NULL)
		{
			// there is an edge from src_vertex to dst_vertex
			sscanf(pch, "%d", &dst_vertex);
            push_front( &adj_list[counter], dst_vertex-1 );
			pch = strtok(NULL, " \n\r");
		}
        counter++;
	}
    // display( adj_list, sizeof( adj_list )/sizeof( *adj_list ) );
    fclose( ifp );
    printf("Time taken = %lf\n", ((double)clock()-begin)/CLOCKS_PER_SEC);
}