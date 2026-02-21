#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "useraccesslist.h"

using namespace std;

namespace
{
string trim(const string& text)
{
  size_t start = 0;
  while (start < text.size() &&
         isspace(static_cast<unsigned char>(text[start])) != 0)
  {
    ++start;
  }

  size_t end = text.size();
  while (end > start &&
         isspace(static_cast<unsigned char>(text[end - 1])) != 0)
  {
    --end;
  }

  return text.substr(start, end - start);
}

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
    string system = trim(line);
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
    string system = trim(line);
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
    const string entry = trim(line);
    if (entry.empty())
    {
      continue;
    }

    const size_t commaPos = entry.find(',');
    if (commaPos == string::npos)
    {
      continue;
    }

    const string system = trim(entry.substr(0, commaPos));
    const string user = trim(entry.substr(commaPos + 1));
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
