#include<stdio.h>

int main()
{
	double h;
	/* Here h should be very close to zero like 0.0001,0.00003 etc.*/
	printf("Enter a very small value of h which tends to zero\n");
	scanf("%lf",&h);
	
	double l,r;
	printf("Enter the left boundary\n");
	scanf("%lf",&l);
	printf("Enter the right boundary\n");
	scanf("%lf",&r);
	
	
	
	double a1 = l; 
	/*The a1 variable will be the lower bounds in every intervals starting from the extreme lower bound */
	double a2 = l+h;
	/*The a2 variable will be the upper bounds in every intervals starting from the extreme lower bound */ 
	
	long int interval =((r-l)/h);
	/* The number of interval is an integral multiple of h */
	
	double integral_sum = 0;
	/* integral_sum variable is taken to store the successive results after each iteration and finally it will give the value of the approximate result afetr final iteration */
	for ( long int i = 1 ; i <= interval ; i++ )
	{
		double x = (a1 + a2)/2;
	/* x is the variable whose function is to be integrated and it is taken as the averge of the lower and upper bounds in every interval */
		
		double function = 8*x*x*x + 12*x*x + x + 1;
	/* A function of x is assumed as f(x) = 8x^3+12x^2+x+1 */
		
		integral_sum += h*function;

		a1 += h; 
		a2 += h;
	/* In each iteration a1 and a2 will store the lower and upper bounds of the next interval */
	}
	
	printf("The approximate value of the definite integral of the function 8x^3+12x^2+x+1 in the limit %lf to %lf is:  %lf",l,r,integral_sum);
	
	return 0;
}
