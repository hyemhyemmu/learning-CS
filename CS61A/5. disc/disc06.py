# Q1
def gen_fib():
    """Evaluates to the smallest number larger than 2024"""
    n, add = 0, 1
    while True:
        yield n
        n, add = n + add, n


next(filter(lambda n: n > 2024, gen_fib()))


# Q2
def differences(t):
    """Yield the differences between adjacent values from iterator t.

    >>> list(differences(iter([5, 2, -100, 103])))
    [-3, -102, 203]
    >>> next(differences(iter([39, 100])))
    61
    """
    previous = next(t)
    for x in t:
        yield x - previous
        previous = x


# Q3: Partitions
def partition_gen(n, m):
    """Yield the partitions of n using parts up to size m.

    >>> for partition in sorted(partition_gen(6, 4)):
    ...     print(partition)
    1 + 1 + 1 + 1 + 1 + 1
    1 + 1 + 1 + 1 + 2
    1 + 1 + 1 + 3
    1 + 1 + 2 + 2
    1 + 1 + 4
    1 + 2 + 3
    2 + 2 + 2
    2 + 4
    3 + 3
    """
    assert n > 0 and m > 0
    if n == m:
        yield str(n)
    if n - m > 0:
        # use m
        for parts in partition_gen(n - m, m):
            yield str(parts) + ' + ' + str(m)
    if m > 1:
        # doesn't use m
        yield from partition_gen(n, m - 1)
