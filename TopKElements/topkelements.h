// ***************************************************************************
// * Name: TopKElements ( topkelements.h filename )                          *
// * Description: Header file for a class of type topkelements. topkelements *
// *    is a helper class for finding the top k words, numbers, and          *
// *    characters in a given string. topkelements uses an unordered map to  *
// *    process each char of a passed in string followed by a priority queue *
// *    to get the top k words, numbers, and characters by using a custom    *
// *    lambda function which compares the occurrences of 2 elements. If the *
// *    2 elements are tied for occurrences, the lambda will break the tie   *
// *    by comparing the priority of the element. (1st occurrence for word   *
// *    and numbers, ascii value in decimal for chars). Functions for        *
// *    clearing the unordered maps, accessor and mutator functions for k,   *
// *    and a print function are also in the public interface.               *
// * Author: William Ryan Miller                                             *
// * References: N/A                                                         *
// * Date: 11/21/2020                                                        *
// ***************************************************************************

#ifndef TOPKELEMENTS_H
#define TOPKELEMENTS_H

#include <istream>
#include <unordered_map>
#include <list>

using namespace std;
typedef pair<string, pair<int, int>> data_pair;            //New alias to make code cleaner
typedef unordered_map<string, pair<int, int>> mapped_data; //New alias to make code cleaner
static const unsigned int KDEFAULT = 10;                   //Default for if invaild k is given

class TopKElements {
public:
    explicit TopKElements(int k = 10);                     //Constructor with default of 10
    ~TopKElements();                                       //Destructor clears maps
    void buildMaps(const string &in);                      //Builds 3 maps from input string
    void printTopKData() const;                            //Prints the top k elements in the maps
    void clearMaps();                                      //Clears the maps
    int getK() const;                                      //Returns kelements
    void setK(int k);                                      //Sets kelements
private:
    void displayData(list<data_pair> topKData) const;
    list<data_pair>  minHeapSort(const mapped_data &map) const;  //Sorts the maps using a priority queue
    mapped_data chars;                                     //Map of chars
    mapped_data words;                                     //Map of words
    mapped_data numbers;                                   //Map of numbers
    int wordcounter;                                       //Counter for number of words
    int kelements;                                         //Holds the value of k
};
#endif //TOPKELEMENTS_H

