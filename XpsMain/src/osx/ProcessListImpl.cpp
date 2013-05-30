#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include <errno.h>
#include <sys/sysctl.h>

#include "Process.h"
#include "ProcessList.h"

std::vector<Process> ProcessList::scan() {
  std::vector<Process> procs;
  kinfo_proc *procList = NULL;
  size_t procCount = 0;
  size_t length = 0;
  kinfo_proc * result = NULL;
  
  static const int name[] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
  
  int err = -1;
  bool done = false;
  
  do {
    err = sysctl((int *) name, (sizeof(name) / sizeof(*name) - 1), NULL, &length, NULL, 0);
    if (err == -1) {
      err = errno;
    }
    
    if (err == 0) {
      result = (kinfo_proc *) malloc(length);
      if (result == NULL) {
        err = ENOMEM;
      }
    }
    
    if (err == 0) {
      err = sysctl((int *) name, (sizeof(name) / sizeof(*name)) - 1, result, &length, NULL, 0);
      if (err == -1) {
        err = errno;
      }
      if (err == 0) {
        done = true;
      } else if (err == ENOMEM) {
        free(result);
        result = NULL;
        err = 0;
      }
    }
  } while (err == 0 && !done);
  
  if (err != 0 && result != NULL) {
    free(result);
    result = NULL;
  }
  
  procList = result;
  if (err == 0) {
    procCount = length / sizeof(kinfo_proc);
  }
  
  if (procList) {
    for (int i = 0; i < procCount; i++) {
      Process p;
      p.pid = procList[i].kp_proc.p_pid;
      p.name = procList[i].kp_proc.p_comm;
      procs.push_back(p);
    }
    free(procList);
  }
  return procs;
}
