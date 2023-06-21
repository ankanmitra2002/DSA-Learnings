#include<stdio.h>

int main()
{
	int k;
	printf("Enter a positive integer upto which pythagorean triples have to be shown\n");
	scanf("%d",&k);
	/* The input k is taken from user */
	
	printf("The pythagorean triples between 1 to %d are:\n",k);
	int a,b,c;
	/* The variables for printing pythagorean triples are declared */
	/* The loops for finding the pythagorean triples is written below */ 
	for( b = 1 ; b < k ; b++ )
	{
		/* At first b is fixed and for each b the inner loop for a is performed where a<=b */
		for ( a = 1 ; a <=b ; a++ )
		{
			int square = a*a + b*b ;
			/*The sum of the squares combination is stored in square variable */
			if(square > k*k)
			break;
			/* When square exceeds the range the loop is broken */
			else
			{ 
			 	 c = 1;
			 	while ( c <= k )
			 	{
					if(square == c*c)
				/* The perfect square withen the input number k which can be expressed as a^2 + b^2 = c^2 are found */
				    {
						printf("%3d %3d %3d\n",a,b,c);
				/* The pythagorean triples a,b,c where 0<a<=b<c<=k are printed */		
				    }
				   	c++;
					   		
			 	}
			}
		}
	}
return 0;	
}
