#ifndef DL_LIST_H
#define DL_LIST_H
#include <iostream>
#include <initializer_list>

// ***************************************************************************
// * Name: Stack ( stack.h filename )                                        *
// * Description: Implementation of a stack via a templated doubly linked    *
// *    list. Contains a const iterator. The stack can be pushed, popped,    *
// *    return the top element, return the size, and return if the stack is  *
// *    empty. Contains copy, move, and default constructors.                *
// * Author: William Ryan Miller                                             *
// * References: Textbook: Data Structures and Algorithm Analysis            *
// *    in C++ fourth edition and the .h file provided by Dr. Gaitros        *
// *    in Assignment 2.                                                     *
// * Date: 10/02/2020                                                        *
// ***************************************************************************

namespace cop4530 {

    template <typename T>
    class Stack {
    private:
        struct Node {
            T data;          //Data stored in node
            Node *prev;      //Pointer to previous node
            Node *next;      //Pointer to next node

            Node(const T & d = T{}, Node *p = nullptr, Node *n = nullptr)
                    : data{d}, prev{p}, next{n} {}
            Node(T && d, Node *p = nullptr, Node *n = nullptr)
                    : data{std::move(d)}, prev{p}, next{n} {}
        };

    public:
        class const_iterator {
        public:
            const_iterator();                    //Default constructor
            const T & operator*() const;         //*Operator overload
            const_iterator & operator++();       //Postfix increment operator overload
            const_iterator operator++(int);      //Prefix increment operator overload
            const_iterator & operator--();       //Postfix decrement operator overload
            const_iterator operator--(int);      //Prefix decrement operator overload
            bool operator==(const const_iterator &rhs) const; //Comparision operator overload
            bool operator!=(const const_iterator &rhs) const; // != operator overload
            bool HasNext() const;                //Is there a next node
            bool HasPrevious() const;            //Is there a previous node

        protected:
            Node *current;                       //Pointer to current node
            T & retrieve() const;                //Get data pointed to by current
            const_iterator(Node *p);             //Constructor
            friend class Stack<T>;
        };

    public:
        Stack();                                 //Default constructor
        ~Stack();                                //Destructor
        Stack(const Stack &rhs);                 //Copy constructor
        Stack(Stack && rhs);                     //Move constructor
        Stack& operator=(const Stack &rhs);      //Copy assignment operator overload
        Stack & operator=(Stack && rhs);         //Move assignment operator overload
        bool empty() const;                      //Is the stack empty
        void clear();                            //Delete the nodes in the stack
        void push(const T& x);                   //Push a new node into the stack
        void push(T && x);                       //Move a new node into the stack
        void pop();                              //Remove a node off the top of the stack
        T& top();                                //Return the top element on the stack
        const T& top() const;                    //Return the top element on the stack
        int size() const;                        //Return the size of the stack
        void print(std::ostream& os, char ofc = ' ') const; //Print the stack
        const_iterator begin() const;            //iterator that points to the head

    private:
        int theSize;                             //Holds the size
        Node *head;                              //Pointer to first node
        Node *tail;                              //Sentinel to last node
        void init();                             //Create a stack
    };

    //Comparision operator overload
    template <typename T>
    bool operator==(const Stack<T> & lhs, const Stack<T> &rhs);
    // != operator overload
    template <typename T>
    bool operator!=(const Stack<T> & lhs, const Stack<T> &rhs);
    //<= operator overload
    template<typename T>
    bool operator<=(const Stack<T>& s1, const Stack<T>& s2);
    //Output operator overload
    template <typename T>
    std::ostream & operator<<(std::ostream &os, const Stack<T> &l);

#include "stack.hpp"

} // end of namespace 4530

#endif

