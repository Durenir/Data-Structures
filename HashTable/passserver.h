#ifndef PASSSERVER_H
#define PASSSERVER_H
#include "hashtable.h"
#include <cstring>

// ***************************************************************************
// * Name: PassServer ( passserver.h filename )                              *
// * Description: Header file of of a PassServer. A PassServer is an         *
// *    adaptor of the template data type HashTable. A PassServer can be     *
// *    constructed, load a file, write a file, add a user, remove a user,   *
// *    change a password, dump the HashTable to the display, find a user,   *
// *    and return the size.                                                 *
// * Author: William Ryan Miller                                             *
// * References: N/A                                                         *
// * Date: 11/09/2020                                                        *
// ***************************************************************************
using namespace cop4530;
    class PassServer
    {
    public:
        PassServer(size_t = 101);                      //Constructor
        ~PassServer();                                 //Destructor
        bool load(const char *filename);               //Load a file to PassServer
        bool addUser(pair<string, string> &kv);        //Add a user to PassServer
        bool addUser(pair<string, string> &&kv);       //Move version of addUser
        bool removeUser(const string & k);             //Remove a user from PassServer
        bool changePassword(const pair<string, string> &p, const string &newpassword);    //Change a users password
        bool find(const string & user) const;          //Find a user in the PassServer
        void dump() const;                             //Display contents of PassServer
        size_t size() const;                           //Return the size of the PassServer
        bool write_to_file(const char *filename) const;//Write data of PassServer to a file
    private:
        string encrypt(const string & str);            //Encrypt users password
        HashTable<string, string> ps;                  //HashTable container for the PassServer
    };
#endif //PASSSERVER_H

