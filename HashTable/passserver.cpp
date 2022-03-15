#include "passserver.h"
#include <unistd.h>
#include <crypt.h>
using namespace cop4530;

// ***************************************************************************
// * Name: PassServer ( passserver.cpp filename )                            *
// * Description: Implementation of of a PassServer. A PassServer is an      *
// *    adaptor of the template data type HashTable. A PassServer can be     *
// *    constructed, load a file, write a file, add a user, remove a user,   *
// *    change a password, dump the HashTable to the display, find a user,   *
// *    and return the size.                                                 *
// * Author: William Ryan Miller                                             *
// * References: N/A                                                         *
// * Date: 11/09/2020                                                        *
// ***************************************************************************
// *****************************************************************
// * Function Name: HashTable                                      *
// * Description: Constructor of type PassServer. Creates a        *
// *    PassServer by initializing the HashTable ps to a passed in *
// *    size.                                                      *
// * Parameter Description: Takes in a size_t called size. Used    *
// *    as the size to initialize the PassServer to.               *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
PassServer::PassServer(size_t size) : ps(size){}

// *****************************************************************
// * Function Name: ~PassServer                                    *
// * Description: Destructor of type PassServer. Restores memory   *
// *    allocated to the PassServer by calling clear() on the      *
// *    HashTable member ps.                                       *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
PassServer::~PassServer() {
    ps.clear();
}

// *****************************************************************
// * Function Name: addUser                                        *
// * Description: Adds a user to the PassServer by calling the     *
// *    HashTable function insert() on PassServer data member ps   *
// *    and passing in a pair kv representing a username and       *
// *    password. Password passed into insert() will encrypted.    *
// * Parameter Description: Takes in a pair of strings called kv.  *
// *    kv is the username and password to be added to the         *
// *    PassServer.                                                *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool PassServer::addUser(pair<string, string> &kv) {
    return ps.insert(pair<string, string>(kv.first, encrypt(kv.second)));
}

// *****************************************************************
// * Function Name: encrypt                                        *
// * Description: Encrypts a passed in string by using the crypt   *
// *    function and a salt. Returns the encrypted password.       *
// * Parameter Description: Takes in a const string by reference   *
// *    called str. str is the string to be encrypted.             *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
string PassServer::encrypt(const string &str) {
    char salt[] = "$1$########";
    string newPass = crypt(str.c_str(), salt);
    return newPass.substr(12);
}

// *****************************************************************
// * Function Name: load                                           *
// * Description: Loads a file of data into the PassServer by      *
// *    calling the load function of the PassServers HashTable data*
// *    member ps. Returns true if succesful. False if file could  *
// *    not be loaded.                                             *
// * Parameter Description: Takes in a const pointer to a filename *
// *    called filename. filename points to the name of the file to*
// *    be loaded into the PassServer.                             *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool PassServer::load(const char *filename) {
    return ps.load(filename);
}

// *****************************************************************
// * Function Name: addUser (move)                                 *
// * Description: Moves a user to the PassServer by calling the    *
// *    HashTable function insert() on PassServer data member ps   *
// *    and passing in a pair kv representing a username and       *
// *    password. Password passed into insert() will encrypted.    *
// * Parameter Description: Takes in a pair of strings called kv.  *
// *    kv is the username and password to be added to the         *
// *    PassServer.                                                *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool PassServer::addUser(pair<string, string> &&kv) {
    return ps.insert(move(pair<string, string>(kv.first, encrypt(kv.second))));
}

// *****************************************************************
// * Function Name: removeUser                                     *
// * Description: Removes a user from the PassServer by calling    *
// *    the remove() function of the HashTable ps.                 *
// * Parameter Description: Takes in a const string k by reference.*
// *    k is the username to be removed from the PassServer.       *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool PassServer::removeUser(const string &k) {
    return ps.remove(k);
}

// *****************************************************************
// * Function Name: ChangePassword                                 *
// * Description: Changes the password of a user. Function first   *
// *    checks to make sure the password is different from the old *
// *    password. Then checks if the pair of username and password *
// *    is in the PassServer. If checks are passed, the new        *
// *    password replaces the old password and returns true.       *
// *    Otherwise returns false.                                   *
// * Parameter Description: Takes in a pair of strings called kv   *
// *    and a const string called newpassword. kv is the pair of   *
// *    strings representing a username and password. newpassword  *
// *    is the new password that will replace the old password.    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword) {
    if(p.second != newpassword && ps.contains(p.first))
    {
        if(ps.match(pair<string, string>(p.first, encrypt(p.second))))
        {
            ps.insert(pair<string, string>(p.first, encrypt(newpassword)));
            return true;
        }
    }
    return false;
}

// *****************************************************************
// * Function Name: find                                           *
// * Description: Finds a user in the PassServer by calling the    *
// *    contains function of private HashTable data member ps.     *
// *    Returns true if found, false if not found.                 *
// * Parameter Description: Takes in const string by reference     *
// *    called user. user is the username the function attempts to *
// *    find in the PassServer.                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool PassServer::find(const string &user) const{
    return ps.contains(user);
}

// *****************************************************************
// * Function Name: dump                                           *
// * Description: Displays the usernames and passwords stored in   *
// *    the PassServer by calling the dump() function of the       *
// *    private HashTable data member.                             *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
void PassServer::dump() const {
    ps.dump();
}

// *****************************************************************
// * Function Name: size                                           *
// * Description: Returns the size of the PassServer by calling the*
// *    size() function of the private HashTable data member.      *
// * Parameter Description: N/A                                    *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
size_t PassServer::size() const {
    return ps.size();
}

// *****************************************************************
// * Function Name: write_to_file                                  *
// * Description: Writes usernames and passwords stored in the     *
// *    PassServer to a file by calling the write_to_file()        *
// *    function of the private HashTable data member.             *
// * Parameter Description: Takes in a const pointer to a char     *
// *    called filename. filename is the location of the file to   *
// *    write the usernames and passwords to. Returns true if      *
// *    successful. False if file could not be written.            *
// * Date: 11/09/2020                                              *
// * Author: William Ryan Miller                                   *
// * References: N/A                                               *
// *****************************************************************
bool PassServer::write_to_file(const char *filename) const{
    return ps.write_to_file(filename);
}


