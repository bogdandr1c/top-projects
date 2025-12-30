#include <cs50.h>
#include <math.h>
#include <stdio.h>

float grade(string text);

int main(void)
{
    // Get a text from the user
    string text = get_string("Text: ");

    float index = grade(text);
    int INDEX = round(index);

    if (INDEX < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (INDEX >= 16)
    {
        printf("Grade 16+\n");
    }
    else
        printf("Grade %d\n", INDEX);
}

float grade(string text)
{
    int cntL = 0;
    int cntW = 0;
    int cntS = 0;
    int i = 0;

    while (text[i] != '\0')
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            cntL += 1;
        }
        if (text[i] == ' ' ||
            ((text[i] == '.' || text[i] == '!' || text[i] == '?') && text[i + 1] == '\0'))
        {
            cntW += 1;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            cntS += 1;
        }
        i++;
    }

    float avgL = (cntL * 100) / (float) cntW;
    float avgS = (cntS * 100) / (float) cntW;

    float index = 0.0588 * avgL - 0.296 * avgS - 15.8;
    return index;
}
