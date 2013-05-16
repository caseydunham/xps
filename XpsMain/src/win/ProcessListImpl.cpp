#pragma comment(lib, "Psapi.lib") 

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include <Windows.h>
#include <Psapi.h>

#include "Process.h"
#include "ProcessList.h"

std::vector<Process> ProcessList::scan() {
  std::vector<Process> procs;
  DWORD processes[1024], cbNeeded;

  if (!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
    return procs;    
  }

  // Calculate how many process identifiers were returned.
  DWORD processCount = cbNeeded / sizeof(DWORD);

  for (unsigned int i = 0; i < processCount; i++) {
    DWORD pid = processes[i];
    if (pid == 0) {
      continue;
    }

    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (processHandle == NULL) {
      continue;
    }

    HMODULE moduleHandle;
    DWORD cbNeeded;

    if (EnumProcessModules(processHandle, &moduleHandle, sizeof(moduleHandle), &cbNeeded)) {
      TCHAR processName[MAX_PATH] = TEXT("<unknown>");
      GetModuleBaseName(processHandle, moduleHandle, processName, sizeof(processName) / sizeof(TCHAR));
      Process process;
      process.name = processName;
      process.pid = pid;
      procs.push_back(process);
    } 

    CloseHandle(moduleHandle);	
    CloseHandle(processHandle);
  }

  return procs;
}
