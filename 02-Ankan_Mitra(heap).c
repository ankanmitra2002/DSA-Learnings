#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void swap(int* x,int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void Heapify(int* arr,int n,int i)
{
	int largest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;
	if (( left < n ) && ( arr[left] > arr[i]))
	{
		largest = left;
	}
	if (( right < n ) && ( arr[right] > arr[largest]))
	{
		largest = right;
	}
	if ( largest != i )
	{
		swap(&arr[i],&arr[largest]);
		Heapify(arr,n,largest);
	}
}
void buildHeap(int* arr,int n)
{
	int NonleafLast = (n/2)-1;
	for ( int i = NonleafLast ; i >= 0 ; i-- )
	{
		Heapify(arr,n,i);
	}
}
int parent(int i)
{
	if ( i%2 == 1 )
	{
		return i/2;
	}
	else
	{
		return i/2 -1;
	}
}
int* insert_Heap(int* arr,int n,int key)
{
	int* newHeap = (int*)malloc((n+1)*sizeof(int));
	for ( int i = 0 ; i < n ; i++ )
	{
		newHeap[i] = arr[i];
	}
	int i = n;
	//free(arr);	
	while (( i > 0 ) && ( newHeap[parent(i)] < key ))
	{
		newHeap[i] = newHeap[parent(i)];
		i = parent(i);
	}
	newHeap[i] = key;
	//Heapify(newHeap,n+1,0);
	return newHeap;
}
void print(int* arr,int n)
{
	int j = 0;
	int index = 0;
	printf("The level order traversal for the heap structure:\n");
	while ( j < n )
	{
		int check = 0;
		int power = pow(2,j);
		for ( int i = 0 ; i < power ; i++ )
		{
			printf("%3d ",arr[index++]);
			if ( index == n )
			{
				check = 1;
				break;
			}
		}
		printf("\n");
		if ( check == 1 )
		{
			return;
		}
		j++;
	}
}
int main()
{
	int n;
	printf("Enter the number of nodes\n");
	scanf("%d",&n);
	int* arr = (int*)malloc(n*sizeof(int));
	srand(time(0));
	for ( int i = 0 ; i < n ; i++ )
	{
		arr[i] = rand()%101;		
	}
	buildHeap(arr,n);
	print(arr,n);
	int key;
	int num;
	printf("\nEnter the number of elements to be inserted\n");
	scanf("%d",&num);
	
	for ( int i = 0 ; i < num ; i++ )
	{
		printf("\nInsert the %dth element\n",i+1);
		scanf("%d",&key);
		arr = insert_Heap(arr,n,key);
		n = n+1;
	}
	printf("\nAfter the insertion heap structure will be: \n");
	print(arr,n);
	return 0;	
}
