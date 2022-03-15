#include <iostream>
#include <string>
#include "tlist.h"

using namespace std;

// ***************************************************************************
// * Name: mydriver ( mydriver.cpp filename )                                *
// * Description: mydriver.cpp will execute a ver thorough test of all       *
// *    functions of the TList and TListIterator class by calling various    *
// *    functions and displaying the results to the user.                    *
// *                                                                         *
// * Author: William Ryan Miller                                             *
// * Date: 09/08/2020                                                        *
// ***************************************************************************
// *****************************************************************
// * Function Name: PrintList                                      *
// * Description: Helper function that displays the contents       *
// *    and size of a list. Borrowed from the driver.cpp class     *
// *    written by Dr. David A Gaitros. Used to simplify output    *
// *    when performing test on the implementation of TList and    *
// *    TListIterator.                                             *
// * Parameter Description: Takes in a TList called L and a string *
// *    called label. The label is used to give a name to the      *
// *    passed in list. Both the name and list are displayed to the*
// *    user on function call.                                     *
// * Date: Unknown                                                 *
// * Author: Dr. David A Gaitros                                   *
// * References: From the assignment1 driver.cpp                   *
// *****************************************************************
template <typename T>
void PrintList(const TList<T>& L, string label)
{
    cout << label << " size is: " << L.GetSize() << "\n"
         << label << " = ";
    L.Print(cout);
    cout << "\n\n";
}

int main()
{
    TList<int> intlist;
    TList<string> stringlist;

    cout << "Populating int and string list using InsertBack()..." << endl;
    for (int i = 0; i < 3; i++)
    {
        stringlist.InsertBack("MyString" + to_string(i));
        intlist.InsertBack(i);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Testing InsertFront(), InsertBack(), RemoveFront(), and RemoveBack() once..." << endl;
    cout << "Testing InsertFront..." << endl;
    intlist.InsertFront(3);
    stringlist.InsertFront("MyString3");
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Testing RemoveFront..." << endl;
    intlist.RemoveFront();
    stringlist.RemoveFront();
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Testing InsertBack..." << endl;
    intlist.InsertBack(3);
    stringlist.InsertBack("MyString3");
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Testing RemoveBack..." << endl;
    intlist.RemoveBack();
    stringlist.RemoveBack();
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");
    cout << "End of initial test of 4 functions..." << endl;

    cout << "Testing interspaced semi-random calls to the same 4 functions..." << endl;
    cout << "Adding 3 more nodes to the front of each list..." << endl;
    for (int i = 3; i < 6; i++)
    {
        stringlist.InsertFront("MyString" + to_string(i));
        intlist.InsertFront(i);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Removing 3 nodes from the back of each list..." << endl;
    for (int i = 0; i < 3; i++)
    {
        intlist.RemoveBack();
        stringlist.RemoveBack();
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Removing 2 nodes from the front of each list..." << endl;
    intlist.RemoveFront();
    stringlist.RemoveFront();
    intlist.RemoveFront();
    stringlist.RemoveFront();
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Inserting 3 nodes to the back of each list..." << endl;
    for (int i = 0; i < 3; i++)
    {
        stringlist.InsertBack("MyString" + to_string(i));
        intlist.InsertBack(i);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout <<"Inserting 3 nodes to the front and removing 3 nodes from the back..." << endl;
    for (int i = 0; i < 3; i++)
    {
        stringlist.InsertFront("MyString" + to_string(i));
        intlist.InsertFront(i);
        intlist.RemoveBack();
        stringlist.RemoveBack();
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout <<"Inserting 3 nodes to the back and removing 3 nodes from the front..." << endl;
    for (int i = 0; i < 3; i++)
    {
        stringlist.InsertBack("MyString" + to_string(i));
        intlist.InsertBack(i);
        intlist.RemoveFront();
        stringlist.RemoveFront();
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Inserting 2 nodes to the front of each list..." << endl;
    intlist.InsertFront(4);
    stringlist.InsertFront("MyString4");
    intlist.InsertFront(5);
    stringlist.InsertFront("MyString5");
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout <<"Removing 3 nodes from the front and 3 nodes from the back..." << endl;
    cout << "This should leave both list empty." << endl;
    for (int i = 0; i < 3; i++)
    {
        stringlist.RemoveBack();
        intlist.RemoveBack();
        intlist.RemoveFront();
        stringlist.RemoveFront();
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");
    cout << "Calling IsEmpty() to verify..." << endl;
    cout << "intlist IsEmpty should return 1: " << intlist.IsEmpty() << endl;
    cout << "stringlist IsEmpty should return 1: " << stringlist.IsEmpty() << endl;
    cout << endl << endl;

    cout << "Inserting 1 node to the front..." << endl;
    intlist.InsertFront(3);
    stringlist.InsertFront("MyString3");
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");
    cout << "End of semi-randomized interspaced test of 4 functions..." << endl << endl;

    cout << "Beginning iterator test..." << endl;
    TListIterator<int> intitr = intlist.GetIterator();
    TListIterator<string> stringitr = stringlist.GetIterator();

    cout << "Inserting 3 nodes into each list at the iterators position." << endl;
    for(int i = 0; i < 3; i++)
    {
        intlist.Insert(intitr, i);
        stringlist.Insert(stringitr, "MyString" + to_string(i));
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Removing 2 nodes off of each list." << endl;
    intitr = intlist.Remove(intitr);
    intitr = intlist.Remove(intitr);
    stringitr = stringlist.Remove(stringitr);
    stringitr = stringlist.Remove(stringitr);
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Moving iterators back one position." << endl;
    intitr.Previous();
    stringitr.Previous();
    cout << "Adding 2 nodes to iterators current position." << endl;
    intlist.Insert(intitr, 2);
    intlist.Insert(intitr, 3);
    stringlist.Insert(stringitr, "MyString2");
    stringlist.Insert(stringitr, "MyString3");
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Moving iterators forward 2 positions." << endl;
    intitr.Next();
    stringitr.Next();
    intitr.Next();
    stringitr.Next();
    cout << "Adding 2 nodes to iterators current position." << endl;
    intlist.Insert(intitr, 4);
    intlist.Insert(intitr, 5);
    stringlist.Insert(stringitr, "MyString4");
    stringlist.Insert(stringitr, "MyString5");
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");


    cout << "Removing 3 nodes from each list at the iterators position." << endl;
    for(int i = 0; i < 3; i++)
    {
        intitr = intlist.Remove(intitr);
        stringitr = stringlist.Remove(stringitr);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Moving iterators position back 1 node." << endl;
    intitr.Previous();
    stringitr.Previous();
    cout << "Adding 2 nodes to iterators current position." << endl;
    for(int i = 0; i < 2; i++)
    {
        intlist.Insert(intitr, i);
        stringlist.Insert(stringitr, "MyString" + to_string(i));
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Moving iterators position back 1 node." << endl;
    intitr.Previous();
    stringitr.Previous();
    cout << "Removing 3 nodes from each list at the iterators position." << endl;
    for(int i = 0; i < 3; i++)
    {
        intitr = intlist.Remove(intitr);
        stringitr = stringlist.Remove(stringitr);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Moving iterators position back 1 node." << endl;
    intitr.Previous();
    stringitr.Previous();
    cout << "Adding 1 node to iterators current position." << endl;
    intlist.Insert(intitr, 1);
    stringlist.Insert(stringitr, "MyString1");
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Moving iterators position forward 1 node." << endl;
    intitr.Next();
    stringitr.Next();
    cout << "Removing 2 nodes from each list at the iterators position." << endl;
    for(int i = 0; i < 2; i++)
    {
        intitr = intlist.Remove(intitr);
        stringitr = stringlist.Remove(stringitr);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");
    cout << "End of Insert() and Remove() iterator test." << endl;
    cout << "Testing remaining functions: HasNext() and HasPrevious()" << endl;
    cout << "Testing intitr HasNext(). Should return 0: " << intitr.HasNext() << endl;
    cout << "Testing stringitr HasNext(). Should return 0: " << stringitr.HasNext() << endl;
    cout << "Testing intitr HasPrevious(). Should return 0: " << intitr.HasPrevious() << endl;
    cout << "Testing stringitr HasPrevious(). Should return 0: " << stringitr.HasPrevious() << endl;
    cout << "End of iterator function test." << endl;

    cout << "Filling the list before traveral w/ iterators test." << endl;
    for(int i = 0; i < 5; i++)
    {
        intlist.Insert(intitr, i);
        stringlist.Insert(stringitr, "MyString" + to_string(i));
    }
    cout << "List now contain data: " << endl;
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    intitr = intlist.GetIterator();
    cout << "Using iterator to traverse the integer list front to back..." << endl;
    for(int i = 0; i < intlist.GetSize(); i++)
    {
        cout << intitr.GetData() << " ";
        intitr.Next();
    }

    stringitr = stringlist.GetIterator();
    cout << endl << endl << "Using iterator to traverse the string list front to back..." << endl;
    for(int i = 0; i < stringlist.GetSize(); i++)
    {
        cout << stringitr.GetData() << " ";
        stringitr.Next();
    }

    intitr = intlist.GetIteratorEnd();
    cout << endl << endl << "Using iterator to traverse the integer list back to front..." << endl;
    for(int i = 0; i < intlist.GetSize(); i++)
    {
        cout << intitr.GetData() << " ";
        intitr.Previous();
    }

    stringitr = stringlist.GetIteratorEnd();
    cout << endl << endl << "Using iterator to traverse the string list back to front..." << endl;
    for(int i = 0; i < stringlist.GetSize(); i++)
    {
        cout << stringitr.GetData() << " ";
        stringitr.Previous();
    }
    cout << endl << "End of iterator traversal test." << endl << endl;

    cout << "Testing all functions and constructors." << endl;
    cout << "Clearing lists and repopulating with data." << endl;
    intlist.Clear();
    stringlist.Clear();

    for (int i = 0; i < 4; i++)
    {
        stringlist.InsertBack("MyString" + to_string(i));
        intlist.InsertBack(i);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Testing IsEmpty() on intlist. Should return 0: " << intlist.IsEmpty() << endl;
    cout << "Testing IsEmpty() on stringlist. Should return 0: " << stringlist.IsEmpty() << endl;
    cout << "Testing GetSize() on intlist. Should return 4: " << intlist.GetSize() << endl;
    cout << "Testing GetSize() on stringlist. Should return 4: " << stringlist.GetSize() << endl;
    cout << "Testing Clear() on intlist then calling IsEmpty. Should return 1: ";
    intlist.Clear();
    cout << intlist.IsEmpty() << endl;
    cout << "Testing Clear() on stringlist then calling IsEmpty. Should return 1: ";
    stringlist.Clear();
    cout << intlist.IsEmpty() << endl;

    cout << "Repopulating list with data." << endl;
    for (int i = 0; i < 4; i++)
    {
        stringlist.InsertBack("MyString" + to_string(i));
        intlist.InsertBack(i);
    }
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Testing intlist GetFirst(). Should return 0: " << intlist.GetFirst() << endl;
    cout << "Testing stringlist GetFirst(). Should return MyString0: " << stringlist.GetFirst() << endl;
    cout << "Testing intlist GetLast(). Should return 3: " << intlist.GetLast() << endl;
    cout << "Testing stringlist GetLast(). Should return MyString3: " << stringlist.GetLast() << endl;

    cout << "Testing TList constructor." << endl;
    TList<int> intlist2(1, 2);
    TList<string> stringlist2("MyString", 2);
    PrintList(intlist2, "intlist2");
    PrintList(stringlist2, "stringlist2");

    cout << "Testing + operator overload and move assignment operator." << endl;
    intlist = intlist + intlist2;
    stringlist = stringlist + stringlist2;
    PrintList(intlist, "intlist");
    PrintList(stringlist, "stringlist");

    cout << "Testing copy constructor." << endl;
    TList<int> intlist3(intlist);
    TList<string> stringlist3(stringlist);
    PrintList(intlist3, "intlist3");
    PrintList(stringlist3, "stringlist3");

    cout << "Testing copy assignment operator." << endl;
    intlist2 = intlist3;
    stringlist2 = stringlist3;
    PrintList(intlist2, "intlist2");
    PrintList(stringlist2, "stringlist2");

    cout << "Testing move constructor." << endl;
    TList<int> intlist4(move(intlist2));
    TList<string> stringlist4(move(stringlist2));
    PrintList(intlist4, "intlist4");
    PrintList(stringlist4, "stringlist4");
}

