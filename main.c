#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

int main() {
  printf("Am parent process with PID: %d and PPID: %d!\n", getpid(), getppid());
  int g;
  int f = fork(); //child process returns 1 to parent
  // u a parent process boi
  if (f != 0){
    f = fork();
    //printf("PID: %d f: %d\n", getpid(), f);
  }
  // child function
  if (f == 0) {
    printf("PID: %d PPID: %d\n", getpid(), getppid());
    int sleep_time;
    int file = open("/dev/random", O_RDONLY);
    read(file, &sleep_time, sizeof(int));
    close(file);
    sleep_time = (abs(sleep_time) % 16) + 5;
    // printf("Sleep time: %d\n", sleep_time);
    sleep(sleep_time);
    printf("I woke up, finished!\n");
    return sleep_time;
  }
  // parent function
  if (f != 0){
    int status;
    int child_id = wait(&status);
    // not sure what to do about the status code being multiples of 256
    printf("Finished child's pid: %d It was asleep for %d seconds.\n", child_id, status/256);
    printf("Parent is done!\n");
  }
  // printf("Exited as process %d with parent %d\n", getpid(), getppid());
  return 0;
}
