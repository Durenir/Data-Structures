#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <fstream>
#include <algorithm>
#include <iostream>

// ***************************************************************************
// * Name: HashTable ( hashtable.h filename )                                *
// * Description: Header file of of a templated HashTable. A HashTable can   *
// *    be constructed, checked if it contains a certain key, checked if it  *
// *    contains a pair, insert a pair, remove a pair, be cleared, load a    *
// *    file, write a file, and dump the contents to the display. Pairs are  *
// *    added to the HashTable by hashing the key (first element of the pair)*
// *    and then using the hashed key to determine where to insert the pair  *
// *    into the HashTable. HashTable will expand capacity as needed.        *
// * Author: William Ryan Miller                                             *
// * References: N/A                                                         *
// * Date: 11/09/2020                                                        *
// ***************************************************************************
using namespace std;
namespace cop4530 {
    static const unsigned int default_capacity = 11;
    static const unsigned int max_prime = 1301081;

    template<typename K, typename V>
    class HashTable {
    public:
        HashTable(size_t size = 101);                       //Constructor
        ~HashTable();                                       //Destructor
        bool contains(const K &k) const;                    //Returns true if hashtable contains a key
        bool match(const pair<K, V> &kv) const;             //Returns true if a pair is in the table
        bool insert(const pair<K, V> &kv);                  //Inserts a pair into the table
        bool insert(pair<K, V> &&kv);                       //Move version of insert
        bool remove(const K &k);                            //Removes a pair from the table
        void clear();                                       //Clears the table
        bool load(const char *filename);                    //Load a file of usernames and passwords to a hashtable
        void dump() const;                                  //Display usernames and passwords in the hashtable
        bool write_to_file(const char *filename) const;     //Write a file with contents of the hashtable
        size_t size() const;                                //Returns the size of a hashtable

    private:
        size_t myhash(const K &k) const;                    //Hashes a key
        size_t count;                                       //Holds the count of pairs
        vector<list<pair < K, V>>> htable;                  //Holds the hashtable itself
        void makeEmpty();                                   //Makes the hashtable empty
        void rehash();                                      //Expands size and rehashes pairs
        unsigned long prime_below(unsigned long n);         //Gets prime below passed in n
        void setPrimes(vector<unsigned long> &vprimes);     //Helps prime_below get primes
    };

#include "hashtable.hpp"
}
#endif

