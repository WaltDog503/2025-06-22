# CS162: Computer Science II
## Algorithm Design Document
### Programming Project: Security

---

## 1. zyBooks

Add your zyBooks screenshots below.

Required completion levels:
- Assigned zyLabs complete (22.9 and 22.10)
- Challenge Activity at least 70%
- Participation Activity at least 80%

**Challenge and Participation % screenshot:**  
`<paste Challenge & Participation screenshot here>`

**Assigned zyLabs completion screenshot (22.9 and 22.10):**  
`<paste assigned zyLabs completion screenshot here>`

---

## 2. Program Description

This program reads a systems file and an access log file to track how often
each user accesses each ship system. The first line of each file contains a
count, and then the program reads exactly that many records.

The program creates a dynamic array of `UserAccessList` objects (one list per
system). Each list is a linked list of `UserAccess` entries that store
`user,count` data, and each list prints a formatted report with Top, Second,
and All user access totals and percentages.

---

## 3. Algorithmic Design

### 3a. Input Variables

| Variable Name | Data Type | Description |
|---|---|---|
| `argc` | integer | Number of command-line arguments. |
| `argv` | array of C-strings (`char*[]`) | Command-line argument values. |
| `accessDataFile` | C-string (`const char*`) | Access log filename (`argv[1]`). |
| `systemsFile` | C-string (`const char*`) | Systems filename (`argv[2]`). |
| `systemsIn` | input file stream | Input stream for systems file. |
| `accessDataIn` | input file stream | Input stream for access file. |
| `numSystems` | integer | Number of systems (first line of systems file). |
| `numEntries` | integer | Number of access records (first line of access file). |
| `sys` | character array (`char[RDBUFSIZE]`) | System name buffer while reading lines. |
| `who` | character array (`char[RDBUFSIZE]`) | User name buffer while reading lines. |

**Input data structures**
- `allLists`: dynamic array of `UserAccessList*`, size `numSystems`
- Each `UserAccessList` contains a linked list of `UserNode`

### 3b. Output Variables

| Variable Name | Data Type | Description |
|---|---|---|
| Console report lines | text output | Formatted report for each system. |
| `mSystem` | dynamic C-string (`char*`) | System name stored in each `UserAccessList`. |
| `topUser` | C-string (`const char*`) | User with highest count for one system. |
| `secondUser` | C-string (`const char*`) | User with second-highest count. |
| `count` | integer | Access count for a user. |
| `percent` | integer | Percent of system accesses by user. |

### 3c. Calculations

1. **Total accesses per system**
   - When a log record matches a list's system:
   - `mTotalAccesses = mTotalAccesses + 1`

2. **Per-user count**
   - If user already exists in linked list:
   - `userCount = userCount + 1`
   - Otherwise create a new `UserAccess` node with initial count of `1`

3. **Percentage in report**
   - `percent = (count * 100) / mTotalAccesses`
   - Integer division is used (truncated percent)

4. **Top and Second users**
   - Traverse linked list and track highest and second-highest counts

### 3d. Logic (Pseudocode)

```text
MAIN
  if argc != 3
    print usage message
    return

  accessDataFile = argv[1]
  systemsFile = argv[2]

  open systems file
  read numSystems
  ignore newline

  allocate allLists as dynamic array of UserAccessList* with numSystems
  loop i from 0 to numSystems - 1
    read one system line into sys
    allLists[i] = new UserAccessList(sys)
  close systems file

  open access file
  read numEntries
  ignore newline

  loop i from 0 to numEntries - 1
    read system text into sys up to comma
    consume one space after comma
    read remaining user text into who

    loop j from 0 to numSystems - 1
      allLists[j]->addUser(sys, who)
  close access file

  loop j from 0 to numSystems - 1
    allLists[j]->printReport()

  loop j from 0 to numSystems - 1
    delete allLists[j]
  delete[] allLists
END MAIN
```

```text
UserAccessList::addUser(systemName, user)
  if systemName does not match this list's mSystem
    do nothing
  else
    mTotalAccesses++

    search linked list for user
    if found
      increment existing count
    else
      create new UserAccess(user)
      create new UserNode(pointer to new UserAccess)
      append node at end of linked list
```

```text
UserAccessList::printReport()
  print "System: <name>"

  traverse list once to determine top and second users by count
  print Top and Second lines

  print "All:"
  traverse list again
    compute percent = (count * 100) / mTotalAccesses
    print "user count (percent%)"
```

---

## 4. Notes

- Export this document as PDF and submit with project files.
- Insert screenshots before final export.
