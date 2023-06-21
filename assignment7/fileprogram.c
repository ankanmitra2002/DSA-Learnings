#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
	int marks,roll;
	char name[25];
};
typedef struct student Std;
/* A structure template of student is generated which contains the details of roll,marks,name as of text file */
int main(int argc,char * argv[])
/* Here command line argument is used to pass commands to main() */ 
  { 
    FILE*ptr=NULL;
    /* FILE pointer is initialized to NULL */
    ptr = fopen(argv[1],"r");
    /* Here we should give the second command as the directory path of student.txt file to the main() function */ 
    
    if(ptr==NULL)
    {
    	printf("The file cannot be opened\n");
    	exit(0);
    /* If there is no file then we terminate the program by giving exit(0) */	
	}
	int number= fgetc(ptr)-'0';
	/* The first number in the text file is the number of students and we create an array of structure of that number size */ 
	printf("The total number of students are %d\n",number);
	Std* stu = (Std*)malloc(number*sizeof(Std));
	
	for ( int i = 0 ; i < number ; i++ )
	{   
	    /* Storing the details from the file to the structure array */
		fscanf(ptr,"%d",&stu[i].roll);
		fscanf(ptr,"%s",&stu[i].name);
		fscanf(ptr,"%d",&stu[i].marks);			
	}
	/* Variables needed for insertion sort are declared below */
    int sort_marks,shift_roll;
    char shift_name[20];
    for ( int i = 1 ; i < number ; i++ )
    {
    	sort_marks = stu[i].marks;
    	shift_roll = stu[i].roll;
    	strcpy(shift_name,stu[i].name);
    	
		int j;
    	for ( j = i - 1 ; ( j >= 0 ) && ( stu[j].marks > sort_marks ) ; j-- )
    	{
    		stu[j+1].marks = stu[j].marks;
    	    stu[j+1].roll = stu[j].roll;
    	    strcpy(stu[j+1].name,stu[j].name);		
		}
    	stu[j+1].marks = sort_marks;
        stu[j+1].roll = shift_roll;
    	strcpy(stu[j+1].name,shift_name);
	/* The marks are sorted by insertion sort algorithm and name,roll are sorted marks wise. */
	}
	/* The description of the students with rank,roll,name according to increasing marks are printed in a tabular format*/
    printf("\n\n******************After sorting of the students based on their marks in increasing order****************\n\n");
    printf("Rank\t Marks\t Roll\t Name\n\n");
    
    for ( int i = 0 ; i < number ; i++ )
    {
    	printf("%2d\t %3d\t %2d\t %s\n",number - i,stu[i].marks,stu[i].roll,stu[i].name);
	}  
	
    return 0;
  }
  
