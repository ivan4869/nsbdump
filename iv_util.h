#ifndef IV_UTIL_H_
#define IV_UTIL_H_

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>
#include <share.h>

using std::pair;
using std::make_pair;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

namespace iv{
  inline void errexit(const string msg)
  {
    cerr << msg << endl;
    exit (-1);
    return;
  }
  inline void todo(const string msg)
  {
    cerr << msg << endl;
    return ;
  }
  int open_or_exit(const string fname, int flag, int pmod=_S_IREAD);
  void make_path(string filename, const char *drive=NULL, const char *dir=NULL, const char *ext=NULL);
  int write_file(string filename, const unsigned char *buff, unsigned len);
  int writetail(int fd, const void *buff, unsigned count);
  long long writef2f(int fd_dest, int fd_src);
  long long filecat(int fd_dest, int fd_src);
  int write(int fd, const void *buff, unsigned count);
  int read(int fd, void *buff, unsigned count);
  int close(int fd);
  inline long long lseek(int fd, long long offset, int seek_set=SEEK_SET){
    return _lseeki64(fd, offset, seek_set);
  }
  inline long long tell(int fd) { return _telli64(fd); }
  inline int eof(int fd) { return _eof(fd); }
}

#endif
