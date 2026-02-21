#ifndef USERACCESS_H
#define USERACCESS_H

class UserAccess
{
public:
  explicit UserAccess(const char* user);
  UserAccess(const UserAccess& other);
  ~UserAccess();

  UserAccess& operator=(const UserAccess& other);

  const char* getUser() const;
  int getCount() const;
  void incr();

private:
  char* mUser;
  int mCount;
};

#endif
