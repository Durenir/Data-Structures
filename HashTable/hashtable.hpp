
#include "hashtable.h"
// ***************************************************************************
// * Name: HashTable ( hashtable.hpp filename )                              *
// * Description: Implementation of a template HashTable. A HashTable can    *
// *    be constructed, checked if it contains a certain key, checked if it  *
// *    contains a pair, insert a pair, remove a pair, be cleared, load a    *
// *    file, write a file, and dump the contents to the display. Pairs are  *
// *    added to the HashTable by hashing the key (first element of the pair)*
// *    and then using the hashed key to determine where to insert the pair  *
// *    into the HashTable. HashTable will expand capacity as needed.        *
// * Author: William Ryan Miller                                             *
// * References: Textbook: Data Structures and Algorithm Analysis            *
// *    in C++ fourth edition. Lectures by Dr. David Gaitros.                *
// * Date: 11/09/2020                                                        *
// ***************************************************************************
// *****************************************************************
// * Function Name: HashTable                                      *
// * Description: Constructor of type HashTable. Creates a         *
// *    HashTable with a size equal to the prime below a passed in *
// *    size_t called size.                                        *
// * Parameter Description: Takes in a size_t called size.         *
// *    HashTable will be initialized with a size equal to the     *
// *    prime below size.                                          *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size) {
    htable.resize(prime_below(size));
    if(htable.size() == 0)
    {
        cout << "set to default capacity" << endl;
        htable.resize(default_capacity);
    }
    count = 0;
}

// *****************************************************************
// * Function Name: ~HashTable                                     *
// * Description: Destructor of type HashTable. Calls makeEmpty()  *
// *    to empty the HashTable.                                    *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
HashTable<K, V>::~HashTable() {
    makeEmpty();
}

// *****************************************************************
// * Function Name: makeEmpty                                      *
// * Description: Function iterates through the HashTable and      *
// *    clears each list in the HashTable.                         *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Pg 200.                             *
// *****************************************************************
template<typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for(auto & list : htable)
    {
        list.clear();
    }
    count = 0;
}

// *****************************************************************
// * Function Name: contains                                       *
// * Description: Function checks if a passed in key is within the *
// *    HashTable. Returns true if the key is within the Hashtable.*
// *    False otherwise.                                           *
// * Parameter Description: Takes in a const K called k. k is the  *
// *    key to be searched for in the HashTable.                   *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
bool HashTable<K, V>::contains(const K &k) const {
    auto & whichlist = htable[myhash(k)];
    for(auto itr = whichlist.begin(); itr != whichlist.end(); itr++)
    {
        if(itr->first == k)
        {
            return true;
        }
    }
    return false;
}

// *****************************************************************
// * Function Name: remove                                         *
// * Description: Function removes an entry in the HashTable by    *
// *    searching for a passed in key location and erasing the     *
// *    pair stored in the list that the key hashes to.            *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Pg 200.                             *
// *****************************************************************
template<typename K, typename V>
bool HashTable<K, V>::remove(const K &k) {
    auto & whichlist = htable[myhash(k)];
    for(auto itr = whichlist.begin(); itr != whichlist.end(); itr++)
    {
        if(itr->first == k)
        {
            whichlist.erase(itr);
            --count;
            return true;
        }
    }
    return false;
}

// *****************************************************************
// * Function Name: rehash                                         *
// * Description: Function rehashes the the data in the HashTable  *
// *    by storing the data in a temp HashTable, resizing the old  *
// *    HashTable, clearing the old HashTable, and then finally    *
// *    reinserts the data back into the HashTable.                *
// * Parameter Description: N/A                                    *
// * Date: Unknown                                                 *
// * Author: Mark Allen Weiss                                      *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. Pg 211.                             *
// *****************************************************************
template<typename K, typename V>
void HashTable<K, V>::rehash() {
    vector<list<pair<K, V>>> oldtable = htable;
    htable.resize(prime_below(2 * htable.size()));
    for(auto & list : htable)
    {
        list.clear();
    }
    count = 0;
    for(auto & list : oldtable)
    {
        for(auto & kv : list)
        {
            insert(move(kv));
        }
    }
}

// *****************************************************************
// * Function Name: insert                                         *
// * Description: Function inserts a passed in pair kv into the    *
// *    HashTable. Function will first check if kv is already in   *
// *    the table, returns false if it is. Function then checks if *
// *    the key is already in the HashTable, removes the data if it*
// *    is and updates to the new data. Otherwise, kv is inserted  *
// *    into the HashTable. Returns true if kv is inserted.        *
// * Parameter Description: Takes in a const K called k. k is the  *
// *    key to be searched for in the HashTable.                   *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. modified from Pg 200.               *
// *****************************************************************
template<typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> &kv) {
    auto & whichlist = htable[myhash(kv.first)];
    if(find(begin(whichlist), end(whichlist), kv) != end(whichlist))
    {
        return false;
    }
    else if(contains(kv.first)) {
        remove(kv.first);
    }
    whichlist.push_back(kv);
    if (++count > htable.size()) {
        rehash();
    }
    return true;
}

// *****************************************************************
// * Function Name: insert (move)                                  *
// * Description: Function moves a passed in pair kv into the      *
// *    HashTable. Function will first check if kv is already in   *
// *    the table, returns false if it is. Function then checks if *
// *    the key is already in the HashTable, removes the data if it*
// *    is and updates to the new data. Otherwise, kv is inserted  *
// *    into the HashTable. Returns true if kv is inserted.        *
// * Parameter Description: Takes in a const K called k. k is the  *
// *    key to be searched for in the HashTable.                   *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: Textbook: Data Structures and Algorithm Analysis  *
// *    in C++ fourth edition. modified from Pg 200.               *
// *****************************************************************
template<typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V> &&kv) {
    auto & whichlist = htable[myhash(kv.first)];
    if(find(begin(whichlist), end(whichlist), kv) != end(whichlist))
    {
        return false;
    }
    else if(contains(kv.first)) {
        remove(kv.first);
    }
    whichlist.push_back(move(kv));
    if (++count > htable.size()) {
        rehash();
    }
    return true;
}

// *****************************************************************
// * Function Name: clear                                          *
// * Description: Function clears the HashTable by calling         *
// *    makeEmpty().                                               *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

// *****************************************************************
// * Function Name: myhash                                         *
// * Description: Function hashes a passed in k by summing up the  *
// *    int casted components that compose k and then returning    *
// *    the modulo of the sum and the size of the HashTable.       *
// * Parameter Description: Takes in a const k by reference. k is  *
// *    the key value to be hashed.                                *
// * Date: Unknown                                                 *
// * Author: David A. Gaitros. Modified with a range based for loop*
// *    by William Ryan Miller.                                    *
// * References: Video lecture titled Chapter 5 within module      *
// *    5: Hash Tables.                                            *
// *****************************************************************
template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const{
    int hash = 0;
    for(auto x : k)
    {
        hash += static_cast<int>(x);
    }
    return hash % htable.size();
}

// *****************************************************************
// * Function Name: match                                          *
// * Description: Function determines if a passed in pair kv is    *
// *    within the HashTable by hashing the key to determine the   *
// *    list the pair is located in, and then uses an iterator to  *
// *    determine the location of the pair within the list. Returns*
// *    true if located. False if not located.                     *
// * Parameter Description: Takes in a pair kv. kv is the pair that*
// *    will be searched for in the HashTable.                     *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
    auto &whichlist = htable[myhash(kv.first)];
    return find(begin(whichlist), end(whichlist), kv) != end(whichlist);
}

// *****************************************************************
// * Function Name: load                                           *
// * Description: Function loads a passed in file into the         *
// *    HashTable by parsing the file for pairs and then inserts   *
// *    the pairs into the HashTable. Returns true if successful.  *
// *    Returns false if file could not be opened.                 *
// * Parameter Description: Takes in const pointer to a file name  *
// *    called filename. filename containts the name of of the     *
// *    file to be opened and parsed for pairs.                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    ifstream in;
    string line, username, password;
    in.open(filename);
    if(in.is_open())
    {
        while(in >> username >> password)
        {
            insert(pair<K,V>(username, password));
        }
        in.close();
        return true;
    }
    return false;
}

// *****************************************************************
// * Function Name: dump                                           *
// * Description: Function displays the contents of the pairs      *
// *    stored within each list in the HashTable by iterating      *
// *    through each pair in each list of the HashTable.           *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
void HashTable<K, V>::dump() const {
    for(int i = 0; i < htable.size(); i++)
    {
        cout << "v[" << i << "]: ";
        for(auto itr = htable[i].begin(); itr != htable[i].end(); itr++)
        {
            if(itr != htable[i].begin())
            {
                cout << ":";
            }
            cout << itr->first << " " << itr->second;
        }
        cout << endl;
    }
}

// *****************************************************************
// * Function Name: write_to_file                                  *
// * Description: Function writes the contents of the HashTable to *
// *    a file by iterating through each pair in each list within  *
// *    the HashTable. Returns true if successful. False if file   *
// *    could not be opened/created.                               *
// * Parameter Description: Takes in a const pointer to file name  *
// *    called filename. filename holds the name of the file to    *
// *    write the data in the HashTable to.                        *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const {
    ofstream out;
    out.open(filename);
    if(out.is_open())
    {
        for (auto &list : htable)
        {
            for (auto &p : list)
            {
                out << p.first << " " << p.second << endl;
            }
        }
        out.close();
        return true;
    }
    return false;
}

// *****************************************************************
// * Function Name: size                                           *
// * Description: Function returns how many pairs are stored in the*
// *    HashTable.                                                 *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
template<typename K, typename V>
size_t HashTable<K, V>::size() const {
    return count;
}

// *****************************************************************
// * Function Name: prime_below                                    *
// * Description: Returns largest prime number <= n or zero if     *
// *    input is too large. This is likely to be more efficient    *
// *    than prime_above(), because it only needs a vector of size *
// *    n.                                                         *
// * Parameter Description: Takes in an unsigned long called n.    *
// *    Function will determine the nearest prime number below n.  *
// * Date: Unknown                                                 *
// * Author: Unknown. Supplied by Dr. David A. Gaitros.            *
// * References: Assignment 5 in Module 5.                         *
// *****************************************************************
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
    if (n > max_prime)
    {
        std::cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime)
    {
        return max_prime;
    }
    if (n <= 1)
    {
        std::cerr << "** input too small \n";
        return 0;
    }

    // now: 2 <= n < max_prime
    std::vector <unsigned long> v (n+1);
    setPrimes(v);
    while (n > 2)
    {
        if (v[n] == 1)
            return n;
        --n;
    }

    return 2;
}

// *****************************************************************
// * Function Name: setPrimes                                      *
// * Description: Sets all prime number indexes to 1. Called by    *
// *    method prime_below(n)                                      *
// * Parameter Description: Takes in an vector of unsigned longs   *
// *    called vprimes. Used for determining prime numbers between *
// *    0 and the HashTable size.                                  *
// * Date: Unknown                                                 *
// * Author: Unknown. Supplied by Dr. David A. Gaitros.            *
// * References: Assignment 5 in Module 5.                         *
// *****************************************************************
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
        vprimes[i] = 1;

    for( i = 2; i*i < n; ++i)
    {
        if (vprimes[i] == 1)
            for(j = i + i ; j < n; j += i)
                vprimes[j] = 0;
    }
}
