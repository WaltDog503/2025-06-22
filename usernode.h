/******************************************************************************
# Author:           Student
# Assignment:       Security
# Date:             2026-02-21
# Description:      Node structure used by UserAccessList linked list.
# Input:            Constructor accepts UserAccess pointer data.
# Output:           None
# Sources:          Assignment specifications.
#******************************************************************************/

#ifndef USERNODE_H
#define USERNODE_H

#include "useraccess.h"

struct UserNode
{
   UserAccess* data;
   UserNode* next;

   explicit UserNode(UserAccess* userData);
   ~UserNode();

   UserNode(const UserNode& other) = delete;
   UserNode& operator=(const UserNode& other) = delete;
};

#endif
