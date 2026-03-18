# The following program identifies a card as american express, visa, mastercard or
# invalid card based on its length, starting numbers and Luhn's algorithm

# Constant values that will be used stored in three dictionaries

# AMERICAN EXPRESS
AMEX = {
    "FIRST_DIGIT": 3, "SECOND_DIGIT": [4, 7], "LENGTH": [15]
}

# MASTERCARD
MASTERCARD = {
    "FIRST_DIGIT": 5, "SECOND_DIGIT": list(range (1, 6)), "LENGTH": [16]
}
# VISA
VISA = {
    "FIRST_DIGIT": 4, "LENGTH": [13,  16]
}


def get_card_number():  # gets a number associated to a card
    while (True):
        try:
            card_number = input("card number: ")
            card_int = int(card_number)
            if (card_int == 0):  # asks again if the user introduces 0
                print("INVALID CARD = 0")
                continue
        except ValueError:  # avoids an error if the user introduces something
            print("Introduce a number")
            continue       # that is not an integer
        else:
            break
    return card_number


def identify_type(card_number):   # checks if the first numbers are associated to a
    try:
        second_digit = int(card_number[1])
        first_digit = int(card_number[0])
    except IndexError:
        return 'INVALID'

    match first_digit:               # valid card
        case 3:  # first digit of AMEX
            if second_digit in AMEX["SECOND_DIGIT"]:
                return 'AMEX'
        case 4:  # first digit of VISA
            return 'VISA'
        case 5:  # first digit of MASTERCARD

            if second_digit in MASTERCARD["SECOND_DIGIT"]:
                return 'MASTERCARD'
    return 'INVALID'


def validate_length_card(card_type, length_card):    # given the possible card type, checks if the
    match card_type:                         # length matches those cards
        case 'AMEX':
            return (length_card in AMEX["LENGTH"])
        case 'MASTERCARD':
            return (length_card in MASTERCARD["LENGTH"])
        case 'VISA':
            return (length_card in VISA["LENGTH"])  # multiple possibilities por visa's length
        case _:
            return False


def check_luhn(card_number, length_card):  # checks the Luhn sum
    luhn_sum = 0
    should_double = False
    for index in range(length_card - 1, -1, -1):
        if should_double:
            delta_sum = 2*int(card_number[index])
            if (delta_sum >= 10):  # if luhn is greater than 10, sum the digits
                delta_sum = (delta_sum // 10) + (delta_sum % 10)
            luhn_sum += delta_sum
            should_double = False
        else:
            luhn_sum += int(card_number[index])
            should_double = True

    return (luhn_sum % 10 == 0)


if __name__ == "__main__":  # main function
    card_number = get_card_number()  # get the card number
    length_card = len(card_number)  # get its length
    card_type = identify_type(card_number)  # checks the begining of the card

    if card_type != 'INVALID':  # for now, it is valid
        if (not validate_length_card(card_type, length_card)):  # not vaid
            card_type = 'INVALID'  # so we change the card_type
        else:   # for now it is valid
            if (not check_luhn(card_number, length_card)):  # not valid
                card_type = 'INVALID'  # so we change the card_type
    print(card_type)  # if it is a valid card, the name will keep its form from check_start
