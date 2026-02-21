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

This program reads two input files: one file containing ship system names and one file containing access log records. It tracks how many times each user accessed each system by storing one linked list per system, where each node contains a user name and that user’s access count for that system.

After all access log entries are processed, the program prints a report for each system. Each report shows the top accessor, the second accessor, and all users with their counts and percentage of total accesses for that system.

---

## 3. Algorithmic Design

### 3a. Input Variables

| Variable Name | Data Type | Description |
|---|---|---|
| `argc` | integer | Number of command-line arguments. |
| `argv` | array of C-strings (`char*[]`) | Command-line argument values. |
| `argv[1]` | C-string (`char*`) | Access log filename provided by user. |
| `argv[2]` | C-string (`char*`) | Systems filename provided by user. |
| `accessFile` | input file stream | Stream used to read access records. |
| `systemsFile` | input file stream | Stream used to read system names. |
| `line` | string | Current line being read from file. |
| `system` | string | Parsed system name from a record. |
| `user` | string | Parsed user name from a record. |
| `commaPos` | integer (`size_t`) | Position of comma separator in access line. |
| `systemCount` | integer | Number of non-empty systems in systems file. |

**Input data structures**
- `systemNames`: dynamic array of C-strings (`char**`)
- `systems`: dynamic array of `UserAccessList*`

### 3b. Output Variables

| Variable Name | Data Type | Description |
|---|---|---|
| Console report lines | string output | Formatted report output for each system. |
| `mSystem` | dynamic C-string (`char*`) | System name shown in report. |
| `topUser` | C-string (`const char*`) | User with the highest count. |
| `secondUser` | C-string (`const char*`) | User with second-highest count. |
| `count` | integer | Number of accesses for a user. |
| `percent` | integer | Percentage of total system accesses by user. |

### 3c. Calculations

1. **System count**
   - `systemCount = number of non-empty lines in systems file`

2. **Total accesses for a system**
   - When an access record belongs to a system list:  
     `mTotalAccesses = mTotalAccesses + 1`

3. **Per-user count**
   - If user is already in linked list:  
     `userCount = userCount + 1`
   - Otherwise, create a new user entry with count `1`.

4. **Percentage for report output**
   - `percent = (count * 100) / mTotalAccesses`  
   (integer division; truncated percentage)

5. **Top and second top accessors**
   - Traverse the linked list and compare counts to track largest and second largest values.

### 3d. Logic (Pseudocode)

```text
MAIN
  if argc is not 3
    print usage message
    stop

  open access file using argv[1]
  if open fails
    print error
    stop

  open systems file using argv[2]
  if open fails
    print error
    stop

  systemCount = 0
  for each line in systems file
    remove leading/trailing whitespace
    if line is not empty
      systemCount++

  if systemCount is 0
    stop

  reopen systems file

  allocate dynamic array systemNames of size systemCount
  read systems file again
    for each non-empty system line
      allocate C-string copy of system name
      store in systemNames array

  allocate dynamic array systems of size systemCount
  for i = 0 to systemCount - 1
    systems[i] = new UserAccessList(systemNames[i])

  for each line in access file
    remove leading/trailing whitespace
    if line is empty, continue
    find comma
    if comma missing, continue

    parse left side as system
    parse right side as user
    trim both parsed values
    if either is empty, continue

    for i = 0 to systemCount - 1
      systems[i]->addUser(system, user)

  for i = 0 to systemCount - 1
    systems[i]->printReport()

  for i = 0 to systemCount - 1
    delete systems[i]
    delete[] systemNames[i]

  delete[] systems
  delete[] systemNames
END MAIN
```

```text
UserAccessList::addUser(systemName, user)
  if systemName does not match mSystem
    return

  mTotalAccesses++

  traverse linked list from mHead
    if current node user matches user
      increment count
      return

  create new UserAccess for user
  create new UserNode with that UserAccess
  append node to end of linked list
```

```text
UserAccessList::printReport()
  print system header

  traverse linked list to determine top and second users
  print top and second names (or "(none)")

  print all user entries in list order:
    percent = (count * 100) / mTotalAccesses
    print user name, count, and percent
```

---

## 4. Notes

- This document should be exported as PDF and submitted with project files.
- Include screenshots before final export.
