#include "useraccess.h"

#include <cstring>

using namespace std;

namespace
{
char* copyString(const char* src)
{
  if (src == nullptr)
  {
    char* empty = new char[1];
    empty[0] = '\0';
    return empty;
  }

  const size_t len = strlen(src);
  char* dst = new char[len + 1];
  strcpy(dst, src);
  return dst;
}
}  // namespace

UserAccess::UserAccess(const char* user) : mUser(copyString(user)), mCount(1)
{
}

UserAccess::UserAccess(const UserAccess& other)
    : mUser(copyString(other.mUser)), mCount(other.mCount)
{
}

UserAccess::~UserAccess()
{
  delete[] mUser;
}

UserAccess UserAccess::operator=(const UserAccess& other)
{
  if (this == &other)
  {
    return *this;
  }

  char* copy = copyString(other.mUser);
  delete[] mUser;
  mUser = copy;
  mCount = other.mCount;
  return *this;
}

const char* UserAccess::getUser()
{
  return mUser;
}

int UserAccess::getCount()
{
  return mCount;
}

void UserAccess::incr()
{
  ++mCount;
}
