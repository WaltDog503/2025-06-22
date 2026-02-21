#include "useraccesslist.h"

#include <cstring>
#include <iostream>

using namespace std;

UserAccessList::UserAccessList(const char* systemName)
{
   const char* source = (systemName == nullptr) ? "" : systemName;
   const int len = static_cast<int>(strlen(source));

   mSystem = new char[len + 1];
   strcpy(mSystem, source);

   mTotalAccesses = 0;
   mHead = nullptr;
}

UserAccessList::~UserAccessList()
{
   UserNode* current = mHead;
   UserNode* next = nullptr;

   while (current != nullptr)
   {
      next = current->next;
      delete current;
      current = next;
   }

   delete[] mSystem;
}

void UserAccessList::addUser(const char* systemName, const char* user)
{
   bool validInput = false;
   bool matchingSystem = false;
   bool foundExistingUser = false;
   UserNode* current = nullptr;
   UserNode* tail = nullptr;
   UserAccess* newAccess = nullptr;
   UserNode* newNode = nullptr;

   validInput = (systemName != nullptr && user != nullptr);
   if (validInput)
   {
      matchingSystem = (strcmp(mSystem, systemName) == 0);
   }

   if (validInput && matchingSystem)
   {
      mTotalAccesses = mTotalAccesses + 1;

      current = mHead;
      tail = nullptr;

      while (current != nullptr && !foundExistingUser)
      {
         if (strcmp(current->data->getUser(), user) == 0)
         {
            current->data->incr();
            foundExistingUser = true;
         }
         else
         {
            tail = current;
            current = current->next;
         }
      }

      if (!foundExistingUser)
      {
         newAccess = new UserAccess(user);
         newNode = new UserNode(newAccess);

         if (mHead == nullptr)
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

void UserAccessList::printReport()
{
   UserNode* topNode = nullptr;
   UserNode* current = nullptr;
   const char* topUser = "";
   bool printedSecond = false;
   int topCount = -1;
   int secondCount = -1;
   int count = 0;
   int percent = 0;

   current = mHead;
   while (current != nullptr)
   {
      count = current->data->getCount();

      if (count > topCount)
      {
         secondCount = topCount;
         topCount = count;
         topNode = current;
      }
      else if (count < topCount && count > secondCount)
      {
         secondCount = count;
      }

      current = current->next;
   }

   if (topNode != nullptr)
   {
      topUser = topNode->data->getUser();
   }

   cout << "System: " << mSystem << '\n';
   cout << "  Top: " << topUser << '\n';

   cout << "  Second: ";
   if (secondCount >= 0)
   {
      current = mHead;
      while (current != nullptr)
      {
         if (current->data->getCount() == secondCount)
         {
            if (printedSecond)
            {
               cout << ", ";
            }
            cout << current->data->getUser();
            printedSecond = true;
         }
         current = current->next;
      }
   }
   cout << '\n';

   cout << "  All:" << '\n';
   current = mHead;
   while (current != nullptr)
   {
      count = current->data->getCount();
      if (mTotalAccesses == 0)
      {
         percent = 0;
      }
      else
      {
         percent = (count * 100) / mTotalAccesses;
      }

      cout << "    " << current->data->getUser() << " " << count;
      cout << " (" << percent << "%)" << '\n';

      current = current->next;
   }
}
