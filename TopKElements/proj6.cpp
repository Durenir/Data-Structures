// ***************************************************************************
// * Name: proj6( proj6.cpp filename )                                       *
// * Description: Driver for helper class TopKElements. Driver creates an    *
// *    instance of TopKElements with K equal to 10. Gets input from the     *
// *    console, stores input line in a string called input, and passes the  *
// *    input to buildMaps. Once all input has been processed through        *
// *    buildMaps, printTopKData is called to output the top 10 elements that*
// *    has been processed by TopKElements.                                  *
// * Author: William Ryan Miller                                             *
// * References: N/A                                                         *
// * Date: 11/21/2020                                                        *
// ***************************************************************************

#include <iostream>
#include "topkelements.h"

using namespace std;

int main(){
    TopKElements topk(10);
    string input;
    while(getline(cin, input)) {
        topk.buildMaps(input);
    }
    topk.printTopKData();
}
