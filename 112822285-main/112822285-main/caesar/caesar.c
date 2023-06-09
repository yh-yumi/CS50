#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool onlydigits(string);
char rotate(char, int);

int main(int argc, string argv[])
{
    if (argc != 2 || onlydigits(argv[1])) //if true, enter the function
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]); //make the number character to integer
    string plaintext = get_string("plaintext: "); // to press the context
    int textlength = strlen(plaintext); // to calculate the length of the context(including space)
    string ciphertext = plaintext; // use original one to initialize the string variable

    for (int j = 0; j < textlength; ++j) //string is a char array, only change the chars that are alphabets
    {
        ciphertext[j] = rotate(plaintext[j], key);
    }

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool onlydigits(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n; ++i) //if i = 0, check the if condition, is digit, not executing, i = 2...until there is a non-digit char to break out the function(return true)
    {
        if (! isdigit(s[i])) //isdigit function return 0 if there is a non-digit char (exception, do not put in the common situation return)
        {
            return true; //if there is a non-digit letter return true and end the function
        }
    }
    return false; //have checked all chars, if all are digits return false (common situation return)

}

char rotate(char letter, int number)
{
    if (letter >= 65 && letter <= 90) //uppercase
    {
        letter -= 64; //make A-Z are 1-26
        letter = (letter + (number % 26)) % 26; //to confirm key's mod and wrap around if the letter is over 26
        letter += 64; // make letter's ASCII CODE to the alphabetical part
        return letter;
    }
    if (letter >= 97 && letter <= 122) //lowercase
    {
        letter -= 96; //make a-z are 1-26
        letter = (letter + (number % 26)) % 26;
        letter += 96;
        return letter;
    }
    return letter; // if not an alphabet, return the original value
}