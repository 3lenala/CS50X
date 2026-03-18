# the following program prints half of a pyramid of a given height h
# definition of functions:
def get_height():  # ensures that the user introudces an integer
    height = ""        # between 0 and 9
    while (True):
        try:
            height = int(input("height: "))
            if height <= 0 or height >= 9:
                continue
        except ValueError:  # if ValueError is raised
            continue       # the user gets asked for input again
        else:
            break
    return height


def print_row(height, row):  # print the ith row for a pyramid of height h
    for column in range(height):  # if we consider the whole structure as a square
        if column < row:        # for the ith row there will be i spaces and h-i
            print(" ", end="")  # hashes. Columns are numerated from left to right
        else:
            print("#", end="")
    print("  ", end="")         # separation between pyramids
    for column in range(height - row):  # for the second pyramid,
        print("#", end="")      # a row will have (height - row) hashes
    print()                     # given the numeration used for columns/ rows


if __name__ == "__main__":  # main section of the code

    height = get_height()  # ask for the height

    for row in range(height-1, -1, -1):  # print each row
        print_row(height, row)         # rows are numbered top to bottom
    # range(height-1, -1, -1) gives me a list from height-1 to 0
