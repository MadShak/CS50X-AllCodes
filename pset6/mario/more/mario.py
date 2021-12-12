# importing get_string from the cs50 library.
from cs50 import get_int

# Main program.


def main():

    # LOOP for get height.
    while True:

        h = get_int("Type a height: ")
        w = h

        if h > 0 and h <= 8:
            break

# Printing hashes and empty spaces.
    for i in range(1, h + 1):

        hashe = i
        empty = w - hashe

# Printing column 1.
        print(" " * empty, end="")
        print("#" * hashe, end="")
        print("  ", end="")
        print("#" * hashe)


# Main program.
if __name__ == "__main__":
    main()