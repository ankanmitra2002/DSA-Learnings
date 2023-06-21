#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	int n;
	// n is the number of observations i.e how many execution times have to be noted for the plot of graph
	int num;
	//num is the number of elements to be pushed in a particular observation
	int data;
	int top = -1,size=1;

	
	printf("Enter the number of observations\n");
	scanf("%d",&n);
	int *frequency = (int*)malloc(n*sizeof(int));
	int *arr = (int*)malloc(n*sizeof(int));
	// arr and frequency pointer for plotting graph of number of elements vs the time to push them
	double* execution_time = (double*)malloc(n*sizeof(double));
	// dynamically creating array to store exact times to push different number of random numbers in a stack
	int max=0;
	// max variable is defined for finding the maximum of the execution times which will be stored in frequency array
	for ( int i =0 ; i < n ; i++ )
	{
		
		printf("Enter the total number of items to be pushed\n");
		scanf("%d",&num);
		arr[i]=num;
		//storing the numbers corresponding to the number of random numbers for the graph
		srand(time(0));
		int*stack;
		stack= (int*)malloc(size*sizeof(int));
		//stack variable to create a stack dynamically with initial size = 1
		
		clock_t start_time,end_time;
		start_time = clock();
		// starting the clock to see execution time
		for( int j = 0 ; j < num ; j++ )
    	{
    		data = rand();
    	//	creating random numbers
    // Algorithm for the growth strategy to increase the size of stack
		if(top==size-1)
		{
			size = 2*size;
			int* newstack;
			newstack = (int*)malloc(size*sizeof(int));
			// copying the elements of stack to newstack which has double size of previous stack
			for(int i=0; i<=top; i++)
			{
				newstack[i] = stack[i];
			}
			stack = newstack;
			// now stack is pointing to the elements of the newstack,size of stack is doubled
		}
	        stack[++top]=data;
	        // pushing data to stack
		}
		end_time = clock();
  		execution_time[i] = (double)(end_time - start_time)/CLOCKS_PER_SEC;
  		// ending the clock to determine execution time
  	    frequency[i] = execution_time[i]*10000;
  	    //storing the proper scaled execution time in integer to frequency array by multiplying with 10000
  	    if(max<frequency[i])
  	    {
  	    	max=frequency[i];	
  	    	// finding the maximun of frequency array
		}
		free(stack);
		// freeing the stack
	}
	for ( int i = 0 ; i < n ; i++)
	{
    	printf("The total time of execution for pushing %d random numbers is %0.10f seconds\n",arr[i],execution_time[i]);
    	// printing the times to push different random numbers
	}
	printf("\n\n**************The graph of value of total items vs execution time (scale 1:10000) is:****************\n\n");
    int storemax = max;
    // storing the maximum exeecution time in storemax
    // Plotting the vertical graph of different n random numbers vs the time to push them
	for (int j = 0; j < storemax ; j++)
    {   
        
        for ( int k = 0 ; k < n ; k++ )
        {
          if(max>frequency[k])
          printf("\t");

          else
          printf("*       ");
        }
        printf("\n");
        max--;   
   	}
   	for (int j = 0; j < n ; j++)
   	{
   		printf("%d\t",arr[j]);	
	}
   	free(frequency);
    free(arr);
    free(execution_time);
    // freeing the memory pointed by frequency,arr and execution_time pointers
    
	return 0;		
}
