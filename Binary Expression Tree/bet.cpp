#include <sstream>
#include <stack>
#include <iostream>
#include "bet.h"

// ***************************************************************************
// * Name: bet ( bet.cpp filename )                                          *
// * Description: Implementation of a binary expression tree. A binary       *
// *    expression tree can be created, the infix notation can be printed,   *
// *    the postfix expression can be printed, the size can be returned, the *
// *    number of leaf nodes can be returned, and it can be emptied.         *
// * Author: William Ryan Miller                                             *
// * References: Textbook: Data Structures and Algorithm Analysis            *
// *    in C++ fourth edition                                                *
// * Date: 10/26/2020                                                        *
// ***************************************************************************
// *****************************************************************
// * Function Name: BET                                            *
// * Description: Default constructor of type BET. Constructs a    *
// *    default binary expression tree by initializing root to a   *
// *    nullptr.                                                   *
// * Parameter Description: N/A                                    *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
BET::BET() {
    root = nullptr;
}

// *****************************************************************
// * Function Name: BET                                            *
// * Description: Constructor of type BET. Constructs binary       *
// *    expression tree from a postfix expression by initializing  *
// *    the root of a tree and calling buildFromPostFix            *
// * Parameter Description: Takes in a string called postfix.      *
// *    Postfix is the string used to form the binary expression   *
// *    tree.                                                      *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
BET::BET(const string &postfix) {
    root = nullptr;
    buildFromPostfix(postfix);
}

// *****************************************************************
// * Function Name: BET                                            *
// * Description: Copy constructor of type BET. Constructs a       *
// *    binary expression tree from a passed in binary expression  *
// *    tree by initializing the root of a new tree and cloning the*
// *    passed in tree.                                            *
// * Parameter Description: Takes in BET called tree. Tree is the  *
// *    binary expression tree to be copied.                       *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
BET::BET(const BET &tree) {
    root = nullptr;
    root = clone(tree.root);
}

// *****************************************************************
// * Function Name: ~BET                                           *
// * Description: Destructor of type BET. Destructor will call     *
// *    makeEmpty() which will recursively delete every node in a  *
// *    tree.                                                      *
// * Parameter Description: N/A                                    *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
BET::~BET() {
    makeEmpty(root);
}

// *****************************************************************
// * Function Name: buildFromPostfix                               *
// * Description: Function will build a binary expression tree from*
// *    a passed in postfix expression using a stack. Function will*
// *    return true if successful. False if an error occurs.       *
// * Parameter Description: Takes in a string called postfix used  *
// *    as the string to build a binary expression tree from.      *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool BET::buildFromPostfix(const string &postfix) {
    stack<BinaryNode> tree;
    string token;
    stringstream ss(postfix);
    BinaryNode *right;
    BinaryNode *left;
    if(!empty())
    {
        makeEmpty(root);
    }
    while (getline(ss, token, ' '))
    {
        if(!(token == "+" || token == "-" || token == "*" || token == "/"))
        {
            tree.push(BinaryNode(token));
        } else {
            if(tree.size() < 2){
                cout << "Error - Missing operand." << endl;
                return false;
            }
            right = new BinaryNode(tree.top());
            tree.pop();
            left = new BinaryNode(tree.top());
            tree.pop();
            tree.push(BinaryNode(token, left, right));
        }
    }
    if(tree.size() != 1)
    {
        cout << "Error - Operand is missing an operator." << endl;
        return false;
    }
    root = new BinaryNode(tree.top());
    return true;
}

// *****************************************************************
// * Function Name: = operator overload                            *
// * Description: Assignment operator overload of type BET. Deep   *
// *    copies the nodes of a passed in tree into another tree.    *
// * Parameter Description: Takes in a BET tree called rhs. rhs    *
// *    will be copied into the calling tree.                      *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
const BET & BET::operator=(const BET &rhs) {
    if(this != &rhs) {
        if (!this->empty()) {
            this->makeEmpty(root);
        }
        root = clone(rhs.root);
    }
    return *this;
}

// *****************************************************************
// * Function Name: printInfixExpression                           *
// * Description: Function will print a BET in infix notation by   *
// *    calling the private recursive printInfixExpression, passing*
// *    in the root.                                               *
// * Parameter Description: N/A                                    *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void BET::printInfixExpression() {
    printInfixExpression(root);
    cout << endl;
}

// *****************************************************************
// * Function Name: printPostfixExpression                         *
// * Description: Function will print a BET in postfix notation by *
// *    calling the private recursive printPostfixExpression,      *
// *    passing in the root.                                       *
// * Parameter Description: N/A                                    *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void BET::printPostfixExpression() {
    printPostfixExpression(root);
    cout << endl;
}

// *****************************************************************
// * Function Name: size                                           *
// * Description: Returns the size of a calling BET. Function calls*
// *    recursive function size() and passes in the root.          *
// * Parameter Description: N/A                                    *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
size_t BET::size() {
    return this->size(root);
}

// *****************************************************************
// * Function Name: leaf_nodes                                     *
// * Description: Returns the number of leaf nodes in a calling BET*
// *    by calling the recursive leaf_nodes() function and passing *
// *    in the root.                                               *
// * Parameter Description: N/A                                    *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
size_t BET::leaf_nodes() {
    return this->leaf_nodes(root);
}

// *****************************************************************
// * Function Name: empty                                          *
// * Description: Function returns true if there are no nodes in a *
// *    tree. False otherwise.                                     *
// * Parameter Description: N/A                                    *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool BET::empty() {
    return this->size() == 0;
}

// *****************************************************************
// * Function Name: printInfixExpression                           *
// * Description: Function recursively prints a BET by performing  *
// *    an inorder traversal. Function adds parenthesis based on   *
// *    operator precedence and the associative property.          *
// * Parameter Description: Takes in a BinaryNode called n. Used   *
// *    as a starting point for an inorder traversal.              *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void BET::printInfixExpression(BET::BinaryNode *n) {
    if(n != nullptr) {
        if(n->leftchild == nullptr && n->rightchild == nullptr)
        {
            cout << n->element << " ";
        } else {
            if(precedence(n->leftchild->element) < precedence(n->element)) {
                cout << "( ";
            }
            printInfixExpression(n->leftchild);
            if(precedence(n->leftchild->element) < precedence(n->element)) {
                cout << ") ";
            }
            cout << n->element << " ";
            if(precedence(n->rightchild->element) <= precedence(n->element)) {
                cout << "( ";
            }
            printInfixExpression(n->rightchild);
            if(precedence(n->rightchild->element) <= precedence(n->element)) {
                cout << ") ";
            }
        }
    }
}

// *****************************************************************
// * Function Name: precedence                                     *
// * Description: Returns the precedence of a passed in string.    *
// *    multiplication and division have a higher precedence than  *
// *    addition and subtraction.                                  *
// * Parameter Description: Takes in a string called data. Data    *
// *    will be identified and given a precedence.                 *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
int BET::precedence(const string &data) const
{
    if(data == "+" || data == "-")
    {
        return 0;
    }
    if(data == "*" || data == "/")
    {
        return 1;
    }
    else return 2;
}

// *****************************************************************
// * Function Name: makeEmpty                                      *
// * Description: Recursively deletes all nodes of a BET.          *
// * Parameter Description: Takes in a BinaryTree called t used as *
// *    a starting point for recursively deleting nodes.           *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. pg 141                              *
// *****************************************************************
void BET::makeEmpty(BET::BinaryNode *&t) {
    if(t != nullptr)
    {
        makeEmpty(t->leftchild);
        makeEmpty(t->rightchild);
        delete t;
    }
    t = nullptr;
}

// *****************************************************************
// * Function Name: clone                                          *
// * Description: Makes a copy of a BET by recursively creating    *
// *    BinaryNodes.                                               *
// * Parameter Description: Takes in a BinaryNode called t used as *
// *    the starting point for recursion.                          *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. pg 142                              *
// *****************************************************************
BET::BinaryNode *BET::clone(BET::BinaryNode *t) {
    if( t == nullptr)
    {
        return nullptr;
    }
    else return new BinaryNode(t->element, clone(t->leftchild), clone(t->rightchild));
}

// *****************************************************************
// * Function Name: printPostFixExpression                         *
// * Description: Prints the post order traversal of a BET         *
// *    recursively.                                               *
// * Parameter Description: Takes in a BinaryNode called n used    *
// *    as the starting node for traversal.                        *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void BET::printPostfixExpression(BET::BinaryNode *n) {
    if(n != nullptr) {
        printPostfixExpression(n->leftchild);
        printPostfixExpression(n->rightchild);
        std::cout << n->element << " ";
    }
}

// *****************************************************************
// * Function Name: size                                           *
// * Description: Recursively calculates the size of a BET by      *
// *    adding up and returning the number of nodes.               *
// * Parameter Description: Takes in a BinaryNode called t used as *
// *    the starting node to be recursively traversed.             *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
size_t BET::size(BET::BinaryNode *t) {
    if(t == nullptr)
    {
        return 0;
    } else {
        return size(t->leftchild) + 1 + size(t->rightchild);
    }
}

// *****************************************************************
// * Function Name: leaf_nodes                                     *
// * Description: Returns the number of a leaf nodes in a BET by   *
// *    recursively traversing a BET and adding up the number      *
// *    of leaf nodes.                                             *
// * Parameter Description: Takes in a BinaryNode called t used as *
// *    the starting node to be recursively traversed.             *
// * Date: 10/26/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
size_t BET::leaf_nodes(BET::BinaryNode *t) {
    if(t == nullptr)
    {
        return 0;
    }
    if(t->leftchild == nullptr && t->rightchild == nullptr && t != root)
    {
        return 1;
    } else {
        return leaf_nodes(t->leftchild) + leaf_nodes(t->rightchild);
    }
}

