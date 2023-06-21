#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include<math.h>

unsigned long int compare_count = 0;/* global variable for counting comparison*/
/* insertion sort function */
void insertion_sort(int* arr,int left,int right)
{
	compare_count = 0;
	int insert;
	int check = 0;
	for ( int i = left+1 ; i <= right ; i++ )
	{
		insert = arr[i];
		int j;
		check = 0;
		for ( j = i-1 ; (( j >= 0 ) && ( arr[j] > insert )); j-- )
		{
			arr[j+1] = arr[j];
			compare_count++;
			check = 1;
		}
		if ( check == 0 )
		{
		    compare_count++;
		}
		
		arr[j+1] = insert;
	}
}
/* bubble sort function */
void bubble_sort(int *arr,int left,int right ) 
{  
	int temp,sort=1;
	compare_count = 0;
    for ( int i = left ; i < right ; i++ )
        {    
			sort=1;
            for ( int j = 0 ; j < right-i ; j++ )
            { 
               if ( arr[j] > arr[j+1] )
               {
                   temp=arr[j];
                   arr[j]=arr[j+1];
                   arr[j+1]=temp;
                   sort=0;
               } 
            	compare_count++;   
            }
            if(sort==1)
            break;
        }
}
/* selection sort function */
void selection_sort(int* arr,int left,int right)
{
	int minindex,select;
	compare_count = 0;
	
	for ( int i = 0 ; i < right ; i++ )
	{
		minindex = i;
		for ( int j= i+1 ; j <= right ; j++ )
		{
			if ( arr[j] < arr[minindex] )
			{
				minindex = j;
			}
			compare_count++;
		}
		select = arr[i];
		arr[i] = arr[minindex];
		arr[minindex] = select;
	}
}
/* function for merge 2 sorted arrays */
void merging(int* arr,int left,int mid,int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;
    int* copy = (int*)malloc((right - left + 1)*sizeof(int));
    while (( i <= mid ) && ( j <= right ))
    {
        if ( arr[i] < arr[j])
        {
            copy[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            copy[k] = arr[j];
            k++;
            j++;
        }
        compare_count++;
    }
    while ( i <= mid )
    {
        copy[k] = arr[i];
        k++;
        i++;
    }
    while ( j <= right )
    {
        copy[k] = arr[j];
        k++;
        j++;
    }
    for ( int i = 0 ; i <= (right - left) ; i++)
    {
        arr[left+i] = copy[i];
    }
    free(copy);/* freeing the extra space */
}
/* recursive merge sort function */
void merge_sort(int* arr,int left,int right)
{
    int mid;
    if ( left < right )
    {
        mid = (left + right)/2;
        merge_sort(arr,left,mid);
        merge_sort(arr,mid+1,right);
        merging(arr,left,mid,right);
    }
}
/* partition for quick sort */
int partition(int* arr,int left,int right)
{
    int pivot = arr[right];
    int i = left-1;
    
    for ( int j = left; j < right ; j++ )
    {
        if ( arr[j] < pivot )
        {
            i++;
            int temp = arr[i]; 
            arr[i] = arr[j];
            arr[j] = temp;
        }
        compare_count++;
    }
    int temp = arr[i+1]; 
    arr[i+1] = arr[right];
    arr[right] = temp;
    return i+1;
}
/* recursive quick sort function */
void quick_sort(int* arr,int left,int right)
{
    if ( left < right )
    {
        int part = partition(arr,left,right);
        quick_sort(arr,left,part-1);
        quick_sort(arr,part+1,right);
    }
}
/* function to copy to an array from original array */
int* array_copy(int* arr_original,int size )
{
    int* copy = (int*)malloc(sizeof(int)*size);
    for ( int i = 0 ; i < size ; i++ )
    {
        copy[i] = arr_original[i];
    }
    return copy;
}

int main(int argc,char* argv[])
{
	if ( argc != 4 ) /* user should give 4 commands */
	{
		fprintf(stderr,"Enter in the format [program.exe] [input_size] [input_file.txt] [output_file.csv]\n");
		/* the .exe file is the sort_graph.exe */
/* input_size is the number of random numbers in the text file of (2^0 to 2^18) files and their ascending and descending input files also*/
	/* output_file.csv is the csv file where the sorting algo,size,and number of comparisons are listed */
		exit(0);
	}
	int size = 0;
	if (( sscanf(argv[1],"%d",&size) != 1) || ( size <= 0 ) || ( size != 1 && size % 2 != 0 ))
	{
		fprintf(stderr,"Give size as exponents of 2 from 2^0 to 2^18 \n");
		exit(0);
	}
    FILE* fptr = fopen(argv[2],"r");/* reading the input file */
    if ( fptr == NULL )
    {
        fprintf(stderr,"%s file is not found\n",argv[2]);
        exit(0);
    }
    int* arr = (int*)malloc(sizeof(int)*size);/* array to store the data from input file */
    for ( int i = 0 ; i < size ; i++ )
    {
        fscanf(fptr,"%d",&arr[i]);
    }
    fclose(fptr);/* closing the input file */
    FILE* fout = fopen(argv[3],"a");/* opening in append mode so that no data is erased in csv file */
    
    int* copy = array_copy(arr,size);/* copying from original array */
    /* selection sort */
    compare_count = 0;
    selection_sort(copy,0,size-1);
    fprintf(fout,"%s,%d,%lu\n","select",size,compare_count);/* entering in csv file in this style */
    free(copy);

	copy = array_copy(arr,size);/* copying from original array */
	/* bubble sort */
	compare_count = 0;
    bubble_sort(copy,0,size-1);
    fprintf(fout,"%s,%d,%lu\n","bubble",size,compare_count);
    free(copy);
    
    copy = array_copy(arr,size);/* copying from original array */
	/* insertion sort */
	compare_count = 0;
    insertion_sort(copy,0,size-1);
    fprintf(fout,"%s,%d,%lu\n","insert",size,compare_count);
    free(copy);
    
    copy = array_copy(arr,size);/* copying from original array */
	/* merge sort */
	compare_count = 0;
    merge_sort(copy,0,size-1);
    fprintf(fout,"%s,%d,%lu\n","merge",size,compare_count);
    free(copy);
    
    copy = array_copy(arr,size);/* copying from original array */
	/* quick sort */
	compare_count = 0;
    quick_sort(copy,0,size-1);
    fprintf(fout,"%s,%d,%lu\n","quick",size,compare_count);
    free(copy);
    free(arr);/* freeing the original array */
    fclose(fout);/* closing the output file */
    
    return 0;
}
