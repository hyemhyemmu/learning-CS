# cascade
def cascade(n):
    if n < 10:
        print(n)
    else:
        print(n)
        cascade(n // 10)
        print(n)


"""
a simpler version but it may not be that readable:
def cascade(n):
        print(n)
    if n>10:
        cascade(n // 10)
        print(n)
"""


# inverse-cascade_initial version
# What I learned? order can be changed by change the order of the recursion
def inverse_cascade(n):
    # we can't finish it in one func, so I decided to use HOF
    grow(
        n)  # we don't need return value here, because if n//10=0,it will just not go into grow or shrink and just print it out
    print(n)
    shrink(n)


def grow(n):  # grow first then print
    if n > 10:
        grow(n // 10)
        print(n // 10)


def shrink(n):
    if n > 10:
        print(n // 10)
        shrink(n // 10)


# inverse-cascade_simplified version
def inverse_cascade_2(n):
    grow_2(n)
    print(n)
    shrink_2(n)


def f_then_g(f, g, n):
    if n:
        f(n)
        g(n)


grow_2 = lambda n: f_then_g(grow_2, print, n // 10)
shrink_2 = lambda n: f_then_g(print, shrink_2, n // 10)


# fibonacci numbers
def fib(n):
    # returns the nth digit of the fib numbers
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)


# counting partitions
def count_partitions(n, m):
    """
    The number of partitions of a positive integer n, using parts up to size m, is the number
    of ways in which n can be expressed as the sum of positive integer parts up to m
    """
    # base cases
    if n == 0:
        return 0
    elif n < 0:
        return 0
    elif m == 0:
        return 0
    # recursions
    else:
        with_m = count_partitions(n - m, m)
        without_m = count_partitions(n, m - 1)
        return with_m + without_m


# streak
def streak(n):
    """Return True if ALL the digits in positive integer n are the same.
    >>> streak(22222)
    True
    >>> streak(4)
    True
    >>> streak(2222322) # 2 and 3 are different digits.
    False
    """
    # single digit:true
    # multiple digit: compare last two digit and then recursion
    return (0 <= n <= 9) or (n > 9 and n % 10 == n // 10 % 10 and streak(n // 10))


# example for mutual recursion
def smallest_factor(n):
    # what really smart is that if we try to find the smallest factor of a number, it must be a prime number because
    # if not, there must be a smaller factor which is contradiction!
    """return n's smallest prime factor"""
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return i
    return n


def unique_prime_factors(n):
    """Return the number of unique prime factors of n.#return value act as a counter
    >>> unique_prime_factors(51) # 3 * 17
    2
    >>> unique_prime_factors(27) # 3 * 3 * 3
    1
    >>> unique_prime_factors(120) # 2 * 2 * 2 * 3 * 5
    3
    """
    k = smallest_factor(n)  # smallest factor of n, the starting point of our searching

    def no_k(n):
        # n=1
        if n == 1:
            return 0
        # k is still a factor of n
        elif n % k == 0:
            no_k(n // k)
        # no more k, we need to find another prime factor
        elif n % k != 0:
            unique_prime_factors(n)

    return 1 + no_k(n)  # everytime use unique...,means we find one prime factor


#parking question.跟青蛙跳台阶非常相似。本质上都是把一个大的问题转化为几个小问题
"""
Definition. When parking vehicles in a row, a motorcycle takes up 1 parking spot and a car
takes up 2 adjacent parking spots. A string of length n can represent n adjacent parking
spots using % for a motorcycle, <> for a car, and . for an empty spot.
For example: '.%%.<><>' (Thanks to the Berkeley Math Circle for introducing this question.)
Implement count_park, which returns the number of ways that vehicles can be parked in n
adjacent parking spots for positive integer n. Some or all spots can be empty.
14
"""
def count_park(n):
    if n<=0:
        return 0
    elif n==1:
        return 1
    else:
        return count_park(n-1)+count_park(n-1)+count_park(n-2)
