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
        without_m = count_partitions(n,m - 1)
        return with_m + without_m
