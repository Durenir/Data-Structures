
#include "List.h"

#ifndef DL_LIST_HPP
#define DL_LIST_HPP
// ***************************************************************************
// * Name: List ( List.hpp filename )                                        *
// * Description: Implementation of a templated doubly linked list.          *
// *    Implementation can create empty list, create list of a user defined  *
// *    size with user defined data, copy list, move list, check if the list *
// *    is empty, clear the list, get the size of the list, insert a node to *
// *    the front and back of a list, remove a node at the front and back of *
// *    a list, get the first and last element of a list, create an iterator *
// *    that points to the first and last position of a list, insert data    *
// *    anywhere within the list, remove data anywhere within the list,      *
// *    print the list, reverse the list, and remove elements determined by  *
// *    a user defined predicate.                                            *
// * Author: William Ryan Miller                                             *
// * References: Textbook: Data Structures and Algorithm Analysis            *
// *    in C++ fourth edition                                                *
// * Date: 09/18/2020                                                        *
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
List<T>::const_iterator::const_iterator()
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
const T & List<T>::const_iterator::operator*() const
{
    return retrieve();
}

// *****************************************************************
// * Function Name: postfix ++ operator overload                   *
// * Description: Overloads the postfix ++ operator by advancing   *
// *    current node being pointed to by the iterator, to the next *
// *    node in the list.                                          *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++() {
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
// *    the list, and returning the old position.                  *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
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
// *    previous node in the list.                                 *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Miller                                        *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Performs the opposite of the        *
// *    postfix ++. Used postfix ++ from the book as a reference.  *
// *****************************************************************
template<typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator--() {
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
// *    node in the list, and returning the old position.          *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Miller                                        *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Performs the opposite of the        *
// *    preefix ++. Used pretfix ++ from the book as a reference.  *
// *****************************************************************
template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
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
bool List<T>::const_iterator::operator==(const List::const_iterator &rhs) const {
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
bool List<T>::const_iterator::operator!=(const List::const_iterator &rhs) const {
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
T &List<T>::const_iterator::retrieve() const {
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
List<T>::const_iterator::const_iterator(List::Node *p) : current{p}{

}

// *****************************************************************
// * Function Name: iterator                                       *
// * Description: Default constructor of type iterator. Inherits   *
// *    from base class const_iterator.                            *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
List<T>::iterator::iterator() {

}

// *****************************************************************
// * Function Name: * operator overload                            *
// * Description: Overloads the dereference operator of the        *
// *    iterator class by calling retrieve() to get and return     *
// *    the data element stored at the address currently being     *
// *    pointed to by the iterator.                                *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
T &List<T>::iterator::operator*() {
    return const_iterator::retrieve();
}

// *****************************************************************
// * Function Name: * operator overload                            *
// * Description: Overloads the dereference operator of the        *
// *    iterator class by using the dereference operator overload  *
// *    in the const_iterator class to get and return the data     *
// *    element stored at the address that iterator is currently   *
// *    pointed to. Returns the data element as a constant.        *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
const T &List<T>::iterator::operator*() const {
    return const_iterator::operator*();
}

// *****************************************************************
// * Function Name: ++ operator overload                           *
// * Description: Overloads the postfix increment operator by      *
// *    advancing the address the iterator is pointing to, to the  *
// *    next address in the list.                                  *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename List<T>::iterator &List<T>::iterator::operator++() {
    if(this->current->next != nullptr)
    {
        this->current = this->current->next;
    }
    return *this;
}

// *****************************************************************
// * Function Name: prefix ++ operator overload                    *
// * Description: Overloads the prefix ++ operator by storing the  *
// *    current iterator in an separate iterator called old,       *
// *    advancing the current iterator forward to the next node in *
// *    the list, and returning the old position.                  *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
    iterator old = *this;
    if(this->current != nullptr)
    {
        ++(*this);
    }
    return old;
}

// *****************************************************************
// * Function Name: postfix -- operator overload                   *
// * Description: Overloads the postfix -- operator by advancing   *
// *    current node being pointed to by the iterator, to the      *
// *    previous node in the list.                                 *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Miller                                        *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Performs the opposite of the        *
// *    postfix ++. Used postfix ++ from the book as a reference.  *
// *****************************************************************
template<typename T>
typename List<T>::iterator &List<T>::iterator::operator--() {
    if(this->current->prev != nullptr)
    {
        this->current = this->current->prev;
    }
    return *this;
}

// *****************************************************************
// * Function Name: prefix -- operator overload                    *
// * Description: Overloads the prefix -- operator by storing the  *
// *    current iterator in an separate iterator called old,       *
// *    advancing the current iterator backward to the previous    *
// *    node in the list, and returning the old position.          *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Miller                                        *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Performs the opposite of the        *
// *    prefix ++. Used prefix ++ from the book as a reference.    *
// *****************************************************************
template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
    iterator old = *this;
    if(this->current->prev != nullptr)
    {
        --(*this);
    }
    return old;
}

// *****************************************************************
// * Function Name: iterator                                       *
// * Description: Constructor of type iterator. Initializes a new  *
// *    iterator that points to the passed in node by passing the  *
// *    node to the const_iterator constructor.                    *
// * Parameter Description: Takes in a Node called p which is used *
// *    as the Node the constructed iterator will point to.        *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
List<T>::iterator::iterator(List::Node *p):const_iterator{p} {

}

// *****************************************************************
// * Function Name: List                                           *
// * Description: Default constructor of type List. Constructs a   *
// *    default List by calling init() to initialize a default     *
// *    List.                                                      *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
List<T>::List() {
    init();
}

// *****************************************************************
// * Function Name: List                                           *
// * Description: Copy constructor of type List. Constructs a List *
// *    by iterating through the passed in List and coping each    *
// *    node one by one into the new list.                         *
// * Parameter Description: Takes in a List called rhs. Used as    *
// *    the container of Nodes that will be copied into the newly  *
// *    constructed List.                                          *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
List<T>::List(const List &rhs) {
    init();
    for(auto & x : rhs)
    {
        push_back(x);
    }
}

// *****************************************************************
// * Function Name: List                                           *
// * Description: Move constructor of type List. Constructor moves *
// *    ownership of the member data from the passed in list to the*
// *    newly created list and then changes the member data of the *
// *    passed in list to point to nothing.                        *
// * Parameter Description: Takes in a List called rhs. Used to    *
// *    initialize a new list by giving the member data to the new *
// *    list. Afterwards, rhs points to nothing with a size of 0.  *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
List<T>::List(List &&rhs)
        : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

// *****************************************************************
// * Function Name: List                                           *
// * Description: Constructor of type List. Initializes a new List *
// *    by adding adding a user defined value into the List. User  *
// *    defined data will be added a user defined number of times. *
// * Parameter Description: Takes in an int call num and a const T *
// *    value by reference called T. T stores the data element to  *
// *    be added to the list and num stores how many times val will*
// *    be added.                                                  *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
List<T>::List(int num, const T &val) {
    init();
    for(int i = 0; i < num; i++)
    {
        push_back(val);
    }
}

// *****************************************************************
// * Function Name: List                                           *
// * Description: Constructor of type List. Creates a new List by  *
// *    using the passed in start and end iterators. Constructor   *
// *    will copy the nodes from start to end but not including    *
// *    end. [start, end).                                         *
// * Parameter Description: Takes in a const_iterator called start *
// *    and a const_iterator called end. Used to iterate from start*
// *    to end, copying each node into the new List being          *
// *    constructed.                                               *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
List<T>::List(List::const_iterator start, List::const_iterator end) {
        init();
        if (start.current != nullptr && end.current != nullptr)
        {
            while (start != end)
            {
                push_back(*start);
                start++;
            }
        }
}

// *****************************************************************
// * Function Name: List                                           *
// * Description: Constructor of type List. Constructs a new List  *
// *    using a passed in initializer list. Constructor will place *
// *    each data element in the initializer list into the         *
// *    constructed List.                                          *
// * Parameter Description: Takes in an initializer_list called    *
// *    iList which contains the data elements to be pushed into   *
// *    the constructed list.                                      *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
List<T>::List(std::initializer_list<T> iList) {
    init();
    for(auto x : iList)
    {
        push_back(x);
    }
}

// *****************************************************************
// * Function Name: ~List                                          *
// * Description: Destructor of type List. Frees allocated memory  *
// *    of a List by calling clear. Deletes the head and the tail  *
// *    just in case.                                              *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
List<T>::~List() {
    clear();
    delete head;
    delete tail;
    head = nullptr;
    tail = nullptr;
}

// *****************************************************************
// * Function Name: = operator overload                            *
// * Description: Copy assignment operator overload of type List.  *
// *    Assigns a list a copy of the passed in (rhs) list.         *
// * Parameter Description: Takes in an List called rhs. Used as   *
// *    the List to be copied into the lhs List.                   *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
const List<T> &List<T>::operator=(const List &rhs) {
    List<T> copy = rhs;
    std::swap(*this, copy);
    return *this;
}

// *****************************************************************
// * Function Name: = operator overload                            *
// * Description: Move assignment operator overload of type List.  *
// *    Moves ownership of of a list from the passed in list to the*
// *    calling list by swapping member data of the lists.         *
// * Parameter Description: Takes in an List called rhs. Used as   *
// *    the List to be moved into the lhs List.                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
List<T> &List<T>::operator=(List &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

// *****************************************************************
// * Function Name: = operator overload                            *
// * Description: Initializer list assignment operator overload    *
// *    of type List. Assigns the calling List the data elements   *
// *    of the passed in initializer list.                         *
// * Parameter Description: Takes in an initializer list called    *
// *    iList. iList is used as a container of data elements to be *
// *    pushed into the List.                                      *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
List<T> &List<T>::operator=(std::initializer_list<T> iList) {
    clear();
    for(auto x : iList)
    {
        push_back(x);
    }
    return *this;
}

// *****************************************************************
// * Function Name: size                                           *
// * Description: Accessor function of private data member theSize.*
// *    Returns the size of a list.                                *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
int List<T>::size() const {
    return theSize;
}

// *****************************************************************
// * Function Name: empty                                          *
// * Description: Function returns true if the calling List is     *
// *    empty. Returns false if not empty. Determines if a list is *
// *    emtpy by checking if the size of the list is 0.            *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
bool List<T>::empty() const {
    return theSize == 0;
}

// *****************************************************************
// * Function Name: begin                                          *
// * Description: Returns an iterator that points to the first     *
// *    node of a list. If the list is empty, returns an iterator  *
// *    that points to the tail, else returns an iterator that     *
// *    points towards the head.                                   *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
typename List<T>::iterator List<T>::begin() {
    if(empty())
    {
        return List::iterator(tail);
    }
    return List::iterator(head);
}

// *****************************************************************
// * Function Name: begin                                          *
// * Description: Returns a const iterator that points to the first*
// *    node of a list. If the list is empty, returns a const      *
// *    iterator that points to the tail, else returns a const     *
// *    iterator that points towards the head.                     *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
typename List<T>::const_iterator List<T>::begin() const {
    if(empty())
    {
        return List::const_iterator(tail);
    }
    return List::const_iterator(head);
}

// *****************************************************************
// * Function Name: end                                            *
// * Description: Returns an iterator that points to the tail.     *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
typename List<T>::iterator List<T>::end() {
    return List::iterator(tail);
}

// *****************************************************************
// * Function Name: end                                            *
// * Description: Returns a const iterator that points to the tail.*
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
typename List<T>::const_iterator List<T>::end() const {
    return List::const_iterator(tail);
}

// *****************************************************************
// * Function Name: clear                                          *
// * Description: Functions clears the list by calling pop_front   *
// *    to delete the first data element of the calling list until *
// *    the List is empty.                                         *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void List<T>::clear() {
    while(!empty())
    {
        pop_front();
    }
}

// *****************************************************************
// * Function Name: front                                          *
// * Description: Returns a reference to the first data element of *
// *    the calling list by calling begin() to get the address of  *
// *    the first address in the List. Function then returns the   *
// *    dereferenced address.                                      *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
T &List<T>::front() {
    return *begin();
}

// *****************************************************************
// * Function Name: front                                          *
// * Description: Returns a const reference to the first data      *
// *    element of the calling list by calling begin() to get the  *
// *    address of the first address in the List. Function then    *
// *    returns the dereferenced address as a const.               *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
const T &List<T>::front() const {
    return *begin();
}

// *****************************************************************
// * Function Name: back                                           *
// * Description: Returns a reference to the last data element of  *
// *    the calling list by calling end() to get the address of    *
// *    the tail in the List. Then uses the decrement operator to  *
// *    get the address of the data element just before the tail.  *
// *    Finally, the function returns the dereferenced address of  *
// *    the data element.                                          *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
T &List<T>::back() {
    return *--end();
}

// *****************************************************************
// * Function Name: back                                           *
// * Description: Returns a const reference to the last data       *
// *    element of the calling list by calling end() to get the    *
// *    address of the tail in the List. Then uses the decrement   *
// *    operator to get the address of the data element just before*
// *    the tail. Finally, the function returns the dereferenced   *
// *    address of the data element as a const.                    *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
const T &List<T>::back() const {
    return *--end();
}

// *****************************************************************
// * Function Name: push_front                                     *
// * Description: Function inserts a passed in data element to the *
// *    front of the list by calling insert() and passing it an    *
// *    iterator that points to the first node in the list and the *
// *    value to be added.                                         *
// * Parameter Description: Takes in a const T called val that     *
// *    contains the value of the data element to be inserted into *
// *    the list.                                                  *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void List<T>::push_front(const T &val) {
    insert(begin(), val);
}

// *****************************************************************
// * Function Name: push_front                                     *
// * Description: Function moves a passed in data element to the   *
// *    front of the list by calling insert() and passing it an    *
// *    iterator that points to the first node in the list and the *
// *    value to be moved.                                         *
// * Parameter Description: Takes in a const T called val that     *
// *    contains the value of the data element to be moved into the*
// *    list.                                                      *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void List<T>::push_front(T &&val) {
    insert(begin(), std::move(val));
}

// *****************************************************************
// * Function Name: push_back                                      *
// * Description: Function stores a passed in data element at the  *
// *    end of the list by calling insert() and passing it an      *
// *    iterator that points to the last node in the list and the  *
// *    value to be stored. Does not replace the tail.             *
// * Parameter Description: Takes in a const T called val that     *
// *    contains the value of the data element to be stored in the *
// *    list.                                                      *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void List<T>::push_back(const T &val) {
    insert(end(), val);
}

// *****************************************************************
// * Function Name: push_back                                      *
// * Description: Function moves a passed in data element into the *
// *    end of the list by calling insert() and passing it an      *
// *    iterator that points to the last node in the list and the  *
// *    value to be moved. Does not replace the tail.              *
// * Parameter Description: Takes in a const T called val that     *
// *    contains the value of the data element to be moved into the*
// *    list.                                                      *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void List<T>::push_back(T &&val) {
    insert(end(), std::move(val));
}

// *****************************************************************
// * Function Name: pop_front                                      *
// * Description: Function removes a data element from the front of*
// *    the List by calling begin() to get an iterator that points *
// *    to the front of a list. That iterator is then passed to    *
// *    erase() which will free up the memory and relink nodes     *
// *    where necessary.                                           *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void List<T>::pop_front() {
    erase(begin());
}

// *****************************************************************
// * Function Name: pop_back                                       *
// * Description: Function removes a data element from the back of *
// *    the List by calling end() to get an iterator that points to*
// *    the tail of the list. That iterator is then deincremented  *
// *    to get the node just before the tail. The iterator is then *
// *    passed to erase() which will free up the memory and relink *
// *    nodes where necessary.                                     *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
void List<T>::pop_back() {
    erase(--end());
}

// *****************************************************************
// * Function Name: insert                                         *
// * Description: Function inserts a passed in data element into   *
// *    the calling list just before the node pointed to by the    *
// *    passed in iterator. Reconstructs links as needed. Returns  *
// *    an iterator to the new node containing the inserted data   *
// *    element.                                                   *
// * Parameter Description: Takes in an iterator called itr and a  *
// *    const T called val. Function will insert data element val  *
// *    just before the position pointed to by iterator itr.       *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename List<T>::iterator List<T>::insert(List::iterator itr, const T &val) {
    List<T>::Node *temp = nullptr;
    List<T>::Node *node = itr.current;
    if (empty()) {
        temp = head = new Node(val, nullptr, tail);
        tail->prev = temp;
    } else if(node == nullptr)
    {
        push_back(val);
    }else if(node == head)
    {
        head = temp = new Node(val, nullptr, node);
        node->prev = temp;
    } else {
        temp = new Node(val, node->prev, node);
        temp->prev->next = temp;
        temp->next->prev = temp;
    }
    theSize++;
    return List<T>::iterator(temp);
}

// *****************************************************************
// * Function Name: insert                                         *
// * Description: Function inserts a passed in data element into   *
// *    the calling list just before the node pointed to by the    *
// *    passed in iterator by moving the data. Reconstructs links  *
// *    as needed. Returns an iterator to the new node containing  *
// *    the inserted data element.                                 *
// * Parameter Description: Takes in an iterator called itr and a  *
// *    const T called val. Function will insert data element val  *
// *    just before the position pointed to by iterator itr.       *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename List<T>::iterator List<T>::insert(List::iterator itr, T &&val) {
    List<T>::Node *temp = nullptr;
    List<T>::Node *node = itr.current;
    if (empty()) {
        temp = head = new Node(std::move(val), nullptr, tail);
        tail->prev = temp;
    } else if(node == nullptr)
    {
        push_back(std::move(val));
    }else if(node == head)
    {
        head = temp = new Node(std::move(val), nullptr, node);
        node->prev = temp;
    } else {
        temp = new Node(std::move(val), node->prev, node);
        temp->prev->next = temp;
        temp->next->prev = temp;
    }
    theSize++;
    return List<T>::iterator(temp);
}

// *****************************************************************
// * Function Name: erase                                          *
// * Description: Function erases the node pointed to by the passed*
// *    in iterator. Function reconstructs the links as needed and *
// *    returns an iterator that points to the node after the      *
// *    erased one.                                                *
// * Parameter Description: Takes in an iterator called itr used to*
// *    pointed to the address of the node to be erased from the   *
// *    list.                                                      *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
    if(!empty() && itr.current != nullptr)
    {
        List<T>::Node  * p = itr.current;
        List<T>::Node * temp;
        if(p == head && p->next == tail)
        {
            tail->prev = nullptr;
            head = nullptr;
            temp = tail;
        } else if(p == head && p->next != tail)
        {
            head = head->next;
            head->prev = nullptr;
            temp = head;
        } else {
            temp = p->next;
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        theSize--;
        delete p;
        return List<T>::iterator(temp);
    }
    return List<T>::iterator();
}

// *****************************************************************
// * Function Name: erase                                          *
// * Description: Function erases all nodes between the node       *
// *    pointed to by the passed in iterator called start and the  *
// *    passed in iterator called end; including start.            *
// *    [start, end) Function does this by calling erase() for each*
// *    node in the interval.                                      *
// * Parameter Description: Takes in an iterator called start and  *
// *    an iterator called end. Used to mark the beginning and end *
// *    of the interval to be erased.                              *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition                                      *
// *****************************************************************
template<typename T>
typename List<T>::iterator List<T>::erase(List::iterator start, List::iterator end) {
    if(start.current == end.current && start.current != tail)
    {
        return erase(start);
    }
    if(start.current != nullptr && end.current != nullptr)
    {
        for (iterator itr = start; itr != end;)
        {
            itr = erase(itr);
        }
        return end;
    }
    return List<T>::iterator();
}

// *****************************************************************
// * Function Name: print                                          *
// * Description: Function outputs each data element in the list   *
// *    with the user defined deliminator between each data        *
// *    element. If no deliminator is passed. Uses a space as the  *
// *    default.                                                   *
// * Parameter Description: Takes in an ostream called os and a    *
// *    char called ofc. os is the stream the data is printed out  *
// *    to and ofc is the deliminator between data elements.       *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
void List<T>::print(std::ostream &os, char ofc) const {
    const_iterator itr = begin();
    while(itr != end())
    {
        os << *itr << ofc;
        itr++;
    }
}

// *****************************************************************
// * Function Name: == operator overload                           *
// * Description: Comparison operator overload of type List.       *
// *    First compares the size of each list to make the common    *
// *    case fast. If both list are of equal size, function will   *
// *    compare the value of each element in the both list. If each*
// *    value is the same for each node in both list, returns true.*
// *    Otherwise, returns false.                                  *
// * Parameter Description: Takes in a List called lhs and a List  *
// *    called rhs. Function compares lhs and rhs to determine if  *
// *    they contain the same data, stored in the same order.      *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
    if(lhs.size() == rhs.size())
    {
        auto lhsitr = lhs.begin();
        auto rhsitr = rhs.begin();
        while(lhsitr != lhs.end())
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
// *    type List. Uses the comparison operator overload to see if *
// *    the Lists are equal. Returns the negation of the returned  *
// *    equality boolean to determine if they are not equal.       *
// * Parameter Description: Takes in a List called lhs and a List  *
// *    called rhs. Function compares lhs and rhs to determine if  *
// *    they contain the same data, stored in the same order.      *
// *    returns true if they don't. False if they do.              *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
    return !(lhs == rhs);
}

// *****************************************************************
// * Function Name: << operator overload                           *
// * Description: Output stream operator overload. Calls print() to*
// *    output the data elements of the passed in List to the      *
// *    passed in output stream.                                   *
// * Parameter Description: Takes in an ostream called os and a    *
// *    List called l. Function outputs List l to ostream os.      *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
    l.print(os);
    return os;
}

// *****************************************************************
// * Function Name: init                                           *
// * Description: Initializes the member data of a list by setting *
// *    the private data members size, head, and tail.             *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void List<T>::init()
{
    theSize = 0;
    head = nullptr;
    tail = new Node();
}

// *****************************************************************
// * Function Name: remove                                         *
// * Description: Function removes all nodes in the calling List   *
// *    that contain the passed in data element by iterating       *
// *    through the List and comparing the dereferenced value of   *
// *    each iteration to the passed in value. If they are equal,  *
// *    function passes the iterator to the erase function.        *
// * Parameter Description: Takes in a const T called val. val is  *
// *    the value of the data element to be searched for in the    *
// *    calling List and removed if found.                         *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
void List<T>::remove(const T &val) {
        for(iterator itr = begin(); itr != end();)
        {
            if(*itr == val)
            {
                itr = erase(itr);
            } else {
                itr++;
            }
        }
}

// *****************************************************************
// * Function Name: reverse                                        *
// * Description: Reverses the order of the nodes in the calling   *
// *    List by reversing the direction of the links of each node. *
// *    Adjust links and reassigns the head accordingly.           *
// * Parameter Description: N/A                                    *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
void List<T>::reverse() {
    if(size() > 1) {
        Node *current = head;
        Node *temp = nullptr;
        while (current != tail) {
            temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        }
        current = head;
        head = tail->prev;
        tail->prev = current;
        current->next = tail;
    }
}

// *****************************************************************
// * Function Name: remove_if                                      *
// * Description: Removes all nodes of the calling List that       *
// *    satisfy a user defined predicate. Function iterates        *
// *    through the List, passing each dereferenced iteration to   *
// *    the predicate function. If the predicate function returns  *
// *    true, the node pointed to by the iterator is erased.       *
// * Parameter Description: Takes in a PREDICATE called pred.      *
// *    pred is the boolean function used to determine if a node   *
// *    should be removed from the list.                           *
// * Date: 09/18/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)
{
    if(!empty()) {
        for (auto itr = begin(); itr != end();) {
            if (pred(*itr)) {
                itr = erase(itr);
            } else {
                itr++;
            }
        }
    }
}
#endif
