import sys
import math

def main():
    card = get_card()
    len = get_len(card)
    if not checksum(card, len):
        print("INVALID")
        sys.exit()
    print_type(card, len)
    sys.exit()

def get_card():
    try:
        n = int(input("Number: "))
    except:
        # print("Improper usage. Example input: 378282246310005")
        sys.exit()
    return n

def get_len(card):
    len = 0
    while card > 0:
        len += 1
        card = math.floor(card / 10)
    return len

def checksum(card, len):
    sum = 0
    for i in range(1, len+1):
        n = int(((card % (10**i)) - (card % 10**(i-1))) / 10**(i-1))
        if i % 2 == 0:
            sum += ((n*2) % 10) + (((n*2) % 100 - (n*2) % 10) / 10)
        else:
            sum += n
    if sum % 10 == 0:
        return True
    return False

def print_type(card, len):
    # Get first two digits
    n = card
    while math.floor(n / 10) > 9:
        n = math.floor(n / 10)

    # Get first digit as a float
    n1 = float("{:.1f}".format(n / 10))

    # Check type
    if (len == 15) and (n == 34 or n == 37):
        print("AMEX")
    elif (len == 16) and (n1 > 5.0 and n1 < 5.6):
        print("MASTERCARD")
    elif (len == 13 or len == 16) and (math.floor(n1) == 4):
        print("VISA")
    else:
        print("INVALID")

# Prevents main from being run when this module is imported
if __name__ == '__main__':
    main()