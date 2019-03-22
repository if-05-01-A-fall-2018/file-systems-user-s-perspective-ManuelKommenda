#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

struct stat attributes;

void file_type(mode_t mode);
void access_privileges(mode_t mode);
void printAttributes();

int main(int argc, char const *argv[]) {

  if(argc != 2) return 1;

  int file = lstat(argv[1], &attributes);
  if (file < 0) {
    return 1;
  }
  printf("--------------- %s ---------------\n", argv[1]);

  file_type(attributes.st_mode);
  access_privileges(attributes.st_mode);
  printAttributes();

  return 0;
}

void file_type(mode_t mode){
  printf("File type          : ");
  if(S_ISREG(mode)){
      printf("Regular file");
  }
  else if(S_ISDIR(mode)){
      printf("Directory");
  }
  else if(S_ISBLK(mode)){
      printf("Block device");
  }
  else if(S_ISCHR(mode)){
      printf("Character device");
  }

  printf("\n");
}

void access_privileges(mode_t mode){
  printf("Access privileges  : ");

  if(mode & S_IRUSR) printf("r"); else printf("-");
  if(mode & S_IWUSR) printf("w"); else printf("-");
  if(mode & S_IXUSR) printf("x"); else printf("-");
  if(mode & S_IRGRP) printf("r"); else printf("-");
  if(mode & S_IWGRP) printf("w"); else printf("-");
  if(mode & S_IXGRP) printf("x"); else printf("-");
  if(mode & S_IROTH) printf("r"); else printf("-");
  if(mode & S_IWOTH) printf("w"); else printf("-");
  if(mode & S_IXOTH) printf("x"); else printf("-");

  printf("\n");
}

void printAttributes(){
  printf("inode-Number       : %ld\n", attributes.st_ino);
  printf("Device numbers     : dev = %ld; rdev = %ld\n", attributes.st_dev, attributes.st_rdev);
  printf("Links count        : %ld\n", attributes.st_nlink);
  printf("UID                : %d\n", attributes.st_uid);
  printf("GID                : %d\n", attributes.st_gid);
  printf("File size          : %ld\n", attributes.st_size);
  printf("Last access        : %ld\n", attributes.st_atime);
  printf("Last modification  : %ld\n", attributes.st_mtime);
  printf("Last inode change  : %ld\n", attributes.st_ctime);
}
