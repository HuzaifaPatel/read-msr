#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MSR_PATH "/dev/cpu/0/msr"
// #define MSR_PATH "/home/huzi/Desktop/test.txt"
#define MSR_ADDR 0xc0000080
// #define MSR_ADDR 0x00
#define MSR_SIZE 8



int read_msr(){
  int fd = open(MSR_PATH, O_RDWR);

  if(fd == -1){
    printf("Open error\n");
    return 1;
  }

  if(lseek(fd, MSR_ADDR, SEEK_SET) == -1){
    printf("lseek Failed\n");
    return 2;
  }

  uint8_t buffer[MSR_SIZE];

  size_t result = read(fd, buffer, MSR_SIZE);

  if(result == -1){
    printf("read error\n");
    return 3;
  }

  for(int i = 0; i < MSR_SIZE; ++i){
    printf("%x ", buffer[i]);
  }

  printf("\n");

}




int write_msr(){
  int fd = open(MSR_PATH, O_WRONLY);

  if(fd == -1){
    printf("Open error\n");
    return 1;
  }

  if(lseek(fd, MSR_ADDR, SEEK_SET) == -1){
    printf("lseek Failed\n");
    return 2;
  }


  char input[MSR_SIZE];


  input[0] = 0x00;
  input[1] = 0x00;
  input[2] = 0x0d;
  input[3] = 0x00;
  input[4] = 0x00;
  input[5] = 0x00;
  input[6] = 0x00;
  input[7] = 0x00;

  // write(fd, input, MSR_SIZE);
  if(pwrite(fd, input, sizeof(input), MSR_ADDR) == -1){
    printf("write error %s\n", strerror(errno));
  }

  close(fd);
}





int main() {
	write_msr();
	return 0;
}

