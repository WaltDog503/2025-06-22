#ifndef USERNODE_H
#define USERNODE_H

#include "useraccess.h"

struct UserNode
{
  UserAccess* data;
  UserNode* next;

  UserNode(UserAccess* userData);
  ~UserNode();

  UserNode(const UserNode& other) = delete;
  UserNode& operator=(const UserNode& other) = delete;
};

#endif
