#include <stdio.h>
#include <string.h>

//Before compiling/running the program, try and identify
// at least 2 bugs. Write your guesses below:
//1. the strlen doesnt get the length of the array 
//but of each object in the array
//2. the putchar on 23 uses "" instead of '' cool


int main(void){
  //not correctlt intialized as string 
  char name[] = "Timothy";

  printf("Hello %s\n", name);

  printf("Your name backwards is:\n");
  //it goes to 7 to 1 instead of 6 to 0 for the index
  //j>0 stops rights before it get the first character of the string
  for(int j = strlen(name)-1; j >= 0; j--)
  {
    putchar(name[j]);

  }
  //used the wrong quotes "" instead of ''
  putchar('\n');

  return 0;
}
