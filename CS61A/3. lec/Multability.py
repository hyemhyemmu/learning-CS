# Function for withdrawing money
def account(balance):
    # mutable list
    b = [balance]

    def withdraw(amount):
        if b[0] < amount:
            return "Sorry, you don't have enough money"
        b[0] = b[0] - amount
        return b

    return withdraw


# building list using append
def sums(n, m):
    """Return lists that sum to n containing positive numbers up to m that
    have no adjacent repeats, for n > 0 and m > 0.
    >>> sums(5, 1)
    []
    >>> sums(5, 2)
    [[2, 1, 2]]
    >>> sums(5, 3)
    [[1, 3, 1], [2, 1, 2], [2, 3], [3, 2]]
    >>> sums(5, 5)
    [[1, 3, 1], [1, 4], [2, 1, 2], [2, 3], [3, 2], [4, 1], [5]]
    >>> sums(6, 3)
    [[1, 2, 1, 2], [1, 2, 3], [1, 3, 2], [2, 1, 2, 1], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
    """
    result = []
    # first number
    for k in range(1, m + 1):
        # rest
        if n - k > 0:
            for rest in sums(n - k, m):
                # no repetition
                if rest[0] != k:
                    result.append([k] + rest)
    if n <= m:
        result.append([n])
    return result


# make path (hard! - lec slide p7)
from Trees import *


def make_path(t, p):
    "Return a tree like t also containing path p."
    assert p[0] == label(t), 'Impossible'
    # single elements -> recursion finished
    if len(p) == 1:
        return t
    new_branches = []
    # 遍历树找下一个节点 -> 找到了：继续往下遍历直到完成整条路径 + 其他的节点所代表的路径全部放入branches
    #                -> 没找到：先把枝干全部添加到branches中，然后直接新建branch
    found_p = False
    for b in branches(t):
        if label(b) == p[1]:
            new_branches.append(make_path(b, p[1:]))
            found_p = True
        else:
            new_branches.append(b)

    if not found_p:
        new_branches.append(make_path(tree(p[1]), p[1:]))

    return tree(label(t),new_branches)
