#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LENGTH 10000

int open_for_reading(char *);
int open_for_writing(char *);

int main(int argcount, char *clargs[])
{
  int input_file;
  int output_file;
  char* filenames[LENGTH];

  char file_data[LENGTH];
  int read_length;
  
  input_file = open_for_reading(clargs[1]);
  
  output_file = open_for_writing(clargs[2]);
  
  while((read_length = read(input_file, file_data, LENGTH)) > 0)
  {
    /*filenames[count] = file_data;*/
  }
  
  close(input_file);
  close(output_file);
  
  char * temp = strtok(file_data, "\n");

  int count = 0;
  while(temp != NULL)
  {
    filenames[count] = temp;
    count++;
    temp = strtok(NULL, "\n");
  }

  for(int i = 0; i < count; i++)
  {
    int f = open_for_reading(filenames[i]);
    char data[LENGTH];
    while((read_length = read(f, &data, LENGTH)) > 0)
    {
      printf("\ndata: %s\n", data);
    } 
    /*TODO: Create method to compute unique tokens and their count */
  }

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

