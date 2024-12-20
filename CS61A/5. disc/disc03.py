# topic: Recursion
# Q1
def swipe(n):
    """
    Print the digits of n, one per line, first backward then forward.
    >>> swipe(2837)
    7
    3
    8
    2
    8
    3
    7
    """
    if n < 10:
        print(n)
    else:
        print(n % 10)
        swipe(n // 10)
        print(n % 10)


# Q2
def skip_factorial(n):
    """Return the product of positive integers n * (n - 2) * (n - 4) * ...

    >>> skip_factorial(5) # 5 * 3 * 1
    15
    >>> skip_factorial(8) # 8 * 6 * 4 * 2
    384
    """
    if n - 2 <= 0:
        return n
    else:
        return n * skip_factorial(n - 2)


# Q3
def is_prime(n):
    """Returns True if n is a prime number and False otherwise.
    >>> is_prime(2)
    True
    >>> is_prime(16)
    False
    >>> is_prime(521)
    True
    """

    def check_all(i):  # check all the numbers from 2-n**0.5
        if i > (n ** 0.5):
            return True
        elif n % i == 0:
            return False
        else:
            return check_all(i + 1)

    return check_all(2)


# Q4
def hailstone(n):
    """Print out the hailstone sequence starting at n,
    and return the number of elements in the sequence.
    >>> a = hailstone(10)
    10
    5
    16
    8
    4
    2
    1
    >>> a
    7
    >>> b = hailstone(1)
    1
    >>> b
    1
    """
    print(n)
    if n % 2 == 0:
        return even(n)
    else:
        return odd(n)


def even(n):
    return 1 + hailstone(n // 2)  # the key is that the return value is a count itself!


def odd(n):
    return 1 + hailstone(3 * n + 1)


# Q5:The Game of Sevens
def sevens(n, k):
    def f(i, who, direction):  # i is the number,"who" is the person, "direction" is clockwise/counterclockwise
        if i == n:
            return who  # if equal to the number we want, return the person at that time
        else:
            # deal with direction
            if i % 7 == 0 and has_seven(i):
                direction = -direction
            # every step, plus one person
            who = who + direction
            # potential transgression
            if who > k or who < k:
                who = k

            # next step(we don't have while here, so we can't just i++, we use recursion instead)
            return f(i + 1, who, direction)

    return f(1, 1, 1)  # initial point. direction~1 means clockwise


def has_seven(n):
    if n == 0:
        return False
    elif n % 10 == 7:
        return True
    else:
        return has_seven(n // 10)


