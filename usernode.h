#ifndef USERNODE_H
#define USERNODE_H

#include "useraccess.h"

struct UserNode
{
   UserAccess* data;
   UserNode* next;

   UserNode(UserAccess* userData)
   {
      data = userData;
      next = nullptr;
   }

   ~UserNode()
   {
      delete data;
   }

   UserNode(const UserNode& other) = delete;
   UserNode& operator=(const UserNode& other) = delete;
};

#endif  // USERNODE_H
