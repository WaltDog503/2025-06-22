/******************************************************************************
# Author:           Student
# Assignment:       Security
# Date:             2026-02-21
# Description:      Reads system and access files, tracks per-system user
#                   counts, then prints reports.
# Input:            Two command-line filenames (access file and systems file).
# Output:           One report per system printed to console.
# Sources:          Assignment specifications.
#******************************************************************************/

#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>

#include "useraccesslist.h"

using namespace std;

const int MAX_LINE_LEN = 256;

void trimWhitespace(char* text);
char* copyCString(const char* source);
int countSystems(const char* systemsFileName);
bool loadSystemNames(const char* systemsFileName, char** systemNames,
                     int systemCount);
bool parseAccessLine(const char* line, char* systemName, char* userName);

// Name:   main(int argc, char* argv[])
// Desc:   Runs the security access reporting program.
// Input:  Command-line filenames for access and systems data.
// Output: Prints summary reports.
// Return: 0 on success, 1 on file/argument errors
int main(int argc, char* argv[])
{
   int status = 0;
   bool canRun = true;
   ifstream accessFile;
   int systemCount = 0;
   char** systemNames = nullptr;
   UserAccessList** systems = nullptr;
   int i = 0;
   char line[MAX_LINE_LEN];
   char parsedSystem[MAX_LINE_LEN];
   char parsedUser[MAX_LINE_LEN];
   bool parsedOk = false;

   if (argc != 3)
   {
      cout << "Usage: " << argv[0] << " <access-file> <systems-file>\n";
      status = 1;
      canRun = false;
   }

   if (canRun)
   {
      accessFile.open(argv[1]);
      if (!accessFile.is_open())
      {
         cout << "Error: unable to open access file.\n";
         status = 1;
         canRun = false;
      }
   }

   if (canRun)
   {
      systemCount = countSystems(argv[2]);
      if (systemCount < 0)
      {
         cout << "Error: unable to open systems file.\n";
         status = 1;
         canRun = false;
      }
      else if (systemCount == 0)
      {
         canRun = false;
      }
   }

   if (canRun)
   {
      systemNames = new char*[systemCount];
      for (i = 0; i < systemCount; ++i)
      {
         systemNames[i] = nullptr;
      }

      canRun = loadSystemNames(argv[2], systemNames, systemCount);
      if (!canRun)
      {
         cout << "Error: unable to read systems file.\n";
         status = 1;
      }
   }

   if (canRun)
   {
      systems = new UserAccessList*[systemCount];
      for (i = 0; i < systemCount; ++i)
      {
         systems[i] = new UserAccessList(systemNames[i]);
      }
   }

   if (canRun)
   {
      while (accessFile.getline(line, MAX_LINE_LEN))
      {
         trimWhitespace(line);
         parsedOk = parseAccessLine(line, parsedSystem, parsedUser);
         if (parsedOk)
         {
            for (i = 0; i < systemCount; ++i)
            {
               systems[i]->addUser(parsedSystem, parsedUser);
            }
         }
      }
   }

   if (canRun)
   {
      for (i = 0; i < systemCount; ++i)
      {
         systems[i]->printReport();
      }
   }

   if (systems != nullptr)
   {
      for (i = 0; i < systemCount; ++i)
      {
         delete systems[i];
      }
      delete[] systems;
   }

   if (systemNames != nullptr)
   {
      for (i = 0; i < systemCount; ++i)
      {
         delete[] systemNames[i];
      }
      delete[] systemNames;
   }

   if (accessFile.is_open())
   {
      accessFile.close();
   }

   return status;
}

// Name:   trimWhitespace(char* text)
// Desc:   Removes leading and trailing whitespace from a C-string in place.
// Input:  text - C-string to modify
// Output: Modified text content
// Return: None
void trimWhitespace(char* text)
{
   int length = 0;
   int start = 0;
   int end = 0;
   int readIndex = 0;
   int writeIndex = 0;

   if (text != nullptr)
   {
      length = static_cast<int>(strlen(text));

      while (start < length &&
             isspace(static_cast<unsigned char>(text[start])) != 0)
      {
         ++start;
      }

      end = length - 1;
      while (end >= start &&
             isspace(static_cast<unsigned char>(text[end])) != 0)
      {
         --end;
      }

      readIndex = start;
      while (readIndex <= end)
      {
         text[writeIndex] = text[readIndex];
         ++writeIndex;
         ++readIndex;
      }
      text[writeIndex] = '\0';
   }
}

// Name:   copyCString(const char* source)
// Desc:   Allocates and copies a C-string.
// Input:  source - C-string to copy
// Output: None
// Return: Heap-allocated C-string
char* copyCString(const char* source)
{
   char* copy = nullptr;
   int length = 0;

   if (source != nullptr)
   {
      length = static_cast<int>(strlen(source));
      copy = new char[length + 1];
      strcpy(copy, source);
   }

   return copy;
}

// Name:   countSystems(const char* systemsFileName)
// Desc:   Counts non-empty system lines in the systems file.
// Input:  systemsFileName - systems filename
// Output: None
// Return: Number of valid systems, or -1 if file cannot be opened
int countSystems(const char* systemsFileName)
{
   ifstream systemsFile;
   int systemCount = -1;
   char line[MAX_LINE_LEN];

   systemsFile.open(systemsFileName);
   if (systemsFile.is_open())
   {
      systemCount = 0;
      while (systemsFile.getline(line, MAX_LINE_LEN))
      {
         trimWhitespace(line);
         if (strlen(line) > 0)
         {
            systemCount = systemCount + 1;
         }
      }
      systemsFile.close();
   }

   return systemCount;
}

// Name:   loadSystemNames(...)
// Desc:   Loads non-empty trimmed system names into a dynamic array.
// Input:  systemsFileName, systemNames destination array, systemCount
// Output: Populated systemNames array
// Return: true if all names were loaded, false otherwise
bool loadSystemNames(const char* systemsFileName, char** systemNames,
                     int systemCount)
{
   ifstream systemsFile;
   bool loadedOk = false;
   char line[MAX_LINE_LEN];
   int index = 0;

   systemsFile.open(systemsFileName);
   if (systemsFile.is_open())
   {
      loadedOk = true;
      while (systemsFile.getline(line, MAX_LINE_LEN) && index < systemCount)
      {
         trimWhitespace(line);
         if (strlen(line) > 0)
         {
            systemNames[index] = copyCString(line);
            if (systemNames[index] != nullptr)
            {
               index = index + 1;
            }
            else
            {
               loadedOk = false;
            }
         }
      }

      if (index != systemCount)
      {
         loadedOk = false;
      }

      systemsFile.close();
   }

   return loadedOk;
}

// Name:   parseAccessLine(...)
// Desc:   Parses "system, user" into separate output C-strings.
// Input:  line text and output buffers
// Output: systemName and userName filled when parse succeeds
// Return: true if parsed valid system/user names, false otherwise
bool parseAccessLine(const char* line, char* systemName, char* userName)
{
   bool parsedOk = false;
   const char* comma = nullptr;
   int systemLen = 0;
   int i = 0;

   if (line != nullptr && systemName != nullptr && userName != nullptr)
   {
      systemName[0] = '\0';
      userName[0] = '\0';

      if (strlen(line) > 0)
      {
         comma = strchr(line, ',');
         if (comma != nullptr)
         {
            systemLen = static_cast<int>(comma - line);
            if (systemLen > MAX_LINE_LEN - 1)
            {
               systemLen = MAX_LINE_LEN - 1;
            }

            for (i = 0; i < systemLen; ++i)
            {
               systemName[i] = line[i];
            }
            systemName[systemLen] = '\0';

            strncpy(userName, comma + 1, MAX_LINE_LEN - 1);
            userName[MAX_LINE_LEN - 1] = '\0';

            trimWhitespace(systemName);
            trimWhitespace(userName);

            if (strlen(systemName) > 0 && strlen(userName) > 0)
            {
               parsedOk = true;
            }
         }
      }
   }

   return parsedOk;
}
