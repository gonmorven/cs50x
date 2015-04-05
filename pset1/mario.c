/*
 * mario.c
 *
 * pset1 2015 cs50x
 *
 * Gonçalo MorVen
 *
 * Recreates the half-pyramid from the game Super Mario Brothers.
 */
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    // asks user for input until input is over 0 and under 24.
    do
    {
        printf("Please give me a positive int, no greater than 23: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    // calculates and prints number of spaces and pounds for each row.
    for (int row = 0; row < height; row++)
    {
        // prints spaces.
        int space = row + 1;
        for (int i = space; i < height; i++)
        {
            printf(" ");
        }
        
        // prints pounds.
        int pound = row + 2;
        for (int n = pound; n > 0; n--)
        {
            printf("#");
        }
        
        printf("\n");
    }
}
