/*****************************************************************************
# Author:           Student
# Assignment:       Security
# Date:             2026-02-21
# Description:      Class definition for one user access count record.
# Input:            Constructor accepts a user name C-string.
# Output:           Getter methods provide user name and count.
# Sources:          Assignment specifications.
#*****************************************************************************/

#ifndef USERACCESS_H
#define USERACCESS_H

class UserAccess
{
public:
   explicit UserAccess(const char* user);
   UserAccess(const UserAccess& other);
   ~UserAccess();

   UserAccess operator=(const UserAccess& other);

   const char* getUser();
   int getCount();
   void incr();

private:
   char* mUser;
   int mCount;
};

#endif
