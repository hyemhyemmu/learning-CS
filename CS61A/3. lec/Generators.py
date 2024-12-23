# count partitions
def count_partitions(n, m):
    """
    Count partitions.
    >>>count_partitions(6,4)
    9
    """
    if n == 0:
        return 1
    elif n < 0 or m == 0:
        return 0
    else:
        with_m = count_partitions(n - m, m)
        without_m = count_partitions(n, m - 1)
        return with_m + without_m


# list partitions
def list_partitions(n, m):
    """list partitions
    >>>for t in list_partitions(6,4):print(t)
    [4, 2]
    [4, 1, 1]
    [3, 3]
    [3, 2, 1]
    [3, 1, 1, 1]
    [2, 2, 2]
    [2, 2, 1, 1]
    [2, 1, 1, 1, 1]
    [1, 1, 1, 1, 1, 1]

    if doesn't use nested list: (totally mess)
    [4, 4, 3, 2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    """
    # exactly match

    if n < 0 or m == 0:
        return []
    else:
        exact_match = []
        if m == n:
            # use nested list here so that each route will be clear, otherwise they will just be a mess
            exact_match = [[m]]
        with_m = [[m] + p for p in list_partitions(n - m, m)]
        without_m = list_partitions(n, m - 1)
        return exact_match + with_m + without_m


# string version
def partitions(n, m):
    """list partitions
    >>>for t in partitions(6,4):print(t)
    2+4
    1+1+4
    3+3
    1+2+3
    1+1+1+3
    2+2+2
    1+1+2+2
    1+1+1+1+2
    1+1+1+1+1+1
"""
    # exactly match

    if n < 0 or m == 0:
        return []
    else:
        exact_match = []
        if m == n:
            # use nested list here so that each route will be clear, otherwise they will just be a mess
            exact_match = [str(m)]
        with_m = [p + '+' + str(m) for p in partitions(n - m, m)]
        without_m = partitions(n, m - 1)
        return exact_match + with_m + without_m


# yield version
def yield_partitions(n, m):
    """list partitions
    >>>for t in yield_partitions(6,4):print(t)
    2+4
    1+1+4
    3+3
    1+2+3
    1+1+1+3
    2+2+2
    1+1+2+2
    1+1+1+1+2
    1+1+1+1+1+1
"""
    # exactly match

    if n > 0 and m > 0:
        if m == n:
            yield str(m)
        for p in yield_partitions(n - m, m):
            yield p + '+' + str(m)
        yield from yield_partitions(n, m - 1)


# fib generator
def fib_generator():
    """
    A generator that yields the Fibonacci sequence indefinitely.
    (The Fibonacci sequence starts with 0 and 1, and each subsequent number
    is the sum of the previous two.)
    >>> fib = fib_generator()
    >>> next(fib)
    0
    >>> next(fib)
    1
    >>> next(fib)
    1
    >>> next(fib)
    2
    >>> list(next(fib) for i in range(0,10)) # list the next 10 fibonacci numbers
    [3, 5, 8, 13, 21, 34, 55, 89, 144, 233]
    """
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b


# iterator practice
def add_to_each(p, edit):
    """
    Given a list, p, of 3-element tuples: [(x1, y1, z1), (x2, y2, z2), ...]
    And an edit tuple (also 3 elements) = (a, b, c),
    return a map object where
    a is added to each x-value,
    b to each y-value, and
    c to each z-value.
    >>> list(add_to_each([(0, 0, 0), (1, 1, 1)], (10, 10, 10)))
    [(10, 10, 10), (11, 11, 11)]
    >>> list(add_to_each([(1, 2, 3), (1, 1, 1)], (10, 20, 30)))
    [(11, 22, 33), (11, 21, 31)]
    """
    return map(lambda x: (x[0] + edit[0], x[1] + edit[1], x[2] + edit[2]), p)


# tree practice
# 2023 MT2 Q4(a)
from Trees import *


def exclude(t, x):
    """
    Return a Tree with the non-root nodes of t whose labels are not equal to x.

    >>> t = tree(1, [tree(2, [tree(2), tree(3)]), tree(4, [tree(1)])])
    >>> exclude(t, 2)
    tree(1, [tree(3), tree(4, [tree(1)])])

    >>> t
    # t is not changed
    tree(1, [tree(2, [tree(2), tree(3)]), tree(4, [tree(1)])])

    >>> exclude(t, 1) # The root node cannot be excluded
    tree(1, [tree(2, [tree(2), tree(3)]), tree(4)])
    """
    filtered_branches = map(lambda y: exclude(y, x), t.branches)

    bs = []
    for b in filtered_branches:
        if label(b) == x:
            bs.extend(branches(b))
        else:
            bs.append(b)
    return tree(t.label, bs)
