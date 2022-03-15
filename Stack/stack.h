
#ifndef STACK_H
#define STACK_H
// Created by David A Gaitros on 10/15/19.
// ********************************************************************
// * Name: Stack Class                                                *
// * Description: A template Stack class designed to be used with     *
// * any simple C++ type to include floating point, double            *
// * floating point, character, and Boolean.                          *
// * The stack pointer, as is the convention, points to the last      *
// * or highest element in the array. So if you allocate 100          *
// * elements of type "T" then the first empty element will be 99.    *
// * Author: Dr. David A. Gaitros                                     *
// * Date: January 19, 2019                                           *
// ********************************************************************
#include <iostream>
using namespace std;

const int DEFAULTSIZE=100;
template <class T>
class Stack {
public:
    Stack();                              // Default Constructor, stack is size 100.
    Stack(const int size);                // Constructor, creates stack of size "size"
    Stack(const Stack & Obj);             // Copy constructor
    ~Stack();
    bool Full();                          // Return true if the stack is full
    bool Empty();                         // Return true if the stack is empty
    int Size();                           // Return the size of the stack
    int Number();                         // Return the number of elements stored
    T Top();                              // Returns the top element, does not pop it
    bool Push (const T item);             // Put an item on the stack
    bool Pop();                           // Pop an item off and display to std out
    Stack & operator =(const Stack & stack);
    friend ostream &operator <<(ostream & os, Stack<T> &s)
    {
        if(s.Empty())
        {
            os << "Empty stack";
            return os;
        }
        os <<  s._stack[--s._top];
        s._number--;
        return os;
    };

private:
    T * _stack;                                   // The "stack"
    int _size;                                    // The number of elements the stack can hold
    int _top;                                     // Points to the first empty node
    int _number;                                  // The number of elements in the stack.
};
#endif

// *******************************************************************************
// * Name:  Stack template implementation                                        *
// * Class: COP4530                                                              *
// * Description: Implementation of the template of a Stack.                     *
// *    Template can create/allocate memory for a Stack, push, pop, and copy a   *
// *    Stack. Contains overloads for << and = operators. Contains functions     *
// *    for getting the top element of a stack, size of a stack, if a stack is   *
// *    full, if a stack is empty, and how many items are on the stack.          *
// *    Constructors allocate memory equal to a user defined size. Default       *
//  *   constructor allocates a Stack size of 100.                               *
// * Author: William Ryan Miller                                                 *
// * References: N/A                                                             *
// * Date: 08/25/2020                                                            *
// *******************************************************************************

// *****************************************************************
// * Function Name: Stack                                          *
// * Description: Default constructor of type Stack. Creates a     *
// *    default stack of size 100.                                 *
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
Stack<T>::Stack()
{
    _size = DEFAULTSIZE;
    _top = 0;
    _stack = new T[_size];
    _number = 0;
}

// *****************************************************************
// * Function Name: Stack                                          *
// * Description: Constructor of type Stack. Creates a Stack of    *
// *    a passed in size.                                          *
// * Parameter Description: Function takes in a constant integer   *
// *    size. Used to determine the stack size to allocate the     *
// *    required memory defined by the user.                       *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
Stack<T>::Stack(const int size)
{
    if(size < 0)
    {
        _size = DEFAULTSIZE;
    } else {
        _size = size;
    }
    _top = 0;
    _stack = new T[_size];
    _number = 0;
}

// *****************************************************************
// * Function Name: Stack                                          *
// * Description: Copy constructor of type Stack. Copies the size, *
// *    top index, number of elements, and elements from one stack *
// *    to another and then returns the newly allocated stack.     *
// * Parameter Description: Takes in a constant Stack called obj.  *
// *    Used to copy the size, top index, number of elements, and  *
// *    elements into the calling stack.                           *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
Stack<T>::Stack(const Stack<T> & Obj)
{
    _size = Obj._size;
    _top = Obj._top;
    _number = Obj._number;
    _stack = new T[_size];
    for(int i = 0; i < _top; i++)
    {
        _stack[i] = Obj._stack[i];
    }
}

// *****************************************************************
// * Function Name: ~Stack                                         *
// * Description: Destructor of type Stack. Deletes allocated      *
// *    memory of a Stack.                                         *
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
Stack<T>::~Stack()
{
    delete [] _stack;
    _stack = nullptr;
}

// *****************************************************************
// * Function Name: Full                                           *
// * Description: Function returns true if the Stack is full, false*
// *    if not full.                                               *
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
bool Stack<T>::Full()
{
    return _top == _size;
}

// *****************************************************************
// * Function Name: Empty                                          *
// * Description: Function returns true if the Stack is empty,     *
// *    false if not empty.                                        *
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
bool Stack<T>::Empty()
{
    return _top == 0;
}

// *****************************************************************
// * Function Name: Size                                           *
// * Description: Accessor for private data called _size. Function *
// *    will return the size of the Stack.                         *
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
int Stack<T>::Size()
{
    return _size;
}

// *****************************************************************
// * Function Name: Top                                            *
// * Description: Function will return the top item of the Stack   *
// *    by getting the element at the _top-1 position in the Stack.*
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
T Stack<T>::Top()
{
    return _stack[_top - 1];
}

// *****************************************************************
// * Function Name: Push                                           *
// * Description: Function will push an item onto the stack. Will  *
// *    first check if the stack is full. If it is, function will  *
// *    display an error message and return false. Otherwise, item *
// *    is added to the stack and returns true.                    *
// * Parameter Description: Takes in a constant T (template class) *
// *    called item. This is the item that will be pushed into the *
// *    stack if the stack isn't full.                             *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
bool Stack<T>::Push(const T item)
{
    if(Full())
    {
        cout << "Stack overflow!" << endl;
        return false;
    }
    _stack[_top++] = item;
    _number++;
    return true;
}

// *****************************************************************
// * Function Name: Pop                                            *
// * Description: Function will pop an item off of the stack.      *
// *    Function will first make sure the stack isn't already      *
// *    empty. If it's empty, function returns false. Otherwise,   *
// *    the top item is popped off and then the _top private data  *
// *    item is reduced to account for the reduction. Function     *
// *    then returns true for successful Pop.                      *
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
bool Stack<T>::Pop()
{
    if(Empty())
    {
        cout << "Empty stack" << endl;
        return false;
    }
    cout << _stack[--_top] << endl;
    _number--;
    return true;
}

// *****************************************************************
// * Function Name: Number                                         *
// * Description: Function will return the number of elements in   *
// *    the stack, as an integer.                                  *
// * Parameter Description: N/A                                    *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
int Stack<T>::Number()
{
    return _number;
}

// *****************************************************************
// * Function Name: = operator overload                            *
// * Description: Assignment operator overload. Function will      *
// *    deallocate memory (if any) of the calling Stack and assign *
// *    the _size, _top, number of elements, and elements of the   *
// *    passed in Stack to the calling Stack and then return the   *
// *    newly created stack.                                       *
// * Parameter Description: Takes in a Stack by constant reference *
// *    called stack. Used to copy the size, top index, number of  *
// *    elements and elements into the calling Stack.              *
// * Date: 08/25/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<class T>
Stack<T> & Stack<T>::operator=(const Stack &stack)
{
    if(_size > 0)
    {
        delete [] _stack;
        _stack = nullptr;
    }
    _size = stack._size;
    _top = stack._top;
    _number = stack._number;
    _stack = new T[_size];
    for(int i = 0; i < _top; i++)
    {
        _stack[i] = stack._stack[i];
    }
    return *this;
}


