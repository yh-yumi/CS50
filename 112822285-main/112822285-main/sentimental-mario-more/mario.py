# TODO
from cs50 import get_int

# Prompt the string to ask for an input if the number is not in the range


def get_height():
    height = int(get_int("Height: "))
    while height < 1 or height > 8:
        height = int(get_int("Height: "))
    return height


def main():
    height = get_height()
    # i starts from 0 and the range is the number of times code will execute
    for i in range(height):
        print(" " * (height - i - 1), end="")
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1))


main()