#include <string>

#include "Process.h"
#include "ProcessList.h"

int main(int argc, char* argv[]) {
  ProcessList pl;
  std::vector<Process> procs = pl.scan();
  std::cout << "PID" << " " << "CMD" << std::endl;
  for (std::vector<Process>::iterator it = procs.begin(); it != procs.end(); ++it) {
    std::cout << (*it).pid << " " << (*it).name << std::endl;
  }
  return 0;
}
