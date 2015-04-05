/*
 * initials.c
 *
 * pset2 2015 cs50x
 *
 * Gonçalo MorVen
 *
 * Prompts the user for his/her name
 * and prints the name's initials in uppercase.
 */

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // prompts user for name.
    string name = GetString();
    
    // loops through every character.
    for (int i = 0, namelen = strlen(name); i < namelen; i++)
    {
        // prints in uppercase if it is the first character
        // or any character after a space.
        if (i == 0 || name[i - 1] == ' ')
        {
            printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
    
    return 0;
}
