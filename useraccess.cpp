#include "useraccess.h"

#include <cstring>

UserAccess::UserAccess(const char* user)
{
  const char* source = (user == nullptr) ? "" : user;
  const int len = static_cast<int>(std::strlen(source));

  mUser = new char[len + 1];
  std::strcpy(mUser, source);
  mCount = 1;
}

UserAccess::UserAccess(const UserAccess& other)
{
  const int len = static_cast<int>(std::strlen(other.mUser));
  mUser = new char[len + 1];
  std::strcpy(mUser, other.mUser);
  mCount = other.mCount;
}

UserAccess::~UserAccess()
{
  delete[] mUser;
}

UserAccess& UserAccess::operator=(const UserAccess& other)
{
  if (this == &other)
  {
    return *this;
  }

  delete[] mUser;

  const int len = static_cast<int>(std::strlen(other.mUser));
  mUser = new char[len + 1];
  std::strcpy(mUser, other.mUser);
  mCount = other.mCount;

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
  ++mCount;
}
