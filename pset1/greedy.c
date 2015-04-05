/*
 * greedy.c
 *
 * pset1 2015 cs50x
 *
 * By: Gon MorVen
 *
 * Asks user how much change is owed and prints
 * the minimum number of coins needed to make the change.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define QUARTER 25;
#define DIME 10;
#define NICKLE 5;

int main(void)
{
    float change;
    int cents;
    int quarter_c;
    int dime_c;
    int nickle_c;
    int coins;
    int left;

    // asks user for a positive value until user complies.
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change <= 0);
    
    // converts the input value from a float to an int (dollars to cents).
    cents = round(change * 100);
    
    // calculates number or quarters needed.
    quarter_c = cents / QUARTER;
    left = cents % QUARTER;
    
    // calculates number or dimes needed.
    dime_c = left / DIME;
    left = left % DIME;
    
    // calculates number or nickles needed.
    nickle_c = left / NICKLE;
    left = left % NICKLE;
    
    // calculates the total number of coins used.
    coins = quarter_c + dime_c + nickle_c + left;
    
    // prints the number of coins used.
    printf("%d\n", coins);
}
