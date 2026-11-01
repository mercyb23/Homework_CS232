#include <stdio.h>

//Before compiling/running the program, try and identify
// at least 3 bugs. Write your guesses below:
//1.the argument for perfectsqr is a char not a int
//2.missing the starting point in the for loop headliner
//3. k= 0 should star with 1? t

int perfectSquare(int num);
int main(void){

    int start = 1, end = 500;
    //lists the perfect squares from start to end
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


int perfectSquare(int num){
    //int isPerfectSquare = 0;
    //int k = 0;

    for(int k = 1; k*k <= num; k++)
    {
      if(k*k == num)
      {
            return 1;
    }
        

    }

    return 0;

}
