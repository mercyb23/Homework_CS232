


void nextFibonacci(int *arr)
{
        arr[2]= arr[0]+arr[1];
    
}


int main()
{



    const int n = 25;
    int fib[n];
    int i;
    fib[0]=0;
    fib[1]=1;
    for(i =2 ;i <n;i++)
        nextFibonacci(&fib[i-2]);

    return 0;

}



