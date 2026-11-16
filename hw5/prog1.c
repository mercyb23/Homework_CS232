#include <stdio.h>

//Before compiling/running the program, try and identify
// at least 3 bugs. Write your guesses below:
//1. line 10 height intialized to 0 not with&area
//2. getchar gets a character and not an integer
//3. line 24 doesnt have a %d for the format

int main (void){
  int width=0, area=0, height = 0;

  printf("Please enter width of rectangle (< 10):\n");
  width = getchar()- '0';
  getchar();
 
  printf("Please enter height of rectangle (< 10):\n");
  height = getchar() - '0';
  getchar();

  for(int i = 0; i < height; i++){
    area += width;
  }

  printf("The area of the rectangle is: %d\n", area);

  return 0;
}



