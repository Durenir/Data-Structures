#ifndef TLIST_HPP
#define TLIST_HPP

// ***************************************************************************
// * Name: TList ( tlist.hpp filename )                                      *
// * Description: Implementation of a templated doubly linked list.          *
// *    Implementation can create empty list, create list of a user defined  *
// *    size with user defined data, copy list, move list, check if the list *
// *    is empty, clear the list, get the size of the list, insert a node to *
// *    the front and back of a list, remove a node at the front and back of *
// *    a list, get the first and last element of a list, create an iterator *
// *    that points to the first and last position of a list, insert data    *
// *    anywhere within the list, remove data anywhere within the list,      *
// *    print the list, and concatenate two list.                            *
// *                                                                         *
// * Author: William Ryan Miller                                             *
// * Date: 09/08/2020                                                        *
// ***************************************************************************
// *****************************************************************
// * Function Name: TList                                          *
// * Description: Default constructor of type TList. Creates an    *
// *    emtpy list of size 0.                                      *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T>::TList()
{
    first = last = nullptr;
    size = 0;
}

// *****************************************************************
// * Function Name: TList                                          *
// * Description: Constructor of type TList. Creates a list of     *
// *    nodes that contain user a defined value. List will be of   *
// *    a user defined size.                                       *
// * Parameter Description: Takes in a data type called val that   *
// *    holds the element to be stored in the list. Takes in an int*
// *    called num that determines how many times val is stored in *
// *    the list.                                                  *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T>::TList(T val, int num)
{
    size = 0;
    first = last = nullptr;
    for(int i = 0; i < num; i++)
    {
        InsertBack(val);
    }
}

// *****************************************************************
// * Function Name: ~TList                                         *
// * Description: Destructor of type Tlist. Frees allocated memory *
// *    of a TList object by deleting each node in the list.       *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T>::~TList()
{
    Clear();
    delete first;
    delete last;
    first = nullptr;
    last = nullptr;
}

// *****************************************************************
// * Function Name: TList                                          *
// * Description: Copy constructor of type TList. Deep copies the  *
// *    nodes of the passed in Tlist into a new Tlist.             *
// * Parameter Description: Takes in a TList called L. Used as     *
// *    the container of nodes to be copied into the new list.     *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T>::TList(const TList& L)
{
    size = 0;
    Node<T> *temp = L.first;
    while(temp != nullptr)
    {
        InsertBack(temp->data);
        temp = temp->next;
    }
}

// *****************************************************************
// * Function Name: = Operator Overload                            *
// * Description: Deep copies the passed in TList into the calling *
// *    TList node by node.                                        *
// * Parameter Description: Takes in a TList called L to be copied *
// *    into the calling TList.                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T>& TList<T>::operator=(const TList& L)
{
    if(!IsEmpty())
    {
        Clear();
    }
    Node<T> *temp = L.first;
        while(temp != nullptr)
        {
            InsertBack(temp->data);
            temp = temp->next;
        }
    return *this;
}

// *****************************************************************
// * Function Name: TList                                          *
// * Description: Move constructor of type TList. Moves ownership  *
// *    of passed in TList to a new TList.                         *
// * Parameter Description: Takes in a TList called L to be moved  *
// *    into a new TList.                                          *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T>::TList(TList && L)
{
    first = L.first;
    last = L.last;
    size = L.size;

    L.size = 0;
    L.first = L.last = nullptr;
}

// *****************************************************************
// * Function Name: = Operator Overload (Move Assignment)          *
// * Description: Assigns a calling (Left hand side) TList the     *
// *    ownership of the passed in TList.                          *
// * Parameter Description: Takes in a TList called L in which the *
// *    data's ownership is to be transferred into the calling     *
// *    TList.                                                     *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T>& TList<T>::operator=(TList && L)
{
    Clear();
    first = L.first;
    last = L.last;
    size = L.size;

    L.size = 0;
    L.first = L.last = nullptr;
    return *this;
}

// *****************************************************************
// * Function Name: IsEmpty                                        *
// * Description: Function returns true if the calling TList is    *
// *    empty and false if not empty.                              *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool TList<T>::IsEmpty() const
{
    return size == 0;
}

// *****************************************************************
// * Function Name: Clear                                          *
// * Description: Function will continuously remove the front most *
// *    node in the calling TList until empty.                     *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void TList<T>::Clear()
{
    while(!IsEmpty())
    {
        RemoveFront();
    }
}

// *****************************************************************
// * Function Name: GetSize                                        *
// * Description: Returns the size private data member of a TList. *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
int TList<T>::GetSize() const
{
    return size;
}

// *****************************************************************
// * Function Name: InsertFront                                    *
// * Description: Inserts a new node containing passed in data into*
// *    the front of the calling list and increases it's size.     *
// * Parameter Description: Takes in a T data type called d which  *
// *    is the data to be inserted into the front of the list.     *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void TList<T>::InsertFront(const T& d)
{
    Node<T> *node;
    node = new Node<T>(d);
    if(IsEmpty())
    {
        last = node;
    } else {
        node->next = first;
        first->prev = node;
    }
    first = node;
    size++;
}

// *****************************************************************
// * Function Name: InsertBack                                     *
// * Description: Inserts a new node containing passed in data into*
// *    the back of the calling TList and increases it's size.     *
// * Parameter Description: Takes in a T data type called d which  *
// *    is the data to be inserted into the back of the calling    *
// *    TList.                                                     *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void TList<T>::InsertBack(const T& d)
{
    Node<T> *node;
    node = new Node<T>(d);
    if(IsEmpty())
    {
        first = node;
    } else {
        node->prev = last;
        last->next = node;
    }
    last = node;
    size++;
}

// *****************************************************************
// * Function Name: RemoveFront                                    *
// * Description: Function frees up the memory of the first most   *
// *    node in the calling TList.                                 *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void TList<T>::RemoveFront()
{
    if(!IsEmpty())
    {
        Node<T> *node = first;
        if(first == last)
        {
            first = last = nullptr;
        } else {
            first = first->next;
            first->prev = nullptr;
        }
        delete node;
        size--;
    }
}

// *****************************************************************
// * Function Name: RemoveBack                                     *
// * Description: Function frees up the memory of the last most    *
// *    node in the calling TList.                                 *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void TList<T>::RemoveBack()
{
    if(!IsEmpty())
    {
        Node<T> *node = last;
        if(first == last)
        {
            first = last = nullptr;
        } else {
            last = last->prev;
            last->next = nullptr;
        }
        delete node;
        size--;
    }
}
// *****************************************************************
// * Function Name: GetFirst                                       *
// * Description: Function returns the data stored in the first    *
// *    node of the calling TList. If the list is empty, returns   *
// *    the dummy object.                                          *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
T& TList<T>::GetFirst() const
{
    if(IsEmpty())
    {
        return dummy;
    } else {
        return first->data;
    }
}

// *****************************************************************
// * Function Name: GetLast                                        *
// * Description: Function returns the data stored in the Last     *
// *    node of the calling TList. If the list is empty, returns   *
// *    the dummy object.                                          *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
T& TList<T>::GetLast() const
{
    if(IsEmpty())
    {
        return dummy;
    } else {
        return last->data;
    }
}

// *****************************************************************
// * Function Name: GetIterator                                    *
// * Description: Function returns an iterator that points to the  *
// *    first node in the calling TList. If the list is empty,     *
// *    function returns a default iterator.                       *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TListIterator<T> TList<T>::GetIterator() const
{
    TListIterator<T> it;
    if(!IsEmpty())
    {
        it.ptr = first;
    }
    return it;
}

// *****************************************************************
// * Function Name: GetIteratorEnd                                 *
// * Description: Function returns an iterator that points to the  *
// *    last node in the calling TList. If the list is empty,      *
// *    function returns a default iterator.                       *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TListIterator<T> TList<T>::GetIteratorEnd() const
{
    TListIterator<T> it;
    if(!IsEmpty())
    {
        it.ptr = last;
    }
    return it;
}

// *****************************************************************
// * Function Name: Insert                                         *
// * Description: Inserts a node containing user passed in data    *
// *    into the calling TList at a user defined position in the   *
// *    TList.                                                     *
// * Parameter Description: Takes in an iterator called pos used   *
// *    to point to a position to insert a new node. Takes in a    *
// *    T data type called d used to define the data that will be  *
// *    stored in the TList at the aforementioned position.        *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void TList<T>::Insert(TListIterator<T> pos, const T& d)
{
    if(pos.ptr == nullptr || IsEmpty())
    {
        InsertBack(d);
    }
    else if(pos.ptr == first)
    {
        InsertFront(d);
    }
    else{
        Node<T> *node;
        node = new Node<T>(d);
        node->prev = pos.ptr->prev;
        node->next = pos.ptr;
        node->prev->next = node;
        node->next->prev = node;
        size++;
    }
}

// *****************************************************************
// * Function Name: Remove                                         *
// * Description: Removes a node pointed to by a passed in         *
// *    iterator.                                                  *
// * Parameter Description: Takes in an iterator called pos. Used  *
// *    to get the position of the node to be removed from the     *
// *    TList.                                                     *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TListIterator<T> TList<T>::Remove(TListIterator<T> pos)
{
    if(!IsEmpty())
    {
        Node<T> *node = pos.ptr->next;
        if(pos.ptr == first)
        {
            RemoveFront();
        } else if(pos.ptr == last)
        {
            RemoveBack();
            node = last;
        } else {
            pos.ptr->prev->next = pos.ptr->next;
            pos.ptr->next->prev = pos.ptr->prev;
            delete pos.ptr;
            size--;
        }
        pos.ptr = node;
    } else {
        return TListIterator<T>();
    }
    return pos;
}

// *****************************************************************
// * Function Name: Print                                          *
// * Description: Displays the data stored in each node of the     *
// *    calling TList. Each node can be separated by a passed in   *
// *    deliminator.                                               *
// * Parameter Description: Takes in an ostream called os used to  *
// *    print the list to the output stream. Takes in a char called*
// *    delim used to separate the data output between nodes.      *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
void TList<T>::Print(std::ostream& os, char delim) const
{
    Node<T> *node = first;
    while(node != nullptr)
    {
        os << node->data << delim;
        node = node->next;
    }
}

// *****************************************************************
// * Function Name: + operator overload                            *
// * Description: Concatenates to list by creating a new list,     *
// *    copying the first list into the new list, and then adding  *
// *    each node from the second list to the back of the new list.*
// * Parameter Description: Takes in 2 Tlist called t1 and t2.     *
// *    The 2 TList are used to create a new TList containing nodes*
// *    from both TList.                                           *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TList<T> operator+(const TList<T>& t1, const TList<T>& t2)
{
    TList<T> temp(t1);
    if(!t2.IsEmpty())
    {
        TListIterator<T> itr = t2.GetIterator();
        while (itr.HasNext())
        {
            temp.InsertBack(itr.GetData());
            itr.Next();
        }
        temp.InsertBack(itr.GetData());
    }
    return temp;
}

// ***************************************************************************
// * Name: TListIterator ( tlist.hpp filename )                              *
// * Description: Implementation of an iterator for a doubly linked list.    *
// *    Implementation can create a new iterator, check if the current node  *
// *    pointed to by the iterator has a next and previous node, move the    *
// *    iterator to point to the next and previous node, and return the data *
// *    stored in the code pointed to by the iterator.                       *
// *                                                                         *
// * Author: William Ryan Miller                                             *
// * Date: 04/09/2020                                                        *
// ***************************************************************************
// *****************************************************************
// * Function Name: TListIterator                                  *
// * Description: Default constructor of type TListIterator.       *
// *    Creates an empty TListIterator.                            *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TListIterator<T>::TListIterator()
{
    ptr = nullptr;
}

// *****************************************************************
// * Function Name: HasNext                                        *
// * Description: Function returns true if the calling iterator    *
// *    points to a node that has another node directly after.     *
// *    Function returns false if otherwise.                       *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool TListIterator<T>::HasNext() const
{
    if(ptr != nullptr)
    {
        return ptr->next != nullptr;
    } else {
        return false;
    }
}

// *****************************************************************
// * Function Name: HasPrevious                                    *
// * Description: Function returns true if the calling iterator    *
// *    points to a node that has another node directly before.    *
// *    Function returns false if otherwise.                       *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
bool TListIterator<T>::HasPrevious() const
{
    if(ptr != nullptr)
    {
        return ptr->prev != nullptr;
    } else {
        return false;
    }
}

// *****************************************************************
// * Function Name: Next                                           *
// * Description: Function returns an iterator that points to the  *
// *    the next node after the node pointed to by the calling     *
// *    iterator if it exist.                                      *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TListIterator<T> TListIterator<T>::Next()
{
    if(HasNext())
    {
        ptr = ptr->next;
    }
    return *this;
}

// *****************************************************************
// * Function Name: Previous                                       *
// * Description: Function returns an iterator that points to the  *
// *    the previous node before the node pointed to by the calling*
// *    iterator if it exist.                                      *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
TListIterator<T> TListIterator<T>::Previous()
{
    if(HasPrevious())
    {
        ptr = ptr->prev;
    }
    return *this;
}

// *****************************************************************
// * Function Name: GetData                                        *
// * Description: Function returns the data stored in the node     *
// *    the calling iterator is currently pointing to.             *
// * Parameter Description: N/A                                    *
// * Date: 09/08/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template <typename T>
T& TListIterator<T>::GetData() const
{
    if (ptr != nullptr)
    {
        return ptr->data;
    } else {
        return TList<T>::dummy;
    }
}
#endif //TLIST_HPP

