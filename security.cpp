#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

  vector<string> systemNames;
  string line;
  while (getline(systemsFile, line))
  {
    const string system = trim(line);
    if (!system.empty())
    {
      systemNames.push_back(system);
    }
  }

  if (systemNames.empty())
  {
    return 0;
  }

  UserAccessList** systems = new UserAccessList*[systemNames.size()];
  for (size_t i = 0; i < systemNames.size(); ++i)
  {
    systems[i] = new UserAccessList(systemNames[i].c_str());
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

    for (size_t i = 0; i < systemNames.size(); ++i)
    {
      systems[i]->addUser(system.c_str(), user.c_str());
    }
  }

  for (size_t i = 0; i < systemNames.size(); ++i)
  {
    systems[i]->printReport();
  }

  for (size_t i = 0; i < systemNames.size(); ++i)
  {
    delete systems[i];
  }
  delete[] systems;

  return 0;
}
