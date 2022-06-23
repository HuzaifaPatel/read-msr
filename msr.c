#include <stdio.h>
#include <stdint.h>

#define MSR_PATH "/dev/cpu/0/msr"
#define MSR_ADDR 0xc0000080
#define MSR_SIZE 8

int main(void) {
  FILE *file = fopen(MSR_PATH, "rb");
  if (file == NULL) {
    fprintf(stderr, "[!] fopen failed\n");
    return 1;
  }

  if (fseek(file, MSR_ADDR, SEEK_SET) != 0) {
    fprintf(stderr, "[!] fseek failed\n");
    return 2;
  }

  uint8_t buffer[MSR_SIZE];

  size_t result = fread(buffer, 1, MSR_SIZE, file);
  if (result != MSR_SIZE) {
    fprintf(stderr, "[!] fread failed\n");
    return 3;
  }

  for (size_t i = 0; i < MSR_SIZE; ++i) {
    printf("%x ", buffer[i]);
  }
  printf("\n");

    return 0;
}

