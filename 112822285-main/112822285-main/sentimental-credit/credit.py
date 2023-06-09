# TODO
from cs50 import get_string

number = get_string("Number: ")
sum = 0
times = len(number) // 2
# For the length of numbers that are even
if len(number) % 2 == 0:
    for i in range(times):
        copy_multiply = int(number[i * 2])
        copy_add = int(number[i * 2 + 1])
        string_number = str(copy_multiply * 2)
# Make strings spilt to be one or two numbers and then add
        if len(string_number) == 2:
            sum = sum + int(string_number[0]) + int(string_number[1])
        else:
            sum += int(string_number[0])
        sum += copy_add
# For the length of numbers that are odd
if len(number) % 2 == 1:
    for i in range(times):
        copy_multiply = int(number[i * 2 + 1])
        copy_add = int(number[i * 2])
        string_number = str(copy_multiply * 2)
        if len(string_number) == 2:
            sum = sum + int(string_number[0]) + int(string_number[1])
        else:
            sum += int(string_number[0])

        sum += copy_add
# Miss the last element in number that needs to be added
    sum += int(number[len(number) - 1])
# Change type to string
total_digit = str(sum)
# Decide if the card is valid
if total_digit[1] == "0":
    if number[0] == "4":
        print("VISA")
    if number[0] == "5" and (number[1] == "1" or number[1] == "2" or number[1] == "3" or number[1] == "4" or number[1] == "5"):
        print("MASTERCARD")
    if number[0] == "3" and (number[1] == "4" or number[1] == "7"):
        print("AMEX")
    else:
        print("INVALID")
else:
    print("INVALID")