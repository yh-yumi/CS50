import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    database = []
    # Use reader() to read, will read as string not dict
    with open(sys.argv[1], "r") as file_database:
        reader = csv.reader(file_database)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    dna_sequence = []
    with open(sys.argv[2], "r") as file_dna:
        dna_sequence = file_dna.read()

    # TODO: Find longest match of each STR in DNA sequence
    STR_list = {}
    # Add STR name to the dictionary and set their count to 0, database[0][j] is the STR name in the different csv header
    for i in range(1, len(database[0])):
        STR_list[database[0][i]] = 0
    # for keys(STR name) in the dictionary, find the largest matched number and change the value in the dict
    for STR in STR_list.keys():
        STR_list[STR] = longest_match(dna_sequence, STR)

    # TODO: Check database for matching profiles
    check_times = 0
    # Start from the second row(exclusive header) and check every STR column
    # if each STR value of the row(database) equals to values in the STR_list
    # Use get() to get special value from STR_list(dictionary)
    # Check if check_times equals to the number of keys, if yes print the name of the row, if not set check_times to 0
    # list[cannot put a string have to be integer]
    for row in database[1:]:
        for j in range(len(STR_list)):
            if int(row[j + 1]) == STR_list.get(database[0][j + 1]):
                check_times += 1
        if check_times == len(database[0]) - 1:
            print(row[0])
            return
        else:
            check_times = 0
    print("No Match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
