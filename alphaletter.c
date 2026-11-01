//
#include <stdio.h>;

const char arr[] = {'w','s','c','p'};
int len = sizeof(arr) /sizeof(arr[0]);



char first_alpha_letter(char *arr,int len)
{
    char letter = arr[0];
    for(int i =1; i < len; i++)
    {
        if(arr[i] <letter)
        {
            letter = arr[i];
        }
    }
    return letter;
}