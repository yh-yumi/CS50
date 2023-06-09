#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int count_letters(string);
float count_words(string);
int count_sentences(string);

int n;

int main(void)
{
    string paragraph = get_string("Text: ");
    n = strlen(paragraph);
    int number_letters = count_letters(paragraph);
    float number_words = count_words(paragraph); //make number_words' datatype float to calculate correctly
    int number_sentences = count_sentences(paragraph);

    float L = number_letters / number_words * 100; //L is the average number of letters per 100 words in the text
    float S = number_sentences / number_words * 100; //S is the average number of sentences per 100 words in the text
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        index += 0.5;
        printf("Grade %i\n", (int)index); //float to int, round to the nearest number
    }


}

int count_letters(string text)
{

    int sum_letters = 0;
    for (int i = 0; i < n; ++i)
    {
        if (islower(text[i]) != 0) // To test if it is a lowercase character
        {
            text[i] = toupper(text[i]); //Transfer to uppercase
        }
        if (text[i] >= 65 && text[i] <= 90) //only count the letters that are A to Z
        {
            sum_letters += 1;
        }
    }

    return sum_letters;
}

float count_words(string text)
{
    float sum_words = 1.0;
    for (int i = 0; i < n; ++i)
    {
        if (text[i] == 32) //if the char is space then calculate
        {
            sum_words += 1;
        }
    }

    return sum_words;
}

int count_sentences(string text)
{
    int sum_sentences = 0;
    for (int i = 0; i < n; ++i)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63) //if the character in string array is ! . ? claculate it as the sentences
        {
            sum_sentences += 1;
        }
    }

    return sum_sentences;

}