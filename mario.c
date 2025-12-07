#include <stdio.h>

int main(void)
{
    // 1. Prompt user for height until they give a number between 1 and 8
    int height;
    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height < 1 || height > 8);

    // 2. Loop from 1 to height to print each row
    for (int i = 1; i <= height; i++)
    {
        // Calculate spaces for left alignment
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        
        // Print left hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        // The gap is always 2 spaces
        printf("  ");
        
        // Print right hashes
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        // Move to next line
        printf("\n");
    }
}
