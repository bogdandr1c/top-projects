import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database/(large/small) sequences/X.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    filename1 = sys.argv[1]
    rows = []
    try:
        with open(filename1) as file1:
            reader1 = csv.DictReader(file1)
            for row in reader1:
                rows.append(row)
    except FileNotFoundError:
        print("Usage: python dna.py database/(large/small) sequences/X.txt")
        sys.exit(2)

    # TODO: Read DNA sequence file into a variable
    filename2 = sys.argv[2]
    try:
        with open(filename2) as file2:
            seq = file2.read()
    except FileNotFoundError:
        print("Usage: python dna.py database/(large/small) sequences/X.txt")
        sys.exit(3)

    # TODO: Find longest match of each STR in DNA sequence
    list_match = []
    for key in rows[0]:
        if key != "name":
            current = longest_match(seq, key)
            list_match.append(current)

    # TODO: Check database for matching profiles
    for person in rows:
        match = True
        cnt = 0
        for key in person:
            if key != "name":
                if int(person[key]) != list_match[cnt]:
                    match = False
                    break
                cnt += 1
        if match:
            print(person["name"])
            return
    print("No match")
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
