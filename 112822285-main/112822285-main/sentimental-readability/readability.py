# TODO\
from cs50 import get_string

# Have to make n pubic innitialized or the function call cannot get n's value
n = 0
paragraph = get_string("Text: ")
n = len(paragraph)


def main():
    number_letters = count_letters(paragraph)
    number_words = count_words(paragraph)
    number_sentences = count_sentences(paragraph)

    L = number_letters / number_words * 100
    S = number_sentences / number_words * 100
    index = 0.0588 * L - 0.296 * S - 15.8
# Check Grade Level
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        index += 0.5
        print(f"Grade {int(index)}")


def count_letters(text):
    sum_letters = 0
# Check if it is a lowercase or uppercase character
    for i in range(n):
        if text[i].islower():
            sum_letters += 1
        if text[i].isupper():
            sum_letters += 1

    return sum_letters


def count_words(text):
    sum_words = 1
    # chr() is to transfer the ASCII number to character
    for i in range(n):
        if text[i] == chr(32):
            sum_words += 1

    return sum_words


def count_sentences(text):
    sum_sentences = 0
    for i in range(n):
        if text[i] == chr(33) or text[i] == chr(46) or text[i] == chr(63):
            sum_sentences += 1

    return sum_sentences


main()
