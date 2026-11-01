int main(int argc, char* argv[])
{
    const int maxlength = 500;
    char joinedStr[maxlength+1];

    int len =0;
    joinedStr[0] = '\0';
    
    for(int i =1; i< argc && len <maxlength;i++)
    {
        strncat(joinedStr,argv[i],maxlength-len)
        len = strlen(joinedStr);
        
    }

}