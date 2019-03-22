#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct stat attributes;

void file_type(mode_t mode);
void access_privileges(mode_t mode);
void printAttributes();

int main(int argc, char const *argv[]) {

  char cwd[1000];
  int file;
  if (argc == 1) {
    if (getcwd(cwd, sizeof(cwd)) == 0) {
      return 1;
    }
    printf("%s\n", cwd);
    file = lstat(cwd, &attributes);
  }
  else{
    file = lstat(argv[1], &attributes);
  }

  if (file < 0) {
    return 1;
  }

  file_type(attributes.st_mode);
  access_privileges(attributes.st_mode);
  printAttributes();

  if (argc == 1) {
    printf("  %s\n", cwd);
  }
  else{
    printf("  %s\n", argv[1]);
  }

  return 0;
}

void file_type(mode_t mode){
  if(S_ISREG(mode)){
      printf("-");
  }
  else if(S_ISDIR(mode)){
      printf("d");
  }
  else if(S_ISBLK(mode)){
      printf("b");
  }
  else if(S_ISCHR(mode)){
      printf("c");
  }
  else if(S_ISFIFO (mode)){
      printf("f");
  }
  else if(S_ISLNK(mode)){
      printf("l");
  }
  /*else if(S_ISSOCK(mode)){
      printf("s");
  }   Causes Error*/
}

void access_privileges(mode_t mode){
  if(mode & S_IRUSR) printf("r"); else printf("-");
  if(mode & S_IWUSR) printf("w"); else printf("-");
  if(mode & S_IXUSR) printf("x"); else printf("-");
  if(mode & S_IRGRP) printf("r"); else printf("-");
  if(mode & S_IWGRP) printf("w"); else printf("-");
  if(mode & S_IXGRP) printf("x"); else printf("-");
  if(mode & S_IROTH) printf("r"); else printf("-");
  if(mode & S_IWOTH) printf("w"); else printf("-");
  if(mode & S_IXOTH) printf("x"); else printf("-");
}

void printAttributes(){
  printf("  %d", attributes.st_uid);
  printf("  %d", attributes.st_gid);
  printf("  %ld", attributes.st_size);
  printf("  %ld", attributes.st_mtime);
}
