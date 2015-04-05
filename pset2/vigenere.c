/*
 * vigenere.c
 *
 * pset2 2015 cs50x
 *
 * Gon MorVen
 *
 * Encrypts a message with Vigenere Cipher.
 * The user provides the encryption keyword and a message.
 * Outputs encrypted message.
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string key;
int keylen;
string text;
int textlen;
int i;
int j;

int main(int argc, string argv[])
{
    // Checks the number of command-line arguments
    // and quits if there are more or less than 2.
    if (argc != 2)
    {
        printf("Failed to provide 2 command-line arguments.\n");
        
        return 1;
    }
    
    key = argv[1];
    
    // Loops through the keyword's characters.
    for (i = 0, keylen = strlen(key); i < keylen; i++)
    {
    
        // Checks if character is alphabetic and quits if not.
        if (!isalpha(key[i]))
        {
            printf("Failed to provide an alphabetical keyword.\n");
            
            return 1;
        }
        
        // Converts the character's ASCII value to a 0 to 25 range.
        else if (islower(key[i]))
        {
            // If we have an 'a' in the key,
            // by subtracting the ASCII value of 'a'(97), 'a' becomes 0.
            key[i] = key[i] - 97;
        }
        else
        {
            // If we have an 'A' in the key,
            // by subtracting the ASCII value of 'A'(65), 'A' becomes 0.
            key[i] = key[i] - 65;
        }
    }
    
    // Prompts the user for a message to decrypt.
    text = GetString();
    
    // Loops through all of the message's characters.
    for (j = 0, i = 0, textlen = strlen(text); j < textlen; j++)
    {
        // Checks if character is alphabetic and lowercase.
        if (isalpha(text[j]) && islower(text[j]))
        {
            // Proceeds with the encryption, printing the result.
            // 97 is the value of 'a' in the ASCII table.
            // '% keylen' forces the keyword to loop itself
            // if it is smaller than the plaintext.
            printf("%c", (((text[j] - 97) + key[i % keylen]) % 26) + 97);
            i++;
        }
        
        // Checks if character is alphabetic and uppercase.
        else if (isalpha(text[j]) && isupper(text[j]))
        {
            // Proceeds with the encryption, printing the result.
            // 65 is the value of 'a' in the ASCII table.
            printf("%c", (((text[j] - 65) + key[i % keylen]) % 26) + 65);
            i++;
        }
        
        // Proceeds to print non-alphabetical characters, without encryption.
        else
        {
            printf("%c", text[j]);
        }
    }
    
    printf("\n");
    
    return 0;
}
