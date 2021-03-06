#include<stdio.h>
#include<stdlib.h>

struct node
{
	struct node *left,*right,*parent;
	char color;
	int data;
}*root=NULL;

void lr(struct node *root, struct node *x,struct node *y)
{
	y=x->right;
	x->right=y->left;
	if(y->left != NULL)
	y->left->parent=x;
	y->parent=x->parent;
	if(x->parent == NULL)
	root=y;
	else if(x == x->parent->left)
	x->parent->left=y;
	else
	x->parent->right=y;
	
	y->left=x;
	x->parent=y;
}

void rr(struct node *root, struct node *x,struct node *y)
{
	y=x->left;
	x->left=y->right;
	if(y->right != NULL)
	y->right->parent=x;
	y->parent=x->parent;
	if(x->parent == NULL)
	root=y;
	else if(x == x->parent->right)
	x->parent->right=y;
	else
	x->parent->left=y;
	
	y->right=x;
	x->parent=y;
}

void inorder(struct node *temp)
{
    if (temp != NULL)
    {
        inorder(temp->left);
        printf("%d\t %c\n",temp->data,temp->color);
        inorder(temp->right);
    }
}

void insert(struct node *root,struct node *x)
{
	struct node *p,*q;
	struct node *temp=(struct node*)malloc(sizeof(struct node*));
	temp->data=x->data;
	temp->left=NULL;
	temp->right=NULL;
	temp->color='R';
	p=root;

	if(root==NULL)
	{
		root=temp;
		root->parent=NULL;
		x=root;
		return;
	}

	while(p!=NULL)
	{
		q=p;
		if(temp->data < p->data)
			p=p->left;
		
		else
			p=p->right;
	}
	temp->parent=q;
	
	if ( q == NULL)
	{         
		root = temp;
	}
	else if( temp->data < q->data )
	{
	          q->left = temp;
	}

	else q->right = temp;
	return;
	
}

void rbinsert(struct node *root,struct node *x)
{
	struct node *y;
	insert(root,x);
	while((x->parent!=NULL) && (x->parent->color == 'R'))
	{
		if(x->parent == x->parent->parent->left)
		{
			y= x->parent->parent->right;
			if(y->color == 'R')
			{
				x->parent->color='B';
				y->color='B';
				x->parent->parent->color='R';
				x=x->parent->parent;
			}

			else if(x == x->parent->right)
			{
				x=x->parent;
				lr(root,x,y);
				x->parent->color='B';
				x->parent->parent->color='R';
				rr(root,x->parent->parent,y);
			}
		}
		else
		y=x->parent->parent->left;
	}		
	root->color='B';
}		

int main()
{
	int i,x,ch;
	while(1)
	{
		printf("1.Insert 2.Exit\n");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
				printf("Enter the node value\n");
				scanf("%d",&x);
				struct node *ele=(struct node *)malloc(sizeof(struct node *));
				ele->data=x;
				ele->right=NULL;
				ele->left=NULL;
				rbinsert(root,ele);
				inorder(root);
				break;
			
			case 2: exit(0);
		}
	}

}



