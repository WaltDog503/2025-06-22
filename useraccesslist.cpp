#include "useraccesslist.h"

#include <cstring>
#include <iostream>

UserAccessList::UserAccessList(const char* systemName)
{
  const char* source = (systemName == nullptr) ? "" : systemName;
  const int len = static_cast<int>(std::strlen(source));

  mSystem = new char[len + 1];
  std::strcpy(mSystem, source);

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
  if (systemName == nullptr || user == nullptr)
  {
    return;
  }

  if (std::strcmp(mSystem, systemName) != 0)
  {
    return;
  }

  ++mTotalAccesses;

  UserNode* current = mHead;
  UserNode* tail = nullptr;

  while (current != nullptr)
  {
    if (std::strcmp(current->data->getUser(), user) == 0)
    {
      current->data->incr();
      return;
    }

    tail = current;
    current = current->next;
  }

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

void UserAccessList::printReport()
{
  UserNode* topNode = nullptr;
  UserNode* secondNode = nullptr;

  for (UserNode* current = mHead; current != nullptr; current = current->next)
  {
    if (topNode == nullptr || current->data->getCount() > topNode->data->getCount())
    {
      secondNode = topNode;
      topNode = current;
    }
    else if (secondNode == nullptr ||
             current->data->getCount() > secondNode->data->getCount())
    {
      secondNode = current;
    }
  }

  std::cout << "System: " << mSystem << '\n';
  std::cout << "  Top: " << (topNode != nullptr ? topNode->data->getUser() : "") << '\n';
  std::cout << "  Second: "
            << (secondNode != nullptr ? secondNode->data->getUser() : "") << '\n';
  std::cout << "  All:" << '\n';

  for (UserNode* current = mHead; current != nullptr; current = current->next)
  {
    const int count = current->data->getCount();
    const int percent = (mTotalAccesses == 0) ? 0 : (count * 100 / mTotalAccesses);

    std::cout << "    " << current->data->getUser() << " " << count << " (" << percent
              << "%)" << '\n';
  }
}
