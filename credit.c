#include <stdio.h>

int main(void)
{
    // Get number
    long number;
    printf("Number: ");
    scanf("%ld", &number);
    
    // Count length
    long copy = number;
    int length = 0;
    
    while (copy > 0)
    {
        copy = copy / 10;
        length = length + 1;
    }
    
    // Get first two digits
    long start = number;
    while (start >= 100)
    {
        start = start / 10;
    }
    
    // Luhn algorithm
    int sum = 0;
    long temp = number;
    int position = 0;
    
    while (temp > 0)
    {
        int digit = temp % 10;
        
        // Second digit (multiply)
        if (position % 2 == 1)
        {
            int product = digit * 2;
            
            // Two digits
            if (product > 9)
            {
                sum = sum + (product / 10) + (product % 10);
            }
            else
            {
                sum = sum + product;
            }
        }
        // First digit (add)
        else
        {
            sum = sum + digit;
        }
        
        position = position + 1;
        temp = temp / 10;
    }
    
    // Check sum
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    
    // Check card type
    // AMEX card
    if (length == 15 && (start == 34 || start == 37))
    {
        printf("AMEX\n");
    }
    // MASTERCARD card
    else if (length == 16 && start >= 51 && start <= 55)
    {
        printf("MASTERCARD\n");
    }
    // VISA card
    else if ((length == 13 || length == 16) && (start / 10 == 4))
    {
        printf("VISA\n");
    }
    // Invalid card
    else
    {
        printf("INVALID\n");
    }
    
    return 0;
}
