#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include "ServerSocket.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "not enough args" << std::endl;
    exit(1);
  }
  char *addr = argv[1];
  int port = atoi(argv[2]);
  pr::Socket sock;

  std::string cmd;
  std::string filename;
  int cmd_out;

  while (1) {
    std::cin >> cmd;
    if (cmd == "LIST") {
      sock.connect(addr, port);
      int fd = sock.getFD();
      cmd_out = 1;
      send(fd, &cmd_out, sizeof(int), 0);
      recv(fd, &cmd_out, sizeof(int), 0);
      char list[cmd_out + 1];
      recv(fd, &list, cmd_out * sizeof(list), 0);
      list[cmd_out] = '\0';
      std::cout << list << std::endl;
    } else if (cmd == "UPLOAD") {
      sock.connect(addr, port);
      int fd = sock.getFD();
      cmd_out = 2;
      send(fd, &cmd_out, sizeof(int), 0);

      std::cin >> filename;

      std::ifstream instream(filename, std::ifstream::in);
      instream.seekg(0, instream.end);
      int filesize = instream.tellg();
      instream.seekg(0, instream.beg);

      char filebuf[filesize];

      instream.read(filebuf, filesize);

      int s = filename.length();
      send(fd, &s, sizeof(int), 0);
      send(fd, filename.c_str(), filename.length(), 0);

      send(fd, &filesize, sizeof(int), 0);
      send(fd, &filebuf, filesize, 0);
      instream.close();

      // UPLOAD
    } else if (cmd == "DOWNLOAD") {
      sock.connect(addr, port);
      int fd = sock.getFD();
      cmd_out = 3;
      send(fd, &cmd_out, sizeof(int), 0);
      int len;
      std::string out = "./";

      std::cin >> filename;
      int s = filename.length();
      send(fd, &s, sizeof(int), 0);
      send(fd, filename.c_str(), filename.length(), 0);

      recv(fd, &len, sizeof(int), 0);
      char filename[len + 1];
      recv(fd, &filename, len, 0);
      filename[len] = '\0';
      out += filename;

      recv(fd, &len, sizeof(int), 0);
      char file[len + 1];
      recv(fd, &file, len, 0);
      file[len] = '\0';
      std::ofstream outstream(out, std::ofstream::out);
      outstream << file;
      outstream.close();
    } else if (cmd == "EXIT") {
      break;
    } else {
      std::cout << "unknown command" << std::endl;
    }
  }

  return 0;
}