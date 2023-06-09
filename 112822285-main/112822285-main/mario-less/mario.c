#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int heights = get_int("Heights:");
    while ((heights < 1) || (heights > 8))
    {
        heights = get_int("Heights:");
    }
    int heights_decrement = heights;
    for (int i = 1; i <= heights; ++i) //for each row
    {
        for (int j = 1; j < heights_decrement; ++j) //print spaces as many as heights minus row
        {
            printf(" ");
        }
        for (int x = 1; x <= i; ++x) //print # as many as the the number of i
        {
            printf("#");
        }
        printf("\n");
        --heights_decrement;
    }

}