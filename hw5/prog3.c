#include <stdio.h>

//Before compiling/running the program, try and identify
// at least 3 bugs. Write your guesses below:
//1.the argument for perfectsqr is a char not a int
//2.missing the starting point in the for loop headliner
//3. k= 0 should star with 1? t
//perfectsqr called in main before being defined
int perfectSquare(int num);
int main(void){

    int start = 1, end = 500;
    
    for(int i = start; i <= end; ++i)
    {
        if(perfectSquare(i))
        {
            printf("%d  ", i);
        }
    }
    printf("\n");

    return 0;
}

//has the char argument when returning an int
int perfectSquare(int num){
   //starts k at 0 and crashes the program
    //isperfectsqr get overwritten and gets set back to 0
    for(int k = 1; k*k <= num; k++)
    {
        /*num/k ==k gets rid of the remainder
         *and return the num even if its not a perfectsqr
         */
      if(k*k == num)
      {
            return 1;
    }
        

    }

    return 0;

}
