#include<stdio.h>
#include<stdlib.h>

typedef struct sparse_matrix
{
	int row;
	int col;
	int nonzero;
}sparse; /* structure for representing rows,colulmns and nonzero values in sparse matrix */

int main(int argc,char* argv[])
{
	FILE* fptr = NULL;
	fptr = fopen("sparse.txt","r");
	/* The sparse.txt file contains the data for the sparse matrix which is given as arguement in command prompt */ 
	if ( fptr == NULL )/* if file is not found then standard error message is given as output */
	{
		fprintf(stderr,"File is not found\n");
		exit(1);
	}
	int row_count,col_count,nonzero_count;
	/* the counts of row,col,non zero elements are taken from file */
	fscanf(fptr,"%d",&row_count);
	fscanf(fptr,"%d",&col_count);
	fscanf(fptr,"%d",&nonzero_count);
	
	/* Array arr of structure sparse is taken to represent sparse matrix */
	sparse* arr = (sparse*)malloc((nonzero_count+1)*sizeof(sparse));
	/* Array transpose of structure transpose is taken to represent the transpose of sparse matrix */
	sparse* transpose = (sparse*)malloc((nonzero_count+1)*sizeof(sparse));
	arr[0].row = row_count;
	arr[0].col = col_count;
	arr[0].nonzero = nonzero_count;
	/* the data from file is taken in arr with ascending order of rows */
	for ( int i = 1 ; i <= nonzero_count ; i++ )
	{
		fscanf(fptr,"%d",&arr[i].row);
		fscanf(fptr,"%d",&arr[i].col);
		fscanf(fptr,"%d",&arr[i].nonzero);
	}
	printf("The sparse matrix taken from file is: \n");
	printf("Row\tColumn\tNonzero values\n");
	for ( int i = 0 ; i <= nonzero_count ; i++ )/* printing the representation of sparse matrix */
	{
		printf("%3d\t%3d\t%3d\n",arr[i].row,arr[i].col,arr[i].nonzero);
	}
	/* The col_count of arr and row_count of transpose are same and vice-versa */
	transpose[0].row = col_count;
	transpose[0].col = row_count;
	transpose[0].nonzero = nonzero_count;
	for ( int column = 0 , i = 1 ; column < col_count ; column++ )/* Traversing the outer loop for total column counts*/
	{
		for ( int j = 1 ; j <= nonzero_count ; j++ )/* Traversing the inner loop for total nonzero element counts*/
		{
			if ( arr[j].col == column )/* Transposing by checking for each column of arr starting from 0 */
			{
				transpose[i].row = arr[j].col;
				transpose[i].col = arr[j].row;
				transpose[i].nonzero = arr[j].nonzero;
				i++;
			}
		}
	}
	printf("The transpose of the sparse matrix is: \n");/* Printing the transpose of sparse matrix */
	printf("Row\tColumn\tNonzero values\n");
	for ( int i = 0 ; i <= nonzero_count ; i++ )
	{
		printf("%3d\t%3d\t%3d\n",transpose[i].row,transpose[i].col,transpose[i].nonzero);
	}
	fclose(fptr);/* closing the file */
	free(arr);/* freeing the memory */
	free(transpose);
	return 0;	
}
