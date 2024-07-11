def guess_number_game():
    secret_number = 100
    guess_count = 0

    while True:
        guess = input()
        guess_count += 1
        if not guess.isdigit():
            print("input error")
            continue
        guess = int(guess)

        if guess == secret_number:
            print("you have tried %d times, you win" % guess_count)
            break
        elif guess < secret_number:
            print("less than expected")
        else:
            print("larger than expected")


guess_number_game()
