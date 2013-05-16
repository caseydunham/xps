#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "Process.h"
#include "ProcessList.h"

std::vector<Process> ProcessList::scan() {
  std::vector<Process> procs;
  DIR *procDir = 0;
  procDir = opendir("/proc");
  if (procDir == NULL) {
    return procs;
  }

  struct dirent *dirEnt;

  while ((dirEnt = readdir(procDir)) != NULL) {
    std::string name = "/proc/";
    name += dirEnt->d_name;

    struct stat statBuf;
    if (stat(name.c_str(), &statBuf) == -1) {
      continue;
    }

    if (statBuf.st_mode & S_IFDIR) {
      if (is_all_digits(dirEnt->d_name)) {
        Process process;
        process.pid = atoi(dirEnt->d_name);
        std::string path = name + std::string("/cmdline");
        int fd = open(path.c_str(), O_RDONLY);
        if (fd != -1) {
          char buf[1024];
          memset(buf, '\0', sizeof(buf));
          int n;
          if ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
            process.name = buf;
            procs.push_back(process);
          } else if (n == 0) {
            path = name + std::string("/status");
            int fd2 = open(path.c_str(), O_RDONLY);
            if (fd2 != -1) {
              memset(buf, '\0', sizeof(buf));
              if ((n = read(fd2, buf, sizeof(buf) - 1)) > 0) {
                char *p = buf;
                while (*p) {
                  if (*p == '\n') {
                    *p = '\0';
                    break;
                  }
                  p++;
                }
                if ((p = strstr(buf, "Name:"))) {
                  p += strlen("Name:");
                  while (*p && isspace(*p)) {
                    p++;
                  }
                } else {
                  p = buf;
                }
                process.name = p;
                procs.push_back(process);
              }
              close(fd2);
            }
          }
          close(fd);
        }
      }
    }
  }

  closedir(procDir);
  return procs;
}

bool ProcessList::is_all_digits(const std::string& s) {
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) {
    ++it;
  }
  return !s.empty() && it == s.end();
}
