#ifndef __TDLLIST__
#define __TDLLIST__

#include <iostream>
#include <string>

using namespace std;

template<typename T> class List;

template<typename T>
class Node
{
private:
    T value;
    Node* prev;
    Node* next;
public:
    Node(T value, Node* prev = NULL, Node* next = NULL);
    friend class List<T>;
};

template<typename T>
class List
{
private:
    Node<T>* h;
    Node<T>* t;
public:
    List();
    ~List();
    bool IsEmpty();
    T GetHead();
    T GetTail();
    void AddToHead(T v);
    void AddToTail(T v);
    bool RemoveHead();
    bool RemoveTail();

    string ToString();
    ///////////////////////////////////////////
    // Do not change the above prototype.
    // Add member function(s) below if you need.


 
    // Do not change the below.
    ///////////////////////////////////////////
};

template<typename T>
string List<T>::ToString()
{
    if (IsEmpty())
        return "()";
    stringstream os;
    os << "(";
    Node<T>* r = h;
    while (r != t)
    {
        os << r->value << ",";
        r = r->next;
    }
    os << r->value << ")";
    string str = os.str();
    return str;
}

template<typename T>
List<T>::List()
{
    h = t = NULL;
}

template<typename T>
bool List<T>::IsEmpty()
{
    return (h == NULL);
}

///////////////////////////////////////////
// Do not change the above.
// Implement your own member functions below.

template<typename T>
 Node<T>::Node(T value1, Node* prev1 , Node* next1 )	//node constructor
 {
	value = value1;				
	next = next1;
	prev = prev1;
 }
template<typename T>
    T List<T>::GetHead()
 {
	return h->value;			//get head function returns the head of the list when called
 }
	
	template<typename T>
    T List<T>::GetTail()
    {
    	return t->value;			//get tail function returns the tail of the list when called
    }
    
    template<typename T>
    void List<T>::AddToHead(T v)	//add to head function takes a value in and adds a head to the list with that value
    {
    
    if(IsEmpty()==true)				//checking if the list is empty
		{
			h = new Node<T>(v, NULL, NULL);		//sets head equal to a new node with a value of v, next-> NULL, prev-> NULL
		
			t=h;								//tail points to the same Node head points too
		}

	else		//if the stack is not empty
		{
			Node<T>* r = new Node<T>(v, NULL, NULL);//creats a new temporary node r with value of v, next-> NULL, prev->NULL
		
			h->prev = r;							//heads previos node is set to r
			r->next = h;							//r's next node is head
			h=r;									// head is pointing to the node r is pointing to
		}
   
    }
    template<typename T>
  	void List<T>::AddToTail(T v)					//add to tail function takes a value in and adds a tail to the list with that value
  	{
  
 		if(IsEmpty()==true)							//checking if the list is empty
 			{
 				h = new Node<T>(v, NULL, NULL);		//sets head equal to a new node with a value of v, next-> NULL, prev-> NULL
 				t=h;								//tail points to the same Node head points too
 			}

		else										//if the stack is not empty
		{
    		Node<T>* r;								
    		r=new Node<T>(v, NULL, NULL); 			//creats a new temporary node r with value of v, next-> NULL, prev->NULL
   			//r->value=v;
    		t->next=r;								//tails next node is r
    		r->prev=t;								//r's prev node is tail
    		t=r;									//tail pionts to the node r is pointing to
   		}
   
  	}
  	template<typename T>
    bool List<T>::RemoveHead()						//removes the head of the list and reasigns it if nessesary
    {
    if(h==t)										//if head and tail point to the same node
    	{
    		delete h;
 			h=NULL;									//delete head
    		return true;							//return true because of success
    	}
    else											//if head and tail point to differnt nodes
    	{
    	Node<T>* r;									//creates a new node pointer r
    	r=h->next;									//r points to h's next pointer
    	r->prev=h;									//r's prev node is the node h points to
    	delete h;									//delete head
    	h=r;										//head points to the node r points to
    	h->prev=NULL;								//head prev is NULL
    	return true;
    	}
    	return false;								//false if not successful
    }
    template<typename T>
    bool List<T>::RemoveTail()						//removes the tail of the list and reasigns it if nessesary
    {
        if(h==t)									//if head and tail point to the same node
    	{
           delete h;								//delete head
	   h=NULL;
    	   t=NULL;
    	   return true;
    	}
    else
    	{
    	Node<T>* r;									//creates a new node pointer r
    	r=t->prev;									//r points to tails
    	r->next=NULL;
    	delete t;
    	t=r;										//tail points to the node r points to
    	return true;
    	}
    	return false;
    }
    
	
    template<typename T>
    List<T>::~List()								//destructor for list
    {
    
    }

///////////////////////////////////////////

#endif //__TDLLIST__
