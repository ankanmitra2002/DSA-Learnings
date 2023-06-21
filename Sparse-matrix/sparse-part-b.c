#include<stdio.h>
#include<stdlib.h>

typedef struct sparse_matrix
{
	int row;
	int col;
	int nonzero;
}sparse; /* structure for representing rows,colulmns and nonzero values in sparse matrix */

int main()
{
	int row_count,col_count,nonzero_count;
	/* the counts of row,col,non zero elements are taken from user */
	printf("Enter the number of rows in sparse matrix\n");
	scanf("%d",&row_count);
	printf("Enter the number of columns in sparse matrix\n");		
	scanf("%d",&col_count);
	printf("Enter the number of nonzero elements in sparse matrix\n");
	scanf("%d",&nonzero_count);
	
	/* Array arr of structure sparse is taken to represent sparse matrix */
	sparse* arr = (sparse*)malloc((nonzero_count+1)*sizeof(sparse));
	/* Array arr of structure transpose is taken to represent the transpose of sparse matrix */
	sparse* transpose = (sparse*)malloc((nonzero_count+1)*sizeof(sparse));
	/* Array for frequency of non zero elements in each column */
	int* frequency = (int*)calloc(col_count,sizeof(int));
	/* Array startingPosition for the starting positions of columns where non zero elements are present */
	int* startingPosition = (int*)calloc(col_count,sizeof(int));
	
	arr[0].row = row_count;
	arr[0].col = col_count;
	arr[0].nonzero = nonzero_count;
	/* Taking input data of sparse matrix with increasing order of rows and columns */
	for ( int i = 1 ; i <= nonzero_count ; i++ )
	{
		printf("Enter the row index for %dth element in sparse matrix\n",i);
		scanf("%d",&arr[i].row);
		printf("Enter the column index for %dth element in sparse matrix\n",i);
		scanf("%d",&arr[i].col);
		frequency[arr[i].col]++;
		/* calculating the frequency of non zero elements in each column */
		printf("Enter the %dth element in sparse matrix\n",i);
		scanf("%d",&arr[i].nonzero);
	}
	printf("The sparse matrix taken from the user is: \n");/* printing the representation of sparse matrix */
	printf("Row\tColumn\tNonzero values\n");
	for ( int i = 0 ; i <= nonzero_count ; i++ )
	{
		printf("%3d\t%3d\t%3d\n",arr[i].row,arr[i].col,arr[i].nonzero);
	}
	startingPosition[0] = 1;/* Initial starting position of column 0 is 1 in transpose matrix */
	for ( int i = 1 ; i < col_count ; i++ )
	{
		startingPosition[i] = startingPosition[i-1] + frequency[i-1];
		/* starting position of ith column comes after all the elements of i-1 th column so frequency[i-1] is also added */
	}
	/* The col_count of arr and row_count of transpose are same and vice-versa */
	transpose[0].row = col_count;
	transpose[0].col = row_count;
	transpose[0].nonzero = nonzero_count;
	for ( int i = 1 ; i <= nonzero_count ; i++ )/* Transposing */
	{		
		transpose[startingPosition[arr[i].col]].row = arr[i].col;
		transpose[startingPosition[arr[i].col]].col = arr[i].row;
		transpose[startingPosition[arr[i].col]].nonzero = arr[i].nonzero;
		startingPosition[arr[i].col]++;
	/* Increasing the startingPosition for a respective column as the same column if encountered,it will come exactly after it */
	}	
	printf("The transpose of the sparse matrix is: \n");/* Printing the transpose of sparse matrix */
	printf("Row\tColumn\tNonzero values\n");
	for ( int i = 0 ; i <= nonzero_count ; i++ )
	{
		printf("%3d\t%3d\t%3d\n",transpose[i].row,transpose[i].col,transpose[i].nonzero);
	}	
	/* freeing the memory */
	free(arr);
	free(transpose);
	free(frequency);
	free(startingPosition);
	return 0;	
}

