# Q1:race
"""
Find positive integers x and y (with y larger than x but not larger than 2 * x) for which either:
race(x, y) returns the wrong value or
race(x, y) runs forever
"""


def race(x, y):
    """The tortoise always walks x feet per minute, while the hare repeatedly
    runs y feet per minute for 5 minutes, then rests for 5 minutes. Return how
    many minutes pass until the tortoise first catches up to the hare.

    >>> race(5, 7)  # After 7 minutes, both have gone 35 steps
    7
    >>> race(2, 4) # After 10 minutes, both have gone 20 steps
    10
    """
    assert y > x and y <= 2 * x, 'the hare must be fast but not too fast'
    tortoise, hare, minutes = 0, 0, 0
    while minutes == 0 or tortoise - hare:
        tortoise += x
        if minutes % 10 < 5:
            hare += y
        minutes += 1
    return minutes


# error: When they meet, the time may not be integer!

# find the combinations:(can only be when infinite or just error)
def find_errors():
    errors = []
    for x in range(1, 100):
        for y in range(x + 1, 2 * x):
            try:
                minutes = race(x, y)
                if minutes == float('inf'):
                    errors.append((x, y))
            except:
                errors.append((x, y))
    return errors


errors = find_errors()
print(errors)


# Q2:fizzbuzz
def fizzbuzz(n):
    for i in range(1, n + 1):
        if i % 3 == 0 and i % 5 == 0:
            print("fizzbuzz")
        elif i % 3 == 0:
            print("fizz")
        elif i % 5 == 0:
            print("buzz")
        else:
            print(i)


# Q3:is prime?
def is_prime(n):
    """
    check all the numbers btw 1 and n if they are divisible by n. If yes,return True. Vise Versa
    """
    for i in range(2, n):
        if n % i == 0:
            return False
    return True


# Q4: unique digits
# a smart way is to iterate in 0-9 and see if they are in the number
def has_digit(n, k):
    """Returns whether k is a digit in n.

    >>> has_digit(10, 1)
    True
    >>> has_digit(12, 7)
    False
    """
    assert 0 <= k < 10, "k must be a digit between 0 and 9"
    for digit in str(n):
        if int(digit) == k:
            return True
    return False


def unique_digits(n):
    """Return the number of unique digits in positive integer n.

    >>> unique_digits(8675309) # All are unique
    7
    >>> unique_digits(13173131) # 1, 3, and 7
    3
    >>> unique_digits(101) # 0 and 1
    2
    """
    count = 0
    for i in range(0, 10):
        if has_digit(n, i):
            count += 1
    return count
