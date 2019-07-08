#include<iostream>
using namespace std;

class node
{
 public:
 int data;
 node* left;
 node* right;
 node* parent;
 node(int val)
 {
 	data=val;
 	left=NULL;
 	right=NULL;
 	parent=NULL;
 } 
};

class bst
{	
	public:
	node* root;
	bst()
	{
		root=NULL;
	}
	
	void inserthelper(node* curr,int val)													//ok
	{
		node* temp=new node(val);
		if(root==NULL)
		{
			root=temp;
		}
		else
		{
			if(val<curr->data)
			{
				if(curr->left==NULL)
				{
					curr->left=temp;
					temp->parent=curr;
				}
				else
				{
					inserthelper(curr->left,val);
				}
			}
			else
			{
				if(curr->right==NULL)
				{
					curr->right=temp;
					temp->parent=curr;
				}
				else
				{
					inserthelper(curr->right,val);
				}
			}
		}
	}
	
	void insert(int val)																				//ok
	{
		inserthelper(root,val);
	}
	
	void displayhelper(node* curr)															//ok
	{
		if(curr==NULL)
		{
			return;
		}
		else
		{
			displayhelper(curr->left);
			cout<<curr->data<<"  ";
			displayhelper(curr->right);
		}
	}
	void display()																							//ok
	{
		if(root==NULL)
		{
			cout<<" bst is empty"<<endl;
		}
		else
		{
			displayhelper(root);
		}
	}
	
	node* searchhelper(node* curr,int x)													//ok
	{
		if(curr==NULL || curr->data==x)
		{
			return curr;
		}
		else if(x<curr->data)
		{
			return searchhelper(curr->left,x);
		}
		else
		{
			return searchhelper(curr->right,x);
		}
	}
	
	node* search(int x)																						//ok
	{
		if(root==NULL)
		{
			cout<<"bst is empty!can't search"<<endl;
			return NULL;
		}
		else
		{
			return searchhelper(root,x);
		}
	}
	
	int counthelper(node* curr)																				//ok
	{
		if(curr==NULL)
		{
			return 0;
		}
		else
		{
			return 1+counthelper(curr->left)+counthelper(curr->right);
		}
	}
	
	int count()																												//ok
	{
		if(root==NULL)
		{
			return 0;
		}
		else
		{
			return counthelper(root);
		}
	}
	
	node* find_min(node* curr)																				//ok
	{
		if(root==NULL)
		{
			return NULL;
		}
		else if(curr->left==NULL)
		{
			return curr;
		}
		else
		{
			return find_min(curr->left);
		}
	}
	
	void deletehelper(node* curr)																		//ok
	{
		//curr have no child
		if(curr->left==NULL && curr->right==NULL)
		{
			if((curr->parent)->left==curr)
			{
				(curr->parent)->left=NULL;
				curr->parent=NULL;
				delete curr;
			}
			else
			{
				(curr->parent)->right=NULL;
				curr->parent=NULL;
				delete curr;
			}
		}
		
		//curr having only right child
		else if(curr->left==NULL && curr->right!=NULL)
		{
			//curr is the left child of its parent
			if((curr->parent)->left==curr)
			{
				(curr->parent)->left=curr->right;
				(curr->right)->parent=curr->parent;
				curr->parent=NULL;
				curr->right=NULL;
				delete curr;
			}
			//curr is the right child of the parent
			else
			{
				(curr->parent)->right=curr->right;
				(curr->right)->parent=curr->parent;
				curr->parent=NULL;
				curr->right=NULL;
				delete curr;
			}
		}
		
		//curr have only left child
		else if(curr->right==NULL && curr->left!=NULL)
		{
			//curr is the left child of its parent
			if((curr->parent)->left==curr)
			{
				(curr->parent)->left=curr->left;
				(curr->left)->parent=curr->parent;
				curr->parent=NULL;
				curr->left=NULL;
				delete curr;
			}
			//curr is the right child of its parent
			else
			{
				(curr->parent)->right=curr->right;
				(curr->right)->parent=curr->parent;
				curr->parent=NULL;
				curr->right=NULL;
				delete curr;
			}
		}
		
		//curr have both child
		else
		{
			node* curr1=find_min(curr->right);
			curr->data=curr1->data;
			deletehelper(curr1);
		}
	}
	
	void delet(int val)																		//ok
	{
		if(root==NULL)
		{
			cout<<" bst is already empty"<<endl;
		}
		else
		{
			node* curr=search(val);
			if(curr==NULL)
			{
				cout<<" element is not present"<<endl;
			}
			else
			{
				deletehelper(curr);
			}
		}
	}
	
	int rangesearchhelper(node* curr,int k1,int k2)									//modify
	{
		if((curr->data)<k1  || (curr->data)>k2)
		{
			return 0;
		}
		else
		{
			return 1+rangesearchhelper(curr->left,k1,k2)+rangesearchhelper(curr->right,k1,k2);
		}
	}
	
	int rangesearch(int k1,int k2)											//modify
	{
		if(root==NULL)
		{
			return 0;
		}
		else if(k1>k2)
		{
			return rangesearchhelper(root,k1,k2);
		}
		else
		{
			return rangesearchhelper(root,k2,k1);
		}
	}
	
	int max(int a,int b)																		//ok
	{
		if(a>b)
		{
			return a;
		}
		else
		{
			return b;
		}
	}
	
	int heighthelper(node* curr)														//ok
	{
		if(curr==NULL)
		{
			return 0;
		}
		else
		{
			return 1+max(heighthelper(curr->left),heighthelper(curr->right));
		}
	}
	
	int height()																						//ok
	{
		if(root==NULL)
		{
			return 0;
		}
		else
		{
			return heighthelper(root);
		}
	}
	
	
	// Function to print binary tree in 2D  
	// It does reverse inorder traversal  
	void print2DUtil(node *curr, int space)													//modufy
	{  
		  // Base case  
		  if (root == NULL)  
		      return;  
		
		  // Increase distance between levels  
		  space += 5;  
		
		  // Process right child first  
		  print2DUtil(root->right, space);  
  
		  // Print current node after space  
		  // count  
		  cout<<endl;  
		  for (int i = 5; i < space; i++)  
		      cout<<"*";  
		  cout<<root->data<<"\n";  
		
		  // Process left child  
		  print2DUtil(root->left, space);  
	}  
  
	// Wrapper over print2DUtil()  
	void print2D(node *curr)  
	{  
		  // Pass initial space count as 0  
		  print2DUtil(root, 0);  
	}  
};



int main()
{
	bst b1;
	b1.insert(7);
	b1.insert(3);
	b1.insert(10);
	b1.insert(2);
	b1.insert(4);
	b1.insert(9);
	b1.insert(11);
	b1.insert(8);
	b1.display();
	cout<<endl;
	b1.delet(6);
	b1.display();
	return 0;
}

