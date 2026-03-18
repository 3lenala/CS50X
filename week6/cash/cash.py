# This program calculates the minimum number of coins needed to make change
# through a greedy algorithm
def get_change():   # gets the change under the conditions:
    while (True):   # has to be a float
        try:        # has to be positive
            change = float(input("change: "))
            if (change <= 0):
                continue
        except ValueError:
            continue
        else:
            break
    return change


def get_coins(currency):   # returns a list with the existing coins for a given currency
    systems = {
        "USD": [0.25, 0.10, 0.05, 0.01],
        "EUR": [2, 1, 0.50, 0.20, 0.10, 0.05, 0.02, 0.01],
        "GBP": [2, 1, 0.50, 0.20, 0.10, 0.05, 0.02, 0.01]
    }
    try:
        coins = systems[currency.upper()]
    except KeyError:    # raises ValueError if the currency introduced is not supported
        raise ValueError(f"Currency not supported: {currency}")
    return coins


def number_coins(change, coins):    # greedy algorithm
    total = 0                       # calculates the minimum number of coins required
    for coin in coins:              # for a certain change
        total += int(change // coin)
        change = round(change % coin, 2)  # rounds to 2 decimal points
    return total


if __name__ == "__main__":  # main function
    change = get_change()
    coins = get_coins("USD")
    total = number_coins(change, coins)
    print(total)
