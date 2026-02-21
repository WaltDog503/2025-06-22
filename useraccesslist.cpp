#include "useraccesslist.h"

#include <cstring>
#include <iostream>

using namespace std;

namespace
{
char* copyString(const char* src)
{
  if (src == nullptr)
  {
    char* empty = new char[1];
    empty[0] = '\0';
    return empty;
  }

  const size_t len = strlen(src);
  char* dst = new char[len + 1];
  strcpy(dst, src);
  return dst;
}
}  // namespace

UserAccessList::UserAccessList(const char* systemName)
    : mSystem(copyString(systemName)), mTotalAccesses(0), mHead(nullptr)
{
}

UserAccessList::~UserAccessList()
{
  delete[] mSystem;

  UserNode* curr = mHead;
  while (curr != nullptr)
  {
    UserNode* next = curr->next;
    delete curr;
    curr = next;
  }
}

void UserAccessList::addUser(const char* systemName, const char* user)
{
  if (systemName == nullptr || user == nullptr)
  {
    return;
  }

  if (strcmp(systemName, mSystem) != 0)
  {
    return;
  }

  ++mTotalAccesses;

  UserNode* curr = mHead;
  UserNode* tail = nullptr;
  while (curr != nullptr)
  {
    if (strcmp(curr->data->getUser(), user) == 0)
    {
      curr->data->incr();
      return;
    }
    tail = curr;
    curr = curr->next;
  }

  UserNode* newNode = new UserNode(new UserAccess(user));
  if (tail == nullptr)
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
  cout << "System: " << mSystem << '\n';

  UserNode* top = nullptr;
  UserNode* second = nullptr;

  UserNode* curr = mHead;
  while (curr != nullptr)
  {
    const int count = curr->data->getCount();
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
    const int count = curr->data->getCount();
    const int percent = (mTotalAccesses == 0) ? 0 : (count * 100) / mTotalAccesses;
    cout << "    " << curr->data->getUser() << " " << count << " (" << percent
         << "%)\n";
    curr = curr->next;
  }
  cout << '\n';
}
