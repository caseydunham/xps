#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "Process.h"
#include "ProcessList.h"

std::vector<Process> ProcessList::scan() {
  std::vector<Process> procs;
  return procs;
}

bool ProcessList::is_all_digits(const std::string& s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) {
    ++it;
  }
  return !s.empty() && it == s.end();
}
