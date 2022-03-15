#include <iostream>
#include <string>
#include <sstream>
#include "stack.h"

// ***************************************************************************
// * Name: main ( in2post.cpp filename )                                     *
// * Description: in2post.cpp can take in an input expression, evaluate      *
// *    if it is a valid expression, extract and process each token within   *
// *    the expression, and convert the expression to postfix notation. If   *
// *    the post fix expression is able to be evaluated, evaluation is       *
// *    displayed to user. Routine will run until user enters End or end.    *
// * Author: William Ryan Miller                                             *
// * References: Ideas for helper functions provided by Dr. Gaitros in the   *
// *    assignment lectures.                                                 *
// * Date: 10/02/2020                                                        *
// ***************************************************************************

using namespace std;
using namespace cop4530;
enum TOKENS {
    unknown, integer, decimal, id,
    lparen, rparen, addition, subtraction, multiplication,
    division
};

TOKENS WhatIsIt(const string &token);
bool IsInteger(const string &instr);
bool IsFloat(const string &instr);
bool IsIdentifier(const string &instr);
float StringToFloat(const string &instr);
bool IsOperator(const string &token);
int StringToInt(const string &inst);
int Precedence(const string &instr);
bool CanBeEvaluated(const string &instr);
string EvaluationOfExpression(const string &outputstring);
string GetInFixNotation(const string &expression);

// *****************************************************************
// * Function Name: main                                           *
// * Description: Main routine will prompt the user for an input   *
// *    expression, convert the expression from infix to postfix,  *
// *    and if possible, evaluate the postfix expression. Routine  *
// *    will prompt for new input until user enters End.           *
// * Parameter Description: N/A                                    *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
int main()
{
    string inputexpression;
    string outputexpression;
    string evaluation;
    cout << "Enter in an expression ('End' to quit): " << endl;
    getline(cin, inputexpression);
    while (inputexpression != "End" && inputexpression != "end")
    {
        cout << "The InFix Notation is: " << inputexpression << endl;
        outputexpression = GetInFixNotation(inputexpression);
        cout << "The PostFix Notation is: " << outputexpression << endl;
        if (CanBeEvaluated(outputexpression))
        {
            evaluation = EvaluationOfExpression(outputexpression);
            cout << "Results are: " << evaluation << endl << endl;
        } else {
            cout << "Cannot evaluate " << outputexpression << endl << endl;
        }
        cout << "Enter in an expression ('End' to quit): " << endl;
        getline(cin, inputexpression);
    }
}

// *****************************************************************
// * Function Name: EvaluationOfExpression                         *
// * Description: Function will process a postfix expression       *
// *    identifying what each token in the expression is and       *
// *    performing operations if an expression can be evaluated.   *
// * Parameter Description: Takes in a string called outputstring. *
// *    Outputstring holds the postfix expression to be evaluated. *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
string EvaluationOfExpression(const string &outputstring)
{
    Stack<string> operands;
    string token;
    stringstream ss(outputstring);
    TOKENS identity;
    while (getline(ss, token, ' '))
    {
        identity = WhatIsIt(token);
        if (identity == integer || identity == decimal)
        {
            operands.push(token);
        } else if (IsOperator(token))
        {
            if (operands.size() < 2)
            {
                return "Error - Incorrect number of operands or operations.";
            } else {
                if (WhatIsIt(operands.top()) == integer)
                {
                    int a = StringToInt(operands.top());
                    operands.pop();
                    int b = StringToInt(operands.top());
                    operands.pop();
                    if (identity == addition)
                    {
                        operands.push(to_string(b + a));
                    } else if (identity == subtraction)
                    {
                        operands.push(to_string(b - a));
                    } else if (identity == multiplication)
                    {
                        operands.push(to_string(b * a));
                    } else if (identity == division)
                    {
                        operands.push(to_string(b / a));
                    }
                } else {
                    float a = StringToFloat(operands.top());
                    operands.pop();
                    float b = StringToFloat(operands.top());
                    operands.pop();
                    if (identity == addition)
                    {
                        operands.push(to_string(b + a));
                    } else if (identity == subtraction)
                    {
                        operands.push(to_string(b - a));
                    } else if (identity == multiplication)
                    {
                        operands.push(to_string(b * a));
                    } else if (identity == division)
                    {
                        operands.push(to_string(b / a));
                    }
                }
            }
        }
    }
    if (operands.size() > 1)
    {
        return "Error - Too few operators.";
    } else if (operands.empty())
    {
        return to_string(0);
    } else {
        return operands.top();
    }
}

// *****************************************************************
// * Function Name: CanBeEvaluated                                 *
// * Description: Function will determine if a passed in string can*
// *    be evaluated by determining if it contains any identifiers *
// * Parameter Description: Takes in a string called instr. Used   *
// *    to determine if instr contains any identifiers (alphabetic *
// *    letters).                                                  *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
bool CanBeEvaluated(const string &instr)
{
    string token;
    stringstream ss(instr);
    while (getline(ss, token, ' '))
    {
        if (WhatIsIt(token) == id)
        {
            return false;
        }
    }
    return true;
}

// *****************************************************************
// * Function Name: GetInFixNotation                               *
// * Description: Function will parse an input InFix expression    *
// *    and convert it to a PostFix expression if possible.        *
// *    contains error checking for mismatched parentheses,        *
// *    operators, and operands.                                   *
// * Parameter Description: Takes in a string called expression.   *
// *    expression holds the InFix expression to be converted to   *
// *    PostFix.                                                   *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
string GetInFixNotation(const string &expression)
{
    Stack<string> results;
    string token, postfix;
    string previous = " ";
    stringstream ss(expression);
    TOKENS identity;
    while (getline(ss, token, ' '))
    {
        identity = WhatIsIt(token);
        if (identity == integer || identity == decimal || identity == id)
        {
            postfix += token + " ";
        } else if (identity == lparen)
        {
            results.push(token);
        } else if (IsOperator(token))
        {
            if(WhatIsIt(previous) != integer && WhatIsIt(previous) != decimal &&
                WhatIsIt(previous) != id && WhatIsIt(previous) != rparen)
            {
                postfix = "Error - To few operands.";
                return postfix;
            }
            while (!results.empty() && WhatIsIt(results.top()) != lparen &&
                   Precedence(token) <= Precedence(results.top()))
            {
                postfix += results.top() + " ";
                results.pop();
            }
            results.push(token);
        } else if (identity == rparen)
        {
            if (IsOperator(previous))
            {
                postfix = "Error - Unbalanced Parenthesis.";
                return postfix;
            }
            while (WhatIsIt(results.top()) != lparen)
            {
                postfix += results.top() + " ";
                results.pop();
                if (results.empty())
                {
                    postfix = "Error - Unbalanced Parenthesis.";
                    return postfix;
                }
            }
            results.pop();
        }
        previous = token;
    }
    if (WhatIsIt(previous) == lparen || IsOperator(previous))
    {
        postfix = "Error - Unbalanced Parenthesis or missing operand.";
        return postfix;
    } else {
        while (!results.empty())
        {
            if (WhatIsIt(results.top()) == lparen)
            {
                postfix = "Error - Unbalanced Parenthesis.";
                return postfix;
            }
            postfix += results.top() + " ";
            results.pop();
        }
    }
    return postfix;
}

// *****************************************************************
// * Function Name: Precedence                                     *
// * Description: Function uses a switch to return a determine and *
// *    return a precedence as an int. Precedence is determined    *
// *    by what is contained in the passed in string.              *
// * Parameter Description: Takes in a string called instr. Used   *
// *    to determine what the precedence is based on what is       *
// *    what is contained within the string.                       *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
int Precedence(const string &instr)
{
    int precedence = 0;
    switch (WhatIsIt(instr)) {
        case unknown:
        case integer:
        case decimal:
        case id:
            precedence = 0;
            break;
        case lparen:
            precedence = 1;
            break;
        case rparen:
            precedence = 4;
            break;
        case addition:
        case subtraction:
            precedence = 2;
            break;
        case multiplication:
        case division:
            precedence = 3;
            break;
        default:
            break;
    }
    return precedence;
}

// *****************************************************************
// * Function Name: WhatIsIt                                       *
// * Description: Function takes in a string token and determines  *
// *    what the token is through a series of function calls and   *
// *    comparisons.                                               *
// * Parameter Description: Takes in a string called token. Used   *
// *    to hold the value to be identified.                        *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
TOKENS WhatIsIt(const string &token)
{
    if (IsInteger(token))
    {
        return integer;
    } else if (IsFloat(token))
    {
        return decimal;
    } else if (IsIdentifier(token))
    {
        return id;
    } else if (token == "+")
    {
        return addition;
    } else if (token == "-")
    {
        return subtraction;
    } else if (token == "*")
    {
        return multiplication;
    } else if (token == "/")
    {
        return division;
    } else if (token == "(")
    {
        return lparen;
    } else if (token == ")")
    {
        return rparen;
    } else {
        return unknown;
    }
}

// *****************************************************************
// * Function Name: IsOperator                                     *
// * Description: Function will determine if a passed in string    *
// *    is a valid mathematical operator.                          *
// * Parameter Description: Takes in a string called token. Token  *
// *    will be evaluated to determine if it is a mathematical     *
// *    operator.                                                  *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
bool IsOperator(const string &token)
{
    for (char i : token)
    {
        if (i == '+' || i == '-' ||
            i == '*' || i == '/')
        {
            return true;
        }
    }
    return false;
}

// *****************************************************************
// * Function Name: StringToInt                                    *
// * Description: Function converts a string to an int.            *
// * Parameter Description: Takes in a string called instr. Instr  *
// *    will be converted from a string to an int.                 *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
int StringToInt(const string &instr)
{
    return stoi(instr);
}

// *****************************************************************
// * Function Name: StringToFloat                                  *
// * Description: Function converts a string to a float            *
// * Parameter Description: Takes in a string called instr. Instr  *
// *    will be converted from a string to an float.               *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
float StringToFloat(const string &instr)
{
    return stof(instr);
}

// *****************************************************************
// * Function Name: IsIdentifier                                   *
// * Description: Function determines if a passed in string is an  *
// *    identifier by checking if the string contains an alphabetic*
// *    letter or an underscore.                                   *
// * Parameter Description: Takes in a string called instr. Instr  *
// *    will be checked to see if it is an identifier.             *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
bool IsIdentifier(const string &instr)
{
    for (char i : instr)
    {
        if (isalpha(i) || i == '_')
        {
            return true;
        }
    }
    return false;
}

// *****************************************************************
// * Function Name: IsFloat                                        *
// * Description: Function will determine if a passed in string is *
// *    a float by determining if the string contains 1 decimal. If*
// *    it contains more than or fewer than 1 decimal, it is not a *
// *    float.                                                     *
// * Parameter Description: Takes in a string called instr. Instr  *
// *    will be checked to see if it is a float.                   *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
bool IsFloat(const string &instr)
{
    bool hasdecimal = false;
    for (char i : instr)
    {
        if (!isdigit(i) && i != '.')
        {
            return false;
        }
        if (i == '.')
        {
            if (hasdecimal)
            {
                return false;
            }
            hasdecimal = true;
        }
    }
    return hasdecimal;
}

// *****************************************************************
// * Function Name: IsInteger                                      *
// * Description: Function will determine if a passed in string is *
// *    an integer by determining if the string only contains      *
// *    digits.                                                    *
// * Parameter Description: Takes in a string called instr. Instr  *
// *    will be checked to see if it is an integer.                *
// * Date: 10/02/2020                                              *
// * Author: William Miller                                        *
// * References: N/A                                               *
// *****************************************************************
bool IsInteger(const string &instr)
{
    for (char i : instr)
    {
        if (!isdigit(i))
        {
            return false;
        }
    }
    return true;
}
