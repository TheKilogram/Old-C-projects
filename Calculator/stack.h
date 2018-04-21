#ifndef __STACK__
#define __STACK__

#include <iostream>
#include <string>
#include "list.h"

template<typename T>
class Stack
{
private:
    List<T> list;
public:
    bool IsEmpty();
    void Push(T elem);
    T Pop();
    T Top();
    void Clear();

    string ToString();
    ///////////////////////////////////////////
    // Do not change the above prototype.
    // Add member function(s) below if you need.



    // Do not change the below.
    ///////////////////////////////////////////
};

template<typename T>
inline string Stack<T>::ToString()
{
    if (IsEmpty())
        return "()";

    Stack buff1;
    while (IsEmpty() == false)
    {
        T top = Pop();
        buff1.Push(top);
    }

    stringstream os;
    os << "(";
    while (buff1.IsEmpty() == false)
    {
        Push(buff1.Pop());
        T top = Top();
        os << top;
        if (buff1.IsEmpty() == false)
            os << ",";
    }
    os << ")";
    string str = os.str();

    return str;
}

template<typename T>
bool Stack<T>::IsEmpty()
{
    return list.IsEmpty();
}

///////////////////////////////////////////
// Do not change the above.
// Implement your own member functions below.

template<typename T>
void Stack<T>::Push(T elem)			//function take an template element and pushes it to the top of the stack
{
	if(IsEmpty()==true)			//if the stack is empty
		{
		list.AddToTail(elem);		//calls the list add to tail function,(adds an element to the top of stack)
		}
		
	else
		{
		
		list.AddToTail(elem);		//calls the list add to tail function,(adds an element to the top of stack)
		}

}



template<typename T>
 T Stack<T>::Pop()				//takes the top element off the stack and returns it
 {
 		T tmp;				//initialization of a temprary variable
 	
 		tmp=list.GetTail();		//tem is set equal to the tail of the list(top of stack)
 		list.RemoveTail();		//deletes the tail of the list(top of stack)

	return tmp;	//return tmp(old top of stack)
 }
 
 
 
 template<typename T>
 T Stack<T>::Top()				//just gets the tail of the list(top of stack) and returns it
 {
 return list.GetTail();
 }



template<typename T>
void Stack<T>::Clear()				//deletes everything in the stack
{

while (IsEmpty()!=true)				//while the stack is not empty
	{
	list.RemoveTail();			//remove the top
	}

}

// Do not change the below.
///////////////////////////////////////////

#endif //__STACK__
