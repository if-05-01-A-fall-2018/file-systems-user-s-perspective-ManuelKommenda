#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define size 50

int main(int argc, char const *argv[]) {
  int to_copy_file, destination_file;
  char buffer[size];
  if(argc != 3) return 1;

  to_copy_file = open(argv[1], O_RDONLY);
  destination_file = open(argv[2], O_WRONLY);

  if (to_copy_file < 0) {
    printf("The file you want to cpy does not exist\n");
    return 1;
  }

  if (destination_file < 0) {
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    destination_file = creat(argv[2], mode);
    open(argv[2], O_WRONLY);
    printf("Created file\n");
  }

  printf("Writing\n");
  int bytesRead;
  do {
    bytesRead = read(to_copy_file, buffer, size);
    write(destination_file, buffer, bytesRead);
  } while (bytesRead == size);

  close(to_copy_file);
  close(destination_file);
  return 0;
}
