#ifndef UNTITLED28_BET_H
#define UNTITLED28_BET_H
#include <string>
#include <utility>

// ***************************************************************************
// * Name: bet ( bet.h filename )                                            *
// * Description: Interface of a binary expression tree. A binary            *
// *    expression tree can be created, the infix notation can be printed,   *
// *    the postfix expression can be printed, the size can be returned, the *
// *    number of leaf nodes can be returned, and it can be emptied.         *
// * Author: William Ryan Miller                                             *
// * References: Textbook: Data Structures and Algorithm Analysis            *
// *    in C++ fourth edition                                                *
// * Date: 10/26/2020                                                        *
// ***************************************************************************
using namespace std;

class BET{
public:
    BET();                                          //Default constructor
    BET(const string& postfix);                     //Constructor of type BET
    BET(const BET&);                                //Copy constructor
    ~BET();                                         //Destructor
    bool buildFromPostfix(const string& postfix);   //Build a tree from postfix string
    const BET & operator=(const BET &);             //Assignment operator overload
    void printInfixExpression();                    //Prints a tree by inorder traversal
    void printPostfixExpression();                  //Prints a tree by post traversal
    size_t size();                                  //Returns the size of a tree
    size_t leaf_nodes();                            //Returns the number of leaf nodes
    bool empty();                                   //Returns true if tree is empty
private:
    struct BinaryNode{
        string element;                      //Data stored in a node
        BinaryNode *leftchild;               //Pointer to a left child
        BinaryNode *rightchild;              //Pointer to a right child

        BinaryNode(const string &data = "", BinaryNode *left = nullptr, BinaryNode *right = nullptr)
                : element{data}, leftchild{left}, rightchild{right} {}
        BinaryNode(string && data, BinaryNode *left = nullptr, BinaryNode *right = nullptr)
                : element{std::move(data)}, leftchild{left}, rightchild{right} {}
    };
    void printInfixExpression(BinaryNode *n);       //Prints inorder traversal recursively.
    void makeEmpty(BinaryNode* &t);                 //Deletes nodes in a tree recursively.
    BinaryNode * clone(BinaryNode *t);              //Clones a tree recursively.
    void printPostfixExpression(BinaryNode *n);     //Prints a postorder traversal recursively.
    size_t size(BinaryNode *t);                     //Calculates the size of a tree recursively.
    size_t leaf_nodes(BinaryNode *t);               //Calculates the num of leaf nodes recursively.
    int precedence(const string &data) const;             //Gets the precedence of a node.
    BinaryNode *root;                               //Holds the root node of a tree.
};

#endif //UNTITLED28_BET_H

