#include "useraccesslist.h"

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
  int returnCode = 0;

  if (argc != 3)
  {
    std::cout << "Usage: ./security accessData systemsData" << '\n';
    returnCode = 1;
  }
  else
  {
    std::ifstream accessFile(argv[1]);
    std::ifstream systemsFile(argv[2]);

    if (!accessFile || !systemsFile)
    {
      std::cout << "Error opening input files." << '\n';
      returnCode = 1;
    }
    else
    {
      int systemCount = 0;
      systemsFile >> systemCount;
      systemsFile.ignore(1000, '\n');

      UserAccessList** systemLists = new UserAccessList*[systemCount];

      for (int i = 0; i < systemCount; ++i)
      {
        std::string systemName;
        std::getline(systemsFile, systemName);
        systemLists[i] = new UserAccessList(systemName.c_str());
      }

      int accessCount = 0;
      accessFile >> accessCount;
      accessFile.ignore(1000, '\n');

      for (int i = 0; i < accessCount; ++i)
      {
        std::string entryLine;
        std::getline(accessFile, entryLine);

        std::size_t commaPos = entryLine.find(',');
        if (commaPos != std::string::npos)
        {
          std::string systemName = entryLine.substr(0, commaPos);
          std::string userName = entryLine.substr(commaPos + 2);

          for (int s = 0; s < systemCount; ++s)
          {
            systemLists[s]->addUser(systemName.c_str(), userName.c_str());
          }
        }
      }

      for (int i = 0; i < systemCount; ++i)
      {
        systemLists[i]->printReport();
      }

      for (int i = 0; i < systemCount; ++i)
      {
        delete systemLists[i];
      }
      delete[] systemLists;
    }
  }

  return returnCode;
}
