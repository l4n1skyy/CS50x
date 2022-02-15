# A program that calculates the minimum number of coins required to give a user change.
import sys

def main():
    change = get_change()
    print(min_coins(change))
    sys.exit()

# Get positive integer as change in dollars
def get_change():
    # Python do-while loop
    while True:
        try:
            n = float(input("Change owed: "))
            if (n > -1):
                break
        except ValueError:
            print("That's not an integer!")
    return n

# Get minimum amount of coins required to give user change
def min_coins(change):
    coins = 0
    while change > 0:
        if change >= 0.25:
            change = round(change - 0.25, 3)
        elif change >= 0.1:
            change = round(change - 0.1, 3)
        elif change >= 0.05:
            change = round(change - 0.05, 3)
        elif change >= 0.01:
            change = round(change - 0.01, 3)
        coins += 1
    return coins

# Prevents main from being run when this module is imported
if __name__ == '__main__':
    main()