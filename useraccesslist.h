#ifndef USERACCESSLIST_H
#define USERACCESSLIST_H

#include "usernode.h"

class UserAccessList
{
private:
   char* mSystem;
   int mTotalAccesses;
   UserNode* mHead;

public:
   UserAccessList(const char* systemName);
   ~UserAccessList();

   UserAccessList(const UserAccessList& other) = delete;
   UserAccessList& operator=(const UserAccessList& other) = delete;

   void addUser(const char* systemName, const char* user);
   void printReport();
};

#endif
