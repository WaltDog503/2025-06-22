#include "useraccess.h"

#include <cstring>

using namespace std;

UserAccess::UserAccess(const char* user)
{
   const char* source = (user == nullptr) ? "" : user;
   const int len = static_cast<int>(strlen(source));

   mUser = new char[len + 1];
   strcpy(mUser, source);
   mCount = 1;
}

UserAccess::UserAccess(const UserAccess& other)
{
   const int len = static_cast<int>(strlen(other.mUser));
   mUser = new char[len + 1];
   strcpy(mUser, other.mUser);
   mCount = other.mCount;
}

UserAccess::~UserAccess()
{
   delete[] mUser;
}

UserAccess& UserAccess::operator=(const UserAccess& other)
{
   int len = 0;

   if (this != &other)
   {
      delete[] mUser;

      len = static_cast<int>(strlen(other.mUser));
      mUser = new char[len + 1];
      strcpy(mUser, other.mUser);
      mCount = other.mCount;
   }

   return *this;
}

const char* UserAccess::getUser() const
{
   return mUser;
}

int UserAccess::getCount() const
{
   return mCount;
}

void UserAccess::incr()
{
   mCount = mCount + 1;
}
