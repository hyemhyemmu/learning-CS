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
    >>>list_partitions(6,4)
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
    >>>partitions(6,4)
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
    >>>yield_partitions(6,4)
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
