#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LENGTH 10000

int open_for_reading(char *);
int open_for_writing(char *);
void compute_and_count_unique_tokens(char *);

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
    
    compute_and_count_unique_tokens(data);
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

void compute_and_count_unique_tokens(char * fdata)
{
  printf("\nfrom compute method, fdata: %s\n", fdata);
  char * tokens = strtok(fdata, " ");
  char * token_data[LENGTH];
  
  int c = 0;
  while(tokens != NULL)
  {
    token_data[c] = tokens;
    printf("\ntoken_data[%d]: %s\n", c, token_data[c]);
    c++;
    tokens = strtok(NULL, " ");
  }
  
  for(int i = 0; i < c; i++)
  {
    int match = 0;
    printf("\n%s ", token_data[i]);
    for(int j = 0; j < c; j++)
    {
      if( (strcmp(token_data[i], token_data[j]) == 0) )
      {
        if(j != i)
        {
          match++;
        }
      }
    }
    printf("%d \n", match + 1);
  }
}

