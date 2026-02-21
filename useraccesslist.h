/******************************************************************************
# Author:           Student
# Assignment:       Security
# Date:             2026-02-21
# Description:      Class definition for per-system linked user access data.
# Input:            Constructor accepts a system name C-string.
# Output:           addUser updates counts, printReport prints report text.
# Sources:          Assignment specifications.
#******************************************************************************/

#ifndef USERACCESSLIST_H
#define USERACCESSLIST_H

#include "usernode.h"

class UserAccessList
{
public:
   explicit UserAccessList(const char* systemName);
   ~UserAccessList();

   UserAccessList(const UserAccessList& other) = delete;
   UserAccessList& operator=(const UserAccessList& other) = delete;

   void addUser(const char* systemName, const char* user);
   void printReport();

private:
   char* mSystem;
   int mTotalAccesses;
   UserNode* mHead;
};

#endif
