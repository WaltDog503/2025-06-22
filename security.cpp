#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "useraccesslist.h"

using namespace std;

#define RDBUFSIZE 100

int main(int argc,char* argv[])
{
    if (argc != 3) {
	cout << "Usage: " << argv[0] << " <access log file> <systems file>" << endl;
	return(0);
    }

    const char* accessDataFile = argv[1];
    const char* systemsFile = argv[2];

    // This program doesn't assume a specific number of systems or the names
    // of these systems. Instead, that data is provided in a data file. This
    // code here reads the list of systems and create an array of
    // UserAccessList objectsAccessTracker objects -- one per system.
    //
    // In order for this to work, you will need to create a class called
    // "UserAccessList" and make sure that it has a constructor that takes in
    // a char*.
    ifstream systemsIn(systemsFile);
    int numSystems;
    systemsIn >> numSystems;
    systemsIn.get();
    UserAccessList** allLists = new UserAccessList*[numSystems];
    for (int i=0;i<numSystems;i++)
    {
	char sys[RDBUFSIZE];
	systemsIn.getline(sys,RDBUFSIZE);
	allLists[i] = new UserAccessList(sys);
    }
    systemsIn.close();

    // After reading in the systems, we will now read in all the access logs
    // and insert these accesses into the UserAccessList that corresponds to
    // the system being accessed. The first line of the logfile tells us how
    // many entries are in that logfile. Each line of the logfile contains a
    // system name and the person accessing it. These two values are separated
    // by a comma. This code here will read the system name and person name
    // then it will loop over all the UserAccessLists (in the array created
    // above) and give each UserAccessList a chance to enter that data. A
    // UserAccessList will only enter the data if it is the right one. That
    // is, the system name matches the name in that log entry.
    ifstream accessDataIn(accessDataFile);
    int numEntries;
    accessDataIn >> numEntries;
    accessDataIn.get();
    for (int i=0;i<numEntries;i++)
    {
	char sys[RDBUFSIZE];
	char who[RDBUFSIZE];

	accessDataIn.getline(sys,RDBUFSIZE,',');
	accessDataIn.get(); // eat the extra space
	accessDataIn.getline(who,RDBUFSIZE);

	for (int j=0;j<numSystems;j++)
	{
	    allLists[j]->addUser(sys,who);
	}
    }
    accessDataIn.close();

    // Now that all the data has been read in, it is time to ask each list to
    // print a report. Make sure to study the example output files to
    // understand the contents and format of the report.
    for (int j=0;j<numSystems;j++)
    {
	allLists[j]->printReport();
    }

    // The last step is to clean up memory to avoid memory leaks. We need to
    // delete each of the UserAccessList objects that were created in the
    // array above. Calling delete on each object will call that object's
    // destructor. After all the objects have been deleted, we have to delete
    // the array itself. Note that your UserAccessList class, which contains a
    // linked list, will need to have a destructor that cleans up its own
    // memory.
    for (int j=0;j<numSystems;j++)
    {
	delete allLists[j];
    }
    delete [] allLists;

    return 0;
}
