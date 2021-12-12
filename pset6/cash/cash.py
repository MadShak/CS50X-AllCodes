# importing floor from math library.
from math import floor
# importing get_float from the cs50 library.
from cs50 import get_float


# Main program.
def main():

    # LOOP.
    while True:
        owed = get_float("Owed: ")
        coins = floor(owed * 100)

        if coins > 0:
            break

    # (qu)quarters, (di)dimes, (ni)nickels, (pe)pennies.
    qu = coins // 25
    di = (coins % 25) // 10
    ni = ((coins % 25) % 10) // 5
    pe = ((coins % 25) % 10) % 5

    # Print results.
    print(f"{qu + di + ni + pe}")


if __name__ == "__main__":
    main()