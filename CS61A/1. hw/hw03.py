# Q1
def num_eights(n):
    """Returns the number of times 8 appears as a digit of n.

    >>> num_eights(3)
    0
    >>> num_eights(8)
    1
    >>> num_eights(88888888)
    8
    >>> num_eights(2638)
    1
    >>> num_eights(86380)
    2
    >>> num_eights(12345)
    0
    >>> num_eights(8782089)
    3
    """

    def is_eight(n):
        # n=0
        if n == 0:
            return 0
        # last digit is 8 -> +1 and check forward
        elif n % 10 == 8:
            return 1 + num_eights(n // 10)
        # last digit is not 8 -> check forward
        else:
            return num_eights(n // 10)

    return is_eight(n)


# Q2
def digit_distance(n):
    """Determines the digit distance of n.

    >>> digit_distance(3)
    0
    >>> digit_distance(777) # 0 + 0
    0
    >>> digit_distance(314) # 2 + 3
    5
    >>> digit_distance(31415926535) # 2 + 3 + 3 + 4 + ... + 2
    32
    >>> digit_distance(3464660003)  # 1 + 2 + 2 + 2 + ... + 3
    16
    """

    def pair_abs(n):
        if n // 10 == 0:
            return 0
        else:
            return abs((n // 10) % 10 - n % 10) + pair_abs(n // 10)

    return pair_abs(n)


# Q3
def interleaved_sum(n, odd_func, even_func):
    """Compute the sum odd_func(1) + even_func(2) + odd_func(3) + ..., up
    to n.

    >>> identity = lambda x: x
    >>> square = lambda x: x * x
    >>> triple = lambda x: x * 3
    >>> interleaved_sum(5, identity, square) # 1   + 2*2 + 3   + 4*4 + 5
    29
    >>> interleaved_sum(5, square, identity) # 1*1 + 2   + 3*3 + 4   + 5*5
    41
    >>> interleaved_sum(4, triple, square)   # 1*3 + 2*2 + 3*3 + 4*4
    32
    >>> interleaved_sum(4, square, triple)   # 1*1 + 2*3 + 3*3 + 4*3
    28
    """

    def f(n):
        # only know the odevity of 1, so we do it backwards
        if n == 1:
            return odd_func(1)
        # even number
        elif n % 2 == 0:
            return even_func(n) + f(n - 1)
        # odd number
        elif n % 2 != 0:
            return odd_func(n) + f(n - 1)

    return f(n)


"""
another solution is to recursion below -> top
def interleaved_sum(n, odd_func, even_func):
    def sum_from(k):
        # 2 numbers a jump, so n must be odd
        if k>n:
            return 0
        elif k == n:
            return odd_func(k)
        else:
            return odd_func(k) + even_func(k+1) + sum_from(k + 2)
    return sum_from(1)
"""


# Q4
def next_smaller_dollar(bill):
    """Returns the next smaller bill in order."""
    if bill == 100:
        return 50
    if bill == 50:
        return 20
    if bill == 20:
        return 10
    elif bill == 10:
        return 5
    elif bill == 5:
        return 1
    return None


def count_dollars(total):
    """Return the number of ways to make change.

    >>> count_dollars(15)  # 15 $1 bills, 10 $1 & 1 $5 bills, ... 1 $5 & 1 $10 bills
    6
    >>> count_dollars(10)  # 10 $1 bills, 5 $1 & 1 $5 bills, 2 $5 bills, 10 $1 bills
    4
    >>> count_dollars(20)  # 20 $1 bills, 15 $1 & $5 bills, ... 1 $20 bill
    10
    >>> count_dollars(45)  # How many ways to make change for 45 dollars?
    44
    >>> count_dollars(100) # How many ways to make change for 100 dollars?
    344
    >>> count_dollars(200) # How many ways to make change for 200 dollars?
    3274
    """

    def f(total, bill = 100):
        "actually calculate methods of changing using given total and bill limit "
        # basic cases
        # finished counting (means that this is a good method)
        if total == 0:
            return 1
        # no smaller bills -> invalid combination
        # below total -> invalid comb as well
        elif total < 0 or bill is None:
            return 0

        next_bill = next_smaller_dollar(bill)
        # use at least one "bill"
        with_next = f(total - bill, bill)
        # does not use "bill"
        without_next = f(total, next_bill)
        return with_next + without_next

    return f(total, 100)


# Q5
def next_larger_dollar(bill = 1):
    """Returns the next larger bill in order."""
    if bill == 1:
        return 5
    elif bill == 5:
        return 10
    elif bill == 10:
        return 20
    elif bill == 20:
        return 50
    elif bill == 50:
        return 100
    return None


def count_dollars_upward(total):
    """Return the number of ways to make change using bills.

    >>> count_dollars_upward(15)  # 15 $1 bills, 10 $1 & 1 $5 bills, ... 1 $5 & 1 $10 bills
    6
    >>> count_dollars_upward(10)  # 10 $1 bills, 5 $1 & 1 $5 bills, 2 $5 bills, 10 $1 bills
    4
    >>> count_dollars_upward(20)  # 20 $1 bills, 15 $1 & $5 bills, ... 1 $20 bill
    10
    >>> count_dollars_upward(45)  # How many ways to make change for 45 dollars?
    44
    >>> count_dollars_upward(100) # How many ways to make change for 100 dollars?
    344
    >>> count_dollars_upward(200) # How many ways to make change for 200 dollars?
    3274
    """

    def f(total, bill):
        if total == 0:
            return 1
        elif bill == None or total < bill:
            return 0

        next_bill = next_larger_dollar(bill)
        with_this = f(total - bill, bill)
        without_this = f(total, next_bill)
        return with_this + without_this

    return f(total, 1)


# Q6:hanoi
def print_move(origin, destination):
    """Print instructions to move a disk."""
    print("Move the top disk from rod", origin, "to rod", destination)


def move_stack(n, start, end):
    """Print the moves required to move n disks on the start pole to the end
    pole without violating the rules of Towers of Hanoi.

    n -- number of disks
    start -- a pole position, either 1, 2, or 3
    end -- a pole position, either 1, 2, or 3

    There are exactly three poles, and start and end must be different. Assume
    that the start pole has at least n disks of increasing size, and the end
    pole is either empty or has a top disk larger than the top n start disks.

    >>> move_stack(1, 1, 3)
    Move the top disk from rod 1 to rod 3
    >>> move_stack(2, 1, 3)
    Move the top disk from rod 1 to rod 2
    Move the top disk from rod 1 to rod 3
    Move the top disk from rod 2 to rod 3
    >>> move_stack(3, 1, 3)
    Move the top disk from rod 1 to rod 3
    Move the top disk from rod 1 to rod 2
    Move the top disk from rod 3 to rod 2
    Move the top disk from rod 1 to rod 3
    Move the top disk from rod 2 to rod 1
    Move the top disk from rod 2 to rod 3
    Move the top disk from rod 1 to rod 3
    """
    assert 1 <= start <= 3 and 1 <= end <= 3 and start != end, "Bad start/end"
    if n == 1:
        print_move(start, end)
    else:
        help = 6 - start - end
        # move n-1 plate from start to help
        move_stack(n - 1, start, help)
        # move the biggest
        print_move(start, end)
        # move the others
        move_stack(n - 1, help, end)


# Q7
from operator import sub, mul


def make_anonymous_factorial():
    """Return the value of an expression that computes factorial.

    >>> make_anonymous_factorial()(5)
    120
    """
    return lambda x: 1 if sub(x, 1) == 0 else mul(x, make_anonymous_factorial()(x - 1))


# extra problems - 2017 MT1 Q4A
def collapse(n):
    """For non-negative N, the result of removing all digits that are equal
    to the digit on their right, so that no adjacent digits are the same.
    >>> collapse(1234)
    1234
    >>> collapse(12234441)
    12341
    >>> collapse(0)
    0
    >>> collapse(3)
    3
    >>> collapse(11200000013333)
    12013
    """
    left, last = n // 10, n % 10
    if left == 0:
        return last
    elif last == left % 10:
        return collapse(left)
    else:
        return collapse(left) * 10 + last

    # extra problems - 2019 Final Q6A


def contains(a, b):
    """Return whether the digits of a are contained in the digits of b.
    >>> contains(357, 12345678)
    True
    >>> contains(753, 12345678)
    False
    >>> contains(357, 37)
    False
    """
    if a > b:
        return False
    elif a == b:
        return True
    # same final digit
    elif a % 10 == b % 10:
        return contains(a // 10, b // 10)
    # find same digit
    else:
        return contains(a, b // 10)
