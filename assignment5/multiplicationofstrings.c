#include<stdio.h>
#include<stdlib.h>

int main()
{
	/* The length of the two integers are taken from user */
	int n,m;
	printf("Enter the length of the first integer\n");
	scanf("%d",&m);
	/* getchar() is used to avoid \n as an input to string */
	getchar();
	/* The string is created dynamically to store the big integer as character array dynamically */
	char* a = (char*)malloc(m+1);
	printf("Enter the integer\n");
	scanf("%s",a);
	/* In the same way of previous one the second integer is stored in a string */
	printf("Enter the length of the second integer\n");
	scanf("%d",&n);
	
	getchar();
	char* b = (char*)malloc(n+1);
	printf("Enter the integer\n");
	scanf("%s",b);
    /* The 2D array result is created dynamically and initialized to zero to perform multiplication of every digit to digit */
	int** result = (int **)calloc(n*(m+n),sizeof(int*));
    int i,j;
    for ( i =0 ; i < n ; i++ )
    {
   		result[i]=(int*)calloc(m+n,sizeof(int*));
    }
    /* The variables needed for the multiplication of every digit to digit,here carrycount is used to measure carry at every step*/ 
    int val_1st,val_2nd,carrycount=0,multiply,shifter=1,row,col;
    /* shifter is declared as it will be used to shift the multiplication of first string with the digits from second string
	   consecutively starting from the end of the second string */ 
	   
	for ( i =n-1 , row = 0 ; i >= 0 ; i-- , row++ )
   {	
   		 val_2nd = b[i] - '0';
   		
   		for ( j = m-1 , col = m+n-shifter ; j >= 0 ; j-- , col-- )
   		{
   		 val_1st = a[j] - '0';
   		 multiply = val_2nd*val_1st + carrycount;
   		 result[row][col] = multiply % 10;
   		 carrycount = multiply/10;
		   	
		}
   		if(carrycount > 0)
   		{
   			result[row][col] = carrycount;		
		}
   		shifter++;
   		carrycount = 0;
   }
   /* The product string is created to store the final result as a string */
    char * product = (char *)calloc(m+n+1,sizeof(char));
	for ( col = m+n-1 ; col >= 0 ; col-- )
	{
		int col_add = 0;
		for ( row = n-1 ; row >= 0 ; row-- )
		{
		 col_add += result[row][col]; 
		/* Digits are added column wise in the final result */ 
		}
		 col_add += carrycount;
		 /* The generated carry in some steps of column addition is added with the next column */
		 product[col] = (col_add % 10) + 48;
		 carrycount =col_add/10;
	}
	if(carrycount > 0)
	{
		product[col] = carrycount;	
	}
	/*If the product[0] is 0 i.e no carry then we will print the string from incremented ointer product+1 */
    if(product[0] == '0')
    {
    	product = product + 1;
	}
	/* The final result is printed */
	printf("\n\n******* The product of the given numbers are : %s**********\n\n",product);
	
    return 0;
}

