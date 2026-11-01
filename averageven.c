#include <stdio.h>;
#include <stdlib.h>;



int arr = {1,3,4,3,7};





void averageEvenPositions(int len,int *arr, double *avg)
{
    int sum =0;
    int count =0;

    
    for(int i =0; i < len; i+=2 )
    {
        sum += arr[i];
        count++;
    }
    *avg = ((double)sum /count);
}


int main()
{
    const int outerLen =100;
    const int innerLen = 100;
    int arr[outerLen][innerLen];
    double targetAvg;


    {
        int numGreater =0;
        double curAvg;
        int i =0;
        do
        {
            averageEvenPositions(innerLen,arr[i], &curAvg)
            if(curAvg> targetAvg)
            {
                numGreater++;
            }
            
            i++;
        } 
        while(i < outerLen );

        printf("%f", (double)numGreater/outerLen);
    }
}
