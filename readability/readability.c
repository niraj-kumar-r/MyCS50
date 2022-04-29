#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int number_letters = count_letters(text);
    int number_words = count_words(text);
    int number_sentences = count_sentences(text);

    float L = ((number_letters * 100.0) / number_words);
    float S = ((number_sentences * 100.0) / number_words);

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int num_of_letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            num_of_letters++;
        }
    }
    return num_of_letters;
}

int count_words(string text)
{
    int num_of_words = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            num_of_words++;
        }
    }

    num_of_words++;

    return num_of_words;
}

int count_sentences(string text)
{
    int num_of_sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            num_of_sentences++;
        }
    }

    return num_of_sentences;
}