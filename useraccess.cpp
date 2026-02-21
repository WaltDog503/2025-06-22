/******************************************************************************
# Author:           Student
# Assignment:       Security
# Date:             2026-02-21
# Description:      Implements the UserAccess class, which stores one user
#                   name and that user's access count for one system.
# Input:            Constructor takes a user name as C-string.
# Output:           Getter methods return user name and count.
# Sources:          Assignment specifications.
#******************************************************************************/

#include "useraccess.h"

#include <cstring>

using namespace std;

namespace
{
// Name:   copyString(const char* src)
// Desc:   Allocates and copies a C-string; uses empty string for null source.
// Input:  src - source C-string pointer
// Output: None
// Return: Heap-allocated C-string copy
char* copyString(const char* src)
{
   char* dst = nullptr;
   size_t len = 0;

   if (src == nullptr)
   {
      dst = new char[1];
      dst[0] = '\0';
   }
   else
   {
      len = strlen(src);
      dst = new char[len + 1];
      strcpy(dst, src);
   }

   return dst;
}
}  // namespace

// Name:   UserAccess(const char* user)
// Desc:   Creates a user/count object with an initial count of 1.
// Input:  user - user name C-string
// Output: None
// Return: None
UserAccess::UserAccess(const char* user)
{
   mUser = copyString(user);
   mCount = 1;
}

// Name:   UserAccess(const UserAccess& other)
// Desc:   Deep-copy constructor for UserAccess.
// Input:  other - source UserAccess object
// Output: None
// Return: None
UserAccess::UserAccess(const UserAccess& other)
{
   mUser = copyString(other.mUser);
   mCount = other.mCount;
}

// Name:   ~UserAccess()
// Desc:   Frees dynamic memory used by the user name.
// Input:  None
// Output: None
// Return: None
UserAccess::~UserAccess()
{
   delete[] mUser;
}

// Name:   operator=(const UserAccess& other)
// Desc:   Deep-copy assignment operator with self-assignment protection.
// Input:  other - source UserAccess object
// Output: None
// Return: UserAccess object (*this)
UserAccess UserAccess::operator=(const UserAccess& other)
{
   char* copy = nullptr;

   if (this != &other)
   {
      copy = copyString(other.mUser);
      delete[] mUser;
      mUser = copy;
      mCount = other.mCount;
   }

   return *this;
}

// Name:   getUser()
// Desc:   Returns the stored user name.
// Input:  None
// Output: None
// Return: const char* user name
const char* UserAccess::getUser()
{
   return mUser;
}

// Name:   getCount()
// Desc:   Returns the current access count for this user.
// Input:  None
// Output: None
// Return: int access count
int UserAccess::getCount()
{
   return mCount;
}

// Name:   incr()
// Desc:   Increments the access count by one.
// Input:  None
// Output: None
// Return: None
void UserAccess::incr()
{
   mCount = mCount + 1;
}
