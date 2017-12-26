#include <iostream>
//#include <iomanip>

using namespace std;

#include "AVL.h"

//--- Definition of constructor
BST::BST()
: myRoot(0)
{}

bool BST::empty() const
{ return myRoot == 0; }


bool BST::search(const int & item) const
{
   BinNode * locptr = myRoot;
   bool found = false;
   while (!found && locptr != 0)
   {
      if (item < locptr->data)       // descend left
        locptr = locptr->left;
      else if (locptr->data < item)  // descend right
        locptr = locptr->right;
      else                           // item found
        found = true;
   }
   
   return found;
}


void BST::insert(const int & item)
{
   BinNode * locptr = myRoot;   // search pointer
   BinNode * parent = 0;        // pointer to parent of current node
   bool found = false;     // indicates if item already in BST
   int lh,rh,diff;
   while (!found && locptr != 0)
   {
      parent = locptr;
      if (item < locptr->data)       // descend left
         {
			 locptr = locptr->left;
		}
      else if (locptr->data < item)  // descend right
	  {
		locptr = locptr->right;
		}
         
      else{                     // item found
		found = true;
		
		}
	}
   
   
   if (!found)
   {                                 // construct node containing item
      locptr = new BinNode(item);  
      if (parent == 0)               // empty tree
         {
			myRoot = locptr;
			locptr->head = 0;
			locptr->height = 0;
			locptr->balance = 0;
		}
      else if (item < parent->data )  // insert to left of parent
		{
			parent->left = locptr;
			locptr->head = parent;
			locptr->height = 0;
			locptr->balance = 0;
		}
      else if (parent->data < item)                           // insert to right of parent
		{
			parent->right = locptr;
			locptr->head = parent;
			locptr->height = 0;
			locptr->balance = 0;
		}
		
		while(locptr->head!=0)
		{
			
			locptr = locptr->head;
			
			if(locptr->left ==0)
				lh = -1;
			else
				lh = locptr->left->height;

			if(locptr->right == 0)
				rh = -1;
			else
				rh = locptr->right->height;
						
			locptr->height = max(lh,rh) + 1;
			
			if(lh==rh){
				locptr->balance = 0;
				diff = 0;
			}
			else if(lh>rh){
				locptr->balance = -1;
				diff = lh-rh;
			}
			else if(lh<rh){
				locptr->balance = 1;
				diff = rh-lh;
			}
			
			
			
			if(diff > 1)
			{
				
				if(locptr->balance == 1)
				{
					if(locptr->right->balance == 1) //right child right heavy ---- done
					{
						///left Rotate
						
						leftrotate(locptr,myRoot);
						
					}
					else if(locptr->right->balance == -1) //right child left heavy
					{
						right_left_rotate(locptr);
					}
					
				}
				else if(locptr->balance == -1)
				{
					if(locptr->left->balance == 1) //left child right heavy
					{
						left_right_rotate(locptr);
					}
					else if(locptr->left->balance == -1) //left child left heavy
					{
						rightrotate(locptr,myRoot);
						
					}
				}
				
			}
		}
	
	//BalanceBST(myRoot);
   }
   else
      cout << "Item already in the tree\n";
}



void BST::BalanceBST(BinNode* node) const {

		if(node->left != 0)
		{
			BalanceBST(node->left);
		}
		
		if(node->right != 0){
			BalanceBST(node->right);
		}
}


void BST::preorder() const
{
	preorderRecursion(myRoot);
}


void BST::preorderRecursion(BinNode* node ) const{
	if(myRoot!= 0)
	{
		cout<< node->data<<endl;
		if(node->left != 0)
		{
			preorderRecursion(node->left);
		}
		
		if(node->right!= 0){
			preorderRecursion(node->right);
		}
	}
	else 
		cout<< "Tree empty"<<endl;
	
}

void BST::inorder() const
{
	inorderRecursion(myRoot);
}	
	
	

void BST::inorderRecursion(BinNode* node ) const{
	
	if(myRoot!= 0)
	{
	if(node->left != 0)
	{
		inorderRecursion(node->left);
		}
		cout<< node->data<<endl;
	if(node->right!= 0){
		inorderRecursion(node->right);
		}
		
	}
	else 
		cout<< "Tree empty"<<endl;

}


void BST::nodeCount() const
{
	int count = 0;
	count = nodeCountRecursion(myRoot,count);
	cout<<count<<endl;
}	
	
	

int BST::nodeCountRecursion(BinNode* node , int count) const{
	if(node!=0)
	{
		count = 1 + nodeCountRecursion(node->left, count) + nodeCountRecursion(node->right, count);
		return count;
	}
	else{
		return 0;
	}
}


void BST::delete_node(const int & item)
{
   BinNode * locptr = myRoot;   // search pointer
   BinNode * parent = 0;        // pointer to parent of current node
   bool found = false;     // indicates if item already in BST
   char pos;
   int lh,rh,diff;
   if(myRoot == 0)
   {
	   cout << "Tree is Empty. No such item to delete" << endl;
	   return;
	   
	}
   while (!found && locptr != 0)
   {
      if (item < locptr->data)
	  {
		  parent = locptr;
		  locptr = locptr->left;
		  pos = 'l';
	  }
   
         
      else if (locptr->data < item)  // descend right
	  {
		parent = locptr;
		locptr = locptr->right;
		pos = 'r';
	  }
  
      else                           // item found
		found = true;
   }
   
   if (found)
   {
	if(locptr->left == 0 && locptr->right == 0){
			if(parent == 0){
				myRoot = 0;
			}
			else if(parent->left == locptr){
				parent->left=0;
			}
			else{
				parent->right=0;
			}
	   }
	   
	   else if(locptr->left == 0 && locptr->right != 0)
	   {
		   if(parent == 0){
				myRoot = locptr->right;
			}
			else if(parent->left == locptr){
				parent->left=locptr->right;
			}
			else{
				parent->right=locptr->right;
			}

		}
		
		else if(locptr->left != 0 && locptr->right == 0)
	   {
		   if(parent == 0){
				  myRoot = locptr->left;
			}
			else if(parent->left == locptr){
				parent->left=locptr->left;
			}
			else{
				parent->right=locptr->left;
			}

		}
		
		else if(locptr->left != 0 && locptr->right != 0)
		{
			BinNode* temp = locptr;
			parent = locptr;
			locptr = locptr->left;
			
			while(locptr->right != 0)
			{
				parent = locptr;
				locptr = locptr->right;
			}
					
			temp->data = locptr->data;

			if(parent->left->data == locptr->data)
			{
				if(locptr->left!=0)
				{
					parent->left = locptr->left;
				}
				else
				{
					parent->left = 0;
				}
			}
				
			else if(parent->right->data == locptr->data)
			{
				if(locptr->left!=0)
				{
					parent->right = locptr->left;
				}
				else
				{
					parent->right = 0;
				}
			}
		}
		
		while(locptr->head!=0)
		{
			
			locptr = locptr->head;
			
			if(locptr->left ==0)
				lh = -1;
			else
				lh = locptr->left->height;

			if(locptr->right == 0)
				rh = -1;
			else
				rh = locptr->right->height;
						
			locptr->height = max(lh,rh) + 1;
			
			if(lh==rh){
				locptr->balance = 0;
				diff = 0;
			}
			else if(lh>rh){
				locptr->balance = -1;
				diff = lh-rh;
			}
			else if(lh<rh){
				locptr->balance = 1;
				diff = rh-lh;
			}

			if(diff > 1)
			{
				
				if(locptr->balance == 1)
				{
					if(locptr->right->balance == 1 || locptr->right->balance == 0) //right child right heavy ---- done
					{
						///left Rotate
						leftrotate(locptr,myRoot);
					}
					else if(locptr->right->balance == -1) //right child left heavy
					{
						right_left_rotate(locptr);
					}
					
				}
				else if(locptr->balance == -1)
				{
					if(locptr->left->balance == 1 || locptr->left->balance == 0) //left child right heavy
					{
						left_right_rotate(locptr);
					}
					else if(locptr->left->balance == -1) //left child left heavy
					{
						rightrotate(locptr,myRoot);
						
					}
				}
				
			}
		}

   }
   else
      cout << "Item doesnt exist in the tree\n";
}

void BST::leftrotate(BinNode* locptr,BinNode* myRoot ) const{
	
	BinNode * temp1;
	BinNode * parent;
	cout<<"Performing Left Rotation";
	parent = locptr->right;
	parent->head = locptr->head;
	
	if(parent->head!=0)
	{
		if(parent->head->right == locptr)
		{
			parent->head->right = parent;
		}
		else{
			parent->head->left = parent;
		}
	}
	else
	{
		myRoot=locptr->right;
	}

	if(locptr->left!=0)
	{
		parent->left->left = locptr->left;
	}
	
	if(parent->left != 0)
	{
		temp1 = parent->left;
		parent->left = new BinNode (locptr->data);
		parent->left->right = temp1;
		locptr->head = parent;
	}
	else{
		parent->left = new BinNode(locptr->data);
	}

	

	cout << "\nInorder Traversal\n";
	inorderRecursion(myRoot);
	
}
void BST::rightrotate(BinNode* locptr, BinNode* myRoot) const{
	
	BinNode * temp1;
	BinNode * parent;
	cout<<"Performing Right Rotation";
	parent = locptr->left;
	parent->head = locptr->head;
			
	if(parent->head!=0)
	{
		if(parent->head->right == locptr) {
			parent->head->right = parent;
		}
		else {
			parent->head->left = parent;
		}
	}
	else
	{
		myRoot = locptr->left;
	}

	if(locptr->right!=0)
	{
		parent->right->right = locptr->right;
	}

	if(parent->right != 0)
	{
		temp1 = parent->right;
		parent->right = new BinNode (locptr->data);
		parent->right->left = temp1;
		locptr->head = parent;
	}
	else{
		parent->right = new BinNode(locptr->data);
	}

	cout << "\nInorder Traversal\n";
	inorderRecursion(myRoot);
}


void BST::left_right_rotate(BinNode* locptr) const{
	BinNode *temp;
	temp=locptr;
	cout<<"Performing Left then right rotate";
	leftrotate(temp->left,myRoot);
	rightrotate(locptr,myRoot);
}

void BST::right_left_rotate(BinNode* locptr) const{
	BinNode *temp;
	temp=locptr;
	cout<<"Performing Right then Left Rotate";
	rightrotate(temp->right,myRoot);
	leftrotate(locptr,myRoot);
}