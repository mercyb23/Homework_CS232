#include <stdio.h>
#include <string.h>

//Before compiling/running the program, try and identify
// at least 2 bugs. Write your guesses below:
//1. the strlen doesnt get the length of the array 
//but of each object in the array
//2. the putchar on 23 uses "" instead of ''


int main(void){
  char name[] = "Timothy";

  printf("Hello %s\n", name);

  printf("Your name backwards is:\n");
  for(int j = strlen(name)-1; j >= 0; j--)
  {
    putchar(name[j]);

  }
  
  putchar('\n');

  return 0;
}
