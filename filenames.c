#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define LENGTH 10000

int open_for_reading(char *);
int open_for_writing(char *);

int main(int argcount, char *clargs[])
{
  int input_file;
  int output_file;

  char file_data[LENGTH];
  int read_length;
  
  input_file = open_for_reading(clargs[1]);
  
  output_file = open_for_writing(clargs[2]);
  
  while((read_length = read(input_file, &file_data, LENGTH)) > 0)
  {
    write(output_file, &file_data, read_length);
    printf("\n%s\n", file_data);

    int fd = open_for_reading(file_data);
    char data[LENGTH];
    while((read_length = read(fd, &data, LENGTH)) > 0)
    {
      printf("\n%s\n", data);
    } 
  }
  
  close(input_file);
  close(output_file);

  return EXIT_SUCCESS;
}

int open_for_reading(char * filename)
{
  int fd;
  fd = open(filename, O_RDONLY, 0644); 
  if(fd == -1)
  {
    printf("Unable to open: %s", filename);
    exit(EXIT_FAILURE);
  }
  return fd;
}

int open_for_writing(char * filename)
{
  int fd;
  fd = open(filename, O_WRONLY | O_CREAT, 0644);
  if(fd == -1)
  {
    printf("Unable to open: %s", filename);
    exit(EXIT_FAILURE);
  }
  return fd;
}

