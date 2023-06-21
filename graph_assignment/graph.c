#include<stdio.h>
#include<stdlib.h>
typedef struct adjacency_list   
{
	int data;
	struct adjacency_list* next;
}List;
List* create(int data)
{
	List* ptr = (List*)malloc(sizeof(List));
	ptr->data = data;
	ptr->next = NULL;
}
List* list_making(List* head,int** matrix,int index,int num_vertices)
{
	List* ptr = head;
	for ( int i = 0 ; i < num_vertices ; i++ )
	{
		if ( matrix[index][i] == 1 )
		{
			List* temp = create(i);
			ptr->next = temp;
			ptr = ptr->next;
		}
	}
	return head;
}
int row_count(int** matrix,int index,int num_vertices)
{
	int count = 0;	
	for ( int i = 0 ; i < num_vertices ; i++ )
	{
    	count += matrix[index][i];
	}
	return count;
}
int col_count(int** matrix,int index,int num_vertices)
{
	int count = 0;	
	for ( int i = 0 ; i < num_vertices ; i++ )
	{
    	count += matrix[i][index];
	}
	return count;
}
void traversal(List* head)
{
	List* ptr = head;
	while( ptr != NULL )
	{
		printf("%d->",(ptr->data)+1);
		ptr = ptr->next;
	}
}
int main(int argc,const char* argv[])
{
	FILE* fptr;
	fptr = fopen(argv[1],"r");// Reading the file
	
	if ( fptr == NULL )
	{
		fprintf(stderr,"File %s is not found\n",argv[1]);
		fprintf(stderr,"Please enter in the format [program_name.exe] [file_name.txt] as commands\n");
		exit(1);
	}
	char graph_type;
	fscanf(fptr,"%c",&graph_type);// Checking the type of the graph	
	int num_vertices;
	fscanf(fptr,"%d",&num_vertices);// number of vertices
	
	int** matrix = (int**)malloc(num_vertices*sizeof(int*));	
	for ( int i = 0 ; i < num_vertices ; i++ )
	{
		matrix[i] = (int*)malloc(num_vertices*sizeof(int));
		for ( int j = 0 ; j < num_vertices ; j++ )
		{
			fscanf(fptr,"%d",&matrix[i][j]);
		}
	}
	fclose(fptr);// Closing the file
	List** list_array = (List**)malloc(num_vertices*sizeof(List*));
	// Creating adjacency list
	for ( int i = 0 ; i < num_vertices ; i++ )
	{
		list_array[i] = create(i);
		list_array[i] = list_making(list_array[i],matrix,i,num_vertices);
	}	
	// Printing the adjacency list
	printf("The adjacency list from the matrix given in the text file is:\n");
	for ( int i = 0 ; i < num_vertices ; i++ )
	{
		traversal(list_array[i]);
		printf("\n");
	}
	// Degrees of the vertices of undirected graph
	int degree_count = 0;
	if ( graph_type == 'U')
	{
		for ( int i = 0 ; i < num_vertices ; i++ )
		{
			printf("The degree of the vertex %d is : %d\n",i+1,row_count(matrix,i,num_vertices));
			degree_count += row_count(matrix,i,num_vertices);
		}	
	}
	// Degrees of the vertices of directed graph
	else
	{
		for ( int i = 0 ; i < num_vertices ; i++ )
		{
			printf("The in-degree and out-degree of the vertex %d is : %d and %d\n",i+1,col_count(matrix,i,num_vertices),row_count(matrix,i,num_vertices));
			degree_count += row_count(matrix,i,num_vertices);
		}	
	}	
	// Total numeber of edges of undirected graph			
	if ( graph_type == 'U')
	{
		printf("The total number of edges of the graph is : %d\n",degree_count/2);
	}
	// Total number of edges of directed graph
	else
	{
		printf("The total number of edges of the graph is : %d\n",degree_count);	
	}
	// Adjacent vertices for vertices in undirected graph
	if ( graph_type == 'U')
	{
		for ( int i = 0 ; i < num_vertices ; i++ )
		{
			printf("The adjacent vertices of the vertex %d is : ",i+1);
			for ( int j = 0 ; j < num_vertices ; j++ )
			{
				if ( matrix[i][j] == 1 )
				{
					printf("%d ",j+1);
				}
			}
			printf("\n");
		}
	}
	// Adjacent vertices for vertices in directed graph
	else
	{
		for ( int i = 0 ; i < num_vertices ; i++ )
		{
			printf("The adjacent vertices of the vertex %d is : ",i+1);
			for ( int j = 0 ; j < num_vertices ; j++ )
			{
				if ( matrix[i][j] == 1 )
				{
					printf("%d ",j+1);
				}
				else if ( matrix[j][i] == 1 )
				{
					printf("%d ",j+1);
				}
			}
			printf("\n");
		}
	}	
	return 0;
}
