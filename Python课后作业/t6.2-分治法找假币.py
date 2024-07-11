def findFalseCoin(coins, start, n):
    if n == 1:
        print(f"Fake coin:{start}")
        return
    coin_1, coin_2, coin_3 = group(coins)
    flag = compare(coin_1, coin_2)
    if flag == 'right':
        findFalseCoin(coin_1, start, len(coin_1))
    elif flag == 'left':
        findFalseCoin(coin_2, start + n // 2, len(coin_2))
    elif flag == 'equal' and len(coin_3) == 0:
        print("Fake coin is not found");
    elif flag == 'equal' and len(coin_3) == 1:
        print(f"Fake coin:{coin_3[0]}");


def group(coins):
    n = len(coins)
    coin_1 = coins[0: n // 2]
    coin_2 = coins[n // 2: n // 2 * 2]
    coin_3 = coins[n // 2 * 2: n]
    if len(coin_3) == 1:
        coin_3[0] = n - 1
    return coin_1, coin_2, coin_3


def compare(first_coin, second_coin):
    sum1, sum2 = sum(first_coin), sum(second_coin)
    if sum1 == sum2:
        result = 'equal'
    elif sum1 < sum2:
        result = 'right'
    else:
        result = 'left'
    return result


coins = list(map(int, input().split(',')))
findFalseCoin(coins, 0, len(coins))
