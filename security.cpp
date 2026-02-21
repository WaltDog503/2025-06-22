#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "useraccesslist.h"

namespace
{
std::string trim(const std::string& text)
{
  std::size_t start = 0;
  while (start < text.size() &&
         std::isspace(static_cast<unsigned char>(text[start])) != 0)
  {
    ++start;
  }

  std::size_t end = text.size();
  while (end > start &&
         std::isspace(static_cast<unsigned char>(text[end - 1])) != 0)
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
    std::cout << "Usage: " << argv[0] << " <access-file> <systems-file>\n";
    return 1;
  }

  std::ifstream accessFile(argv[1]);
  if (!accessFile)
  {
    std::cout << "Error: unable to open access file.\n";
    return 1;
  }

  std::ifstream systemsFile(argv[2]);
  if (!systemsFile)
  {
    std::cout << "Error: unable to open systems file.\n";
    return 1;
  }

  std::vector<std::string> systemNames;
  std::string line;
  while (std::getline(systemsFile, line))
  {
    const std::string system = trim(line);
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
  for (std::size_t i = 0; i < systemNames.size(); ++i)
  {
    systems[i] = new UserAccessList(systemNames[i].c_str());
  }

  while (std::getline(accessFile, line))
  {
    const std::string entry = trim(line);
    if (entry.empty())
    {
      continue;
    }

    const std::size_t commaPos = entry.find(',');
    if (commaPos == std::string::npos)
    {
      continue;
    }

    const std::string system = trim(entry.substr(0, commaPos));
    const std::string user = trim(entry.substr(commaPos + 1));
    if (system.empty() || user.empty())
    {
      continue;
    }

    for (std::size_t i = 0; i < systemNames.size(); ++i)
    {
      systems[i]->addUser(system.c_str(), user.c_str());
    }
  }

  for (std::size_t i = 0; i < systemNames.size(); ++i)
  {
    systems[i]->printReport();
  }

  for (std::size_t i = 0; i < systemNames.size(); ++i)
  {
    delete systems[i];
  }
  delete[] systems;

  return 0;
}
