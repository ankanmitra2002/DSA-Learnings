#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Tree of characters */
typedef struct node
{
	char data;
	struct node* lchild;
	struct node* rchild;
}Tree;
/* creating node*/
Tree* creation(char data)
{
	Tree* ptr = (Tree*)malloc(sizeof(Tree));
	ptr->data = data;
	ptr->lchild = NULL;
	ptr->rchild = NULL;
	return ptr;
}
/* searching for the position of a charcter */
int search(char* inorder,char currentnode,int start,int end)
{
	for ( int i = start ; i <= end ; i++ )
	{
		if ( inorder[i] == currentnode )
		{
			return i;
		}
	}
	return -1;
}
/* building the tree */
static int preindex = 0;
Tree* building_of_Tree(char* preorder,char* inorder,int start,int end)
{	
	if ( start > end )
	{
		return NULL;
	}
	char currentnode = preorder[preindex++];/* current data */
	Tree* root = creation(currentnode);
	if ( start == end )
	{
		return root;
	}
	int root_position = search(inorder,currentnode,start,end);
	root->lchild = building_of_Tree(preorder,inorder,start,root_position-1);/* creating left subtree */
	root->rchild = building_of_Tree(preorder,inorder,root_position+1,end);/* creating right subtree */
	return root;
}
/* inorder traversal to print the nodes of binary tree */
void inorderTraversal(Tree* root)
{
	if(root == NULL)
	{
		return;
	}	
	inorderTraversal(root->lchild);/* traversing for left child */
	printf("%c ",root->data);/* printing data inorder */
	inorderTraversal(root->rchild);/* traversing for right child */
}
int main()
{
	char preorder[] = {'D', 'B', 'J' , 'A', 'E', 'C', 'F' , 'I'};/* preorder input */
    char inorder[] = {'D', 'B', 'E', 'A', 'F', 'I' , 'C' , 'J'};/* inorder input */
    int length = sizeof(inorder) / sizeof(inorder[0]);
    printf("The preorder input of characters are: ");
    for ( int i = 0 ; i < length ; i++ )
    {
        printf("%c",preorder[i]);
    }
    printf("\n");
    printf("The inorder input of characters are: ");
    for ( int i = 0 ; i < length ; i++ )
    {
        printf("%c",inorder[i]);
    }
    printf("\n");
	Tree* root = building_of_Tree(preorder,inorder,0,length-1);
	printf("The inorder traversal of the tree built by the given preoder and inorder input is : ");
	inorderTraversal(root);/* inorder traversal */
	return 0;
}
