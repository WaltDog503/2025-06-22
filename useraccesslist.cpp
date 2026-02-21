/******************************************************************************
# Author:           Student
# Assignment:       Security
# Date:             2026-02-21
# Description:      Implements the UserAccessList linked-list class for one
#                   ship system.
# Input:            addUser() receives system/user C-strings.
# Output:           printReport() prints a report for one system.
# Sources:          Assignment specifications.
#******************************************************************************/

#include "useraccesslist.h"

#include <cstring>
#include <iostream>

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

// Name:   UserAccessList(const char* systemName)
// Desc:   Creates an empty user-access list for one system.
// Input:  systemName - system name C-string
// Output: None
// Return: None
UserAccessList::UserAccessList(const char* systemName)
{
   mSystem = copyString(systemName);
   mTotalAccesses = 0;
   mHead = nullptr;
}

// Name:   ~UserAccessList()
// Desc:   Frees system name and all linked-list nodes.
// Input:  None
// Output: None
// Return: None
UserAccessList::~UserAccessList()
{
   UserNode* curr = nullptr;
   UserNode* next = nullptr;

   delete[] mSystem;

   curr = mHead;
   while (curr != nullptr)
   {
      next = curr->next;
      delete curr;
      curr = next;
   }
}

// Name:   addUser(const char* systemName, const char* user)
// Desc:   Adds one access event for a user when system name matches.
// Input:  systemName - requested system, user - user name
// Output: None
// Return: None
void UserAccessList::addUser(const char* systemName, const char* user)
{
   bool validData = false;
   bool matchingSystem = false;
   bool foundUser = false;
   UserNode* curr = nullptr;
   UserNode* tail = nullptr;
   UserNode* newNode = nullptr;

   if (systemName != nullptr && user != nullptr)
   {
      validData = true;
   }

   if (validData)
   {
      if (strcmp(systemName, mSystem) == 0)
      {
         matchingSystem = true;
      }
   }

   if (matchingSystem)
   {
      mTotalAccesses = mTotalAccesses + 1;

      curr = mHead;
      while (curr != nullptr && !foundUser)
      {
         if (strcmp(curr->data->getUser(), user) == 0)
         {
            curr->data->incr();
            foundUser = true;
         }
         else
         {
            tail = curr;
            curr = curr->next;
         }
      }

      if (!foundUser)
      {
         newNode = new UserNode(new UserAccess(user));
         if (tail == nullptr)
         {
            mHead = newNode;
         }
         else
         {
            tail->next = newNode;
         }
      }
   }
}

// Name:   printReport()
// Desc:   Prints this system's top users and all counts with percentages.
// Input:  None
// Output: Report text printed to console
// Return: None
void UserAccessList::printReport()
{
   UserNode* top = nullptr;
   UserNode* second = nullptr;
   UserNode* curr = nullptr;
   int count = 0;
   int percent = 0;

   cout << "System: " << mSystem << '\n';

   curr = mHead;
   while (curr != nullptr)
   {
      count = curr->data->getCount();
      if (top == nullptr || count > top->data->getCount())
      {
         second = top;
         top = curr;
      }
      else if (curr != top &&
               (second == nullptr || count > second->data->getCount()))
      {
         second = curr;
      }
      curr = curr->next;
   }

   cout << "  Top: ";
   if (top == nullptr)
   {
      cout << "(none)\n";
   }
   else
   {
      cout << top->data->getUser() << '\n';
   }

   cout << "  Second: ";
   if (second == nullptr)
   {
      cout << "(none)\n";
   }
   else
   {
      cout << second->data->getUser() << '\n';
   }

   cout << "  All:\n";
   curr = mHead;
   while (curr != nullptr)
   {
      count = curr->data->getCount();
      if (mTotalAccesses == 0)
      {
         percent = 0;
      }
      else
      {
         percent = (count * 100) / mTotalAccesses;
      }

      cout << "    " << curr->data->getUser() << " " << count
           << " (" << percent << "%)\n";
      curr = curr->next;
   }
}
