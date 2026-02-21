#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "useraccesslist.h"

using namespace std;

namespace
{
char* copyCString(const string& source)
{
  char* result = new char[source.size() + 1];
  strcpy(result, source.c_str());
  return result;
}
}  // namespace

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <access-file> <systems-file>\n";
    return 1;
  }

  ifstream accessFile(argv[1]);
  if (!accessFile)
  {
    cout << "Error: unable to open access file.\n";
    return 1;
  }

  ifstream systemsFile(argv[2]);
  if (!systemsFile)
  {
    cout << "Error: unable to open systems file.\n";
    return 1;
  }

  string line;
  int systemCount = 0;
  while (getline(systemsFile, line))
  {
    string system = line;
    size_t start = 0;
    while (start < system.size() &&
           isspace(static_cast<unsigned char>(system[start])) != 0)
    {
      ++start;
    }

    size_t end = system.size();
    while (end > start &&
           isspace(static_cast<unsigned char>(system[end - 1])) != 0)
    {
      --end;
    }

    system = system.substr(start, end - start);
    if (!system.empty())
    {
      ++systemCount;
    }
  }

  if (systemCount == 0)
  {
    return 0;
  }

  systemsFile.close();
  systemsFile.open(argv[2]);
  if (!systemsFile)
  {
    cout << "Error: unable to reopen systems file.\n";
    return 1;
  }

  char** systemNames = new char*[systemCount];
  for (int i = 0; i < systemCount; ++i)
  {
    systemNames[i] = nullptr;
  }

  int index = 0;
  while (index < systemCount && getline(systemsFile, line))
  {
    string system = line;
    size_t start = 0;
    while (start < system.size() &&
           isspace(static_cast<unsigned char>(system[start])) != 0)
    {
      ++start;
    }

    size_t end = system.size();
    while (end > start &&
           isspace(static_cast<unsigned char>(system[end - 1])) != 0)
    {
      --end;
    }

    system = system.substr(start, end - start);
    if (system.empty())
    {
      continue;
    }
    systemNames[index] = copyCString(system);
    ++index;
  }

  UserAccessList** systems = new UserAccessList*[systemCount];
  for (int i = 0; i < systemCount; ++i)
  {
    systems[i] = new UserAccessList(systemNames[i]);
  }

  while (getline(accessFile, line))
  {
    string entry = line;
    size_t start = 0;
    while (start < entry.size() &&
           isspace(static_cast<unsigned char>(entry[start])) != 0)
    {
      ++start;
    }

    size_t end = entry.size();
    while (end > start &&
           isspace(static_cast<unsigned char>(entry[end - 1])) != 0)
    {
      --end;
    }

    entry = entry.substr(start, end - start);
    if (entry.empty())
    {
      continue;
    }

    const size_t commaPos = entry.find(',');
    if (commaPos == string::npos)
    {
      continue;
    }

    string system = entry.substr(0, commaPos);
    start = 0;
    while (start < system.size() &&
           isspace(static_cast<unsigned char>(system[start])) != 0)
    {
      ++start;
    }

    end = system.size();
    while (end > start &&
           isspace(static_cast<unsigned char>(system[end - 1])) != 0)
    {
      --end;
    }

    system = system.substr(start, end - start);

    string user = entry.substr(commaPos + 1);
    start = 0;
    while (start < user.size() &&
           isspace(static_cast<unsigned char>(user[start])) != 0)
    {
      ++start;
    }

    end = user.size();
    while (end > start &&
           isspace(static_cast<unsigned char>(user[end - 1])) != 0)
    {
      --end;
    }

    user = user.substr(start, end - start);
    if (system.empty() || user.empty())
    {
      continue;
    }

    for (int i = 0; i < systemCount; ++i)
    {
      systems[i]->addUser(system.c_str(), user.c_str());
    }
  }

  for (int i = 0; i < systemCount; ++i)
  {
    systems[i]->printReport();
  }

  for (int i = 0; i < systemCount; ++i)
  {
    delete systems[i];
    delete[] systemNames[i];
  }
  delete[] systems;
  delete[] systemNames;

  return 0;
}
