/******************************************************************************
# Author:           Student
# Assignment:       Security
# Date:             2026-02-21
# Description:      Implements constructor/destructor for UserNode.
# Input:            UserAccess pointer passed to constructor.
# Output:           None
# Sources:          Assignment specifications.
#******************************************************************************/

#include "usernode.h"

// Name:   UserNode(UserAccess* userData)
// Desc:   Stores data pointer and initializes next pointer.
// Input:  userData - pointer to UserAccess object
// Output: None
// Return: None
UserNode::UserNode(UserAccess* userData) : data(userData), next(nullptr)
{
}

// Name:   ~UserNode()
// Desc:   Deletes stored UserAccess data object.
// Input:  None
// Output: None
// Return: None
UserNode::~UserNode()
{
   delete data;
}
