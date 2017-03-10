#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define LENGTH 10000

int open_for_reading(char *);
int open_for_writing(char *);
void compute_and_count_unique_tokens(char *, char *);

int main(int argcount, char *clargs[])
{
  int input_file;
  char* filenames[LENGTH];

  char file_data[LENGTH];
  int read_length;
  
  input_file = open_for_reading(clargs[1]);
  
  while((read_length = read(input_file, file_data, LENGTH)) > 0)
  {
    /*filenames[count] = file_data;*/
  }
  
  close(input_file);
  
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
      /*printf("\ndata: %s\n", data);*/
    } 
    
    compute_and_count_unique_tokens(data, clargs[2]);
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

void compute_and_count_unique_tokens(char * fdata, char * fname)
{
  char * tokens = strtok(fdata, " ");
  char * token_data[LENGTH];
  char match_data[LENGTH];
  char match_count[LENGTH];
  
  int c = 0;
  while(tokens != NULL)
  {
    token_data[c] = tokens;
    c++;
    tokens = strtok(NULL, " ");
  }

  int fild = open_for_writing(fname);  

  for(int i = 0; i < c; i++)
  {
    int match = 0;
    strcat(match_data, token_data[i]);
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

    sprintf(match_count, " %d\n", match + 1);
    strcat(match_data, match_count);
    write(fild, match_data, sizeof(match_data));  
  }

  close(fild);
}

