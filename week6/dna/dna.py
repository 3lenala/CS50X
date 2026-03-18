import csv
import sys

USAGE_ERROR = 1
FILE_NOT_FOUND = 2
EMPTY_FILE = 3
NO_MATCH = 4


def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database sequence")
        sys.exit(USAGE_ERROR)  # usage error

    # Read database file into a variable
    database, strs = read_database(sys.argv[1])

    # Read DNA sequence file into a variable
    dna_string = read_sequence(sys.argv[2])

    # Find longest match of each STR in DNA sequence
    longest_matches = calculate_longest_matches(dna_string, strs)

    # Check database for matching profiles
    match = find_matching_profile(longest_matches, database)
    if (not match):
        print('No match')
        sys.exit(NO_MATCH)
    print(match)
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


def read_database(database_db):
    try:
        with open(database_db, "r", newline="") as database_file:
            reader = csv.DictReader(database_file)
            database = []  # empty list
            # we will create a list made out of dictionaries
            # each dictionary will contain the data for one person
            for person in reader:
                database.append(person)
    except FileNotFoundError:
        print("Database file not found")
        sys.exit(FILE_NOT_FOUND)  # file not fond error
    else:
        if (len(database) == 0):
            print("Empty database")
            sys.exit(EMPTY_FILE)  # empty file error
        strs = [key for key in database[0] if key.lower() != "name"]
        return database, strs


def read_sequence(sequence_file):
    try:
        with open(sequence_file, "r") as dna:
            dna_string = dna.read()
        # read the sequence as a whole string
    except FileNotFoundError:
        print("Sequence file not found")
        sys.exit(FILE_NOT_FOUND)  # file no fond error
    else:
        if dna_string == '':
            print("File contains no sequence")
            sys.exit(EMPTY_FILE)  # empty file error
        return dna_string


def calculate_longest_matches(dna_string, strs):
    longest_matches = {}
    for str in strs:
        # for each possible STR according to the database, find the longest match in the sequence
        longest_matches[str] = longest_match(dna_string, str)
    return longest_matches


def find_matching_profile(longest_matches, database):
    # each person in the database is numerated based on its location in the database list
    for person in range(len(database)):
        for strs in longest_matches:  # for each str considered in the problem
            # if one of the str count for the ith person does not match the sequence that
            if (longest_matches[strs] != int(database[person][strs])):
                # is being analized -> break the j-loop
                break
        else:
            match = database[person]["name"]  # name of the person that has completed the j-loop
            return (match)
    return False


if __name__ == "__main__":
    main()
    sys.exit(0)
