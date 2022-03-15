#ifndef DL_LIST_HPP
#define DL_LIST_HPP
#include "stack.h"
// ***************************************************************************
// * Name: Stack ( stack.hpp filename )                                      *
// * Description: Implementation of a stack via a templated doubly linked    *
// *    list. Contains a const iterator. The stack can be pushed, popped,    *
// *    return the top element, return the size, and return if the stack is  *
// *    empty. Contains copy, move, and default constructors.                *
// * Author: William Ryan Miller                                             *
// * References: Textbook: Data Structures and Algorithm Analysis            *
// *    in C++ fourth edition                                                *
// * Date: 10/02/2020                                                        *
// ***************************************************************************
// *****************************************************************
// * Function Name: const_iterator                                 *
// * Description: Default constructor of type const_iterator.      *
// *    Creates an empty const_iterator by setting data member     *
// *    current equal to nullptr.                                  *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template <typename T>
    Stack<T>::const_iterator::const_iterator()
{
    current= nullptr;
}

// *****************************************************************
// * Function Name: * operator overload                            *
// * Description: Overloads the * operator by calling retrieve     *
// *    and returning the value that is returned by retrieve.      *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template <typename T>
const T & Stack<T>::const_iterator::operator*() const
{
    return retrieve();
}

// *****************************************************************
// * Function Name: postfix ++ operator overload                   *
// * Description: Overloads the postfix ++ operator by advancing   *
// *    current node being pointed to by the iterator, to the next *
// *    node in the stack.                                         *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename Stack<T>::const_iterator &Stack<T>::const_iterator::operator++() {
    if(current->next != nullptr) {
        current = current->next;
    }
    return *this;
}

// *****************************************************************
// * Function Name: prefix ++ operator overload                    *
// * Description: Overloads the prefix ++ operator by storing the  *
// *    current iterator in an separate iterator called old,       *
// *    advancing the current iterator forward to the next node in *
// *    the stack, and returning the old position.                 *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename Stack<T>::const_iterator Stack<T>::const_iterator::operator++(int) {
    const_iterator old = *this;
    if(current->next != nullptr)
    {
        ++(*this);
    }
    return old;
}

// *****************************************************************
// * Function Name: postfix -- operator overload                   *
// * Description: Overloads the postfix -- operator by advancing   *
// *    current node being pointed to by the iterator, to the      *
// *    previous node in the stack.                                *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Performs the opposite of the        *
// *    postfix ++. Used postfix ++ from the book as a reference.  *
// *****************************************************************
template<typename T>
typename Stack<T>::const_iterator &Stack<T>::const_iterator::operator--() {
    if(current->prev != nullptr)
    {
        current = current->prev;
    }
    return *this;
}

// *****************************************************************
// * Function Name: prefix -- operator overload                    *
// * Description: Overloads the prefix -- operator by storing the  *
// *    current iterator in an separate iterator called old,       *
// *    advancing the current iterator backward to the previous    *
// *    node in the stack, and returning the old position.         *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Performs the opposite of the        *
// *    preefix ++. Used pretfix ++ from the book as a reference.  *
// *****************************************************************
template<typename T>
typename Stack<T>::const_iterator Stack<T>::const_iterator::operator--(int) {
    const_iterator old = *this;
    if(current->prev != nullptr)
    {
        --(*this);
    }
    return old;
}

// *****************************************************************
// * Function Name:  == operator overload                          *
// * Description: Overloads the comparison operator by comparing   *
// *    node being pointed to by the lhs to the node being pointed *
// *    to by the rhs. If they point to the same address, return   *
// *    true, else returns false.                                  *
// * Parameter Description: Takes in a const_iterator called rhs.  *
// *    rhs is used to compare the the address of rhs to the       *
// *    address pointed to by the calling const_iterator.          *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
bool Stack<T>::const_iterator::operator==(const Stack::const_iterator &rhs) const {
    return current == rhs.current;
}

// *****************************************************************
// * Function Name: != operator overload                           *
// * Description: Overloads the comparison operator by comparing   *
// *    the address pointed to by the calling iterator to the      *
// *    address pointed to by the passed in rhs. If they are equal *
// *    returns false, if they aren't equal, returns true.         *
// * Parameter Description: Takes in a const_iterator called rhs.  *
// *    rhs is used as the right hand side in the comparison       *
// *    operation.                                                 *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
bool Stack<T>::const_iterator::operator!=(const Stack::const_iterator &rhs) const {
    return !(*this == rhs);
}

// *****************************************************************
// * Function Name: retrieve                                       *
// * Description: Returns the data element at the address being    *
// *    pointed to by the calling const_iterator.                  *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
T &Stack<T>::const_iterator::retrieve() const {
    return current->data;
}

// *****************************************************************
// * Function Name: const_iterator                                 *
// * Description: Constructor of type const_iterator. Takes in a   *
// *    Node called p. Constructor sets p as the current node      *
// *    being pointed to.                                          *
// * Parameter Description: Takes in a Node called p. Passed in    *
// *    node becomes the node that const_iterator is pointing to.  *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
Stack<T>::const_iterator::const_iterator(Stack::Node *p) : current{p}{

}

// *****************************************************************
// * Function Name: HasNext                                        *
// * Description: HasNext will check if the next node in a doubly  *
// *    linked list is valid. Returns false if not valid.          *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
bool Stack<T>::const_iterator::HasNext() const {
    return current->next != nullptr;
}

// *****************************************************************
// * Function Name: HasPrevious                                    *
// * Description: HasPrevious will check if the previous node in a *
// *    doubly linked list is valid. Returns false if not valid.   *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
bool Stack<T>::const_iterator::HasPrevious() const {
    return current->prev != nullptr;
}

// *****************************************************************
// * Function Name: Stack                                          *
// * Description: Default constructor of type Stack. Constructs a  *
// *    default stack by calling init() to initialize a default    *
// *    Stack.                                                     *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
Stack<T>::Stack() {
    init();
}

// *****************************************************************
// * Function Name: Stack                                          *
// * Description: Copy constructor of type Stack. Constructs a     *
// *    stack by iterating through the passed in stack and coping  *
// *    each node one by one into the new stack.                   *
// * Parameter Description: Takes in a stack called rhs. Used as   *
// *    the container of Nodes that will be copied into the newly  *
// *    constructed stack.                                         *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
Stack<T>::Stack(const Stack &rhs) {
    init();
    const_iterator itr(rhs.tail);
    while(itr.HasPrevious())
    {
        push(*--itr);
    }
}

// *****************************************************************
// * Function Name: Stack                                          *
// * Description: Move constructor of type Stack. Constructor moves*
// *    ownership of the member data from the passed in Stack to   *
// *    the newly created stack and then changes the member data of*
// *    the passed in stack to point to nothing.                   *
// * Parameter Description: Takes in a stack called rhs. Used to   *
// *    initialize a new stack by giving the member data to the new*
// *    stack. Afterwards, rhs points to nothing with a size of 0. *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
Stack<T>::Stack(Stack &&rhs)
        : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

// *****************************************************************
// * Function Name: ~Stack                                         *
// * Description: Destructor of type Stack. Frees allocated memory *
// *    of a Stack by calling clear and deletes the tail.          *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                             *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
Stack<T>::~Stack() {
    clear();
    delete tail;
    tail = nullptr;
}

// *****************************************************************
// * Function Name: = operator overload                            *
// * Description: Copy assignment operator overload of type stack. *
// *    Assigns a stack a copy of the passed in (rhs) stack.       *
// * Parameter Description: Takes in a stack called rhs. Used as   *
// *    the stack to be copied into the lhs stack.                   *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
Stack<T> &Stack<T>::operator=(const Stack &rhs) {
    Stack<T> copy = rhs;
    std::swap(*this, copy);
    return *this;
}

// *****************************************************************
// * Function Name: = operator overload                            *
// * Description: Move assignment operator overload of type Stack. *
// *    Moves ownership of of a stack from the passed in stack to   *
// *    the calling stack by swapping member data of the stacks.   *
// * Parameter Description: Takes in a stack called rhs. Used as   *
// *    the stack to be moved into the lhs stack.                  *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
Stack<T> &Stack<T>::operator=(Stack &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

// *****************************************************************
// * Function Name: size                                           *
// * Description: Accessor function of private data member theSize.*
// *    Returns the size of a stack.                                *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
int Stack<T>::size() const {
    return theSize;
}

// *****************************************************************
// * Function Name: empty                                          *
// * Description: Function returns true if the calling stack is    *
// *    empty. Returns false if not empty. Determines if a stack is*
// *    emtpy by checking if the size of the stack is 0.           *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
bool Stack<T>::empty() const {
    return theSize == 0;
}

// *****************************************************************
// * Function Name: begin                                          *
// * Description: Returns a const iterator that points to the first*
// *    node of a stack. If the stack is empty, returns a const    *
// *    iterator that points to the tail, else returns a const     *
// *    iterator that points towards the head.                     *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
typename Stack<T>::const_iterator Stack<T>::begin() const {
    if(empty())
    {
        return Stack::const_iterator(tail);
    }
    return Stack::const_iterator(head);
}

// *****************************************************************
// * Function Name: clear                                          *
// * Description: Functions clears the stack by calling pop to     *
// *    delete the first data element of the calling stack until   *
// *    the stack is empty.                                        *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void Stack<T>::clear() {
    while(!empty())
    {
        pop();
    }
}

// *****************************************************************
// * Function Name: top                                            *
// * Description: Returns the data stored in the head. If the      *
// *    stack is empty, returns the tail.                          *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
T &Stack<T>::top() {
    if(!empty())
    {
        return head->data;
    } else {
        return tail->data;
    }
}

// *****************************************************************
// * Function Name: top                                            *
// * Description: Returns a const reference to the first data      *
// *    element of the calling stack by calling begin() to get the *
// *    address of the first address in the stack. Function then   *
// *    returns the dereferenced address as a const.               *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
const T &Stack<T>::top() const {
    return *begin();
}

// *****************************************************************
// * Function Name: print                                          *
// * Description: Function outputs each data element in the stack  *
// *    with the user defined deliminator between each data        *
// *    element. If no deliminator is passed. Uses a space as the  *
// *    default.                                                   *
// * Parameter Description: Takes in an ostream called os and a    *
// *    char called ofc. os is the stream the data is printed out  *
// *    to and ofc is the deliminator between data elements.       *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
void Stack<T>::print(std::ostream &os, char ofc) const {
    const_iterator itr(tail);
    while(itr.HasPrevious())
    {
        os << *--itr << ofc;
    }
}

// *****************************************************************
// * Function Name: == operator overload                           *
// * Description: Comparison operator overload of type stack.      *
// *    First compares the size of each stack to make the common   *
// *    case fast. If both stacks are of equal size, function will *
// *    compare the value of each element in the both stacks. If   *
// *    each value is the same for each node in both stacks,       *
// *    returns true. Otherwise, returns false.                    *
// * Parameter Description: Takes in a stack called lhs and a stack*
// *    called rhs. Function compares lhs and rhs to determine if  *
// *    they contain the same data, stored in the same order.      *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool operator==(const Stack<T> & lhs, const Stack<T> &rhs)
{
    if(lhs.size() == rhs.size())
    {
        auto lhsitr = lhs.begin();
        auto rhsitr = rhs.begin();
        while(lhsitr.HasNext())
        {
            if(*lhsitr != *rhsitr)
            {
                return false;
            }
            lhsitr++;
            rhsitr++;
        }
        return true;
    }
    return false;
}

// *****************************************************************
// * Function Name: != operator overload                           *
// * Description: Negation of the comparison operator overload of  *
// *    type stack. Uses the comparison operator overload to see if*
// *    the stacks are equal. Returns the negation of the returned *
// *    equality boolean to determine if they are not equal.       *
// * Parameter Description: Takes in a stack called lhs and a stack*
// *    called rhs. Function compares lhs and rhs to determine if  *
// *    they contain the same data, stored in the same order.      *
// *    returns true if they don't. False if they do.              *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool operator!=(const Stack<T> & lhs, const Stack<T> &rhs)
{
    return !(lhs == rhs);
}

// *****************************************************************
// * Function Name: << operator overload                           *
// * Description: Output stream operator overload. Calls print() to*
// *    output the data elements of the passed in stack to the     *
// *    passed in output stream.                                   *
// * Parameter Description: Takes in an ostream called os and a    *
// *    stack called l. Function outputs stack l to ostream os.    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
std::ostream & operator<<(std::ostream &os, const Stack<T> &l)
{
    l.print(os);
    return os;
}

// *****************************************************************
// * Function Name: <= operator overload                           *
// * Description: Less than or equal to operator overload. Compares*
// *    two Stacks to determine if one stack is less than or equal *
// *    to another stack.                                          *
// * Parameter Description: Takes in a stack called s1 and a stack *
// *    called s2. Function compares s1 and s1 to determine if they*
// *    contain the same data or if s1 is < s2.                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool operator<=(const Stack<T>& s1, const Stack<T>& s2)
{
    auto lhsitr = s1.begin();
    auto rhsitr = s2.begin();
    if(s1.size() == s2.size())
    {
        while(lhsitr.HasNext())
        {
            if(*lhsitr > *rhsitr) {
                return false;
            }
            lhsitr++;
            rhsitr++;
        }
        return true;
    }
    return false;
}

// *****************************************************************
// * Function Name: init                                           *
// * Description: Initializes the member data of a stack by setting*
// *    the private data members size, head, and tail.             *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void Stack<T>::init()
{
    theSize = 0;
    head = nullptr;
    tail = new Node();
}

// *****************************************************************
// * Function Name: push                                           *
// * Description: Pushes a new node into the stack with the passed *
// *    in data element. Node will be inserted as the new head.    *
// * Parameter Description: Takes in a const T called x which      *
// *    contains the data to be stored.                            *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
void Stack<T>::push(const T &x) {
    if(empty())
    {
        head = new Node(x, nullptr, tail);
        tail->prev = head;
    } else {
        Node *node = new Node(x, nullptr, head);
        head->prev = node;
        head = node;
    }
    theSize++;
}

// *****************************************************************
// * Function Name: push                                           *
// * Description: Moves a passed in data into the stack.           *
// *    Pushes a new node into the stack with the passed           *
// *    in data element. Node will be inserted as the new head.    *
// * Parameter Description: Takes in a const T called x which      *
// *    contains the data to be moved into the stack.              *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
void Stack<T>::push(T &&x) {
    if(empty())
    {
        head = new Node(std::move(x), nullptr, tail);
        tail->prev = head;
    } else {
        Node *node = new Node(std::move(x), nullptr, head);
        head->prev = node;
        head = node;
    }
    theSize++;
}

// *****************************************************************
// * Function Name: pop                                            *
// * Description: Deletes the node pointed to by the head of the   *
// *    stack. The following node becomes the new head.            *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
void Stack<T>::pop() {
    if(!empty())
    {
        Node *p = head;
        if(head->next != tail) {
            head = head->next;
            head->prev = nullptr;
        } else {
            tail->prev = nullptr;
        }
        delete p;
        theSize--;
    }
}


#endif
