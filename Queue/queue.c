#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define CIRCULAR_QUEUE_SIZE 16 /* setting the size of circular queue as 16 */

int queuesize = 16; /* initai size of normal queue is set as 16 */
int front = -1;/* front,rear are set as -1 */
int rear = -1;
int fullcount = 0;/* fullcount,emptycount counts the number of queuefull,queueempty conditions */
int emptycount = 0;
int queuefull = 0;/* queuefull checks when normal queue is full and when the size is needed to be increased */


void QueueFull()
{
	fullcount++;/* QueueFull() function contains count of queuefull conditions */
}
void QueueEmpty()
{
	emptycount++;/* QueueEmpty() function contains count of queueempty conditions */
}

/* function to enqueue */
void enQueue(int *queue,int element)
{
	if ( rear == queuesize-1 )
	{
		 QueueFull();
		 queuefull=1;/* when rear reaches the end then queuefull is set to 1 to denote the queuefull condition */
	}
	else
	{
		queue[++rear] = element;/* enqueueing element */
	}
}
/* function to dequeue */
int deQueue(int *queue)
{
	if ( rear == front )
	{
		 QueueEmpty();
		 return -1;
	}
	else
	{
		return queue[++front];/* dequeueing */
	}
}

/* enqueueing for the circular queue */
void enCircularQueue(int *circularqueue,int element)
{
	if(front == -1 && rear == CIRCULAR_QUEUE_SIZE-1 )
	{
		QueueFull();/* speacial case of queuefull condition */		
	}
	/* queuefull condition for circular queue */
	else if ( front == (rear + 1)%CIRCULAR_QUEUE_SIZE )
	{
		QueueFull(); 
		
	}
	else
	{
		rear = (rear + 1)%CIRCULAR_QUEUE_SIZE;
		circularqueue[rear] = element;/* enqueueing */
	}
}

/* dequeueing for the circular queue */
int deCircularQueue(int *circularqueue)
{
	if ( rear == front )
	{
		 QueueEmpty();
		 return -1;
	}
	else
	{
		front = (front + 1)%CIRCULAR_QUEUE_SIZE;
		return circularqueue[front];/* dequeueing */
	}
}


int main()
{
	int* queue = malloc(queuesize*sizeof(int));/* formation of queue */
	int* circularqueue = malloc(CIRCULAR_QUEUE_SIZE*sizeof(int));/* formation of circular queue */
	
	printf("*****The number of queuefull and queueempty conditions of a normal queue after successive 25 operations*****\n\n");
	 srand(time(0));/* srand is set with time(0) to generate different random numbers at different time */
	 
	int deletion = 0;/* variable for storing dequeueing element */
	for ( int i = 1 ; i <= 1000 ; i++ )
	{
	   	
		int random = rand()%2;/* generating 0 or 1 as random number */
		if ( random == 0 )
		{
			enQueue(queue,random);/* 0 is chosen to enqueue */
			/* if quuefull is 1 i.e rear at the end so we need to increase the size for the current enqueue*/
			if ( queuefull == 1 )
			{
				queuesize = queuesize*2;/* applying growth strategy to increase the size */
				int* newqueue;
				newqueue = (int*)malloc(queuesize*sizeof(int));
				
				for(int i=0; i<=rear; i++)/* copying the previous elements */
				{
					newqueue[i] = queue[i];
				}
				queue = newqueue;
				queue[++rear] = random;/* enqueueing the element after increased size */
				queuefull = 0;/* queuefull is again set to zero */
				
			}
		}
		else
		{
			deletion = deQueue(queue);/* if random = 1, dequeue option is chosen */ 
		}
		
		if ( i%25 == 0 )
		{	
			/* printing queuefull,queueempty condition after every 25 operations */		
			printf("\nThe number of queuefull conditions are %d after %d operation \n",fullcount,i);
			printf("The number of queueempty conditions are %d after %d operation \n",emptycount,i);
		}
		
		
	}
	fullcount = 0,emptycount = 0;/* fullcount,emptycount are set to 0 for counting circular queue operations */
	
	printf("\n\n**The number of queuefull and queueempty conditions of a circular queue after successive 25 operations**\n\n");		
	for ( int i = 1 ; i <= 1000 ; i++ )
	{
		int random = rand()%2;/* generating 0 or 1 as random number */
		if ( random == 0 )
		{
			enCircularQueue(circularqueue,random);/* 0 is chosen to enqueue */		
		}
		else
		{
			deletion = deCircularQueue(circularqueue);/* if random = 1, dequeue option is chosen */
		}
		if ( i%25 == 0 )
		{	
			/* printing queuefull,queueempty condition after every 25 operations */		
			printf("\nThe number of queuefull conditions are %d after %d operation \n",fullcount,i);
			printf("The number of queueempty conditions are %d after %d operation \n",emptycount,i);
		}
	}
	free(queue);/* freeing the used memory after desired output is generated */
	free(circularqueue);
	return 0;
}


