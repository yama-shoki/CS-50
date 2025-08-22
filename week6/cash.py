# TODO

def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)

def get_cents():
    user_input = None
    while True:
        user_input = int(input("type your payment_amount"))
        if user_input >= 0:
            break
    return user_input

# Calculate the number of quarters to give the customer
def calculate_quarters(cents):
    print(f"user_input: {cents}")  # get_cents()できてる
    return cents // 25

# Calculate the number of dimes to give the customer
def calculate_dimes(cents):
    # TODO
    return cents // 10

# Calculate the number of nickels to give the customer
def calculate_nickels(cents):
    # TODO
    return cents // 5

# Calculate the number of pennies to give the customer
def calculate_pennies(cents):
    # TODO
    return cents // 1


main()


