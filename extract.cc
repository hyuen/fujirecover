#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main(void) {
  int fd = open("usb.img", O_RDONLY);
  ssize_t s;
  struct stat sb;
  fstat(fd, &sb);
  cout << sb.st_size << endl;
  char* addr;
  auto SZ = sb.st_size; // 1000000L;
  
  addr = mmap(NULL, SZ, PROT_READ, MAP_PRIVATE, fd, 0);

  auto prev = 0;
  auto ct = 0;
  for (int i=0; i < SZ; i++) {
    if (strncmp(addr+i, "FUJIFILMCCD-RAW", 15) == 0){
      cout << "found " << i << " " << prev << " " << i - prev << endl;
      if (prev != 0) {
	cout << "writing " << ct << endl;
	int ofd = open(("IMG_"+ to_string(ct) + ".RAW").c_str(), O_CREAT| O_WRONLY);
	write(ofd, addr+i, i-prev);
	close(ofd);
	ct++;
      }
      prev = i;
    }
    //cout << i << " " << *(char*)(addr+i) << endl;
  }
  

  
  return 0;
}
