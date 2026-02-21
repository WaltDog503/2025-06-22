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
