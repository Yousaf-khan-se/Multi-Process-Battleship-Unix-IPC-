#ifndef PIPEMANAGER_H
#define PIPEMANAGER_H

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#define R 0
#define W 1

using namespace std;

class ProcessCommunication {
  int *pipe;
  size_t buffSize;
  char *buffer;

public:
  ProcessCommunication(int pipe[], size_t buffSize = 2048)
      : pipe(pipe), buffSize(buffSize), buffer(new char[buffSize]) {}

  ~ProcessCommunication() {
    delete[] buffer;
    close(pipe[0]);
    close(pipe[1]);
  }

  ProcessCommunication(const ProcessCommunication &) = delete;
  ProcessCommunication &operator=(const ProcessCommunication &) = delete;

  string Read(size_t bytes = 0) {
    if (bytes == 0) {
      bytes = buffSize;
    }
    ssize_t bytesRead = read(pipe[R], buffer, bytes - 1);
    if (bytesRead == -1) {
      cerr << "Unable to Read " << endl;
      return "error";
    }
    buffer[bytesRead] = '\0';
    return string(buffer);
  }

  ssize_t Write(const string &msg) {
    ssize_t bytesWritten = write(pipe[W], msg.c_str(), msg.length());
    if (bytesWritten == -1) {
      cerr << "Unable to Read " << endl;
      return bytesWritten;
    }
    return bytesWritten;
  }
};

#endif