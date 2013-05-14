#ifndef PROCESS_H_
#define PROCESS_H_

#include <vector>

class Process;

class ProcessList {
  public:
    std::vector<Process> scan();
  private:
    bool is_all_digits(const std::string& s);
};

#endif /* PROCESS_H_ */
