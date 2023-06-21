#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>
/* quick_sort algorithm and the partition function */
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
    }
    int temp = arr[i+1]; 
    arr[i+1] = arr[right];
    arr[right] = temp;
    return i+1;
}
void quick_sort(int* arr,int left,int right)
{
    if ( left < right )
    {
        int part = partition(arr,left,right);
        quick_sort(arr,left,part-1);
        quick_sort(arr,part+1,right);
    }
}

int main(){
	/* Generating 2^0 to 2^19 files which will contain random numbers and their 2 copies one for ascending,one for descending */
    for( int i = 0 ; i < 20 ; i++ )
    {
        int length=pow(2,i);
        int* arr=(int *)malloc(length*sizeof(int));
        FILE *fptr,*fasc,*fdesc;/* 3 FILE pointers for three types */
        char* str=(char*)malloc(100*sizeof(char));
        sprintf(str,"E:\\sortingAssignment\\sortingfiles\\input_size-(2^%d).txt",i);
        fptr=fopen(str,"w");/* creating or opening file in "write" mode */
        
        srand(time(0));/* setting time(0) in srand() to generate different random numbers at different time */
        int r,k;
        for(int i = 0;i < length;i++)
        {
            r = rand()%INT_MAX + 1;
            k = -r;
    		/* desciding randomly when to give negative and positive random numbers */
            if(r % 2 == 0)
            {
                fprintf(fptr,"%d\n",r);
                arr[i] = r;
            }
            else
            {
                fprintf(fptr,"%d\n",k);
                arr[i] = k;
            }
        }
        for ( int j = 0 ; j < length ; j++ )
        {
            fscanf(fptr,"%d",&arr[j]);
        }
        quick_sort(arr,0,length-1);/*sorting the array by quick_sort */
        
        char* str1=(char*)malloc(100*sizeof(char));
        char* str2=(char*)malloc(100*sizeof(char));
       	sprintf(str1,"E:\\sortingAssignment\\sortingfiles\\ascending_size-(2^%d).txt",i);/* for the ascending file */
       	sprintf(str2,"E:\\sortingAssignment\\sortingfiles\\descending_size-(2^%d).txt",i);/* for the descending file */
        fasc = fopen(str1,"w");
        fdesc = fopen(str2,"w");
        
        for ( int j = 0 ; j < length ; j++ )
        {
            fprintf(fasc,"%d\n",arr[j]);/* storing the sorted numbers */
        }
        for ( int j = length-1 ; j >= 0 ; j-- )
        {    
            fprintf(fdesc,"%d\n",arr[j]);/* storing the sorted numbers in descending order */
        }
        /* closing the files and freeing the memory used */
        fclose(fptr);
        fclose(fasc);
        fclose(fdesc);
        free(arr);
        free(str);
        free(str1);
        free(str2);
    }
    return 0;
}
