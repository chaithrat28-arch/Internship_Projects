#include<stdio.h>

int main()
{
    int var1 = 10;
    float var2 = 10.8;

    /*this 
    is
    multi line comment 
    */
    if(var1 == var2)
    {
        printf("var1 is equal to var2\n");
    }
    else
    {
        printf("var1 is not equal to var2\n");
    }
    //this is comment
    int i = 0;
    
    while( i != 5)
    {
        if(i == 2)
        {
            break;
        }
        i++;
    }

    return 0;
}