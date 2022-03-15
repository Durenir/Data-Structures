// ***************************************************************************
// * Name: TopKElements ( topkelements.cpp filename )                        *
// * Description: Implementation file for a class of type TopKElements.      *
// *    TopKElements is a helper class for finding the top k words, numbers, *
// *    and characters in a given string. TopKElements uses an unordered map *
// *    to process each char of a passed in string followed by a priority    *
// *    queue to get the top k words, numbers, and characters by using a     *
// *    custom lambda function which compares the occurrences of 2 elements. *
// *    If the 2 elements are tied for occurrences, the lambda will break the*
// *    tie by comparing the priority of the element. (1st occurrence for    *
// *    word and numbers, ascii value in decimal for chars). Functions for   *
// *    clearing the unordered maps, accessor and mutator functions for k,   *
// *    and a print function are also in the public interface.               *
// * Author: William Ryan Miller                                             *
// * References: N/A                                                         *
// * Date: 11/21/2020                                                        *
// ***************************************************************************

#include <queue>
#include <iostream>
#include <iomanip>
#include "topkelements.h"

// *****************************************************************
// * Function Name: TopKElements                                   *
// * Description: Constructor of type TopKElements. Constructor    *
// *    initializes kelements to the passed in integer k. If passed*
// *    in k value is too small, uses the KDEFAULT instead. Then   *
// *    initializes wordcounter to 0.                              *
// * Parameter Description: Takes in an integer k which is used    *
// *    as the amount of top elements a user wants to return. For  *
// *    example, a k value of 10 will give the top 10 elements.    *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
TopKElements::TopKElements(int k) {
    if(k > 0) {
        kelements = k;
    } else {
        kelements = KDEFAULT;
    }
    wordcounter = 0;
}

// *****************************************************************
// * Function Name: buildMaps                                      *
// * Description: Function builds 3 unordered maps (one for words, *
// *    one for numbers, and one for chars) by parsing a passed in *
// *    string, character by character, and inserting into the     *
// *    appropriate maps as a pair. The key is the element itself  *
// *    and the value is another pair. The value pair consist of   *
// *    two integers. The first is the the number of occurrences   *
// *    and the second is the priority. Priority for words and     *
// *    numbers is equal to what the wordcounter is when the number*
// *    or word is first encountered. Priority for a char is equal *
// *    to the chars ascii decimal value.                          *
// * Parameter Description: Takes in an string by const reference  *
// *    called in. String is the string to be parsed and placed    *
// *    into the three unordered maps.                             *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void TopKElements::buildMaps(const string &in) {
    string builder;
        for(size_t i = 0; i < in.length(); i++)
        {
            if(isalpha(in[i])) {
                builder += tolower(in[i]);
                if(!isalpha(in[i+1]))
                {
                    if(words.find(builder) == words.end())
                    {
                        words[builder].second = wordcounter;
                    }
                    words[builder].first++;
                    wordcounter++;
                    builder = "";
                }
            }
            else if(isdigit(in[i])) {
                builder += tolower(in[i]);
                if(!isdigit(in[i+1]))
                {
                    if(numbers.find(builder) == numbers.end())
                    {
                        numbers[builder].second = wordcounter;
                    }
                    numbers[builder].first++;
                    builder = "";
                    wordcounter++;
                }
            }
            string str(1, in[i]);
            if(in[i] == ' ')
            {
                str = "space";
            } else if(in[i] == '\t')
            {
                str = "\\t";
            } else if (in[i] == '\r')
            {
                str = "\\r";
            }
            chars[str].first++;
            chars[str].second = int(in[i]);
        }
        chars["\\n"].first++;
        chars["\\n"].second = 10;
}

// *****************************************************************
// * Function Name: mipHeapSort                                    *
// * Description: Function will iterate over a passed in unordered *
// *    map and sort using a priority queue and a lambda function. *
// *    Priority queue is optimized by only storing k elements at  *
// *    a time. This increases the sort speed from logn to logk.   *
// *    When finished iterating, the top k elements will be left   *
// *    in the priority queue in reverse order. Priority queue is  *
// *    transferred into a list in the proper order and then the   *
// *    list is returned.                                          *
// * Parameter Description: Takes in an unordered map called map by*
// *    const reference. map is the unordered map to be sorted.    *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
list<data_pair> TopKElements::minHeapSort(const mapped_data & map) const{
    //Lambda function for determining order via occurrence count and priority
    auto comp = [](const data_pair& a, const data_pair& b)
    {
        if(a.second.first > b.second.first)
        {
            return true;
        } else if(a.second.first == b.second.first)
        {
            return a.second.second < b.second.second;
        } else {
            return false;
        }
    };
    priority_queue<data_pair, vector<data_pair>, decltype(comp)> pq(comp);
    for(auto & it : map)
    {
        pq.push(it);
        if(pq.size() > kelements)
        {
            pq.pop();
        }
    }
    list<data_pair> results;
    while(!pq.empty())
    {
        results.push_front(pq.top());
        pq.pop();
    }
    return results;
}

// *****************************************************************
// * Function Name: displayData                                    *
// * Description: Function iterates over a passed in list and      *
// *    outputs the index, item, occurrence count, and priority    *
// *    stored at each index.                                      *
// * Parameter Description: Takes in a list called topKData.       *
// *    topKData is the list to be iterated over and contents      *
// *    output to the console.                                     *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void TopKElements::displayData(list<data_pair> topKData) const{
    cout << left;
    cout << setw(8)<< "Index" << setw(10) << "Item" << setw(8) << "Number" << "Priority" << endl;
    for(int i = 0; !topKData.empty(); i++)
    {
        cout << left;
        cout << "[" << i << setw(5) << "]" << setw(13) << topKData.front().first <<
        setw(7) << topKData.front().second.first << topKData.front().second.second << endl;
        topKData.pop_front();
    }
    cout << endl << endl;
}

// *****************************************************************
// * Function Name: printTopKData                                  *
// * Description: Function displays how many unique words, numbers,*
// *    and characters were found when parsing the input data. Then*
// *    calls minHeapSort for each unordered map and passes the    *
// *    result to displayData to output the result to the console. *
// * Parameter Description: N/A                                    *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void TopKElements::printTopKData() const {
    cout << "There are " << words.size() << " Unique Words, The Top " << kelements << " Words\n\n";
    displayData(minHeapSort(words));
    cout << "There are " << numbers.size() << " Unique Numbers, The Top " << kelements << " Numbers\n\n";
    displayData(minHeapSort(numbers));
    cout << "There are " << chars.size() << " Unique Characters, The Top " << kelements << " Characters\n\n";
    displayData(minHeapSort(chars));
}

// *****************************************************************
// * Function Name: clearMaps                                      *
// * Description: Function clears the contents of the unordered    *
// *    maps for words, numbers, and characters. Then resets the   *
// *    wordcounter back to 0.                                     *
// * Parameter Description: N/A                                    *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void TopKElements::clearMaps() {
    words.clear();
    numbers.clear();
    chars.clear();
    wordcounter = 0;
}

// *****************************************************************
// * Function Name: ~TopKElements                                  *
// * Description: Destructor of type TopKElements. Calls clearMaps *
// *    function to clear all data and prevent any possible memory *
// *    leaks.                                                     *
// * Parameter Description: N/A                                    *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
TopKElements::~TopKElements() {
    clearMaps();
}

// *****************************************************************
// * Function Name: setK                                           *
// * Description: Mutator function for private data member         *
// *    kelements. Sets kelements equal to the passed in integer if*
// *    passed in integer is greater than 0.                       *
// * Parameter Description: Takes in an integer called k. kelements*
// *    is set equal to k if k is greater than 0.                  *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void TopKElements::setK(int k) {
    if(k > 0) {
        kelements = k;
    }
}

// *****************************************************************
// * Function Name: getK                                           *
// * Description: Accessor function for kelements. Returns the     *
// *    value stored in private data member kelements.             *
// * Parameter Description: N/A                                    *
// * Date: 11/21/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
int TopKElements::getK() const {
    return kelements;
}

