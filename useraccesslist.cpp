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
  while (current != nullptr)
  {
    UserNode* next = current->next;
    delete current;
    current = next;
  }

  delete[] mSystem;
}

void UserAccessList::addUser(const char* systemName, const char* user)
{
  bool validInput = (systemName != nullptr && user != nullptr);
  bool matchingSystem = false;
  bool foundExistingUser = false;

  if (validInput)
  {
    matchingSystem = (strcmp(mSystem, systemName) == 0);
  }

  if (validInput && matchingSystem)
  {
    ++mTotalAccesses;

    UserNode* current = mHead;
    UserNode* tail = nullptr;

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
      UserAccess* newAccess = new UserAccess(user);
      UserNode* newNode = new UserNode(newAccess);

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
  int topCount = -1;
  int secondCount = -1;

  for (UserNode* current = mHead; current != nullptr; current = current->next)
  {
    const int count = current->data->getCount();

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
  }

  cout << "System: " << mSystem << '\n';
  cout << "  Top: " << (topNode != nullptr ? topNode->data->getUser() : "") << '\n';

  cout << "  Second: ";
  bool printedSecond = false;
  if (secondCount >= 0)
  {
    for (UserNode* current = mHead; current != nullptr; current = current->next)
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
    }
  }
  cout << '\n';

  cout << "  All:" << '\n';

  for (UserNode* current = mHead; current != nullptr; current = current->next)
  {
    const int count = current->data->getCount();
    const int percent = (mTotalAccesses == 0) ? 0 : (count * 100 / mTotalAccesses);

    cout << "    " << current->data->getUser() << " " << count << " (" << percent
         << "%)" << '\n';
  }
}
