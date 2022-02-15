# A program that prints out a double half-pyramid of a specified height
import sys

def main():
    height = get_height()
    double_half_pyramid(height)
    sys.exit()

# Get height between 1 and 8
def get_height():
    # Python do-while loop
    while True:
        try:
            n = int(input("Height: "))
            if (n > 0 and n < 9):
                break
        except ValueError:
            print("That's not an integer!")
    return n

# Print out a double half-pyramid
def double_half_pyramid(height):
    line = 1
    while line <= height:
        print(" " * (height - line), end="")
        print("#" * line, end="  ")
        print("#" * line)
        line += 1

# Prevents main from being run when this module is imported
if __name__ == '__main__':
    main()