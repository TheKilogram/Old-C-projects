#ifndef __BST__
#define __BST__
//g++ -ansi -pedantic -Wall Sort.cxx -o sort
template<typename T> class BST;

template<typename T>
class Node
{
private:
    T     value;
    Node* left;
    Node* right;
public:
    Node(T v, Node* l = NULL, Node* r = NULL)
    {
        value = v;
        left = l;
        right = r;
    }
    T GetValue() const
    {
        return value;
    }
    friend class BST<T>;
};

template<typename T>
class BST
{
private:
    Node<T>* root;
public:
    BST(Node<T>* r = NULL)
    {
        root = r;
    }
    bool IsEmpty() const
    {
        return (root == NULL);
    }
    string ToString() const
    {
        if (IsEmpty()) return "()";
        string str = ToString(root);
        if (root->left == NULL && root->right == NULL) str = "(" + str + ")";
        return str;
    }

    void Clear();
    Node<T>* Search(T query);
    void Insert(T value);
    void Inorder(void (*visit)(const Node<T>*));
    void Preorder(void (*visit)(const Node<T>*));
    void Postorder(void (*visit)(const Node<T>*));

    ///////////////////////////////////////////
    // Do not change the above prototype.
    // Add member function(s) below if you need.

    // Do not change the below.
    ///////////////////////////////////////////
private:
    string ToString(Node<T>* n) const
    {
        if (n == NULL) return "_";
        stringstream ss;
        if (n->left == NULL && n->right == NULL) ss << n->value;
        else                                     ss << "(" << ToString(n->left) << "," << n->value << "," << ToString(n->right) << ")";
        return ss.str();
    }

    ///////////////////////////////////////////
    // Do not change the above prototype.
    // Add member function(s) below if you need.
    void Insert(Node<T>*,T value);							//does the actual insertion of the values
	void Inorder(Node<T>*,void (*visit)(const Node<T>*));	//does the inorder algorithym
	void Preorder(Node<T>*,void (*visit)(const Node<T>*));	//does the preorder algorithym
	void Postorder(Node<T>*,void (*visit)(const Node<T>*));	//does the postorder algorithym
	
    // Do not change the below.
    ///////////////////////////////////////////
};

///////////////////////////////////////////
// Do not change the above prototype.
// Implement function body
//template<typename T>

//clear function deletes the BST
template<typename T>
void BST<T>::Clear()
{
	Node<T>* tmp;	//initializes a new node pointer tmp
	tmp=root;		//tmp points to the root node
	
	//loop while the root has children
	while(tmp->left && tmp->right != NULL)
	{
		if (tmp->left != NULL)	//if there is a node to the left
		{
			tmp=tmp->left;		//move to the left node
		}
		else if (tmp->right != NULL)	//if there is a node to the right
		{
			tmp=tmp->right;				//move to the right node
		}
	
	}
	
	delete tmp;		//delete node tmp is on, will be on the bottom of the tree
	
	if (root->left && root->right == NULL)	//if the root has no children
	{
		delete root;	//delete root
	}
	else Clear();		//if the root still has children call the function again
	
}
//finds a value stored in the BST
template<typename T>
Node<T>* BST<T>::Search(T query)
{
	Node<T>* tmp;	//initializes a new node pointer tmp
	tmp=root;		//tmp points to the root node
	
	//loop while the current node's value does not equal the value being serched for
	while (tmp->value!=query)
	{
		if(tmp->value>query)	//if the nodes value is greater than the value being looked for
		{
			if (tmp->left==NULL)	//if the node has no left child
			{
				return NULL;	//return
			}
			
			else			//if the node does have a left child
			{
				tmp=tmp->left;	//move to the left node
			}		
		}
	
		else if(tmp->value<query)	//if the nodes value is lessthan the value being looked at
		{
			if (tmp->right==NULL)	//if the node does not have a right child
			{
				return NULL;	//return
			}
			
			else			//if the node does have a right child
			{
				tmp=tmp->right;	//move to the right
			}
		}
		
	}
	
	return tmp;
}

//calles the insert function with the algorithym in it
template<typename T>
 void BST<T>::Insert(T value)	//public
 {
	Insert(root,value); //calls the insert privat function
 }
 //insert private function
 template<typename T>
 void BST<T>::Insert(Node<T>* tmp,T value)
 {
 
 	if (root==NULL)	//if there is no root create one
 	{
 		root=new Node<T>(value,NULL, NULL);	//creates a new node with root pointing to it
 		tmp=root;				//sets tmp pointing to the same node root is
 		tmp->value=value;			//sets the root node's value to the value being inserted
 	}
 	
 	else	//if a root already exists
 	{
 	tmp=root;//make sure tmp points to root node
 		while(tmp != NULL)	//while the current node exists
 		{
 		
 			if(tmp->value==value)	//if the node value is equal to the inserting value
			{
				
				if (tmp->right != NULL)	//if the node has right children
 				{
 					Node<T>* tmpTwo=tmp->right;			//initalizes a new temporary node pointer and has it point to the right child of the current node
					tmp->right=new Node<T>(value,NULL, NULL);	//creates a new node with the value inside, this is the right child of the current node
					tmp=tmp->right;					//point at the newly created node
					tmp->right=tmpTwo;				//set the right child to the new node to the old right child of its parent
					break;						//leave the loop
 				}
 				else	//if the node does not have a right child (right child == NULL)
 				{
 					tmp->right=new Node<T>(value,NULL, NULL);	//create a new node for the right child
					tmp=tmp->right;					//point to the new node
					break;						//leave loop
 				}
				
				
			}
 		
 		    else if(tmp->value > value)	//if the current nodes value is greater than the inserting value
 			{
 			
 				if(tmp->left!=NULL)	//if there is a left child
 				{
 					tmp = tmp->left;	//move to the left node
 				}
 				
 				else			//if there is no left child (left child==NULL)
 				{
 					tmp->left=new Node<T>(value,NULL, NULL);	//create a new node for the left child with the value being inserted in side
 					tmp=tmp->left;					//move to the new node
 					break;						//leave loop
 				}
 			}
 			
 			else if(tmp->value < value)		//if the node value is lessthan the inserting node
 			{
 				if (tmp->right != NULL)		//if the node has a right child
 				{
 					tmp = tmp->right;	//mode to the right child
 				}
 				else				//if the node does not have a right child
 				{
 					tmp->right=new Node<T>(value,NULL, NULL);	//create a new node for the right child with the value being inserted
					tmp=tmp->right;		//move to the right node
					break;			//leave the loop
				}
 			}
			
 			

 			
 			else	//if somehow these if statmetns donot apply, leave the loop
 			{
 				break;
 			}
 		}
 	
 	}

 }
 //public inorder
template<typename T>
 void BST<T>::Inorder(void (*visit)(const Node<T>* const n))
 {
 	Inorder(root,visit);	//calls the private inorder
 }

//public preorder
template<typename T>
 void BST<T>::Preorder(void (*visit)(const Node<T>*))
 {
	Preorder(root, visit);	//calls the private preorder
 }

//public postorder
template<typename T>
 void BST<T>::Postorder(void (*visit)(const Node<T>*))
 {
	Postorder(root, visit);	//calls the private postorder
 }
 
//private inorder
template<typename T>
 void BST<T>::Inorder(Node<T>* curN,void (*visit)(const Node<T>*))
 {
 	if(curN != NULL)	//if the current node is not NULL
 	{
 	Inorder(curN->left, visit);	//move to the left node
 	visit(curN);			//return the viseted value for your ordering in Sort.cxx
 	Inorder(curN->right, visit);	//move to the right node
 	}
 }
 
//private preorder
 template<typename T>
 void BST<T>::Preorder(Node<T>* curN,void (*visit)(const Node<T>*))
 {
 	if(curN != NULL)	//if the current node is not NULL
 	{
	visit(curN);	//return as a visit to that node
 	Preorder(curN->left, visit);	//move to the lsft child
 	Preorder(curN->right, visit);	//move to the right child
 	}
 }
  
 template<typename T>
 void BST<T>::Postorder(Node<T>* curN,void (*visit)(const Node<T>*))
 {
 	if(curN != NULL)	//if the current node is not NULL
 	{
 	Postorder(curN->left, visit);	//move to the left child
 	Postorder(curN->right, visit);	//move to the right child
 	visit(curN);			//return as a visit to the current node
 	}
 }

// Implement function body
///////////////////////////////////////////

#endif //__BST__
