#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Get text
    char text[1000];
    printf("Text: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove newline
    int len = strlen(text);
    if (len > 0 && text[len - 1] == '\n')
    {
        text[len - 1] = '\0';
    }
    
    // Count things
    int letters = 0;
    int words = 0;
    int sentences = 0;
    
    // Check each character
    int i = 0;
    while (text[i] != '\0')
    {
        // Is letter
        if (isalpha(text[i]))
        {
            letters = letters + 1;
        }
        
        // Is space
        if (text[i] == ' ')
        {
            words = words + 1;
        }
        
        // Is sentence end
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences = sentences + 1;
        }
        
        i = i + 1;
    }
    
    // Add last word
    words = words + 1;
    
    // Calculate averages
    float L = (float)letters / words * 100;
    float S = (float)sentences / words * 100;
    
    // Calculate index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    // Round number
    int grade = round(index);
    
    // Print result
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    
    return 0;
}
