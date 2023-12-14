#include <dirent.h>
#include <signal.h>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#include "ServerSocket.h"


int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cout << "not enough agrs" << std::endl;
    exit(1);
  }
  int port = atoi(argv[1]);
  char* path = argv[2];
  int fd;

  pr::ServerSocket ss(port);
  pr::Socket sc;

  std::string out;
  std::string name;
  DIR* dirp;
  struct dirent* dp;

  while (true) {
    sc = ss.accept();
    fd = sc.getFD();
    int cmd;
    int len;

    recv(fd, &cmd, sizeof(cmd), 0);
    if (cmd == 1) {  // LIST
      dirp = opendir(path);
      while ((dp = readdir(dirp)) != NULL) {
        out += dp->d_name;
        out += "\n";
      }
      closedir(dirp);
      len = out.length();
      write(fd, &len, sizeof(int));
      write(fd, out.c_str(), out.length());
    }
    if (cmd == 2) {
      recv(fd, &len, sizeof(int), 0);
      char filename[len + 1];
      recv(fd, &filename, len, 0);
      filename[len] = '\0';
      out = path;
      out += "/";
      out += filename;

      recv(fd, &len, sizeof(int), 0);
      char file[len + 1];
      recv(fd, &file, len, 0);
      file[len] = '\0';
      std::ofstream outstream(out, std::ofstream::out);
      outstream << file;
      outstream.close();
    }
    if (cmd == 3) {
      recv(fd, &len, sizeof(int), 0);
      char filename[len + 1];
      recv(fd, &filename, len, 0);
      filename[len] = '\0';
      std::ifstream instream(filename, std::ifstream::in);
      instream.seekg(0, instream.end);
      int filesize = instream.tellg();
      instream.seekg(0, instream.beg);

      char filebuf[filesize];

      instream.read(filebuf, filesize);

      int s = strlen(filename);
      write(fd, &s, sizeof(int));
      write(fd, &filename, s);

      write(fd, &filesize, sizeof(int));
      write(fd, &filebuf, filesize);
      instream.close();
      // DOWNLOAD
    }
    sc.close();
  }
  ss.close();

  return 0;
}